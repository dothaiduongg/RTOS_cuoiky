/* DS3231 Real Time Clock AVR Lirary
 *
 * Copyright (C) 2016-2017 Sergey Denisov.
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public Licence
 * as published by the Free Software Foundation; either version 3
 * of the Licence, or (at your option) any later version.
 *
 * Original library written by Adafruit Industries. MIT license.
 */

#ifndef __DS3231_H__
#define __DS3231_H__
#include "!/1 thoi gian.h"
#include <stdio.h>

#define RTC_WADDR 0b11010000
#define RTC_RADDR 0b11010001

#include "i2csoft.c"

struct rtc_time
{
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
};

struct rtc_date
{
	uint8_t wday;
	uint8_t day;
	uint8_t month;
	uint8_t year;
};

/*
 * Clock initialization
 */

void ds3231_init(void);

/**
 * Reading time from clock
 * @time: time structure with reading data
 */
void ds3231_read_time(struct rtc_time *time);

/**
 * Reading date from clock
 * @date: date structure with reading data
 */
void ds3231_read_date(struct rtc_date *date);

/**
 * Reading date and time from clock
 * @time: time structure with reading data
 * @date: date structure with reading data
 */
void ds3231_read_datetime(struct rtc_time *time, struct rtc_date *date);

/**
 * Writing new time in clock
 * @time: time structure for writing data
 */
void ds3231_write_time(struct rtc_time *time);

/**
 * Writing new date in clock
 * @date: date structure for writing data
 */
void ds3231_write_date(struct rtc_date *date);


#endif
static unsigned char bcd (unsigned char data)
{
	unsigned char bc;

	bc = ((((data & (1 << 6)) | (data & (1 << 5)) | (data & (1 << 4)))*0x0A) >> 4)
	+ ((data & (1 << 3))|(data & (1 << 2))|(data & (1 << 1))|(data & 0x01));

  return bc;
}

static unsigned char bin(unsigned char dec)
{
	char bcd;
	char n, dig, num, count;

	num = dec;
	count = 0;
	bcd = 0;

	for (n = 0; n < 4; n++) {
		dig = num % 10;
		num = num / 10;
		bcd = (dig << count) | bcd;
		count += 4;
	}
	return bcd;
}


void ds3231_init(void)
{
	SoftI2CStart();
	SoftI2CWriteByte(RTC_WADDR);
	SoftI2CWriteByte(0x0E);
	SoftI2CWriteByte(0x20);
	SoftI2CWriteByte(0x08);
	ds3231_dat_pin(1,0);
	SoftI2CStop();
}

void ds3231_read_time(struct rtc_time *time)
{
	SoftI2CStart();
	SoftI2CWriteByte(RTC_WADDR);
	SoftI2CWriteByte(0x00);
	SoftI2CStop();

	SoftI2CStart();
	i2c_send_byte(RTC_RADDR);
	time->sec = bcd(i2c_recv_byte());
	time->min = bcd(i2c_recv_byte());
	time->hour = bcd(i2c_recv_byte());
	SoftI2CStop();
}

void ds3231_read_date(struct rtc_date *date)
{
	SoftI2CStart();
	i2c_send_byte(RTC_WADDR);
	i2c_send_byte(0x00);
	SoftI2CStop();

	SoftI2CStart();
	i2c_send_byte(RTC_RADDR);
	bcd(i2c_recv_byte());
	bcd(i2c_recv_byte());
	bcd(i2c_recv_byte());

	date->wday = bcd(i2c_recv_byte());
	date->day = bcd(i2c_recv_byte());
	date->month = bcd(i2c_recv_byte());
	date->year = bcd(i2c_recv_last_byte());
	SoftI2CStop();
}

void ds3231_read_datetime(struct rtc_time *time, struct rtc_date *date)
{
	SoftI2CStart();
	SoftI2CWriteByte(RTC_WADDR);
	SoftI2CWriteByte(0x00);
	SoftI2CStop();

	SoftI2CStart();
	i2c_send_byte(RTC_RADDR);
	time->sec = bcd(i2c_recv_byte());
	time->min = bcd(i2c_recv_byte());
	time->hour = bcd(i2c_recv_byte());

	date->wday = bcd(i2c_recv_byte());
	date->day = bcd(i2c_recv_byte());
	date->month = bcd(i2c_recv_byte());
	date->year = bcd(i2c_recv_last_byte());
	SoftI2CStop();
}

void ds3231_write_time(struct rtc_time *time)
{
    SoftI2CStart();
    SoftI2CWriteByte(RTC_WADDR);
    SoftI2CWriteByte(0x00);
    SoftI2CWriteByte(bin(time->sec));
	SoftI2CWriteByte(bin(time->min));
    SoftI2CWriteByte(bin(time->hour));
    SoftI2CStop();
}

void ds3231_write_date(struct rtc_date *date)
{
	SoftI2CStart();
    SoftI2CWriteByte(RTC_WADDR);
    SoftI2CWriteByte(0x03);
    SoftI2CWriteByte(bin(date->wday));
    SoftI2CWriteByte(bin(date->day));
	SoftI2CWriteByte(bin(date->month));
	SoftI2CWriteByte(bin(date->year));
    SoftI2CStop();
}

#ifndef DS3231_h
#define DS3231_h


#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>


#define  DS3231_ADDRESS      0x68
#define  DS3231_REG_SEC		 0x00
#define  DS3231_REG_MIN		 0x01
#define  DS3231_REG_HOUR     0x02
#define  DS3231_REG_DOW		 0x03
#define  DS3231_REG_DATE     0x04
#define  DS3231_REG_MON		 0x05
#define  DS3231_REG_YEAR     0x06
#define  DS3231_REG_CON		 0x0E
#define  DS3231_REG_STATUS	 0x0F
#define  DS3231_REG_AGING	 0x10
#define  DS3231_REG_TEMPM	 0x11
#define  DS3231_REG_TEMPL	 0x12


// Convert normal decimal numbers to binary coded decimal
uint8_t decimalToBcd(uint8_t val){
	return( (val/10*16) + (val%10) );
}

// Convert binary coded decimal to normal decimal numbers
uint8_t bcdToDec(uint8_t val){
	return( (val/16*10) + (val%16) );
}



void DS3231_setTime(uint8_t second, uint8_t minute,uint8_t hour,
uint8_t dayOfWeek,
uint8_t dayOfMonth,
uint8_t month,
uint8_t year){
	
	cli();
	SoftI2CStart();
	SoftI2CWriteByte(DS3231_ADDRESS<<1|0);
	SoftI2CWriteByte(0x00);    //move pointer location 0 which is seconds
	SoftI2CWriteByte(decimalToBcd(second));
	SoftI2CWriteByte(decimalToBcd(minute));
	SoftI2CWriteByte(decimalToBcd(hour));
	SoftI2CWriteByte(decimalToBcd(dayOfWeek));
	SoftI2CWriteByte(decimalToBcd(dayOfMonth));
	SoftI2CWriteByte(decimalToBcd(month));
	SoftI2CWriteByte(decimalToBcd(year));
	SoftI2CStop();
	
	
	sei();
}

void DS3231_getTime()
{
	
	SoftI2CStart();
	SoftI2CWriteByte(DS3231_ADDRESS<<1|0);
	SoftI2CWriteByte(0x00);            // set DS3231 register pointer to 00h
	SoftI2CStop();
	
	SoftI2CStart();
	SoftI2CWriteByte(DS3231_ADDRESS<<1|1);
	
	giay     = bcdToDec(SoftI2CReadByte(1) & 0x7f);
	phut     = bcdToDec(SoftI2CReadByte(1));
	gio       = bcdToDec(SoftI2CReadByte(1) & 0x3f);
	thu  = bcdToDec(SoftI2CReadByte(1));
	ngay = bcdToDec(SoftI2CReadByte(1));
	thang      = bcdToDec(SoftI2CReadByte(1));
	nam       = bcdToDec(SoftI2CReadByte(0));
	
}


float DS3231_getTemperature(void){
	//    uint8_t _msb = _readRegister(REG_TEMPM);
	//    uint8_t _lsb = _readRegister(REG_TEMPL);
	//    return (float)_msb + ((_lsb >> 6) * 0.25f);
	
	uint8_t tmpMsbbuf[1];
	uint8_t tmpLsbbuf[1];

	twi_read(DS3231_ADDRESS, 1, DS3231_REG_TEMPM, tmpMsbbuf);
	twi_read(DS3231_ADDRESS, 1, DS3231_REG_TEMPL, tmpLsbbuf);
	
	return (float)tmpMsbbuf[0] + ((tmpLsbbuf[0] >> 6) * 0.25f);
}

//========================================
u8 DS3231_doc_byte(u8 dia_chi)
{
	cli();
	SoftI2CStart();
	SoftI2CWriteByte(RTC_WADDR);
	SoftI2CWriteByte(dia_chi); // Start at REG 0 - Seconds
	SoftI2CStart();
	SoftI2CWriteByte(RTC_RADDR);
	dia_chi = SoftI2CReadByte(0);
	SoftI2CStop();
	sei();
	return dia_chi;
}
//========================================
void DS3231_ghi_byte(uint8_t dia_chi,uint8_t du_lieu)
{
	cli();
	SoftI2CStart();
	SoftI2CWriteByte(RTC_WADDR);	//DS1307 address + W
	SoftI2CWriteByte(dia_chi);
	SoftI2CWriteByte(du_lieu);
	SoftI2CStop();
	sei();
}
//========================================
void ds3231_dat_ntndpd()
{
	cli();
	DS3231_ghi_byte(0,bin2bcd(giay));
	delay_ms(1); // tao thoi gian tre ms
	DS3231_ghi_byte(1,bin2bcd(phut));
	delay_ms(1); // tao thoi gian tre ms
	DS3231_ghi_byte(2,bin2bcd(gio));
	delay_ms(1); // tao thoi gian tre ms
	DS3231_ghi_byte(4,bin2bcd(ngay));
	delay_ms(1); // tao thoi gian tre ms
	DS3231_ghi_byte(5,bin2bcd(thang));
	delay_ms(1); // tao thoi gian tre ms
	DS3231_ghi_byte(6,bin2bcd(nam));
	delay_ms(1); // tao thoi gian tre ms
	sei();
}
//========================================
void ds3231_doc_dpd()
{
	u8 d,p,da;
	da=bcd2bin(DS3231_doc_byte(0));
	p=bcd2bin(DS3231_doc_byte(1));
	d=bcd2bin(DS3231_doc_byte(2));
	if(da<60&&p<60&&d<24)
	{
		giay = da;
		phut = p;
		gio = d;
	}
}
//========================================
void ds3231_doc_ntn()
{
	u8 n,t,na;
	n=bcd2bin(DS3231_doc_byte(4));
	t=bcd2bin(DS3231_doc_byte(5));
	na=bcd2bin(DS3231_doc_byte(6));
	if(n<32&&t<13&&n<100)
	{
		ngay = n;
		thang = t;
		nam = na;
	}
}
#endif /* DS3231_h */

void ds3231_dat_pin(u8 timeBattery, u8 squareBattery)
{
	uint8_t value;

	value = DS3231_doc_byte(0x0e);

	if (squareBattery==1)
	{
		value |= 0b01000000;
	} else
	{
		value &= 0b10111111;
	}

	if (timeBattery==1)
	{
		value &= 0b01111011;
	} else
	{
		value |= 0b10000000;
	}

	DS3231_ghi_byte(0x0e, value);
}