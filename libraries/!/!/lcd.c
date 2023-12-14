/*
 * lcd.c
 * 
 * Copyright 2013 Shimon <shimon@monistit.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>

#include <!/lcd.h>
#include <!/! LDN.h>

//Custom Charset support

#define LCD_DATA_PORT 	PORT(LCD_DATA)
#define LCD_E_PORT 		PORT(LCD_E)
#define LCD_RS_PORT 	PORT(LCD_RS)
#define LCD_RW_PORT 	PORT(LCD_RW)

#define LCD_DATA_DDR 	DDR(LCD_DATA)
#define LCD_E_DDR 		DDR(LCD_E)
#define LCD_RS_DDR 		DDR(LCD_RS)
#define LCD_RW_DDR 		DDR(LCD_RW)

#define LCD_DATA_PIN	PIN(LCD_DATA)

#define SET_E() (LCD_E_PORT|=(1<<LCD_E_POS))
#define SET_RS() (LCD_RS_PORT|=(1<<LCD_RS_POS))
#define SET_RW() (LCD_RW_PORT|=(1<<LCD_RW_POS))

#define CLEAR_E() (LCD_E_PORT&=(~(1<<LCD_E_POS)))
#define CLEAR_RS() (LCD_RS_PORT&=(~(1<<LCD_RS_POS)))
#define CLEAR_RW() (LCD_RW_PORT&=(~(1<<LCD_RW_POS)))

#ifdef LCD_TYPE_162
	#define LCD_TYPE_204
#endif

#ifdef LCD_TYPE_202
	#define LCD_TYPE_204
#endif

//========================================
void l_xuat_4(u8 dl) // xuat ma 7 doan theo bit không theo thu tu
{
	l_d4=(dl&0x1);
	dl>>=1;
	l_d5=(dl&0x1);
	dl>>=1;
	l_d6=(dl&0x1);
	dl>>=1;
	l_d7=(dl&0x1);
}
//======================================== 
//void l_ban()
// {
// 	u8 busy,status=0x00,temp;
// 	l_d4_d=l_d5_d=l_d6_d=l_d7_d=vao;
// 	l_rw=1;
// 	l_rs=0;
// 	_delay_us(0.5);		//tAS
// 	do
// 	{
// 		status=busy=0;
// 		l_en=1;
// 		_delay_us(0.5);
// 		status|=l_d7_p;
// 		status<<=1;
// 		status|=l_d6_p;
// 		status<<=1;
// 		status|=l_d5_p;
// 		status<<=1;
// 		status|=l_d4_p;
// 		_delay_us(0.5);
// 		l_en=0;
// 		_delay_us(1);	//tEL
// 		l_en=1;
// 		_delay_us(0.5);
// 		busy|=l_d7_p;
// 		busy<<=1;
// 		busy|=l_d6_p;
// 		busy<<=1;
// 		busy|=l_d5_p;
// 		busy<<=1;
// 		busy|=l_d4_p;
// 		busy<<=4;
// 		busy|=status;
// 		_delay_us(0.5);
// 		l_en=0;
// 		_delay_us(1);	//tEL
// 	}while(busy!=0);
// 	l_rw=0;
// 	l_d4_d=l_d5_d=l_d6_d=l_d7_d=ra;
// }
//========================================
void l_gui(uint8_t c,uint8_t isdata)
{
	uint8_t hn,ln;			//Nibbles
	uint8_t temp;
	hn=c>>4; 
	ln=(c & 0x0F);
	if(isdata==0)
		l_rs=0;
	else
		l_rs=1;
	_delay_us(0.500);		//tAS
	l_en=1;
	l_xuat_4(hn);
	_delay_us(1);			
	l_en=0;
	_delay_us(1);
	l_en=1;
	l_xuat_4(ln);
	_delay_us(1);			//tEH
	l_en=0;
	_delay_us(1);			//tEL
	//l_ban();
	_delay_us(500);
}
//======================================== 
void l_toi_xy(uint8_t x,uint8_t y)
{
	if(x>=20) return;

	#ifdef LCD_TYPE_204
	
	switch(y)
	{
		case 0:
		break;
		case 1:
		x|=0b01000000;
		break;
		case 2:
		x+=0x14;
		break;
		case 3:
		x+=0x54;
		break;
	}

	#endif

	#ifdef LCD_TYPE_164
	switch(y)
	{
		case 0:
		break;
		case 1:
		x|=0b01000000;
		break;
		case 2:
		x+=0x10;
		break;
		case 3:
		x+=0x50;
		break;
	}

	#endif

	x|=0b10000000;
	l_lenh(x);
}
//========================================
void l_khoi_tao(uint8_t style)
{
	_delay_ms(30);
	l_d4_d=l_d5_d=l_d6_d=l_d7_d=ra;
	l_en_d=l_rs_d=ra;
	l_en=l_rs=0;
	l_d4=l_d5=l_d6=l_d7=0;
	_delay_us(0.3);	//tAS
	l_en=1;
	l_xuat_4(0b00000010);
	_delay_us(1);
	l_en=0;
	_delay_us(1);
	delay_ms(4);
	//l_ban();                                  //[B] Forgot this delay
	l_lenh(0b00001100|style);	//Display On
	l_lenh(0b00101000);			//function set 4-bit,2 line 5x7 dot format
	l_toi_xy(0,0);
	l_lenh(1); 

}
//======================================== 
void l_in_x(char *p, char l) 
{
	if(l==1)l_lenh(0x80);
	else l_lenh(0xc0);
	while(*p)
	l_dl(*p++);
}
//========================================
void l_in(char *p)
{
	while(*p)
	l_dl(*p++); 
}
//======================================== 
void l_tuy_chinh()
{
	uint8_t i,j;
	i=0;j=0;
	l_lenh(64);
	for(i=1;i<=8;i++) {
		for(j=8;j>i;j--)
		l_dl(0);
		for(j=i;j>0;j--)
		l_dl(0xff);
	}
}
//======================================== 
void LCDByte(uint8_t c,uint8_t isdata)
{
//Sends a byte to the LCD in 4bit mode
//cmd=0 for data
//cmd=1 for command


//NOTE: THIS FUNCTION RETURS ONLY WHEN LCD HAS PROCESSED THE COMMAND

uint8_t hn,ln;			//Nibbles
uint8_t temp;

hn=c>>4;
ln=(c & 0x0F);

if(isdata==0)
	CLEAR_RS();
else
	SET_RS();

_delay_us(0.500);		//tAS

SET_E();

//Send high nibble

temp=(LCD_DATA_PORT & (~(0X0F<<LCD_DATA_POS)))|((hn<<LCD_DATA_POS));
LCD_DATA_PORT=temp;

_delay_us(1);			//tEH

//Now data lines are stable pull E low for transmission

CLEAR_E();

_delay_us(1);

//Send the lower nibble
SET_E();

temp=(LCD_DATA_PORT & (~(0X0F<<LCD_DATA_POS)))|((ln<<LCD_DATA_POS));

LCD_DATA_PORT=temp;

_delay_us(1);			//tEH

//SEND

CLEAR_E();

_delay_us(1);			//tEL

LCDBusyLoop();
}

void LCDBusyLoop()
{
	//This function waits till lcd is BUSY

	uint8_t busy,status=0x00,temp;

	//Change Port to input type because we are reading data
	LCD_DATA_DDR&=(~(0x0f<<LCD_DATA_POS));

	//change LCD mode
	SET_RW();		//Read mode
	CLEAR_RS();		//Read status

	//Let the RW/RS lines stabilize

	_delay_us(0.5);		//tAS

	
	do
	{

		SET_E();

		//Wait tDA for data to become available
		_delay_us(0.5);

		status=(LCD_DATA_PIN>>LCD_DATA_POS);
		status=status<<4;

		_delay_us(0.5);

		//Pull E low
		CLEAR_E();
		_delay_us(1);	//tEL

		SET_E();
		_delay_us(0.5);

		temp=(LCD_DATA_PIN>>LCD_DATA_POS);
		temp&=0x0F;

		status=status|temp;

		busy=status & 0b10000000;

		_delay_us(0.5);
		CLEAR_E();
		_delay_us(1);	//tEL
	}while(busy);

	CLEAR_RW();		//write mode
	//Change Port to output
	LCD_DATA_DDR|=(0x0F<<LCD_DATA_POS);

}

void LCDInit(uint8_t style)
{
	/*****************************************************************
	
	This function Initializes the lcd module
	must be called before calling lcd related functions

	Arguments:
	style = LS_BLINK,LS_ULINE(can be "OR"ed for combination)
	LS_BLINK :The cursor is blinking type
	LS_ULINE :Cursor is "underline" type else "block" type

	*****************************************************************/
	
	//After power on Wait for LCD to Initialize
	_delay_ms(30);
	
	//Set IO Ports
	LCD_DATA_DDR|=(0x0F<<LCD_DATA_POS);
	LCD_E_DDR|=(1<<LCD_E_POS);
	LCD_RS_DDR|=(1<<LCD_RS_POS);
	LCD_RW_DDR|=(1<<LCD_RW_POS);

	LCD_DATA_PORT&=(~(0x0F<<LCD_DATA_POS));
	CLEAR_E();
	CLEAR_RW();
	CLEAR_RS();

	//Set 4-bit mode
	_delay_us(0.3);	//tAS

	SET_E();
	LCD_DATA_PORT|=((0b00000010)<<LCD_DATA_POS); //[B] To transfer 0b00100000 i was using LCD_DATA_PORT|=0b00100000
	_delay_us(1);
	CLEAR_E();
	_delay_us(1);
	
	//Wait for LCD to execute the Functionset Command
	LCDBusyLoop();                                    //[B] Forgot this delay

	//Now the LCD is in 4-bit mode

	LCDCmd(0b00001100|style);	//Display On
	LCDCmd(0b00101000);			//function set 4-bit,2 line 5x7 dot format

	
	LCDGotoXY(0,0);

}




void LCDWriteString(const char *msg)
{
	/*****************************************************************
	
	This function Writes a given string to lcd at the current cursor
	location.

	Arguments:
	msg: a null terminated string to print

	Their are 8 custom char in the LCD they can be defined using
	"LCD Custom Character Builder" PC Software. 

	You can print custom character using the % symbol. For example
	to print custom char number 0 (which is a degree symbol), you 
	need to write

		LCDWriteString("Temp is 30%0C");
		                          ^^
								  |----> %0 will be replaced by
								  		custom char 0.

	So it will be printed like.
		
		Temp is 30°C
		
	In the same way you can insert any syblom numbered 0-7 	


	*****************************************************************/
 while(*msg!='\0')
 {
 	//Custom Char Support
	if(*msg=='%')
	{
		msg++;
		int8_t cc=*msg-'0';

		if(cc>=0 && cc<=7)
		{
			LCDData(cc);
		}
		else
		{
			LCDData('%');
			LCDData(*msg);
		}
	}
	else
	{
		LCDData(*msg);
	}
	msg++;
 }
}

void LCDWriteInt(int val,unsigned int field_length)
{
	/***************************************************************
	This function writes a integer type value to LCD module

	Arguments:
	1)int val	: Value to print

	2)unsigned int field_length :total length of field in which the value is printed
	must be between 1-5 if it is -1 the field length is no of digits in the val

	****************************************************************/

	char str[5]={0,0,0,0,0};
	int i=4,j=0;
	while(val)
	{
	str[i]=val%10;
	val=val/10;
	i--;
	}
	if(field_length==-1)
		while(str[j]==0) j++;
	else
		j=5-field_length;

	if(val<0) LCDData('-');
	for(i=j;i<5;i++)
	{
	LCDData(48+str[i]);
	}
}
void LCDGotoXY(uint8_t x,uint8_t y)
{
 	if(x>=20) return;

	#ifdef LCD_TYPE_204
	
	switch(y)
	{
		case 0:
			break;
		case 1:
			x|=0b01000000;
			break;
		case 2:
			x+=0x14;
			break;
		case 3:
			x+=0x54;
			break;
	}

	#endif

	#ifdef LCD_TYPE_164
	switch(y)
	{
		case 0:
			break;
		case 1:
			x|=0b01000000;
			break;
		case 2:
			x+=0x10;
			break;
		case 3:
			x+=0x50;
			break;
	}

	#endif

	x|=0b10000000;
  	LCDCmd(x);
}



void LCDHexDumpXY(uint8_t x, uint8_t y,uint8_t d)
{
	LCDGotoXY(x,y);
	uint8_t byte = '0';
	(((d>>4)&0x0F)<=9) ? (byte='0'+((d>>4)&0x0F)) : (byte='A'+ ((d>>4)&0x0F)-0x0A);
	LCDByte(byte,1);
	LCDBusyLoop();
	
	((d&0x0F)<=9) ? (byte='0'+ (d&0x0F)) : (byte='A'+ (d&0x0F)-0x0A);
	LCDByte(byte,1);
	LCDBusyLoop();
}

void lcd_print(char *p, char l)
{
	if(l==1)
	{
		LCDByte(0x80,1);
		LCDBusyLoop();
	}
	else 
	{
		LCDByte(0xc0,1);
		LCDBusyLoop();
	}
	while(*p)
	{
		LCDByte(*p++,0);
		LCDBusyLoop();
	}
}

void lcd_in(char *p, char l)
{
	if(l==1)LCDCmd(0x80);
	else LCDCmd(0xc0);
	while(*p)
	LCDData(*p++);
}

void lcd_fill_custom()
{
	uint8_t i,j;
	i=0;j=0;
	LCDCmd(64);
	for(i=1;i<=8;i++) {
		for(j=8;j>i;j--)
		LCDData(0);
		for(j=i;j>0;j--)
		LCDData(0xb00001110);
	}
}