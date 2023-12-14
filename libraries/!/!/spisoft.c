/**********************************************************

Software I2C Library for AVR Devices.

Copyright 2008-2012
eXtreme Electronics, India
www.eXtremeElectronics.co.in 
**********************************************************/
#ifndef _spisoft_c
#define _spisoft_c
#include <stdint.h>
#include <avr/io.h>

u8 spi_transmit(u8 dl);
void spi_init();
#ifndef mi_p
#define mi_p dk_bit(PORTC,2)
#define mi dk_bit(PINC,2)
#define mi_d dk_bit(DDRC,2)
#define mo dk_bit(PORTC,3)
#define mo_d dk_bit(DDRC,3)
#define ckspi dk_bit(PORTC,4)
#define ckspi_d dk_bit(DDRC,4)
#endif

//======================================== 
void spi_init()
{
	mo_d=ra;
	ckspi_d=ra;
	mi=vao;
	mi_p=1;
}
//======================================== 
u8 spi_transmit(u8 dl)
{
	u8 i;
	u8 dl2=dl;
	for(i=0;i<8;i++)
	{
		dl2<<=1;
		mo=(dl&0x80)?1:0;
		ckspi=1;
		dl2|=mi;
		ckspi=0;
		dl<<=1;
	}
	return dl2;
}
//========================================
u8 spi_transmit1(u8 dl)
{
	u8 i;
	u8 dl2=dl;
	for(i=0;i<8;i++)
	{
		dl2<<=1;
		mo=(dl&0x80)?1:0;
		ckspi=1;
		ckspi=0;
		dl2|=mi;
		dl<<=1;
	}
	return dl2;
}
//========================================
u8 spi_transmit2(u8 dl)
{
	u8 i;
	u8 dl2=dl;
	for(i=0;i<8;i++)
	{
		dl2<<=1;
		mo=(dl&0x80)?1:0;
		ckspi=0;
		dl2|=mi;
		ckspi=1;
		dl<<=1;
	}
	return dl2;
}
//========================================
u8 spi_transmit3(u8 dl)
{
	u8 i;
	u8 dl2=dl;
	for(i=0;i<8;i++)
	{
		dl2<<=1;
		mo=(dl&0x80)?1:0;
		ckspi=0;
		ckspi=1;
		dl2|=mi;
		dl<<=1;
	}
	return dl2;
}
#endif















