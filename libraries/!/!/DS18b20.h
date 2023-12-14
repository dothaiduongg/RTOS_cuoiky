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
	#define DS18B20_PORT PORTC
	#define DS18B20_DDR DDRC
	#define DS18B20_PIN PINC
	#define DS18B20_DQ PC1
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

#endif
