///////////////////////////////////////////////////////////////////////////////
////                             lcd.c                                     ////
////                 driver for common lcd modules                         ////
////                                                                       ////
////  lcd_init()   must be called before any other function.               //// 
////                                                                       ////
////  lcd_putc(c)  will display c on the next position of the lcd.         ////
////                 \a  set cursor position to upper left                 ////
////                 \f  clear display, set cursor to upper left           ////
////                 \n  go to start of second line                        ////
////                 \b  move back one position                            ////
////              if lcd_extended_newline is defined, the \n character     ////
////              will erase all remanining characters on the current      ////
////              line, and move the cursor to the beginning of the next   ////
////              line.                                                    ////
////              if lcd_extended_newline is defined, the \r character     ////
////              will move the cursor to the start of the current         ////
////              line.                                                    ////
////                                                                       ////
////  lcd_gotoxy(x,y) set write position on lcd (upper left is 1,1)        ////
////                                                                       ////
////  lcd_getc(x,y)   returns character at position x,y on lcd             ////
////                                                                       ////
////  lcd_cursor_on(int1 on)   turn the cursor on (on=true) or off         ////
////              (on=false).                                              ////
////                                                                       ////
////  lcd_set_cgram_char(w, *p)   write a custom character to the cgram.   ////
////                                                                       ////
////                                                                       ////
////  configuration                                                        ////
////  the lcd can be configured in one of two ways: a.) port access or     ////
////  b.) pin access.  port access requires the entire 7 bit interface     //// 
////  connected to one gpio port, and the data bits (d4:d7 of the lcd)     ////
////  connected to sequential pins on the gpio.  pin access                ////
////  has no requirements, all 7 bits of the control interface can         ////
////  can be connected to any gpio using several ports.                    ////
////                                                                       ////
////  to use port access, #define lcd_data_port to the sfr location of     ////
////  of the gpio port that holds the interface, -and- edit lcd_pin_map    ////
////  of this file to configure the pin order.  if you are using a         ////
////  baseline pic (pcb), then lcd_output_map and lcd_input_map also must  ////
////  be defined.                                                          ////
////                                                                       ////
////  example of port access:                                              ////
////     #define lcd_data_port getenv("sfr:portd")                         ////
////                                                                       ////
////  to use pin access, the following pins must be defined:               ////
////     lcd_enable_pin                                                    ////
////     lcd_rs_pin                                                        ////
////     lcd_rw_pin                                                        ////
////     l_d4_p                                                         ////
////     l_d5_p                                                         ////
////     l_d6_p                                                         ////
////     l_d7_p                                                         ////
////                                                                       ////
////  example of pin access:                                               ////
////     #define lcd_enable_pin  pin_e0                                    ////
////     #define lcd_rs_pin      pin_e1                                    ////
////     #define lcd_rw_pin      pin_e2                                    ////
////     #define l_d4_p       pin_d4                                    ////
////     #define l_d5_p       pin_d5                                    ////
////     #define l_d6_p       pin_d6                                    ////
////     #define l_d7_p       pin_d7                                    ////
////                                                                       ////
///////////////////////////////////////////////////////////////////////////////
////        (c) copyright 1996,2010 custom computer services           ////
//// this source code may only be used by licensed users of the ccs c  ////
//// compiler.  this source code may only be distributed to other      ////
//// licensed users of the ccs c compiler.  no other use, reproduction ////
//// or distribution is permitted without written permission.          ////
//// derivative programs created using this software in object code    ////
//// form are not restricted in any way.                               ////
/*
#define lcd_enable_pin  pin_e0
#define lcd_rs_pin      pin_e1
#define lcd_rw_pin      pin_e2
#define l_d4_p       pin_d4
#define l_d5_p       pin_d5
#define l_d6_p       pin_d6
#define l_d7_p       pin_d7
*/


#ifndef __lcd_c__
#define __lcd_c__
#include <!/! ldn.h>
#ifndef l_en
#define l_en dk_bit(PORTD,4)
#define l_en_d dk_bit(DDRD,4)
#define l_rs dk_bit(PORTD,0)
#define l_rs_d dk_bit(DDRD,0)

#define l_d4 dk_bit(PORTB,6)
#define l_d4_d dk_bit(DDRB,6)
#define l_d4_p dk_bit(PINB,6)
#define l_d5 dk_bit(PORTB,7)
#define l_d5_d dk_bit(DDRB,7)
#define l_d5_p dk_bit(PINB,7)
#define l_d6 dk_bit(PORTD,5)
#define l_d6_d dk_bit(DDRD,5)
#define l_d6_p dk_bit(PIND,5)
#define l_d7 dk_bit(PORTD,6)
#define l_d7_d dk_bit(DDRD,6)
#define l_d7_p dk_bit(PIND,7)
#endif
#define CGRAM 0x40
u8 busy=0;
u8 busy2=0;
// define the pinout.
// only required if port access is being used.
typedef struct
{                            // this structure is overlayed
	int1 enable;           // on to an i/o port to gain
	int1 rs;               // access to the lcd pins.
	int1 rw;               // the bits are allocated from
	int1 unused;           // low order up.  enable will
	unsigned int     data : 4;         // be lsb pin of that port.
	#if defined(__pcd__)       // the port used will be lcd_data_port.
	unsigned int    reserved: 8;
	#endif
} lcd_pin_map;

// this is to improve compatability with previous lcd drivers that accepted
// a define labeled 'use_portb_lcd' that configured the lcd onto port b.
#if ((defined(use_portb_lcd)) && (use_portb_lcd==true))
#define lcd_data_port getenv("sfr:portb")
#endif

#if defined(__pcb__)
// these definitions only need to be modified for baseline pics.
// all other pics use lcd_pin_map or individual lcd_xxx pin definitions.
/*                                    en, rs,   rw,   unused,  data  */
const lcd_pin_map lcd_output_map =  {0,  0,    0,    0,       0};
const lcd_pin_map lcd_input_map =   {0,  0,    0,    0,       0xf};
#endif

////////////////////// end configuration ///////////////////////////////////

// #ifndef lcd_enable_pin
// #define l_en(x) lcdlat.enable=x
// #define lcd_enable_tris()   lcdtris.enable=0
// #else
// #define l_en(x) output_bit(lcd_enable_pin, x)
// #define lcd_enable_tris()  output_drive(lcd_enable_pin)
// #endif

// #ifndef lcd_rs_pin
// #define l_rs(x) lcdlat.rs=x
// #define lcd_rs_tris()   lcdtris.rs=0
// #else
// #define l_rs(x) output_bit(lcd_rs_pin, x)
// #define lcd_rs_tris()  output_drive(lcd_rs_pin)
// #endif

// #ifndef lcd_rw_pin
// #define l_rw(x) lcdlat.rw=x
// #define lcd_rw_tris()   lcdtris.rw=0
// #else
// #define l_rw(x) output_bit(lcd_rw_pin, x)
// #define lcd_rw_tris()  output_drive(lcd_rw_pin)
// #endif

// original version of this library incorrectly labeled lcd_data0 as l_d4_p,
// lcd_data1 as l_d5_p, and so on.  this block of code makes the driver
// compatible with any code written for the original library
#if (defined(lcd_data0) && defined(lcd_data1) && defined(lcd_data2) && defined(lcd_data3) && !defined(l_d4_p) && !defined(l_d5_p) && !defined(l_d6_p) && !defined(l_d7_p))
#define  l_d4_p    lcd_data0
#define  l_d5_p    lcd_data1
#define  l_d6_p    lcd_data2
#define  l_d7_p    lcd_data3
#endif

#ifndef l_d4_p
#ifndef lcd_data_port
#if defined(__pcb__)
#define lcd_data_port      0x06     //portb
#define set_tris_lcd(x)   set_tris_b(x)
#else
#if defined(pin_d0)
#define lcd_data_port      getenv("sfr:portd")     //portd
#else
#define lcd_data_port      getenv("sfr:portb")     //portb
#endif
#endif
#endif

#if defined(__pcb__)
lcd_pin_map lcd, lcdlat;
#byte lcd = lcd_data_port
#byte lcdlat = lcd_data_port
#elif defined(__pcm__)
lcd_pin_map lcd, lcdlat, lcdtris;
#byte lcd = lcd_data_port
#byte lcdlat = lcd_data_port
#byte lcdtris = lcd_data_port+0x80
#elif defined(__pch__)
lcd_pin_map lcd, lcdlat, lcdtris;
#byte lcd = lcd_data_port
#byte lcdlat = lcd_data_port+9
#byte lcdtris = lcd_data_port+0x12
#elif defined(__pcd__)
lcd_pin_map lcd, lcdlat, lcdtris;
#word lcd = lcd_data_port
#word lcdlat = lcd_data_port+2
#word lcdtris = lcd_data_port-0x02
#endif
#endif   //l_d4_p not defined

#ifndef lcd_type
#define lcd_type 2           // 0=5x7, 1=5x10, 2=2 lines
#endif

#ifndef lcd_line_two
#define lcd_line_two 0x40    // lcd ram address for the second line
#endif

#ifndef lcd_line_length
#define lcd_line_length 20
#endif

u8 lcd_read_nibble(void);

void lcd_send_nibble(u8 n)
{
	l_d4=(n&0x1);
	n>>=1;
	l_d5=(n&0x1);
	n>>=1;
	l_d6=(n&0x1);
	n>>=1;
	l_d7=(n&0x1);
	_delay_us(1);
	l_en=1;
	delay_us(2);
	l_en=0;
}

void lcd_send_byte(u8 address, u8 n)
{
	l_rs=0;
	_delay_us(700);
	l_rs=address;
	_delay_us(1);
	l_en=0;
	lcd_send_nibble(n >> 4);
	lcd_send_nibble(n & 0xf);
}

#if defined(lcd_extended_newline)
unsigned int8 g_lcdx, g_lcdy;
#endif
void lcd_init(void)
{
	u8 i;
	u8 lcd_init_string[4] = {0x20 | (lcd_type << 2), 0xc, 1, 6};
	// these bytes need to be sent to the lcd
	// to start it up.
	l_en_d=ra;
	l_en=0;
	l_rs_d=ra;
	l_rs=0;
	l_d4_d=l_d5_d=l_d6_d=l_d7_d=ra;

	
	delay_ms(15);
	for(i=1;i<=3;++i)
	{
		lcd_send_nibble(3);
		delay_ms(5);
	}
	
	lcd_send_nibble(2);
	delay_ms(5);
	for(i=0;i<=3;++i)
	lcd_send_byte(0,lcd_init_string[i]);

	#if defined(lcd_extended_newline)
	g_lcdx = 0;
	g_lcdy = 0;
	#endif
}

void lcd_gotoxy(u8 x, u8 y)
{
	u8 address;
	
	if(y!=1)
	address=lcd_line_two;
	else
	address=0;
	
	address+=x-1;
	lcd_send_byte(0,0x80|address);

	#if defined(lcd_extended_newline)
	g_lcdx = x - 1;
	g_lcdy = y - 1;
	#endif
}
//======================================== 
void l_toi_xy(u8 x, u8 y)
{
	u8 address;
	
	if(y!=1)
	address=lcd_line_two;
	else
	address=0;
	
	address+=x-1;
	lcd_send_byte(0,0x80|address);

	#if defined(lcd_extended_newline)
	g_lcdx = x - 1;
	g_lcdy = y - 1;
	#endif
}

void lcd_putc(char c)
{
	switch (c)
	{
		case '\a'   :  lcd_gotoxy(1,1);     break;

		case '\f'   :  lcd_send_byte(0,1);
		delay_ms(2);
		#if defined(lcd_extended_newline)
		g_lcdx = 0;
		g_lcdy = 0;
		#endif
		break;

		#if defined(lcd_extended_newline)
		case '\r'   :  lcd_gotoxy(1, g_lcdy+1);   break;
		case '\n'   :
		while (g_lcdx++ < lcd_line_length)
		{
			lcd_send_byte(1, ' ');
		}
		lcd_gotoxy(1, g_lcdy+2);
		break;
		#else
		case '\n'   : lcd_gotoxy(1,2);        break;
		#endif
		
		case '\b'   : lcd_send_byte(0,0x10);  break;
		
		#if defined(lcd_extended_newline)
		default     :
		if (g_lcdx < lcd_line_length)
		{
			lcd_send_byte(1, c);
			g_lcdx++;
		}
		break;
		#else
		default     : lcd_send_byte(1,c);     break;
		#endif
	}
}

char lcd_getc(u8 x, u8 y)
{
	char value;

	lcd_gotoxy(x,y);
	while ( bit_test(lcd_read_byte(),7) ); // wait until busy flag is low
	l_rs=1;
	value = lcd_read_byte();
	l_rs=0;
	
	return(value);
}

// write a custom character to the ram
// which is 0-7 and specifies which character array we are modifying.
// ptr points to an array of 8 bytes, where each byte is the next row of
//    pixels.  only bits 0-4 are used.  the last row is the cursor row, and
//    usually you will want to leave this byte 0x00.
void lcd_set_cgram_char(u8 which, u8 *ptr)
{
	unsigned int i;

	which <<= 3;
	which &= 0x38;

	lcd_send_byte(0, 0x40 | which);  //set cgram address

	for(i=0; i<8; i++)
	{
		lcd_send_byte(1, *ptr++);
	}
	
	#if defined(lcd_extended_newline)
	lcd_gotoxy(g_lcdx+1, g_lcdy+1);  //set ddram address
	#endif
}

void lcd_cursor_on(int1 on)
{
	if (on)
	{
		lcd_send_byte(0,0x0f);           //turn lcd cursor on
	}
	else
	{
		lcd_send_byte(0,0x0c);           //turn lcd cursor off
	}
}
		
void l_in(char *p)
{
	while(*p)
	{
		lcd_putc(*p++);
	}
}

//========================================
void l_tuy_chinh1()
{
	uint8_t i,j;
	i=0;j=0;
	lcd_send_byte(0,CGRAM+0);
	for(i=1;i<=8;i++) 
	{
		for(j=8;j>i;j--)
		lcd_send_byte(1,0);
		for(j=i;j>0;j--)
		lcd_send_byte(1,0b00011111);
	} 
}
//========================================
void l_tuy_chinh()
{
	uint8_t i,j;
	i=0;j=0;
	lcd_send_byte(0,CGRAM+0);
	lcd_send_byte(1,0);
	for(j=0;j<7;j++)
	{
		for(i=0;i<6;i++)
		{
			lcd_send_byte(1,0);
		}
		lcd_send_byte(1,0b00011111);
	}
	for(j=0;j<6;j++)
	lcd_send_byte(1,0);
	lcd_send_byte(1,0b00011111);
	for(j=0;j<7;j++)
	lcd_send_byte(1,0);
}

void l_in_16 (uint8_t *string)
{
	uint8_t len = 0;  //16 Char on LCD

	while ((*string) && (len++ < 16))
	lcd_send_byte (1,*string++);
}



#define l_lenh(c) (lcd_send_byte(0,c))
#define l_dl(d) (lcd_send_byte(1,d))
#define l_xoa() l_lenh(0b00000001)
#define l_goc() l_lenh(0b00000010)

#endif

