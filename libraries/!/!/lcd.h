/*
 * lcd.h
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

#include <util/delay.h>

#include <!/myutils.h>

#ifndef _LCD_H
#define _LCD_H



/*_________________________________________________________________________________________*/

/************************************************
	LCD CONNECTIONS
*************************************************/
//#ifndef LCD_DATA
//#define LCD_DATA D			//Port PD0-PD3 are connected to D4-D7
//#define LCD_DATA_POS 0	
//
//#define LCD_E D 			//Enable/strobe signal
//#define LCD_E_POS	PD4		//Position of enable in above port
//
//#define LCD_RS D			//RS SIGNAL
//#define LCD_RS_POS PD5
//
//#define LCD_RW D			//RW SIGNAL
//#define LCD_RW_POS PD6
//#endif

#ifndef l_en
#define l_en dk_bit(PORTB,3)
#define l_en_d dk_bit(DDRB,3)
#define l_rs dk_bit(PORTB,4)
#define l_rs_d dk_bit(DDRB,4)

#define l_d4 dk_bit(PORTD,5)
#define l_d4_d dk_bit(DDRD,5)
#define l_d5 dk_bit(PORTD,6)
#define l_d5_d dk_bit(DDRD,6)
#define l_d6 dk_bit(PORTD,7)
#define l_d6_d dk_bit(DDRD,7)
#define l_d7 dk_bit(PORTB,0)
#define l_d7_d dk_bit(DDRB,0)
#define l_d7_p dk_bit(PINB,0)
#endif

/***********************************************

LCD Type Selection
Uncomment Just one of them

************************************************/

//#define LCD_TYPE_202	//For 20 Chars by 2 lines

//#define LCD_TYPE_204	//For 20 Chars by 4 lines

#define LCD_TYPE_162	//For 16 Chars by 2 lines

//#define LCD_TYPE_164	//For 16 Chars by 4 lines


//************************************************

	


//************************************************

#define LS_BLINK 0B00000001
#define LS_ULINE 0B00000010
#define LS_NONE	 0B00000000



/***************************************************
			F U N C T I O N S
****************************************************/


 
void LCDInit(uint8_t style);
void LCDWriteString(const char *msg);
void LCDWriteInt(int val,unsigned int field_length);
void LCDGotoXY(uint8_t x,uint8_t y);
void LCDHexDumpXY(uint8_t x, uint8_t y,uint8_t d);

//Low level
void LCDByte(uint8_t,uint8_t);
#define LCDCmd(c) (LCDByte(c,0))
#define LCDData(d) (LCDByte(d,1))

void l_gui(uint8_t,uint8_t);
#define l_lenh(c) (l_gui(c,0))
#define l_dl(d) (l_gui(d,1))
#define l_xoa() l_lenh(0b00000001)
#define l_goc() l_lenh(0b00000010);
void LCDBusyLoop();





/***************************************************
			F U N C T I O N S     E N D
****************************************************/


/***************************************************
	M A C R O S
***************************************************/
#define LCDClear() LCDCmd(0b00000001)
#define LCDHome() LCDCmd(0b00000010);

#define LCDWriteStringXY(x,y,msg) {\
 LCDGotoXY(x,y);\
 LCDWriteString(msg);\
}

#define LCDWriteIntXY(x,y,val,fl) {\
 LCDGotoXY(x,y);\
 LCDWriteInt(val,fl);\
}
/***************************************************/




/*_________________________________________________________________________________________*/
#endif




