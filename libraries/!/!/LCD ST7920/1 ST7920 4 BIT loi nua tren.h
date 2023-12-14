/*****************************************************************/
/*           LCD12864-ST7920-Demo with ATMega32                  */
/*  ************************************************************ */
/*  Mikrocontroller:  ATMEL AVR ATmega32, 8 MHz                  */
/*                                                               */
/*  Compiler:         GCC (GNU AVR C-Compiler)                   */
/*  Author:           Peter Rachow (DK7IH)                       */
/*  Letzte Aenderung: 2018-12-25                                 */
/*****************************************************************/

// O U T P U T for LCD 

//Connection LCD to uC:
//LCD-Data: PD0..PD7
//RS:       PC0
//RW:       PC1
//E:        PC2
//RST       PC3

//#define F_CPU 8000000

u8 lx,ly;
#define FONTHEIGHT 8
#define font_rong 5
#define font_cao 7
#define GLCD_WIDTH   128 //DEFINE 128 COLUNAS 
#define  ON   1
#define  OFF   0

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include "!/1 font5x7 hoa.h" 

#include <avr/pgmspace.h>


// LCD Functions
void LCD_Init(void);
void LCD_TextDisplayString(unsigned char line, char* string); // hien thi duoc 4 dong theo font cua LCD
void LCD_GraphicsDisplayString(unsigned char line, char* str); // hien thi duoc dong theo font 5x7
void LCD_EnableGraphics(void);
void LCD_DisableGraphics(void);
void LCD_FillScreenGraphics(const unsigned char* graphic);
void LCD_ClearGraphics(void);
void LCD_WriteData(unsigned char data);
void LCD_WriteCommand(unsigned char command);

u8 che_do_graphic=100;



	
//#ifndef d7
//#define d4 dk_bit(PORTB,5)
//#define d4_d dk_bit(DDRB,5)
//#define d4_i dk_bit(PINB,5)
//#define d5 dk_bit(PORTD,7)
//#define d5_d dk_bit(DDRD,7)
//#define d5_i dk_bit(PIND,7)
//#define d6 dk_bit(PORTD,6)
//#define d6_d dk_bit(DDRD,6)
//#define d6_i dk_bit(PIND,6)
//#define d7 dk_bit(PORTB,0)
//#define d7_d dk_bit(DDRB,0)
//#define d7_i dk_bit(PINB,0)
//
//#define rsl dk_bit(PORTB,1)
//#define rsl_d dk_bit(DDRB,1)
//#define rwl dk_bit(PORTB,2)
//#define rwl_d dk_bit(DDRB,2)
//#define enl dk_bit(PORTB,3)
//#define enl_d dk_bit(DDRB,3)
//#define rstl dk_bit(PORTB,3)
//#define rstl_d dk_bit(DDRB,3)
////RS:       PC0
////RW:       PC1
////E:        PC2
////RST       PC3
//
//#endif

u8 is_lcd_busy();

u8 doc_dl_lcd_4bit()
{
	u8 dl=0;
	//delay_us(1);
	dl|=d7_i;
	dl<<=1;
	dl|=d6_i;
	dl<<=1; 
	dl|=d5_i;
	dl<<=1;
	dl|=d4_i;
	return dl;
}
void dl_xuat_nhap(u8 kieu)
{
	d4_d=d5_d=d6_d=d7_d=kieu;
}


//Set RW line
// void set_rw(u8 status)  
// {
// 	rwl=status;
// 	delay_us(1);
// }

//Set RS line
void set_rs(u8 status) 
{
	rsl=status;
	delay_us(1);
}

//Set E line
void set_e(u8 status)  
{
	enl=status;
	delay_us(1);
}


//========================================
void ghi_byte_kep(u8 b0,u8 b1)
{
	lcd_write(1, b0);
	lcd_write(1, b1);
}
//Send one character to LCD (Normal size)
//
void lcd_putchar_ldn(u8 ch0, int inv)
{
	//u8 b,b2;
	//
	//u8 o_doc; // o doc chi co 2 gia tri, 0 hoac 1, 0 la nua tren man hinh, 1 la nua giuoi man hinh
	//int t1;
	//int odd = 0;
	//u8 v1, v2;
	//int o_ngan = 0;//lx/8;// / 2; // 0-1
	//int row = ly;// * font_cao;
	//u8 ch;
	////u8 x=lx
	//
	//if(row & 0x20)  //Enter lower part of screen => go to next page
	//{
		//row &= ~0x20;
		//o_ngan |= 8;
	//}
	//
	//if(o_ngan & 1) //Detect odd coloumn
	//{
		//odd = 1;
	//}
	//
	//for(t1 = 0; t1 < font_cao; t1++)
	//{
		////Set address
		//lcd_write(0, 0x80 + row + t1);
		//lcd_write(0, 0x80 + o_ngan);
		////Get old values of 2 GDRAM bytes
		//v1 = lcd_read(1);
		//v1 = lcd_read(1);
		//v2 = lcd_read(1);
//
		////Set address
		////lcd_write(0, 0x80 + row + t1);
		////lcd_write(0, 0x80 + o_ngan);
		//
		//b=b2=font[ch0 * FONTHEIGHT + t1];
		//b<<=2;
		//b>>=lx;
		//b|=v1;
		//
		////if(!inv)
		////{
			////ch = b;
		////}
		////else
		////{
			////ch = ~b;
		////}
		//
		////if(odd)
		////{
			//////Write data on RIGHT side of existing character
			////lcd_write(1, v1);
			////lcd_write(1, ch);
		////}
		////else
		////{
			//////Write data on LEFT side of existing character
			////lcd_write(1, ch);
			////lcd_write(1, v2);
		////}
		////b2<<=7;
		//
		////ch=b2;
		////ch<<=7;
		//lcd_write(0, 0x80 + row + t1);
		//lcd_write(0, 0x80 + o_ngan);
		//
		//if(lx >= 8-font_rong)
		//{
			//b2<<=(7+(8-font_rong)-lx);
			//b2|=v2;
		//}
		//else
		//{
			//b2=v2;
		//}
		//ghi_byte_kep(b,b2);
	//}
}
void lcd_putstring_ldn(u8 *s, int inv)
{
	u8 t1;

	for(t1 = 0; *(s); t1++)
	{
		lcd_putchar_ldn(*(s++), inv);
		delay_ms(1000);
		lx+=font_rong+1;
	}
}

void lcd_putchar(int row0, int col0, u8 ch0, int inv)
{
	//int t1;
	//int odd = 0;
	//u8 v1, v2;
	//int col = col0 / 2;
	//int row = row0 * FONTHEIGHT;
	//u8 ch;
		//
	//if(row & 0x20)  //Enter lower part of screen => go to next page
	//{
        //row &= ~0x20;
        //col |= 8;
    //}
        //
	//if(col0 & 1) //Detect odd coloumn
	//{
		//odd = 1;
	//}
		//
	//for(t1 = 0; t1 < FONTHEIGHT; t1++)
    //{
	    ////Set address
        //lcd_write(0, 0x80 + row + t1);
        //lcd_write(0, 0x80 + col);
             //
        ////Get old values of 2 GDRAM bytes	
	    //v1 = lcd_read(1);                
        //v1 = lcd_read(1);
        //v2 = lcd_read(1);
//
        ////Set address
        //lcd_write(0, 0x80 + row + t1);
        //lcd_write(0, 0x80 + col);
        //
        //if(!inv)
        //{
			//ch = font[ch0 * FONTHEIGHT + t1];
		//}
		//else	
        //{
			//ch = ~font[ch0 * FONTHEIGHT + t1];
		//}
		     //
        //if(odd)
        //{     
            ////Write data on RIGHT side of existing character
            //lcd_write(1, v1);
            //lcd_write(1, ch);
        //}
        //else    
        //{   
			////Write data on LEFT side of existing character
            //lcd_write(1, ch);
            //lcd_write(1, v2);
        //}
    //}    
}   

//Send one character to LCD (DOUBLE size and normal width)
//
void lcd_putchar2(int row0, int col0, u8 ch0, int inv)
{
	//int t1, t2;
	//int odd = 0;
	//u8 v1, v2;
	//int col = col0 >> 1;
	//int row = row0 * FONTHEIGHT;
	//u8 ch;
		//
	//if(row & 0x20)  //Enter lower part of screen => go to next page
	//{
        //row &= ~0x20;
        //col |= 8;
    //}
        //
	//if(col0 & 1) //Detect odd coloumn
	//{
		//odd = 1;
	//}
		//
	//for(t1 = 0; t1 < FONTHEIGHT; t1++)
    //{
		//if(!inv) //Calculate character position in array and xor invert number if needed
        //{
			//ch = (font[ch0 * FONTHEIGHT + t1]);
		//}
		//else	
        //{
			//ch = (~font[ch0 * FONTHEIGHT + t1]);
		//}
		//ch<<=2;
		//
		//for(t2 = 0; t2 < 2; t2++)
		//{
	        ////Set address
            //lcd_write(0, 0x80 + row + t1 * 2 + t2);
            //lcd_write(0, 0x80 + col);
             //
            ////Get old values of 2 GDRAM bytes	
	        //v1 = lcd_read(1);                
            //v1 = lcd_read(1);
            //v2 = lcd_read(1);
//
            ////Set address
            //lcd_write(0, 0x80 + row + t1 * 2 + t2);
            //lcd_write(0, 0x80 + col);
        		     //
            //if(odd)
            //{     
                ////Write data on RIGHT side of existing character
                //lcd_write(1, v1);
                //lcd_write(1, ch);
            //}
            //else    
            //{   
			    ////Write data on LEFT side of existing character
                //lcd_write(1, ch);
                //lcd_write(1, v2);
            //}    
        //}
    //}    
}   

//Send one character to LCD (DOUBLE size and DOUBLE width)
//
void lcd_putchar3_4b(int row0, int col0, u8 ch0, int inv)
{
	//int t1, t2;
	//u8 ch;
	////unsigned int i[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	//unsigned int i[FONTHEIGHT] = {0, 0, 0, 0, 0, 0, 0, 0};
	//int col = col0 >> 1;
	//int row = row0 * FONTHEIGHT;
	//
	//if(row & 0x20)  //Enter lower part of screen => go to next page
	//{
        //row &= ~0x20;
        //col |= 8;
    //}
        //
		//
	//for(t1 = 0; t1 < FONTHEIGHT; t1++)
    //{
		//if(!inv) //Calculate character position in array and xor invert number if needed
        //{
			//ch = (font[ch0 * FONTHEIGHT + t1]);
		//}
		//else	
        //{
			//ch = (~font[ch0 * FONTHEIGHT + t1]);
		//}
		//
		////Double 8 to 16 bits
	    //i[t1] = 0;
		//for(t2 = 7; t2 > -1; t2--)
		//{
			//if(ch & (1 << t2))
			//{
				//i[t1] += (1 << ((t2 << 1) + 1)) + (1 << (t2 << 1)); //Double bit pattern 2 by 1
			//}
		//}
	//}
	//
	//t2 = 0;
	//for(t1 = 0; t1 < FONTHEIGHT; t1++)
	//{
		//for(t2 = 0; t2 < 2; t2++)
		//{
	        ////Set address
			//LCD_WriteCommand(0x80 + row + t1 * 2 + t2);
			//LCD_WriteCommand(0x80 + col);
			//LCD_WriteData(((i[t1] >> 8) & 0xFF));
			//LCD_WriteData(i[t1] & 0xFF);
        //}    
    //}    
		
}	


void lcd_putchar3(int row0, int col0, u8 ch0, int inv)
{
	//int t1, t2;
	//u8 ch;
	////unsigned int i[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	//unsigned int i[FONTHEIGHT] = {0, 0, 0, 0, 0, 0, 0, 0};
	//int col = col0 >> 1;
	//int row = row0 * FONTHEIGHT;
	//
	//if(row & 0x20)  //Enter lower part of screen => go to next page
	//{
		//row &= ~0x20;
		//col |= 8;
	//}
	//
	//
	//for(t1 = 0; t1 < FONTHEIGHT; t1++)
	//{
		//if(!inv) //Calculate character position in array and xor invert number if needed
		//{
			//ch = (font[ch0 * FONTHEIGHT + t1]);
		//}
		//else
		//{
			//ch = (~font[ch0 * FONTHEIGHT + t1]);
		//}
		//
		////Double 8 to 16 bits
		//i[t1] = 0;
		//for(t2 = 7; t2 > -1; t2--)
		//{
			//if(ch & (1 << t2))
			//{
				//i[t1] += (1 << ((t2 << 1) + 1)) + (1 << (t2 << 1)); //Double bit pattern 2 by 1
			//}
		//}
	//}
	//
	//t2 = 0;
	//for(t1 = 0; t1 < FONTHEIGHT; t1++)
	//{
		//for(t2 = 0; t2 < 2; t2++)
		//{
			////Set address
			//lcd_write(0, 0x80 + row + t1 * 2 + t2);
			//lcd_write(0, 0x80 + col);
			//
			//lcd_write(1, ((i[t1] >> 8) & 0xFF));
			//lcd_write(1, i[t1] & 0xFF);
			////lcd_putnumber(t1, 0, i[t1] , -1, 0, 0);
		//}
	//}
	
}


//Send string (\0 terminated) to LCD normal or double height
void lcd_putstring_a(int row, int col, u8 *s, int size, int inv)
{
    u8 t1;

    for(t1 = col; *(s); t1++)
	{
		if(!size)
		{
            lcd_putchar(row, t1, *(s++), inv);
        }
        else    
        {
            lcd_putchar2(row, t1, *(s++), inv);
        }
	}	
}

//String in DOUBLE height and DOUBLE width
void lcd_putstring_b(int row, int col, u8 *s, int inv)
{
    u8 t1;

    for(t1 = col; *(s); t1++)
	{
	    lcd_putchar3(row, t1 * 2, *(s++), inv);
	}	
}
//= 
void lcd_putstring_b_4b(int row, int col, u8 *s, int inv)
{
	if (che_do_graphic!=1)
	{
		LCD_EnableGraphics(); // neu muon ghi chu tu font ngoai hoac hinh anh phai chuyen qua che do Graphic
		che_do_graphic=1;
	}
	u8 t1;

	for(t1 = col; *(s); t1++)
	{
		lcd_putchar3_4b(row, t1 * 2, *(s++), inv);
	}
}
//Clear LCD
void lcd_cls(void)
{
	int x, y;
    for(x = 0; x < 16; x++)
    {
		for(y = 0; y < 64; y++)
		{
			//Set address
            lcd_write(0, 0x80 + y);
            lcd_write(0, 0x80 + x);
             
            //Write data
            lcd_write(1, 0);
            lcd_write(1, 0);
        }
    }    
}

//Convert a number to a string and print it
//col, row: Coordinates, Num: int or long to be displayed
//dec: Set position of decimal separator
//
//inv: Set to 1 if inverted charactor is required
void lcd_putnumber(int col, int row, long num, int dec, int lsize, int inv)
{
    u8 *s = malloc(16);
	if(s != NULL)
	{
	    int2asc(num, dec, s, 16);
	    lcd_putstring_a(col, row, s, lsize, inv);
	    free(s);
	}	
	else
	{
		lcd_putstring_a(col, row, "Error", 0, 0);
	}	
}
//////////////////////
// STRING FUNCTIONS //
//////////////////////
//INT 2 ASC
int int2asc(long num, int dec, u8 *buf, int buflen)
{
    int i, c, xp = 0, neg = 0;
    long n, dd = 1E09;

    if(!num)
	{
	    *buf++ = '0';
		*buf = 0;
		return 1;
	}	
		
    if(num < 0)
    {
     	neg = 1;
	    n = num * -1;
    }
    else
    {
	    n = num;
    }

    //Fill buffer with \0
    for(i = 0; i < 12; i++)
    {
	    *(buf + i) = 0;
    }

    c = 9; //Max. number of displayable digits
    while(dd)
    {
	    i = n / dd;
	    n = n - i * dd;
	
	    *(buf + 9 - c + xp) = i + 48;
	    dd /= 10;
	    if(c == dec && dec)
	    {
	        *(buf + 9 - c + ++xp) = '.';
	    }
	    c--;
    }

    //Search for 1st char different from '0'
    i = 0;
    while(*(buf + i) == 48)
    {
	    *(buf + i++) = 32;
    }

    //Add minus-sign if neccessary
    if(neg)
    {
	    *(buf + --i) = '-';
    }

    //Eleminate leading spaces
    c = 0;
    while(*(buf + i))
    {
	    *(buf + c++) = *(buf + i++);
    }
    *(buf + c) = 0;
	
	return c;
}


// int main(void)
//{
    //// Set ports for LCD output and input data
    //DDRC = 0x0F; //LCD RS, RW, E and RST at PC0:PC3
	//DDRD = 0xFF; //LCD data on PD0:PD7
   	                 		//
	////Display init
	//_delay_ms(100);
    //lcd_init();
	//_delay_ms(100);
	//
    //lcd_cls();
        //
    //lcd_putstring_a(0, 0, "LCD 12864 ST7920", 0, 0);
    //lcd_putstring_a(1, 0, "   DK7IH 2018   ", 0, 1);
    //lcd_putstring_a(2, 0, "Graphical Fonts:", 0, 0);
    //lcd_putstring_a(3, 0, "8x8px.", 0, 0);
    //lcd_putnumber(4, 0, 1234, 1, 0, 0);    
       //
	//lcd_putstring_a(4, 0, "16x8px.", 1, 0);
	//
	//lcd_putstring_b(6, 0, "16x16px.", 0);
			    //
    //for(;;) 
	//{
    //
    //
	//}
	//return 0;
//}

u8 lcd_read_4_bit(u8 lcdmode)
{
	u8 h,l;
	dl_xuat_nhap(vao); // 
	rwl=1;       //Read operation
	set_rs(lcdmode);   //Get value 0: for busy flag, 1 for other data
	set_e(1);          //Read data
	delay_us(1);
	h = doc_dl_lcd_4bit();
	set_e(0);
	delay_us(1);
	set_e(1);          //Read data
	delay_us(1);
	l = doc_dl_lcd_4bit();
	set_e(0);
	return ((h<<4) | l);
}
void LCD_Write_Byte_4_bit(u8 command)
{
	enl = 1;
	delay_us(12);
	// Move higher nibble first
	d4 = (command & (1 << 4)) >> 4;
	d5 = (command & (1 << 5)) >> 5;
	d6 = (command & (1 << 6)) >> 6;
	d7 = (command & (1 << 7)) >> 7;
	delay_us(111); // 7-10
	enl = 0;

	enl = 1;
	delay_us(12);
	// Then move the lower nibble
	d4 = (command & (1 << 0)) >> 0;
	d5 = (command & (1 << 1)) >> 1;
	d6 = (command & (1 << 2)) >> 2;
	d7 = (command & (1 << 3)) >> 3;
	delay_us(111);
	enl = 0;

	delay_us(126);					// Please increase this delay if the screen is not showing things correctly.
}

void LCD_WriteData(unsigned char data) //write data
{
	rsl=1;
	dl_xuat_nhap(ra);
	rwl=0;	     //Write operation
	LCD_Write_Byte_4_bit(data);
}

void LCD_WriteCommand(unsigned char command) //write command
{
	rsl=0;
	dl_xuat_nhap(ra);
	rwl=0;	     //Write operation
	LCD_Write_Byte_4_bit(command);
}

void LCD_ClearGraphics(void)
{
	// This function performs similar to the LCD_FillScreenGraphics but
	// only zeros are sent into the screen instead of data from an array.
	unsigned char x, y;
	for(y = 0; y < 64; y++)
	{
		if(y < 32)
		{
			LCD_WriteCommand(0x80 | y);
			LCD_WriteCommand(0x80);
		}
		else
		{
			LCD_WriteCommand(0x80 | (y-32));
			LCD_WriteCommand(0x88);
		}
		for(x = 0; x < 8; x++)
		{
			LCD_WriteData(0x00);
			LCD_WriteData(0x00);
		}
	}
}

void xoa_lcd_4_bit(void)
{
	if (che_do_graphic!=1)
	{
		LCD_EnableGraphics(); // neu muon ghi chu tu font ngoai hoac hinh anh phai chuyen qua che do Graphic
		che_do_graphic=1;
	}
	int x, y;
	for(x = 0; x < 16; x++)
	{
		for(y = 0; y < 64; y++)
		{
			//Set address
			LCD_WriteCommand(0x80 + y);
			LCD_WriteCommand(0x80 + x);
			
			//Write data
			LCD_WriteData(0);
			LCD_WriteData(0);
		}
	}
}



void LCD_TextDisplayString(unsigned char line, char* string)
{
	if (che_do_graphic!=0)
	{
		LCD_DisableGraphics(); // muon ghi text thi phai chuyen qua che do ghi text 
		che_do_graphic=0;
	}
	unsigned char addr,i;
	if(line==1)
	addr=0x80; //The first line address
	else if(line==2)
	addr=0x90; //The second line address
	else if(line==3)
	addr=0x88;   //The third line address
	else if(line==4)
	addr=0x98;    //The fourth line address

	LCD_WriteCommand(addr);

	for(i=0;i<16;i++)
	LCD_WriteData(*string++);
}

void LCD_EnableGraphics(void)
{
	LCD_WriteCommand(0x20);
	delay_ms(1);
	LCD_WriteCommand(0x24);			// Switch to extended instruction mode.
	delay_ms(1);
	LCD_WriteCommand(0x26);			// Enable graphics mode.
	delay_ms(1);
}

void LCD_DisableGraphics(void)
{
	LCD_WriteCommand(0x20);			// Graphics and extended instruction mode turned off.
	delay_ms(1);
}

void LCD_FillScreenGraphics(const unsigned char* graphic)
{
	unsigned char x, y;
	for(y = 0; y < 64; y++)
	{
		if(y < 32)
		{
			for(x = 0; x < 8; x++)							// Draws top half of the screen.
			{												// In extended instruction mode, vertical and horizontal coordinates must be specified before sending data in.
				LCD_WriteCommand(0x80 | y);					// Vertical coordinate of the screen is specified first. (0-31)
				LCD_WriteCommand(0x80 | x);					// Then horizontal coordinate of the screen is specified. (0-8)
				LCD_WriteData(graphic[2*x + 16*y]);			// Data to the upper byte is sent to the coordinate.
				LCD_WriteData(graphic[2*x+1 + 16*y]);		// Data to the lower byte is sent to the coordinate.
			}
		}
		else
		{
			for(x = 0; x < 8; x++)							// Draws bottom half of the screen.
			{												// Actions performed as same as the upper half screen.
				LCD_WriteCommand(0x80 | (y-32));			// Vertical coordinate must be scaled back to 0-31 as it is dealing with another half of the screen.
				LCD_WriteCommand(0x88 | x);
				LCD_WriteData(graphic[2*x + 16*y]);
				LCD_WriteData(graphic[2*x+1 + 16*y]);
			}
		}
		
	}
}

void LCD_GraphicsDisplayString(unsigned char line, char* str)
{
	//if (che_do_graphic!=1)
	//{
		//LCD_EnableGraphics(); // neu muon ghi chu tu font ngoai hoac hinh anh phai chuyen qua che do Graphic
		//che_do_graphic=1;
	//}
	//
	//// Output text to the LCD in graphics mode using a 5x7 font
	//// Each char occupies 6 cols, 8 lines, including of space to next char
	//unsigned char row;
	//unsigned char colInd;
	//unsigned char shouldContinue = 1;
	//unsigned char count = 0;
//
	//while(*str && shouldContinue)
	//{
		//unsigned char letterA = *str++;
		//if (letterA == 0)
		//{
			//letterA = 32;
			//shouldContinue = 0;
		//}
//
		//// if string length is odd, last letter does not come in pair, append space
		//unsigned char letterB = *str++;
		//if (letterB == 0)
		//{
			//letterB = 32; // odd number of characters in a string, replace NULL with space
			//shouldContinue = 0;
		//}
//
		//unsigned char indA = letterA < 0x52 ? letterA - 0x20 : letterA - 0x52;
		//unsigned char indB = letterB < 0x52 ? letterB - 0x20 : letterB - 0x52;
		//unsigned char colListA[5];
		//unsigned char colListB[5];
		//
		//if(letterA < 0x52){
			//colListA[4] = Alpha1[(indA*5)];
			//colListA[3] = Alpha1[(indA*5)+1];
			//colListA[2] = Alpha1[(indA*5)+2];
			//colListA[1] = Alpha1[(indA*5)+3];
			//colListA[0] = Alpha1[(indA*5)+4];
		//}
		//else
		//{
			//colListA[4] = Alpha2[(indA*5)];
			//colListA[3] = Alpha2[(indA*5)+1];
			//colListA[2] = Alpha2[(indA*5)+2];
			//colListA[1] = Alpha2[(indA*5)+3];
			//colListA[0] = Alpha2[(indA*5)+4];
		//}
		//
		//if(letterB < 0x52){
			//colListB[4] = Alpha1[(indB*5)];
			//colListB[3] = Alpha1[(indB*5)+1];
			//colListB[2] = Alpha1[(indB*5)+2];
			//colListB[1] = Alpha1[(indB*5)+3];
			//colListB[0] = Alpha1[(indB*5)+4];
		//}
		//else
		//{
			//colListB[4] = Alpha2[(indB*5)];
			//colListB[3] = Alpha2[(indB*5)+1];
			//colListB[2] = Alpha2[(indB*5)+2];
			//colListB[1] = Alpha2[(indB*5)+3];
			//colListB[0] = Alpha2[(indB*5)+4];
		//}
//
		//for (row=0;row<8;row++)
		//{
			//if (line < 4)	// first half
			//{
				//LCD_WriteCommand(0x80 | (line * 8 + row));
				//LCD_WriteCommand(0x80 | count);
			//}
			//else
			//{
				//LCD_WriteCommand(0x80 | ( (line-4) * 8 + row));
				//LCD_WriteCommand(0x88 | count);
			//}
			//
			//unsigned char dataA = 0x00;
			//for (colInd=0;colInd<5;colInd++)
			//{
				//if (colListA[colInd] & (1 << row))
				//{
					//dataA = dataA | (1 << (colInd+3));
				//}
			//}
//
			//unsigned char dataB = 0x00;
			//for (colInd=0;colInd<5;colInd++)
			//{
				//if (colListB[colInd] & (1 << row))
				//{
					//dataB = dataB | (1 << (colInd+3));
				//}
			//}
			//
			//LCD_WriteData(dataA);
			//LCD_WriteData(dataB);
		//}
//
		//count++;
	//}
}
#define  YVAL 64 // DEFINE 64 LINHAS
#define  XVAL 8 // DEFINE COLUNAS 8X16=128 COLUNAS
//typedef union
//{
	//u16 word;
	//u8 nbyte[2];
//} Dots;
//
//typedef struct
//{
	//Dots pix[YVAL][XVAL];   // Max dimensions for display (x,y) = (128,32)
//} GD_RAM;             //  (0,0) corresponds to upper lefthand corner.
//
//GD_RAM gdram;


// typedef struct
// {
// 	u8 refresh;
// 	Dots pix[YVAL][XVAL];   // Max dimensions for display (x,y) = (128,32)
// } GD_RAM;             //  (0,0) corresponds to upper lefthand corner.
// 
// GD_RAM gdram;
u8 refresh_lcd;

u8 gx,gy;

void glcd_fillScreen (u8 color)//GRAVA 1 OU 0 EM TODOS OS PIXEL
{
	//u8 v, h;
	//u16 d;
	//d = (color == ON ? 0xFFFF : 0x0000);
	//// d = (color == ON ? 0x0000 : 0xFFFF );
	//for (v=0; v < YVAL; v++)//32
	//{
		//for (h=0; h < XVAL; h++)//16
		//{
			//gdram.pix[v][h].word = d;
		//}
	//}
	//refresh_lcd = 1;
}

void glcd_update ()//ATUALIZA LCD
{
	//int8 v, h;
	//if (refresh_lcd==1)//verifica se foi atualizado
	//{
		//for (v=0; v <YVAL; v++) //64 linhas
		//{
			//if(v<32)
			//{
				//LCD_WriteCommand( 0x80 | v);   // Set Vertical Address.
				//LCD_WriteCommand( 0x80);   // Set Horizontal Address.
			//}
			//else
			//{
				//LCD_WriteCommand( 0x80 | (v - 32));   // Set Vertical Address.
				//LCD_WriteCommand( 0x88);   // Set Horizontal Address.
			//}
			//for (h=0; h <XVAL; h++) //8x16=128 colunas
			//{
//// 				LCD_WriteData( gdram.pix[v][h].word>>8);   // Write High Byte.
//// 				LCD_WriteData( gdram.pix[v][h].word&0xff);   // Write Low Byte.
				//LCD_WriteData( gdram.pix[v][h].nbyte[1]);   // Write High Byte.
				//LCD_WriteData( gdram.pix[v][h].nbyte[0]);   // Write Low Byte.
			//}
		//}
		//refresh_lcd = 0;
	//}
}

//void glcd_pixel(u8 x, u8 y, bool color)
//{
	//u8 data;
	//bool side = GLCD_LEFT;  // Stores which chip to use on the LCD
	//if(x > 63)              // Check for first or second display area
	//{
		//x -= 64;
		//side = GLCD_RIGHT;
	//}
	//lcdrs=0;
	////output_low(GLCD_DI);                         // Set for instruction
	//x &= ~(1<<7);
	////bit_clear(x,7);                              // Clear the MSB. Part of an instruction code
	//x |= (1<<6);
	////bit_set(x,6);                                // Set bit 6. Also part of an instruction code
	//
	//glcd_writeByte(side, x);                     // Set the horizontal address
	//glcd_writeByte(side, (y/8 & 0xBF) | 0xB8);   // Set the vertical page address
	//lcdrs=1;
	////output_high(GLCD_DI);                        // Set for data
	//glcd_readByte(side);                         // Need two reads to get data
	//data = glcd_readByte(side);                  //  at new address
//
	//if(color == 1)
	//data |= (1<<y%8);
	////bit_set(data, y%8);        // Turn the pixel on
	//else
	//data &= ~(1<<y%8);                     // or
	////bit_clear(data, y%8);      // turn the pixel off
	//lcdrs=0;
	////output_low(GLCD_DI);          // Set for instruction
	//glcd_writeByte(side, x);      // Set the horizontal address
	//lcdrs=1;
	////output_high(GLCD_DI);         // Set for data
	//glcd_writeByte(side, data);   // Write the pixel data
//}
//              0     0        0
////========================================
//void glcd_pixel(u8 x, u8 y, bool color)
//{
	//u8 data;
	//bool side = GLCD_LEFT;  // Stores which chip to use on the LCD
	//if(x > 63)              // Check for first or second display area
	//{
		//x -= 64;
		//side = GLCD_RIGHT;
	//}
	//lcdrs=0;
	////output_low(GLCD_DI);                         // Set for instruction
	//x &= ~(1<<7);
	////bit_clear(x,7);                              // Clear the MSB. Part of an instruction code
	//x |= (1<<6);
	////bit_set(x,6);                                // Set bit 6. Also part of an instruction code
	//
	//glcd_writeByte(side, x);                     // Set the horizontal address
	//glcd_writeByte(side, (y/8 & 0xBF) | 0xB8);   // Set the vertical page address
	//lcdrs=1;
	////output_high(GLCD_DI);                        // Set for data
	//glcd_readByte(side);                         // Need two reads to get data
	//data = glcd_readByte(side);                  //  at new address
//
	//if(color == 1)
	//data |= (1<<y%8);
	////bit_set(data, y%8);        // Turn the pixel on
	//else
	//data &= ~(1<<y%8);                     // or
	////bit_clear(data, y%8);      // turn the pixel off
	//lcdrs=0;
	////output_low(GLCD_DI);          // Set for instruction
	//glcd_writeByte(side, x);      // Set the horizontal address
	//lcdrs=1;
	////output_high(GLCD_DI);         // Set for data
	//glcd_writeByte(side, data);   // Write the pixel data
//}

void glcd_pixel(int8 x, int8 y, u8 color)//GRAVA NOVO VALOR DOS PIXEL
{
	//int8 v, h, b;
	//v = y;
	//h = x/16;
	//b = 15 - (x%16);
	//
	//if (color == ON)
	//{
		////gdram.pix[v][h].word=bit_set (gdram.pix[v][h].word, b);
		//gdram.pix[v][h].word|=(1<<b);
		////bit_set()
	//}
	//
	//else
	//{
		////gdram.pix[v][h].word=bit_clear (gdram.pix[v][h].word, b);
		//gdram.pix[v][h].word&=~(1<<b); 
		////bit_clear
	//}
	//refresh_lcd = 1;
}


void glcd_ghi_du_lieu();
u8 glcd_vi_tri_mang;
u16 glcd_mang_dl[64];
//u8 
u16 dl_lcd_doc; // byte doc du lieu giup chi doc du lieu neu dia chi thay doi de tiet kiem thoi gian
u16 dl_lcd_ghi; // byte doc du lieu giup chi luu du lieu neu dia chi thay doi de tiet kiem thoi gian
u8 o_16bit_cu=200; // dia chi 
u8 dong_32_cu=200; // dia chi
u8 can_ghi=0; // bao can phai ghi du lieu o lan tiep theo
u8 phai_ghi=0;// bao phai ghi du lieu neu chua ghi
u8 o_16bit_ghi=200; // dia chi
u8 dong_32_ghi=200; // dia chi
void glcd_pixel_lcd(int8 x, int8 y, u8 color)// khong dung ram vi dieu khien
{
	int8 o_16bit, dong_32, b;
	dong_32 = y;
	o_16bit = x/16;
	b = 15 - (x%16);
	u8 v1,v2;
	u16 b16;
	
	//if (o_16bit_cu!=o_16bit||dong_32_cu!=dong_32)
	{
		//if(dong_32_cu!=200) // dia chi khac lan khoi dong dau tien
		//{
			////can_ghi++;
			////if (can_ghi==1)
			//{
				//o_16bit_ghi=o_16bit_cu;
				//dong_32_ghi=dong_32_cu;
				//dl_lcd_ghi=dl_lcd_doc; // lay du lieu de chuan bi ghi truoc khi doc du lieu moi
				////glcd_ghi_du_lieu();
			//}
		//}
		
		
		if(dong_32<32)
		{
			LCD_WriteCommand(0x80 | dong_32);   // Set Vertical Address.
			LCD_WriteCommand(0x88|o_16bit);   // Set Horizontal Address.
		}
		else
		{
			LCD_WriteCommand(0x80 | (dong_32 - 32));   // Set Vertical Address.
			LCD_WriteCommand(0x88|o_16bit);   // Set Horizontal Address.
		}
		lcd_read_4_bit(1);
		v1 = lcd_read_4_bit(1);
		v2 = lcd_read_4_bit(1);
		b16=v1;
		b16<<=8;
		b16|=v2;
		dl_lcd_doc=b16;
		o_16bit_cu=o_16bit;
		dong_32_cu=dong_32;
		
	}
	dl_lcd_doc|=(1<<b);
	
	//can_ghi=1;
	//o_16bit_ghi=o_16bit_cu;
	//dong_32_ghi=dong_32_cu;
	//dl_lcd_ghi=dl_lcd_doc;
	
	//v1 = 
	//if (can_ghi==1)
	{
		can_ghi=0;
		if (color == ON)
		{
			if(dong_32_ghi<32)
			{
				LCD_WriteCommand(0x80|dong_32);   // Set Vertical Address.
				LCD_WriteCommand(0x80|o_16bit);   // Set Horizontal Address.
			}
			else
			{
				LCD_WriteCommand(0x80|(dong_32 - 32));   // Set Vertical Address.
				LCD_WriteCommand(0x88|o_16bit);   // Set Horizontal Address.
			}
			LCD_WriteData(dl_lcd_doc>>8);   // Write High Byte.
			LCD_WriteData(dl_lcd_doc&0xff);   // Write Low Byte.
			//gdram.pix[v][h].word=bit_set (gdram.pix[v][h].word, b);
			//gdram.pix[v][h].word|=(1<<b);
			//bit_set()
		}
		
		else
		{
			//gdram.pix[v][h].word=bit_clear (gdram.pix[v][h].word, b);
			//gdram.pix[v][h].word&=~(1<<b);
			//bit_clear
		}
	}
	
	//refresh_lcd = 1;
}
void glcd_pixel_mang(int8 x, int8 y, u8 color)// khong dung ram vi dieu khien
{
	int8 o_16bit, dong_32, b;
	dong_32 = y;
	o_16bit = x/16;
	b = 15 - (x%16);
	u8 v1,v2;
	u16 b16;
	
	if (o_16bit_cu!=o_16bit||dong_32_cu!=dong_32)
	{
		//if(dong_32_cu!=200) // dia chi khac lan khoi dong dau tien
		//{
		////can_ghi++;
		////if (can_ghi==1)
		//{
		//o_16bit_ghi=o_16bit_cu;
		//dong_32_ghi=dong_32_cu;
		//dl_lcd_ghi=dl_lcd_doc; // lay du lieu de chuan bi ghi truoc khi doc du lieu moi
		////glcd_ghi_du_lieu();
		//}
		//}
		
		
		//if(dong_32<32)
		//{
			//LCD_WriteCommand(0x80 | dong_32);   // Set Vertical Address.
			//LCD_WriteCommand(0x80|o_16bit);   // Set Horizontal Address.
		//}
		//else
		//{
			//LCD_WriteCommand(0x80 | (dong_32 - 32));   // Set Vertical Address.
			//LCD_WriteCommand(0x88|o_16bit);   // Set Horizontal Address.
		//}
		//lcd_read_4_bit(1);
		//v1 = lcd_read_4_bit(1);
		//v2 = lcd_read_4_bit(1);
		//b16=v1;
		//b16<<=8;
		//b16|=v2;
		dl_lcd_doc=glcd_mang_dl[glcd_vi_tri_mang];
		glcd_vi_tri_mang++;
		o_16bit_cu=o_16bit;
		dong_32_cu=dong_32;
		
	}
	dl_lcd_doc|=(1<<b);
	glcd_mang_dl[glcd_vi_tri_mang-1]=dl_lcd_doc;
	
	//can_ghi=1;
	//o_16bit_ghi=o_16bit_cu;
	//dong_32_ghi=dong_32_cu;
	//dl_lcd_ghi=dl_lcd_doc;
	
	//v1 =
	//if (can_ghi==1)
	//{
		//can_ghi=0;
		//if (color == ON)
		//{
			//if(dong_32_ghi<32)
			//{
				//LCD_WriteCommand(0x80|dong_32);   // Set Vertical Address.
				//LCD_WriteCommand(0x80|o_16bit);   // Set Horizontal Address.
			//}
			//else
			//{
				//LCD_WriteCommand(0x80|(dong_32 - 32));   // Set Vertical Address.
				//LCD_WriteCommand(0x88|o_16bit);   // Set Horizontal Address.
			//}
			//LCD_WriteData(dl_lcd_doc>>8);   // Write High Byte.
			//LCD_WriteData(dl_lcd_doc&0xff);   // Write Low Byte.
			////gdram.pix[v][h].word=bit_set (gdram.pix[v][h].word, b);
			////gdram.pix[v][h].word|=(1<<b);
			////bit_set()
		//}
		//
		//else
		//{
			////gdram.pix[v][h].word=bit_clear (gdram.pix[v][h].word, b);
			////gdram.pix[v][h].word&=~(1<<b);
			////bit_clear
		//}
	//}
	
	//refresh_lcd = 1;
}
void glcd_mang_ghi(int8 x, int8 y, u8 color)// khong dung ram vi dieu khien
{
	int8 o_16bit, dong_32, b;
	dong_32 = y;
	o_16bit = x/16;
	b = 15 - (x%16);
	u8 v1,v2;
	u16 b16;
	
	if (o_16bit_cu!=o_16bit||dong_32_cu!=dong_32)
	{
		//if(dong_32_cu!=200) // dia chi khac lan khoi dong dau tien
		//{
		////can_ghi++;
		////if (can_ghi==1)
		//{
		//o_16bit_ghi=o_16bit_cu;
		//dong_32_ghi=dong_32_cu;
		//dl_lcd_ghi=dl_lcd_doc; // lay du lieu de chuan bi ghi truoc khi doc du lieu moi
		////glcd_ghi_du_lieu();
		//}
		//}
		
		
		//if(dong_32<32)
		//{
			//LCD_WriteCommand(0x80 | dong_32);   // Set Vertical Address.
			//LCD_WriteCommand(0x80|o_16bit);   // Set Horizontal Address.
		//}
		//else
		//{
			//LCD_WriteCommand(0x80 | (dong_32 - 32));   // Set Vertical Address.
			//LCD_WriteCommand(0x88|o_16bit);   // Set Horizontal Address.
		//}
		//lcd_read_4_bit(1);
		//v1 = lcd_read_4_bit(1);
		//v2 = lcd_read_4_bit(1);
		//b16=v1;
		//b16<<=8;
		//b16|=v2;
		dl_lcd_doc=glcd_mang_dl[glcd_vi_tri_mang];
		glcd_vi_tri_mang++;
		
		if (color == ON)
		{
			if(dong_32_ghi<32)
			{
				LCD_WriteCommand(0x80|dong_32);   // Set Vertical Address.
				LCD_WriteCommand(0x80|o_16bit);   // Set Horizontal Address.
			}
			else
			{
				LCD_WriteCommand(0x80|(dong_32 - 32));   // Set Vertical Address.
				LCD_WriteCommand(0x88|o_16bit);   // Set Horizontal Address.
			}
			LCD_WriteData(dl_lcd_doc>>8);   // Write High Byte.
			LCD_WriteData(dl_lcd_doc&0xff);   // Write Low Byte.
			//gdram.pix[v][h].word=bit_set (gdram.pix[v][h].word, b);
			//gdram.pix[v][h].word|=(1<<b);
			//bit_set()
		}
		
		o_16bit_cu=o_16bit;
		dong_32_cu=dong_32;
		
	}
	//dl_lcd_doc|=(1<<b);
	
	//can_ghi=1;
	//o_16bit_ghi=o_16bit_cu;
	//dong_32_ghi=dong_32_cu;
	//dl_lcd_ghi=dl_lcd_doc;
	
	//v1 =
	//if (can_ghi==1)
	//{
		//can_ghi=0;
		//if (color == ON)
		//{
			//if(dong_32_ghi<32)
			//{
				//LCD_WriteCommand(0x80|dong_32);   // Set Vertical Address.
				//LCD_WriteCommand(0x80|o_16bit);   // Set Horizontal Address.
			//}
			//else
			//{
				//LCD_WriteCommand(0x80|(dong_32 - 32));   // Set Vertical Address.
				//LCD_WriteCommand(0x88|o_16bit);   // Set Horizontal Address.
			//}
			//LCD_WriteData(dl_lcd_doc>>8);   // Write High Byte.
			//LCD_WriteData(dl_lcd_doc&0xff);   // Write Low Byte.
			////gdram.pix[v][h].word=bit_set (gdram.pix[v][h].word, b);
			////gdram.pix[v][h].word|=(1<<b);
			////bit_set()
		//}
		//
		//else
		//{
			////gdram.pix[v][h].word=bit_clear (gdram.pix[v][h].word, b);
			////gdram.pix[v][h].word&=~(1<<b);
			////bit_clear
		//}
	//}
	
	//refresh_lcd = 1;
}
void glcd_doc_mang_du_lieu(int8 x, int8 y)
{
	int8 o_16bit, dong_32, b;
	dong_32 = y;
	o_16bit = x/16;
	b = 15 - (x%16);
	u8 v1,v2;
	u16 b16;
	if (o_16bit_cu!=o_16bit||dong_32_cu!=dong_32)
	{
		//if(dong_32_cu!=200) // dia chi khac lan khoi dong dau tien
		//{
		////can_ghi++;
		////if (can_ghi==1)
		//{
		//o_16bit_ghi=o_16bit_cu;
		//dong_32_ghi=dong_32_cu;
		//dl_lcd_ghi=dl_lcd_doc; // lay du lieu de chuan bi ghi truoc khi doc du lieu moi
		////glcd_ghi_du_lieu();
		//}
		//}
		if(dong_32<32)
		{
			LCD_WriteCommand(0x80|dong_32);   // Set Vertical Address.
			LCD_WriteCommand(0x80|o_16bit);   // Set Horizontal Address.
		}
		else
		{
			LCD_WriteCommand(0x80|(dong_32 - 32));   // Set Vertical Address.
			LCD_WriteCommand(0x88|o_16bit);   // Set Horizontal Address.
		}
		lcd_read_4_bit(1);
		v1 = lcd_read_4_bit(1);
		v2 = lcd_read_4_bit(1);
		b16=v1;
		b16<<=8;
		b16|=v2;
		dl_lcd_doc=b16;
		o_16bit_cu=o_16bit;
		dong_32_cu=dong_32;
		glcd_mang_dl[glcd_vi_tri_mang]=b16;
		glcd_vi_tri_mang++;
	}
}

void glcd_ghi_du_lieu()
{
	can_ghi=0;
	//if (color == ON)
	{
		if(dong_32_ghi<32)
		{
			LCD_WriteCommand(0x80|dong_32_ghi);   // Set Vertical Address.
			LCD_WriteCommand(0x80|o_16bit_ghi);   // Set Horizontal Address.
		}
		else
		{
			LCD_WriteCommand(0x80|(dong_32_ghi - 32));   // Set Vertical Address.
			LCD_WriteCommand(0x88|o_16bit_ghi);   // Set Horizontal Address.
		}
		LCD_WriteData(dl_lcd_ghi>>8);   // Write High Byte.
		LCD_WriteData(dl_lcd_ghi&0xff);   // Write Low Byte.
		//gdram.pix[v][h].word=bit_set (gdram.pix[v][h].word, b);
		//gdram.pix[v][h].word|=(1<<b);
		//bit_set()
	}
}

void glcd_pixel_lcd_8_bit(int8 x, int8 y, u8 color)// khong dung ram vi dieu khien
{
	int8 v, h, b;
	v = y;
	h = x/16;
	b = 15 - (x%16);
	
	u8 v1,v2;
	u16 b16;
	
	if(v<32)
	{
		lcd_write(0,0x80 | v);   // Set Vertical Address.
		lcd_write(0, 0x80);   // Set Horizontal Address.
	}
	else
	{
		lcd_write(0, 0x80 | (v - 32));   // Set Vertical Address.
		lcd_write(0, 0x88);   // Set Horizontal Address.
	}
	
	//lcd_write(0, 0x80 + y);
	//lcd_write(0, 0x80 + x);
	
	//Write data
// 	lcd_write(1, 0);
// 	lcd_write(1, 0);
	
	v1 = lcd_read(1);
	v1 = lcd_read(1);
	v2 = lcd_read(1);
	if (color == ON)
	{
		b16=v1;
		b16<<=8;
		b16|=v2;
		b16|=(1<<b);
		
			if(v<32)
			{
				lcd_write(0,0x80 | v);   // Set Vertical Address.
				lcd_write(0, 0x80);   // Set Horizontal Address.
			}
			else
			{
				lcd_write(0, 0x80 | (v - 32));   // Set Vertical Address.
				lcd_write(0, 0x88);   // Set Horizontal Address.
			}
		lcd_write(1,b16>>8);   // Write High Byte.
		lcd_write(1,b16&0xff);   // Write Low Byte.
		//gdram.pix[v][h].word=bit_set (gdram.pix[v][h].word, b);
		//gdram.pix[v][h].word|=(1<<b);
		//bit_set()
	}
	
	else
	{
		//gdram.pix[v][h].word=bit_clear (gdram.pix[v][h].word, b);
		//gdram.pix[v][h].word&=~(1<<b);
		//bit_clear
	}
	refresh_lcd = 1;
}
#ifdef LARGE_LCD
void glcd_text57(u16 x, u16 y, char* textptr, u8 size, u8 color)
#else
void glcd_text57(u8 x, u8 y, char* textptr, u8 size, u8 color)
#endif
{
	if (che_do_graphic!=1)
	{
		LCD_EnableGraphics(); // neu muon ghi chu tu font ngoai hoac hinh anh phai chuyen qua che do Graphic
		che_do_graphic=1;
	}
	u8 j, k, l, m, i;                       // Loop counters
	u8 inv=~color;
	u8 pixelData[5];                     // Stores character data 
	//if(color==1)inv=0;
	//else inv=1;
	for(; *textptr != '\0'; ++textptr, ++x)// Loop through the passed string
	{
		//if(*textptr < 'S') // Checks if the letter is in the first font array
		//memcpy(pixelData, FONT[*textptr - ' '], 5);
		//else if(*textptr <= '~') // Check if the letter is in the second font array
		//memcpy(pixelData, FONT2[*textptr - 'S'], 5);
		//else
		//memcpy(pixelData, FONT[0], 5);   // Default to space
		//GLCD_WriteChar(*s);
		for(i = 0; i < 5; i++)
		{
			pixelData[i]=(pgm_read_byte(&font5x7_hoa[((*textptr-0x20) * 5) + i]));
		}
		


		// Handles newline and carriage returns
		//switch(*textptr)
		//{
			//case '\n':
			//y += 7*size + 1;
			//continue;
			//case '\r':
			//x = 0;
			//continue;
		//}

		if(x+5*size >= GLCD_WIDTH)          // Performs character wrapping
		{
			x = 0;                           // Set x at far left position
			y += 7*size + 1;                 // Set y at next position down
		}
		for(j=0; j<5; ++j, x+=size)         // Loop through character byte data
		{
			for(k=0; k < 7; ++k)             // Loop through the vertical pixels
			{
				
				//if(bit_test_8(pixelData[j], k))
				if(pixelData[j] & (1<<k)) // Check if the pixel should be set
				{
					for(l=0; l < size; ++l)    // These two loops change the
					{                          // character's size
						for(m=0; m < size; ++m)
						{
							glcd_pixel_lcd(x+m, y+k*size+l, color); // Draws the pixel
						}
					}
				}
				else
				{
					for(l=0; l < size; ++l)    // These two loops change the
					{                          // character's size
						for(m=0; m < size; ++m)
						{
							glcd_pixel_lcd(x+m, y+k*size+l, inv); // Draws the pixel
						}
					}
				}
			}
		}
	}
}






#ifdef LARGE_LCD
void glcd_text57(u16 x, u16 y, char* textptr, u8 size, u8 color)
#else
void glcd_text57_gram_ram(u8 x, u8 y, char* textptr, u8 size, u8 color)
#endif
{
	u8 x1,x2,x3;
	if (che_do_graphic!=1)
	{
		LCD_EnableGraphics(); // neu muon ghi chu tu font ngoai hoac hinh anh phai chuyen qua che do Graphic
		che_do_graphic=1;
	}
	u8 j, k, l, m, i;                       // Loop counters
	u8 inv=~color;
	u8 pixelData[5];                     // Stores character data
	//if(color==1)inv=0;
	//else inv=1;
	for(; *textptr != '\0'; ++textptr, ++x)// Loop through the passed string
	{
		for(i = 0; i < 5; i++)
		{
			pixelData[i]=(pgm_read_byte(&font5x7_hoa[((*textptr-0x20) * 5) + i]));
		}
		


		// Handles newline and carriage returns
		//switch(*textptr)
		//{
		//case '\n':
		//y += 7*size + 1;
		//continue;
		//case '\r':
		//x = 0;
		//continue;
		//}
		//
		//x=xx;
		//if(x+5*size >= GLCD_WIDTH)          // Performs character wrapping
		//{
		//x = 0;                           // Set x at far left position
		//y += 7*size + 1;                 // Set y at next position down
		//}
		//
		//glcd_vi_tri_mang=0;
		//for(j=0; j<5; ++j, x+=size)         // Loop through character byte data
		//{
		//for(k=0; k < 7; ++k)             // Loop through the vertical pixels
		//{
		//if(pixelData[j] & (1<<k)) // Check if the pixel should be set
		//{
		//for(l=0; l < size; ++l)    // These two loops change the
		//{                          // character's size
		//for(m=0; m < size; ++m)
		//{
		//glcd_doc_mang_du_lieu(x+m, y+k*size+l); // Draws the pixel
		//}
		//}
		//}
		//else
		//{
		//for(l=0; l < size; ++l)    // These two loops change the
		//{                          // character's size
		//for(m=0; m < size; ++m)
		//{
		//glcd_doc_mang_du_lieu(x+m, y+k*size+l); // Draws the pixel
		//}
		//}
		//}
		//}
		//}
		//
		//if(x+5*size >= GLCD_WIDTH)          // Performs character wrapping
		//{
		//x = 0;                           // Set x at far left position
		//y += 7*size + 1;                 // Set y at next position down
		//}
		//
		//glcd_vi_tri_mang=0;
		//for(j=0; j<5; ++j, x+=size)         // Loop through character byte data
		//{
		//for(k=0; k < 7; ++k)             // Loop through the vertical pixels
		//{
		//if(pixelData[j] & (1<<k)) // Check if the pixel should be set
		//{
		//for(l=0; l < size; ++l)    // These two loops change the
		//{                          // character's size
		//for(m=0; m < size; ++m)
		//{
		//glcd_pixel_mang(x+m, y+k*size+l, color); // Draws the pixel
		//}
		//}
		//}
		//else
		//{
		//for(l=0; l < size; ++l)    // These two loops change the
		//{                          // character's size
		//for(m=0; m < size; ++m)
		//{
		//glcd_pixel_mang(x+m, y+k*size+l, inv); // Draws the pixel
		//}
		//}
		//}
		//}
		//}
		//
		//
		//x;//=xx;
		if(x+5*size >= GLCD_WIDTH)          // Performs character wrapping
		{
			x = 0;                           // Set x at far left position
			y += 7*size + 1;                 // Set y at next position down
		}
		
		for(j=0; j<5; ++j, x+=size)         // Loop through character byte data
		{
			
			
			
			
			
			glcd_vi_tri_mang=0;
			for(k=0; k < 7; ++k)             // Loop through the vertical pixels
			{
				if(pixelData[j] & (1<<k)) // Check if the pixel should be set
				{
					for(l=0; l < size; ++l)    // These two loops change the
					{                          // character's size
						for(m=0; m < size; ++m)
						{
							glcd_doc_mang_du_lieu(x+m, y+k*size+l); // Draws the pixel
						}
					}
				}
				else
				{
					for(l=0; l < size; ++l)    // These two loops change the
					{                          // character's size
						for(m=0; m < size; ++m)
						{
							glcd_doc_mang_du_lieu(x+m, y+k*size+l); // Draws the pixel
						}
					}
				}
			}
			glcd_vi_tri_mang=0;
			for(k=0; k < 7; ++k)             // Loop through the vertical pixels
			{
				if(pixelData[j] & (1<<k)) // Check if the pixel should be set
				{
					for(l=0; l < size; ++l)    // These two loops change the
					{                          // character's size
						for(m=0; m < size; ++m)
						{
							glcd_pixel_mang(x+m, y+k*size+l, color); // Draws the pixel
						}
					}
				}
				else
				{
					for(l=0; l < size; ++l)    // These two loops change the
					{                          // character's size
						for(m=0; m < size; ++m)
						{
							glcd_pixel_mang(x+m, y+k*size+l, inv); // Draws the pixel
						}
					}
				}
			}
			glcd_vi_tri_mang=0;
			for(k=0; k < 7; ++k)             // Loop through the vertical pixels
			{
				if(pixelData[j] & (1<<k)) // Check if the pixel should be set
				{
					for(l=0; l < size; ++l)    // These two loops change the
					{                          // character's size
						for(m=0; m < size; ++m)
						{
							glcd_mang_ghi(x+m, y+k*size+l, color); // Draws the pixel
						}
					}
				}
				else
				{
					for(l=0; l < size; ++l)    // These two loops change the
					{                          // character's size
						for(m=0; m < size; ++m)
						{
							glcd_mang_ghi(x+m, y+k*size+l, inv); // Draws the pixel
						}
					}
				}
			}
			
			
			
			
			
			
			
			
			
		}
		
		//for(j=0; j<5; ++j, x+=size)         // Loop through character byte data
		//{
		//for(k=0; k < 7; ++k)             // Loop through the vertical pixels
		//{
		//if(pixelData[j] & (1<<k)) // Check if the pixel should be set
		//{
		//for(l=0; l < size; ++l)    // These two loops change the
		//{                          // character's size
		//for(m=0; m < size; ++m)
		//{
		//glcd_pixel_lcd(x+m, y+k*size+l, color); // Draws the pixel
		//}
		//}
		//}
		//else
		//{
		//for(l=0; l < size; ++l)    // These two loops change the
		//{                          // character's size
		//for(m=0; m < size; ++m)
		//{
		//glcd_pixel_lcd(x+m, y+k*size+l, inv); // Draws the pixel
		//}
		//}
		//}
		//}
		//}
		
		
		
	}
}






#ifdef LARGE_LCD
void glcd_text57(u16 x, u16 y, char* textptr, u8 size, u8 color)
#else
void glcd_text57_gram(u8 x, u8 y, char* textptr, u8 size, u8 color)
#endif
{
	u8 x1,x2,x3;
	if (che_do_graphic!=1)
	{
		LCD_EnableGraphics(); // neu muon ghi chu tu font ngoai hoac hinh anh phai chuyen qua che do Graphic
		che_do_graphic=1;
	}
	u8 j, k, l, m, i;                       // Loop counters
	u8 inv=~color;
	u8 pixelData[5];                     // Stores character data
	//if(color==1)inv=0;
	//else inv=1;
	for(; *textptr != '\0'; ++textptr, ++x)// Loop through the passed string
	{
		for(i = 0; i < 5; i++)
		{
			pixelData[i]=(pgm_read_byte(&font5x7_hoa[((*textptr-0x20) * 5) + i]));
		}
		


		// Handles newline and carriage returns
		//switch(*textptr)
		//{
		//case '\n':
		//y += 7*size + 1;
		//continue;
		//case '\r':
		//x = 0;
		//continue;
		//}
//
		//x=xx;
		//if(x+5*size >= GLCD_WIDTH)          // Performs character wrapping
		//{
			//x = 0;                           // Set x at far left position
			//y += 7*size + 1;                 // Set y at next position down
		//}
		//
		//glcd_vi_tri_mang=0;
		//for(j=0; j<5; ++j, x+=size)         // Loop through character byte data
		//{
			//for(k=0; k < 7; ++k)             // Loop through the vertical pixels
			//{
				//if(pixelData[j] & (1<<k)) // Check if the pixel should be set
				//{
					//for(l=0; l < size; ++l)    // These two loops change the
					//{                          // character's size
						//for(m=0; m < size; ++m)
						//{
							//glcd_doc_mang_du_lieu(x+m, y+k*size+l); // Draws the pixel
						//}
					//}
				//}
				//else
				//{
					//for(l=0; l < size; ++l)    // These two loops change the
					//{                          // character's size
						//for(m=0; m < size; ++m)
						//{
							//glcd_doc_mang_du_lieu(x+m, y+k*size+l); // Draws the pixel
						//}
					//}
				//}
			//}
		//}
		//
		//if(x+5*size >= GLCD_WIDTH)          // Performs character wrapping
		//{
			//x = 0;                           // Set x at far left position
			//y += 7*size + 1;                 // Set y at next position down
		//}
		//
		//glcd_vi_tri_mang=0;
		//for(j=0; j<5; ++j, x+=size)         // Loop through character byte data
		//{
			//for(k=0; k < 7; ++k)             // Loop through the vertical pixels
			//{
				//if(pixelData[j] & (1<<k)) // Check if the pixel should be set
				//{
					//for(l=0; l < size; ++l)    // These two loops change the
					//{                          // character's size
						//for(m=0; m < size; ++m)
						//{
							//glcd_pixel_mang(x+m, y+k*size+l, color); // Draws the pixel
						//}
					//}
				//}
				//else
				//{
					//for(l=0; l < size; ++l)    // These two loops change the
					//{                          // character's size
						//for(m=0; m < size; ++m)
						//{
							//glcd_pixel_mang(x+m, y+k*size+l, inv); // Draws the pixel
						//}
					//}
				//}
			//}
		//}
		//
		//
		//x;//=xx;
		if(x+5*size >= GLCD_WIDTH)          // Performs character wrapping
		{
			x = 0;                           // Set x at far left position
			y += 7*size + 1;                 // Set y at next position down
		}
		
		for(j=0; j<5; ++j, x+=size)         // Loop through character byte data
		{
			for(k=0; k < 7; ++k)             // Loop through the vertical pixels
			{
				if(pixelData[j] & (1<<k)) // Check if the pixel should be set
				{
					for(l=0; l < size; ++l)    // These two loops change the
					{                          // character's size
						for(m=0; m < size; ++m)
						{
							glcd_pixel_lcd(x+m, y+k*size+l, color); // Draws the pixel
						}
					}
				}
				else
				{
					for(l=0; l < size; ++l)    // These two loops change the
					{                          // character's size
						for(m=0; m < size; ++m)
						{
							glcd_pixel_lcd(x+m, y+k*size+l, inv); // Draws the pixel
						}
					}
				}
			}
		}
		
		//for(j=0; j<5; ++j, x+=size)         // Loop through character byte data
		//{
			//for(k=0; k < 7; ++k)             // Loop through the vertical pixels
			//{
				//if(pixelData[j] & (1<<k)) // Check if the pixel should be set
				//{
					//for(l=0; l < size; ++l)    // These two loops change the
					//{                          // character's size
						//for(m=0; m < size; ++m)
						//{
							//glcd_pixel_lcd(x+m, y+k*size+l, color); // Draws the pixel
						//}
					//}
				//}
				//else
				//{
					//for(l=0; l < size; ++l)    // These two loops change the
					//{                          // character's size
						//for(m=0; m < size; ++m)
						//{
							//glcd_pixel_lcd(x+m, y+k*size+l, inv); // Draws the pixel
						//}
					//}
				//}
			//}
		//}
		
		
		
	}
}


					//glcd_vi_tri_mang=0;
					//for(l=0; l < size; ++l)    // These two loops change the
					//{                          // character's size
						//for(m=0; m < size; ++m)
						//{
							//glcd_doc_mang_du_lieu(x+m, y+k*size+l); // Draws the pixel
						//}
					//}
					//glcd_vi_tri_mang=0;
					//for(l=0; l < size; ++l)    // These two loops change the
					//{                          // character's size
						//for(m=0; m < size; ++m)
						//{
							//glcd_pixel_mang(x+m, y+k*size+l,color); // Draws the pixel
						//}
					//}
					//glcd_vi_tri_mang=0;
					//for(l=0; l < size; ++l)    // These two loops change the
					//{                          // character's size
						//for(m=0; m < size; ++m)
						//{
							//glcd_mang_ghi(x+m, y+k*size+l,color); // Draws the pixel
						//}
					//}


void glcd_text57_8_bit(u8 x, u8 y, char* textptr, u8 size, u8 color)
{
	if (che_do_graphic!=1)
	{
		//LCD_EnableGraphics(); // neu muon ghi chu tu font ngoai hoac hinh anh phai chuyen qua che do Graphic
		che_do_graphic=1;
	}
	u8 j, k, l, m, i;                       // Loop counters
	u8 inv=~color;
	u8 pixelData[5];                     // Stores character data
	//if(color==1)inv=0;
	//else inv=1;
	for(; *textptr != '\0'; ++textptr, ++x)// Loop through the passed string
	{
		//if(*textptr < 'S') // Checks if the letter is in the first font array
		//memcpy(pixelData, FONT[*textptr - ' '], 5);
		//else if(*textptr <= '~') // Check if the letter is in the second font array
		//memcpy(pixelData, FONT2[*textptr - 'S'], 5);
		//else
		//memcpy(pixelData, FONT[0], 5);   // Default to space
		//GLCD_WriteChar(*s);
		for(i = 0; i < 5; i++)
		{
			pixelData[i]=(pgm_read_byte(&font5x7_hoa[((*textptr-0x20) * 5) + i]));
		}
		


		// Handles newline and carriage returns
		//switch(*textptr)
		//{
		//case '\n':
		//y += 7*size + 1;
		//continue;
		//case '\r':
		//x = 0;
		//continue;
		//}

		if(x+5*size >= GLCD_WIDTH)          // Performs character wrapping
		{
			x = 0;                           // Set x at far left position
			y += 7*size + 1;                 // Set y at next position down
		}
		for(j=0; j<5; ++j, x+=size)         // Loop through character byte data
		{
			for(k=0; k < 7; ++k)             // Loop through the vertical pixels
			{
				
				//if(bit_test_8(pixelData[j], k))
				if(pixelData[j] & (1<<k)) // Check if the pixel should be set
				{
					for(l=0; l < size; ++l)    // These two loops change the
					{                          // character's size
						for(m=0; m < size; ++m)
						{
							glcd_pixel_lcd_8_bit(x+m, y+k*size+l, color); // Draws the pixel
						}
					}
				}
				else
				{
					for(l=0; l < size; ++l)    // These two loops change the
					{                          // character's size
						for(m=0; m < size; ++m)
						{
							glcd_pixel_lcd_8_bit(x+m, y+k*size+l, inv); // Draws the pixel
						}
					}
				}
			}
		}
	}
}
//#endif
//======================================== 
void LCD_Init_4bit(void)
{
	rsl_d=rwl_d=enl_d=rstl_d=ra;
	dl_xuat_nhap(ra);
	rstl=1;
	delay_ms(5);
	rstl=0;
	delay_ms(5);
	rstl=1;
	delay_ms(60);
	LCD_WriteCommand(0b00100000); // function set, 4 bit mode
	delay_ms(10);
	LCD_WriteCommand(0b00100000); // 4 bit mode again
	delay_ms(10);
	LCD_WriteCommand(0b00001100); // display on, cursor off, blink off
	delay_ms(10);
	LCD_WriteCommand(0x01); 	  // display clear
	delay_ms(10);
	LCD_WriteCommand(0x06); 	  // Cursor moves right, no display shift.
	delay_ms(10);
	LCD_WriteCommand(0b00000010); // Returns to home. Cursor moves to starting point.
	delay_ms(10);
}