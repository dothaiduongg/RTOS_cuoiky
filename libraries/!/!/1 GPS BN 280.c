

/*#ifndef TinyGPS_h*/
#define TinyGPS_h

// #if defined(ARDUINO) && ARDUINO >= 100
// #include "Arduino.h"
// #else
// #include "WProgram.h"
// #endif

#include <stdlib.h>
u8 co_232=0;
// #define _GPS_VERSION 13 // software version of this library
// #define _GPS_MPH_PER_KNOT 1.15077945
// #define _GPS_MPS_PER_KNOT 0.51444444
// #define _GPS_KMPH_PER_KNOT 1.852
// #define _GPS_MILES_PER_METER 0.00062137112
// #define _GPS_KM_PER_METER 0.001
// #define _GPS_NO_STATS


// u32 GPS_INVALID_AGE = 0xFFFFFFFF;
// u32 GPS_INVALID_ANGLE = 999999999;
// u32 GPS_INVALID_ALTITUDE = 999999999;
// u32 GPS_INVALID_DATE = 0;
// u32 GPS_INVALID_TIME = 0xFFFFFFFF;
// u32 GPS_INVALID_SPEED = 999999999;
// u32 GPS_INVALID_FIX_TIME = 0xFFFFFFFF;
// u32 GPS_INVALID_SATELLITES = 0xFF;
// u32 GPS_INVALID_HDOP = 0xFFFFFFFF;

//   static const float GPS_INVALID_F_ANGLE, GPS_INVALID_F_ALTITUDE, GPS_INVALID_F_SPEED;
// 
//   void TinyGPS();
//   bool encode(char c); // process one character received from GPS
//   TinyGPS &operator << (char c) {encode(c); return *this;}
// 
//   // lat/long in MILLIONTHs of a degree and age of fix in milliseconds
//   // (note: versions 12 and earlier gave lat/long in 100,000ths of a degree.
//   void get_position(long *latitude, long *longitude, unsigned long *fix_age = 0);
// 
//   // date as ddmmyy, time as hhmmsscc, and age in milliseconds
   void get_datetime(unsigned long *date, unsigned long *time, unsigned long *age);

   unsigned long _time, _new_time;
   unsigned long _date, _new_date;
//   long _latitude, _new_latitude;
//   long _longitude, _new_longitude;
//   long _altitude, _new_altitude;
//   unsigned long  _speed, _new_speed;
//   unsigned long  _course, _new_course;
//   unsigned long  _hdop, _new_hdop;
//   unsigned short _numsats, _new_numsats;
// 
//   unsigned long _last_time_fix, _new_time_fix;
//   unsigned long _last_position_fix, _new_position_fix;
// 
//   // parsing state variables
//   byte _parity;
//   bool _is_checksum_term;
//   char _term[15];
//   byte _sentence_type;
//   byte _term_number;
//   byte _term_offset;
//   bool _gps_data_good;
// 
// #ifndef _GPS_NO_STATS
//   // statistics
//   unsigned long _encoded_characters;
//   unsigned short _good_sentences;
//   unsigned short _failed_checksum;
//   unsigned short _passed_checksum;
// #endif
// 
//   // internal utilities
//   int from_hex(char a);
//   unsigned long parse_decimal();
//   unsigned long parse_degrees();
//   bool term_complete();
//   bool gpsisdigit(char c) { return c >= '0' && c <= '9'; }
//   long gpsatol(const char *str);
//   int gpsstrcmp(const char *str1, const char *str2);
// /*};*/
// 
// #if !defined(ARDUINO) 
// // Arduino 0012 workaround
// #undef int
// #undef char
// #undef long
// #undef byte
// #undef float
// #undef abs
// #undef round 
// #endif
// 
// #endif
// 
// 
// 
// 



/*#include "TinyGPS.h"*/
// 
// #define _GPRMC_TERM   "GPRMC"
// #define _GPGGA_TERM   "GPGGA"
// 
// TinyGPS()
//   :  _time(GPS_INVALID_TIME)
//   ,  _date(GPS_INVALID_DATE)
//   ,  _latitude(GPS_INVALID_ANGLE)
//   ,  _longitude(GPS_INVALID_ANGLE)
//   ,  _altitude(GPS_INVALID_ALTITUDE)
//   ,  _speed(GPS_INVALID_SPEED)
//   ,  _course(GPS_INVALID_ANGLE)
//   ,  _hdop(GPS_INVALID_HDOP)
//   ,  _numsats(GPS_INVALID_SATELLITES)
//   ,  _last_time_fix(GPS_INVALID_FIX_TIME)
//   ,  _last_position_fix(GPS_INVALID_FIX_TIME)
//   ,  _parity(0)
//   ,  _is_checksum_term(false)
//   ,  _sentence_type(_GPS_SENTENCE_OTHER)
//   ,  _term_number(0)
//   ,  _term_offset(0)
//   ,  _gps_data_good(false)
// #ifndef _GPS_NO_STATS
//   ,  _encoded_characters(0)
//   ,  _good_sentences(0)
//   ,  _failed_checksum(0)
// #endif
// {
//   _term[0] = '\0';
// }
// 
// //
// // public methods
// //
// 
// bool encode()
// {
//   bool valid_sentence = false;
// 
// #ifndef _GPS_NO_STATS
//   ++_encoded_characters;
// #endif
//   switch(c)
//   {
//   case ',': // term terminators
//     _parity ^= c;
//   case '\r':
//   case '\n':
//   case '*':
//     if (_term_offset < sizeof(_term))
//     {
//       _term[_term_offset] = 0;
//       valid_sentence = term_complete();
//     }
//     ++_term_number;
//     _term_offset = 0;
//     _is_checksum_term = c == '*';
//     return valid_sentence;
// 
//   case '$': // sentence begin
//     _term_number = _term_offset = 0;
//     _parity = 0;
//     _sentence_type = _GPS_SENTENCE_OTHER;
//     _is_checksum_term = false;
//     _gps_data_good = false;
//     return valid_sentence;
//   }
// 
//   // ordinary characters
//   if (_term_offset < sizeof(_term) - 1)
//     _term[_term_offset++] = c;
//   if (!_is_checksum_term)
// 
// // date as ddmmyy, time as hhmmsscc, and age in milliseconds
void get_datetime_m8(unsigned long *date, unsigned long *time, unsigned long *age)
{
  if (date) *date = _date;
  if (time) *time = _time;
}
// 
// void f_get_position(float *latitude, float *longitude, unsigned long *fix_age)
// {
//   long lat, lon;
//   get_position(&lat, &lon, fix_age);
//   *latitude = lat == GPS_INVALID_ANGLE ? GPS_INVALID_F_ANGLE : (lat / 1000000.0);
//   *longitude = lat == GPS_INVALID_ANGLE ? GPS_INVALID_F_ANGLE : (lon / 1000000.0);
// }
// 
void crack_datetime_m8(int *year, byte *month, byte *day, 
  byte *hour, byte *minute, byte *second, byte *hundredths, unsigned long *age)
{
  unsigned long date, time;
  get_datetime(&date, &time, age);
  if (year) 
  {
    *year = date % 100;
    *year += *year > 80 ? 1900 : 2000;
  }
  if (month) *month = (date / 100) % 100;
  if (day) *day = date / 10000;
  if (hour) *hour = time / 1000000;
  if (minute) *minute = (time / 10000) % 100;
  if (second) *second = (time / 100) % 100;
  if (hundredths) *hundredths = time % 100;
}
// 




#ifndef kai_bao_tg_gps
#define kai_bao_tg_gps
u8 gio1,gio2;
u8 phut1,phut2;
u8 giay1,giay2;
u8 ngay1,ngay2;
u8 thang1,thang2;
u8 nam1,nam2;
u8 ma_kt;
u8 dl;
u8 co_dl=0;
u8 tt_dl=0;
const u8 bag_ma_kt_m6[7] = {"$GPRMC,"};
#endif
const u8 bag_ma_kt_m8[7] = {"$GNRMC,"};

//$GNRMC,024759.00,A,1052.51417,N,10638.10660,E,2.027,,240220,,,A*6F

#ifndef thu_232_gps
#define thu_232_gps
ISR(USART_RXC_vect)
{
	#if  defined(__AVR_ATmega8__)  || defined(__AVR_ATmega16__) || defined(__AVR_ATmega32__) \
	|| defined(__AVR_ATmega8515__) || defined(__AVR_ATmega8535__) \
	|| defined(__AVR_ATmega323__)
	co_232 = 1;
	dl = UDR; // TB co gia tri du lieu nhan duoc
	if(co_dl==0)
	{
		if(dl==bag_ma_kt_m8[tt_dl]||dl==bag_ma_kt_m6[tt_dl])
		{
			if(tt_dl==6)
			{
				co_dl=1;
				tt_dl=0;
			}
			else
			tt_dl++;
		}
		else
		{
			tt_dl=0;
		}
	}
	else
	if(co_dl==1)
	{
		if(dl==',')
		{
			co_dl=0;
			tt_dl=0;
		}
		else
		{
			gio1=dl;
			co_dl=2;
		}
	}
	else
	if(co_dl==2)
	{
		if(dl==',')
		{
			co_dl=0;
			tt_dl=0;
		}
		else
		{
			gio2=dl;
			co_dl=3;
		}
	}
	else
	if(co_dl==3)
	{
		if(dl==',')
		{
			co_dl=0;
			tt_dl=0;
		}
		else
		{
			phut1=dl;
			co_dl=4;
		}
	}
	else
	if(co_dl==4)
	{
		if(dl==',')
		{
			co_dl=0;
			tt_dl=0;
		}
		else
		{
			phut2=dl;
			co_dl=5;
		}
	}
	else
	
	if(co_dl==5)
	{
		if(dl==',')
		{
			co_dl=0;
			tt_dl=0;
		}
		else
		{
			giay1=dl;
			co_dl=6;
		}
	}
	else
	if(co_dl==6)
	{
		if(dl==',')
		{
			co_dl=0;
			tt_dl=0;
		}
		else
		{
			giay2=dl;
			co_dl=7;
		}
	}
	else
	if(co_dl==7)
	{
		if(dl==',')
		{
			if(tt_dl==7)
			{
				co_dl=8;
				tt_dl=0;
			}
			else
			tt_dl++;
		}
	}
	else
	switch (co_dl)
	{
		case 8:
		if(dl==',')
		{
			co_dl=0;
			tt_dl=0;
		}
		else
		{ngay1=dl;co_dl=9;}break;
		case 9:
		if(dl==',')
		{
			co_dl=0;
			tt_dl=0;
		}
		else
		{ngay2=dl;co_dl=10;}break;
		case 10:
		if(dl==',')
		{
			co_dl=0;
			tt_dl=0;
		}
		else
		{thang1=dl;co_dl=11;}break;
		case 11:
		if(dl==',')
		{
			co_dl=0;
			tt_dl=0;
		}
		else
		{thang2=dl;co_dl=12;}break;
		case 12:
		if(dl==',')
		{
			co_dl=0;
			tt_dl=0;
		}
		else
		{nam1=dl;co_dl=13;}break;
		case 13:
		if(dl==',')
		{
			co_dl=0;
			tt_dl=0;
		}
		else
		{nam2=dl;co_dl=14;}break;
	}
	out_time_232 = tg_out_232; // thoi gian out cho 1 chuoi du lieu la 50 ms
	#endif
}

ISR(USART_RX_vect)
{
	#if  defined(__AVR_ATmega328__)||defined(__AVR_ATmega328A__)
	co_232 = 1;
	dl = UDR0; // TB co gia tri du lieu nhan duoc
	if(co_dl==0)
	{
		if(dl==bag_ma_kt_m8[tt_dl]||dl==bag_ma_kt_m6[tt_dl])
		{
			if(tt_dl==6)
			{
				co_dl=1;
				tt_dl=0;
			}
			else
				tt_dl++;
		}
		else
		{
			tt_dl=0;
		}
	}
	else
	if(co_dl==1)
	{
		if(dl==',')
		{
			co_dl=0;
			tt_dl=0;
		}
		else
		{
			gio1=dl;
			co_dl=2;
		}
	}
	else
	if(co_dl==2)
	{
		if(dl==',')
		{
			co_dl=0;
			tt_dl=0;
		}
		else
		{
			gio2=dl;
			co_dl=3;
		}
	}
	else
	if(co_dl==3)
	{
		if(dl==',')
		{
			co_dl=0;
			tt_dl=0;
		}
		else
		{
			phut1=dl;
			co_dl=4;
		}
	}
	else
	if(co_dl==4)
	{
		if(dl==',')
		{
			co_dl=0;
			tt_dl=0;
		}
		else
		{
			phut2=dl;
			co_dl=5;
		}
	}
	else
	
	if(co_dl==5)
	{
		if(dl==',')
		{
			co_dl=0;
			tt_dl=0;
		}
		else
		{
			giay1=dl;
			co_dl=6;
		}
	}
	else
	if(co_dl==6)
	{
		if(dl==',')
		{
			co_dl=0;
			tt_dl=0;
		}
		else
		{
			giay2=dl;
			co_dl=7;
		}
	}
	else
	if(co_dl==7)
	{
		if(dl==',')
		{
			if(tt_dl==7)
			{
				co_dl=8;
				tt_dl=0;
			}
			else
			tt_dl++;
		}
	}
	else
	switch (co_dl)
	{
		case 8:
		if(dl==',')
		{
			co_dl=0;
			tt_dl=0;
		}
		else
		{ngay1=dl;co_dl=9;}break;
		case 9:
		if(dl==',')
		{
			co_dl=0;
			tt_dl=0;
		}
		else
		{ngay2=dl;co_dl=10;}break;
		case 10:
		if(dl==',')
		{
			co_dl=0;
			tt_dl=0;
		}
		else
		{thang1=dl;co_dl=11;}break;
		case 11:
		if(dl==',')
		{
			co_dl=0;
			tt_dl=0;
		}
		else
		{thang2=dl;co_dl=12;}break;
		case 12:
		if(dl==',')
		{
			co_dl=0;
			tt_dl=0;
		}
		else
		{nam1=dl;co_dl=13;}break;
		case 13:
		if(dl==',')
		{
			co_dl=0;
			tt_dl=0;
		}
		else
		{nam2=dl;co_dl=14;}break;
	}
	out_time_232 = tg_out_232; // thoi gian out cho 1 chuoi du lieu la 50 ms
	#endif
}
#endif
//======================================== 
u8 so_sah_so(u8 s)
{
	if(s>=0x30&&s<=0x39)
	{
		s=1;
	}
	else
	{
		s=0;
	}
	return s;
}
//======================================== 
u8 chuyen_doi_thoi_dan_bn280()
{
	u8 loi=1;
	if(co_dl==14)
	{
		co_dl=0;
		if(so_sah_so(gio1)&&so_sah_so(gio2)&&so_sah_so(phut1)&&so_sah_so(phut2)&&
		so_sah_so(giay1)&&so_sah_so(giay2)&&so_sah_so(ngay1)&&so_sah_so(ngay2)&&
		so_sah_so(thang1)&&so_sah_so(thang2)&&so_sah_so(nam1)&&so_sah_so(nam2))
		{
			loi=0;
		}
		if(loi==0)
		{
			gio0=(gio1-0x30)*10+(gio2-0x30);
			phut0=(phut1-0x30)*10+(phut2-0x30);
			giay0=(giay1-0x30)*10+(giay2-0x30);
			ngay0=(ngay1-0x30)*10+(ngay2-0x30);
			thang0=(thang1-0x30)*10+(thang2-0x30);
			nam0=(nam1-0x30)*10+(nam2-0x30);
		}
		if(gio0>23) loi=1;
		if(phut0>59) loi=1;
		if(giay0>59) loi=1;
		if(ngay0>31) loi=1;
		if(thang0>12) loi=1;
		if(nam0<18||nam>30) loi=1;
	}
	return loi;
}
//======================================== 
#ifndef doi_zone_gps
#define doi_zone_gps
void doi_zone_utc_7c()
{
	u8 cog=0;
	do0=do0+7;
	if(do0>=24)
	{
		do0=do0-24;
		ngay0++;
		if(ngay0>tinh_ngay_theo_thag(thag0,nam0))
		{
			ngay0=1;
			thag0++;
			if(thag0>12)
			{
				thag0=1;
				nam0++;
			}
		}
	}
}
#endif