/*
ds18b20 lib 0x01

copyright (c) Davide Gironi, 2012

Released under GPLv3.
Please refer to LICENSE file for licensing information.

References:
  + Using DS18B20 digital temperature sensor on AVR microcontrollers
    by Gerard Marull Paretas, 2007
    http://teslabs.com/openplayer/docs/docs/other/ds18b20_pre1.pdf
*/


#ifndef DS18B20_H_
#define DS18B20_H_

#include <avr/io.h>

//setup connection
#ifndef DS18B20_DQ
	#define DS18B20_PORT PORTB
	#define DS18B20_DDR DDRB
	#define DS18B20_PIN PINB
	#define DS18B20_DQ PB0
#endif

//setup connection
#ifndef ds1820_d
	#define ds1820_d dk_bit(DDRC,1)
	#define ds1820_i dk_bit(PINC,1)
	#define ds1820_o dk_bit(PORTC,1)
#endif

//commands
#define DS18B20_CMD_CONVERTTEMP 0x44
#define DS18B20_CMD_RSCRATCHPAD 0xbe
#define DS18B20_CMD_WSCRATCHPAD 0x4e
#define DS18B20_CMD_CPYSCRATCHPAD 0x48
#define DS18B20_CMD_RECEEPROM 0xb8
#define DS18B20_CMD_RPWRSUPPLY 0xb4
#define DS18B20_CMD_SEARCHROM 0xf0
#define DS18B20_CMD_READROM 0x33
#define DS18B20_CMD_MATCHROM 0x55
#define DS18B20_CMD_SKIPROM 0xcc
#define DS18B20_CMD_ALARMSEARCH 0xec

//decimal conversion table
#define DS18B20_DECIMALSTEPS_9BIT  5000 //0.5
#define DS18B20_DECIMALSTEPS_10BIT 2500 //0.25
#define DS18B20_DECIMALSTEPS_11BIT 1250 //0.125
#define DS18B20_DECIMALSTEPS_12BIT 625  //0.0625
#define DS18B20_DECIMALSTEPS DS18B20_DECIMALSTEPS_12BIT

#define DS18B20_TCONV_12BIT      750
#define DS18B20_TCONV_11BIT      DS18B20_TCONV_12_BIT/2
#define DS18B20_TCONV_10BIT      DS18B20_TCONV_12_BIT/4
#define DS18B20_TCONV_9BIT       DS18B20_TCONV_12_BIT/8
#define DS18S20_TCONV            DS18B20_TCONV_12_BIT

//functions
extern double ds18b20_gettemp();





#include <avr/io.h>
#include <util/delay.h>
#ifndef bu_c
#define bu_c 1000
#endif
// #define ds1820_d1 dk_bit(DDRB,0)
// #define ds1820_p1 dk_bit(PINB,0)
// #define ds1820_1 dk_bit(PORTB,0)
// #define ds1820_d2 dk_bit(DDRB,1)
// #define ds1820_p2 dk_bit(PINB,1)
// #define ds1820_2 dk_bit(PORTB,1)

// #define ds1820_d3 dk_bit(DDRB,2)
// #define ds1820_p3 dk_bit(PINB,2)
// #define ds1820_3 dk_bit(PORTB,2)


#ifndef ds1820_d1
#define ds1820_d1 dk_bit(DDRB,2)
#define ds1820_p1 dk_bit(PINB,2)
#define ds1820_1 dk_bit(PORTB,2)
#endif
#ifndef ds1820_d2
// #define ds1820_d2 dk_bit(DDRD,6)
// #define ds1820_p2 dk_bit(PIND,6)
// #define ds1820_2 dk_bit(PORTD,6)

// #define ds1820_d3 dk_bit(DDRB,5)
// #define ds1820_3_i dk_bit(PINB,5)
// #define ds1820_3 dk_bit(PORTB,5)


// #define dq PC0 
// #define dq1 PC1
// #define dq2 PC2
uint8_t gSensorIDs[2][2];
#ifndef dq_p
// #define dq_p PORTC
// #define ds1820_d1= DDRC
// #define ds1820_p1= PINC
#endif
#endif
#include "1 DS18b20.h"

#include <stdio.h>
#include <stdarg.h> 
#include <string.h>
#include <stdlib.h>

#include <inttypes.h>
#include <stdint.h>
#include <math.h>

#include "1wire.c" // truy xuat vao file 1wire
//#include "ds1820.c" // truy xuat vao file ds1820.c
u16 tinh_tp;
uint8_t nd_h,nd_l;
	unsigned int tempint = 0,tempint1,tempint2,tempint3; // ?????????? ??? ?????? ???????? ???????????
	unsigned int temppoint = 0,temppoint1; // ?????????? ??? ???????? ???????? ???????????

int 	flagRX = 0; 
int 	blink;
uint8_t m7d1,m7d2,m7d3,m7d4; // ch?a mã 7 ?o?n c?n hi?n th?
volatile unsigned char ma_quet = 0;
volatile int display1 = 0, display2 = 0, display3 = 0, display4 = 0;
uint8_t nSensors;//, i;
#define		def		 		0.0196  	// (5 div 255)
#define     TIMECONST   	800000  	// it bestter at 400000
#define     TIMEOUT     	0xFE

u8 ds_moi_bat_ngat=0;

// ISR (TIMER2_OVF_vect)
// {
// 	PORTD = 0xFF;
// 	PORTB = (1 << ma_quet);
// 	
// 	switch (ma_quet)
// 	{
// 		case 0:
// 
// 		break;
// 	}
// 	if ((ma_quet++) > 2) ma_quet = 0;
// }
//======================================== 
unsigned char Temp_H = 0,Temp_L = 0,OK_Flag = 0,temp_flag;

/*** ????????????? DS18B20 ***/
// unsigned char DS18B20_init(void)
// {
// 	PORTC &= ~(1 << dq); // ????????????? ?????? ???????
// 	DDRC |= (1 << dq);
// 	_delay_us(490);
// 	DDRC &= ~(1 << dq);
// 	_delay_us(68);
// 	OK_Flag = (PINC & (1 << dq)); // ????? ??????? ??????????? ???????
// 	// ???? OK_Flag = 0 ?????? ?????????, OK_Flag = 1 ?????? ?? ?????????
// 	_delay_us(422);
// 	return OK_Flag;
// }
//========================================
#if so_ds > 2
u8 DS18B20_init_3(void)
{
	ds1820_1=0;
	ds1820_d1=vao;
	ds1820_2=0;
	ds1820_d2=vao; 
	ds1820_3=0;
	ds1820_d3=vao;
	ds1820_d1=ra;
	ds1820_d2=ra;
	ds1820_d3=ra;
	_delay_us(490);
	ds1820_d1=vao;
	ds1820_d2=vao;
	ds1820_d3=vao;
	_delay_us(68);
	OK_Flag = ds1820_p1; // ????? ??????? ??????????? ???????
	_delay_us(422);
	return OK_Flag;
}
#endif 
//========================================
// #if so_ds > 3
// u8 DS18B20_init_4(void)
// {
// 	ds1820_1=0;
// 	ds1820_d1=vao;
// 	ds1820_2=0;
// 	ds1820_d2=vao; 
// 	ds1820_3=0;
// 	ds1820_d3=vao;
// 	ds1820_4=0;
// 	ds1820_d4=vao;
// 	ds1820_d1=ra;
// 	ds1820_d2=ra;
// 	ds1820_d3=ra;
// 	ds1820_d4=ra;
// 	_delay_us(490);
// 	ds1820_d1=vao;
// 	ds1820_d2=vao;
// 	ds1820_d3=vao;
// 	ds1820_d4=vao;
// 	_delay_us(68);
// 	OK_Flag = ds1820_p1; // ????? ??????? ??????????? ???????
// 	_delay_us(422);
// 	return OK_Flag;
// }
// #endif
//======================================== 
// #if so_ds == 4 
// u8 DS18B20_init_4(void)
// {
// 	PORTC &= ~(1 << dq2);
// 	DDRC &= ~(1 << dq2);
// 	PORTC &= ~(1 << dq1);
// 	DDRC &= ~(1 << dq1);
// 	#if so_ds==0
// 	PORTC &= ~(1 << dq);
// 	#endif
// 	PORTC &= ~(1 << dq1);
// 	PORTC &= ~(1 << dq2);
// 	PORTC &= ~(1 << dq3);
// 	#if so_ds==0
// 	DDRC |= (1 << dq);
// 	#endif
// 	DDRC |= (1 << dq1);
// 	DDRC |= (1 << dq2);
// 	DDRC |= (1 << dq3);
// 	_delay_us(490);
// 	#if so_ds==0
// 	DDRC &= ~(1 << dq);
// 	#endif
// 	DDRC &= ~(1 << dq1);
// 	DDRC &= ~(1 << dq2);
// 	DDRC &= ~(1 << dq3);
// 	_delay_us(68);
// 	#if so_ds==0
// 	OK_Flag = (ds1820_p1= & (1 << dq)); // ????? ??????? ??????????? ???????
// 	#endif
// 	_delay_us(422);
// 	return OK_Flag;
// }
// #endif
//======================================== 
u8 khoi_tao_1820(void)
{
	cli();
	ds1820_1=0;
	ds1820_d1=1;
	_delay_us(490);
	ds1820_d1=0;
	_delay_us(68);
	OK_Flag = (ds1820_p1);
	_delay_us(422);
	return OK_Flag;
	ds_moi_bat_ngat=1;
	sei();
}
//========================================
u8 khoi_tao_1820_1(void)
{
	cli();
	ds1820_1=0;
	ds1820_d1=1;
	_delay_us(490);
	ds1820_d1=0;
	_delay_us(68);
	OK_Flag = (ds1820_p1);
	_delay_us(422);
	return OK_Flag;
	ds_moi_bat_ngat=1;
	sei();
}
//========================================
#if so_ds > 2
u8 ds1820_khoi_tao_x3(void)
{
	cli();
	ds1820_1=0;
	ds1820_d1=1;
	ds1820_2=0;
	ds1820_d2=1;
	ds1820_3=0;
	ds1820_d3=1; 
	_delay_us(490);
	ds1820_d1=0;
	ds1820_d2=0;
	ds1820_d3=0;
	_delay_us(68);
	OK_Flag = (ds1820_p1&ds1820_p2&ds1820_p3);
	_delay_us(422);
	return OK_Flag;
	ds_moi_bat_ngat=1;
	sei();
}
#endif
//========================================
#if so_ds > 3
u8 ds1820_khoi_tao_x4(void)
{
	cli();
	ds1820_1=0;
	ds1820_d1=1;
	ds1820_2=0;
	ds1820_d2=1;
	ds1820_3=0;
	ds1820_d3=1;
	ds1820_4=0;
	ds1820_d4=1;
	_delay_us(490);
	ds1820_d1=0;
	ds1820_d2=0;
	ds1820_d3=0;
	ds1820_d4=0;
	_delay_us(68);
	OK_Flag = (ds1820_p1&ds1820_p2&ds1820_p3&ds1820_p4);
	_delay_us(422);
	return OK_Flag;
	ds_moi_bat_ngat=1;
	sei();
}
#endif
//========================================
unsigned char doc_1820_1(void)
{
	unsigned char i;
	unsigned char dat = 0;
	cli();
	for(i = 0;i < 8;i++)
	{
		ds1820_d1=1;
		_delay_us(2);
		ds1820_d1=0;
		_delay_us(4);
		dat = dat >> 1;
		if(ds1820_p1==1)
		{
			dat |= 0x80;
		}
		_delay_us(62);
	}
	ds_moi_bat_ngat=1;
	sei();
	return dat;
}
//========================================
u8 ds1820_d1oc(void)
{
	u8 i;
	u8 dat = 0;
	cli();
	for(i = 0;i < 8;i++)
	{
		ds1820_d1=1;
		_delay_us(2);
		ds1820_d1=0;
		_delay_us(4);
		dat = dat >> 1;
		if(ds1820_p1==1)
		{
			dat |= 0x80;
		}
		_delay_us(62);
	}
	ds_moi_bat_ngat=1;
	sei();
	return dat;
}
//========================================
unsigned char ds1820_doc_1(void)
{
	unsigned char i;
	unsigned char dat = 0;
	cli();
	for(i = 0;i < 8;i++)
	{
		ds1820_d1=1;
		_delay_us(2);
		ds1820_d1=0;
		_delay_us(4);
		dat = dat >> 1;
		if(ds1820_p1==1)
		{
			dat |= 0x80;
		}
		_delay_us(62);
	}
	ds_moi_bat_ngat=1;
	sei();
	return dat;
}
//========================================
#if so_ds > 1
unsigned char ds1820_doc_2(void)
{
	unsigned char i;
	unsigned char dat = 0;
	cli();
	for(i = 0;i < 8;i++)
	{
		ds1820_d2=1;
		_delay_us(2);
		ds1820_d2=0;
		_delay_us(4);
		dat = dat >> 1;
		if(ds1820_p2==1)
		{
			dat |= 0x80;
		}
		_delay_us(62);
	}
	ds_moi_bat_ngat=1;
	sei();
	return dat;
}
#endif
//========================================
#if so_ds > 2
unsigned char ds1820_doc_3(void)
{
	unsigned char i;
	unsigned char dat = 0;
	cli();
	for(i = 0;i < 8;i++)
	{
		ds1820_d3=1;
		_delay_us(2);
		ds1820_d3=0;
		_delay_us(4);
		dat = dat >> 1;
		if (ds1820_p3==1)
		{
			dat |= 0x80;
		}
		_delay_us(62);
	}
	ds_moi_bat_ngat=1;
	sei();
	return dat;
}
#endif
//========================================
#if so_ds > 2
unsigned char ds1820_doc_4(void)
{
	unsigned char i;
	unsigned char dat = 0;
	cli();
	for(i = 0;i < 8;i++)
	{
		ds1820_d4=1;
		_delay_us(2);
		ds1820_d4=0;
		_delay_us(4);
		dat = dat >> 1;
		if (ds1820_p4==1)
		{
			dat |= 0x80;
		}
		_delay_us(62);
	}
	ds_moi_bat_ngat=1;
	sei();
	return dat;
}
#endif
//========================================
unsigned char read_18b20_1(void)
{
	unsigned char i;
	unsigned char dat = 0;
	for(i = 0;i < 8;i++)
	{
		ds1820_d1=ra;
		_delay_us(2);
		ds1820_d1=vao;
		_delay_us(4);
		dat = dat >> 1;
		if(ds1820_p1==1)
		{
			dat |= 0x80;
		}
		_delay_us(62);
	}
	return dat;
}
//========================================
#if so_ds > 1
unsigned char read_18b20_2(void)
{
	unsigned char i;
	unsigned char dat = 0;
	for(i = 0;i < 8;i++)
	{
		ds1820_d2=ra;
		_delay_us(2);
		ds1820_d2=vao;
		_delay_us(4);
		dat = dat >> 1;
		if(ds1820_p2==1)
		{
			dat |= 0x80;
		}
		_delay_us(62);
	}
	return dat;
}
#endif
//======================================== 
#if so_ds > 2
unsigned char read_18b20_3(void)
{
	unsigned char i;
	unsigned char dat = 0;
	for(i = 0;i < 8;i++)
	{
		ds1820_d3=ra;
		_delay_us(2);
		ds1820_d3=vao;
		_delay_us(4);
		dat = dat >> 1;
		if(ds1820_p3==1)
		{
			dat |= 0x80;
		}
		_delay_us(62);
	}
	return dat;
}
#endif
//========================================
void ghi_1820_1(unsigned char dat)
{
	unsigned char i;
	cli();
	for(i = 0;i < 8;i++)
	{
		ds1820_d1=1;
		_delay_us(2);
		if(dat & 0x01)
		{
			ds1820_d1=0;
		}
		else
		{
			ds1820_d1=1;
		}
		dat = dat >> 1;
		_delay_us(62);
		ds1820_d1=0;
		_delay_us(2);
	}
	ds_moi_bat_ngat=1;
	sei();
}
//========================================
#if so_ds > 2
void ds1820_ghi_x3(unsigned char dat)
{
	unsigned char i;
	cli();
	for(i = 0;i < 8;i++)
	{
		ds1820_d1=1;
		ds1820_d2=1;
		ds1820_d3=1;
		_delay_us(2);
		if(dat & 0x01)
		{
			ds1820_d1=0;
			ds1820_d2=0;
			ds1820_d3=0;
		}
		else
		{
			ds1820_d1=1;
			ds1820_d2=1;
			ds1820_d3=1;
		}
		dat = dat >> 1;
		_delay_us(62);
		ds1820_d1=0;
		ds1820_d2=0;
		ds1820_d3=0;
		_delay_us(2);
	}
	ds_moi_bat_ngat=1;
	sei();
}
#endif
//========================================
#if so_ds==4
void ds1820_ghi_x4(unsigned char dat)
{
	unsigned char i;
	cli();
	for(i = 0;i < 8;i++)
	{
		ds1820_d1=1;
		ds1820_d2=1;
		ds1820_d3=1;
		ds1820_d4=1;
		_delay_us(2);
		if(dat & 0x01)
		{
			ds1820_d1=0;
			ds1820_d2=0;
			ds1820_d3=0;
			ds1820_d4=0;
		}
		else
		{
			ds1820_d1=1;
			ds1820_d2=1;
			ds1820_d3=1;
			ds1820_d4=1;
		}
		dat = dat >> 1;
		_delay_us(62);
		ds1820_d1=0; 
		ds1820_d2=0;
		ds1820_d3=0;
		ds1820_d4=0;
		_delay_us(2);
	} 
	ds_moi_bat_ngat=1;
	sei();
}
#endif
//========================================
//#if so_ds==0
void write_18b20_1(unsigned char dat)
{
	unsigned char i;
	for(i = 0;i < 8;i++)
	{
		ds1820_d1=ra;
		_delay_us(2);
		if(dat & 0x01)
		{
			ds1820_d1=vao;
		}
		else
		{
			ds1820_d1=ra;
		}
		dat = dat >> 1;
		_delay_us(62);
		ds1820_d1=vao;
		_delay_us(2);
	}
}
//#endif
//========================================
#if so_ds > 1
void write_18b20_2(unsigned char dat)
{
	unsigned char i;
	for(i = 0;i < 8;i++)
	{
		ds1820_d2=ra;
		_delay_us(2);
		if(dat & 0x01)
		{
			ds1820_d2=vao;
		}
		else
		{
			ds1820_d2=ra;
		}
		dat = dat >> 1;
		_delay_us(62);
		ds1820_d2=vao;
		_delay_us(2);
	}
}
#endif
//========================================
#if so_ds > 2
void write_18b20_3(unsigned char dat)
{
	unsigned char i;
	for(i = 0;i < 8;i++)
	{
		ds1820_d3=ra;
		_delay_us(2);
		if(dat & 0x01)
		{
			ds1820_d3=vao;
		}
		else
		{
			ds1820_d3=ra;
		}
		dat = dat >> 1;
		_delay_us(62);
		ds1820_d3=vao;
		_delay_us(2);
	}
}
#endif
//========================================
void write_18b20_x3(unsigned char dl)
{
	write_18b20_1(dl);
	write_18b20_2(dl);
	write_18b20_3(dl);
}
//========================================
void write_18b20_4(unsigned char dl)
{
	write_18b20_1(dl);
	write_18b20_2(dl);
	write_18b20_3(dl);
	write_18b20_4(dl);
}
//========================================
u16 doi_nhiet_do_ds18b20_f(u16 nd_ds) // chuyen doi gia tri nhiet do ds18b20 sang do F
{
	bool dau_nd;
	u8 nguyen_nd,tp_nd;
	if (nd_ds& 0x8000 )
	{
		dau_nd=1; // mark negative
		nd_ds ^= 0xffff;  // convert to positive => (twos complement)++
		nd_ds+=2;
	}
	else dau_nd=0;
	nguyen_nd  = (uint8_t)(nd_ds >> 4);
	tp_nd =(nd_ds & 0x000F)*10/16;
	nd_ds=nguyen_nd*10+tp_nd;
	if(dau_nd==0)
	{
		nd_ds=nd_ds*18+3200;
	}
	else
	nd_ds=3200-nd_ds*18;
	return chia_10(nd_ds);
}
//========================================
u16 doi_nhiet_do_ds18b20_c(u16 nd_ds) // chuyen doi gia tri nhiet do ds18b20 sang do F
{
	bool dau_nd;
	u8 nguyen_nd,tp_nd;
	if (nd_ds& 0x8000 )
	{
		dau_nd=1; // mark negative
		nd_ds ^= 0xffff;  // convert to positive => (twos complement)++
		nd_ds+=2;
	}
	else dau_nd=0;
	nguyen_nd  = (uint8_t)(nd_ds >> 4);
	tp_nd =(nd_ds & 0x000F)*10/16;
	nd_ds=nguyen_nd*10+tp_nd;
	//if(dau_nd==0)
	//{
		//nd_ds=nd_ds*18+3200;
	//}
	//else
	//nd_ds=3200-nd_ds*18;
	return (nd_ds);
}
u16 doi_nhiet_do_ds18b20_c_dau(u16 nd_ds) // chuyen doi gia tri nhiet do ds18b20 sang do C
{
	bool dau_nd;
	u8 nguyen_nd,tp_nd;
	if (nd_ds& 0x8000 )
	{
		dau_nd=1; // mark negative
		nd_ds ^= 0xffff;  // convert to positive => (twos complement)++
		nd_ds+=2;
	}
	else dau_nd=0;
	nguyen_nd  = (uint8_t)(nd_ds >> 4);
	tp_nd =(nd_ds & 0x000F)*10/16;
	nd_ds=nguyen_nd*10+tp_nd;
	if(dau_nd==0)
	{
		nd_ds=nd_ds+bu_c;
	}
	else
	{
		nd_ds=bu_c-nd_ds;
	}
	
	return (nd_ds);
}








/*
 * ds18b20 init
 */
uint8_t ds18b20_reset() {
	uint8_t i;

	//low for 480us
	DS18B20_PORT &= ~ (1<<DS18B20_DQ); //low
	DS18B20_DDR |= (1<<DS18B20_DQ); //output
	_delay_us(480);

	//release line and wait for 60uS
	DS18B20_DDR &= ~(1<<DS18B20_DQ); //input
	_delay_us(60);

	//get value and wait 420us
	i = (DS18B20_PIN & (1<<DS18B20_DQ));
	_delay_us(420);

	//return the read value, 0=ok, 1=error
	return i;
}

/*
 * write one bit
 */
void ds18b20_writebit(uint8_t bit){
	//low for 1uS
	DS18B20_PORT &= ~ (1<<DS18B20_DQ); //low
	DS18B20_DDR |= (1<<DS18B20_DQ); //output
	_delay_us(1);

	//if we want to write 1, release the line (if not will keep low)
	if(bit)
		DS18B20_DDR &= ~(1<<DS18B20_DQ); //input

	//wait 60uS and release the line
	_delay_us(60);
	DS18B20_DDR &= ~(1<<DS18B20_DQ); //input
}

/*
 * read one bit
 */
uint8_t ds18b20_readbit(void){
	uint8_t bit=0;

	//low for 1uS
	DS18B20_PORT &= ~ (1<<DS18B20_DQ); //low
	DS18B20_DDR |= (1<<DS18B20_DQ); //output
	_delay_us(1);

	//release line and wait for 14uS
	DS18B20_DDR &= ~(1<<DS18B20_DQ); //input
	_delay_us(14);

	//read the value
	if(DS18B20_PIN & (1<<DS18B20_DQ))
		bit=1;

	//wait 45uS and return read value
	_delay_us(45);
	return bit;
}

/*
 * write one byte
 */
void ds18b20_writebyte(uint8_t byte){
//	uint8_t i=8;
	for (u8 i=0;i<8;i++)
//	while(i--){
	{
		ds18b20_writebit(byte&1);
		byte >>= 1;
	}
}

/*
 * read one byte
 */
uint8_t ds18b20_readbyte(void){
	uint8_t i=8, n=0;
	while(i--){
		n >>= 1;
		n |= (ds18b20_readbit()<<7);
	}
	return n;
}

/*
 * get temperature
 */
double ds18b20_gettemp() {
	uint8_t temperature[2];
	int8_t digit;
	uint16_t decimal;
	double retd = 0;

	ds18b20_reset(); //reset
	ds18b20_writebyte(DS18B20_CMD_SKIPROM); //skip ROM
	ds18b20_writebyte(DS18B20_CMD_CONVERTTEMP); //start temperature conversion

	while(!ds18b20_readbit()); //wait until conversion is complete

	ds18b20_reset(); //reset
	ds18b20_writebyte(DS18B20_CMD_SKIPROM); //skip ROM
	ds18b20_writebyte(DS18B20_CMD_RSCRATCHPAD); //read scratchpad

	//read 2 byte from scratchpad
	temperature[0] = ds18b20_readbyte();
	temperature[1] = ds18b20_readbyte();

	ds18b20_reset(); //reset

	//store temperature integer digits
	digit = temperature[0]>>4;
	digit |= (temperature[1]&0x7)<<4;

	//store temperature decimal digits
	decimal = temperature[0]&0xf;
	decimal *= DS18B20_DECIMALSTEPS;

	//compose the double temperature value and return it
	retd = digit + decimal * 0.0001;

	return retd;
}

#endif
