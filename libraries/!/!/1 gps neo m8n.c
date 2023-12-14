
#include <!/! LDN.h>
/*#ifndef TinyGPS_h*/
#define TinyGPS_h

// #if defined(ARDUINO) && ARDUINO >= 100
// #include "Arduino.h"
// #else
// #include "WProgram.h"
// #endif

#include <stdlib.h>

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
// 
//   // signed altitude in centimeters (from GPGGA sentence)
//   inline long altitude() { return _altitude; }
// 
//   // course in last full GPRMC sentence in 100th of a degree
//   inline unsigned long course() { return _course; }
// 
//   // speed in last full GPRMC sentence in 100ths of a knot
//   inline unsigned long speed() { return _speed; }
// 
//   // satellites used in last full GPGGA sentence
//   inline unsigned short satellites() { return _numsats; }
// 
//   // horizontal dilution of precision in 100ths
//   inline unsigned long hdop() { return _hdop; }
// 
//   void f_get_position(float *latitude, float *longitude, unsigned long *fix_age = 0);
//   void crack_datetime(int *year, byte *month, byte *day, 
//     byte *hour, byte *minute, byte *second, byte *hundredths = 0, unsigned long *fix_age = 0);
//   float f_altitude();
//   float f_course();
//   float f_speed_knots();
//   float f_speed_mph();
//   float f_speed_mps();
//   float f_speed_kmph();
// 
//   static int library_version() { return _GPS_VERSION; }
// 
//   static float distance_between (float lat1, float long1, float lat2, float long2);
//   static float course_to (float lat1, float long1, float lat2, float long2);
//   static const char *cardinal(float course);
// 
// #ifndef _GPS_NO_STATS
//   void stats(unsigned long *chars, unsigned short *good_sentences, unsigned short *failed_cs);
// #endif
// 
// //private: 
//   enum {_GPS_SENTENCE_GPGGA, _GPS_SENTENCE_GPRMC, _GPS_SENTENCE_OTHER};
// 
//   // properties
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
//     _parity ^= c;
// 
//   return valid_sentence;
// }
// 
// #ifndef _GPS_NO_STATS
// void stats(unsigned long *chars, unsigned short *sentences, unsigned short *failed_cs)
// {
//   if (chars) *chars = _encoded_characters;
//   if (sentences) *sentences = _good_sentences;
//   if (failed_cs) *failed_cs = _failed_checksum;
// }
// #endif
// 
// //
// // internal utilities
// //
// int from_hex(char a) 
// {
//   if (a >= 'A' && a <= 'F')
//     return a - 'A' + 10;
//   else if (a >= 'a' && a <= 'f')
//     return a - 'a' + 10;
//   else
//     return a - '0';
// }
// 
// unsigned long parse_decimal()
// {
//   char *p = _term;
//   bool isneg = *p == '-';
//   if (isneg) ++p;
//   unsigned long ret = 100UL * gpsatol(p);
//   while (gpsisdigit(*p)) ++p;
//   if (*p == '.')
//   {
//     if (gpsisdigit(p[1]))
//     {
//       ret += 10 * (p[1] - '0');
//       if (gpsisdigit(p[2]))
//         ret += p[2] - '0';
//     }
//   }
//   return isneg ? -ret : ret;
// }
// 
// // Parse a string in the form ddmm.mmmmmmm...
// unsigned long parse_degrees()
// {
//   char *p;
//   unsigned long left_of_decimal = gpsatol(_term);
//   unsigned long hundred1000ths_of_minute = (left_of_decimal % 100UL) * 100000UL;
//   for (p=_term; gpsisdigit(*p); ++p);
//   if (*p == '.')
//   {
//     unsigned long mult = 10000;
//     while (gpsisdigit(*++p))
//     {
//       hundred1000ths_of_minute += mult * (*p - '0');
//       mult /= 10;
//     }
//   }
//   return (left_of_decimal / 100) * 1000000 + (hundred1000ths_of_minute + 3) / 6;
// }
// 
// #define COMBINE(sentence_type, term_number) (((unsigned)(sentence_type) << 5) | term_number)
// 
// // Processes a just-completed term
// // Returns true if new sentence has just passed checksum test and is validated
// bool term_complete()
// {
//   if (_is_checksum_term)
//   {
//     byte checksum = 16 * from_hex(_term[0]) + from_hex(_term[1]);
//     if (checksum == _parity)
//     {
//       if (_gps_data_good)
//       {
// #ifndef _GPS_NO_STATS
//         ++_good_sentences;
// #endif
//         _last_time_fix = _new_time_fix;
//         _last_position_fix = _new_position_fix;
// 
//         switch(_sentence_type)
//         {
//         case _GPS_SENTENCE_GPRMC:
//           _time      = _new_time;
//           _date      = _new_date;
//           _latitude  = _new_latitude;
//           _longitude = _new_longitude;
//           _speed     = _new_speed;
//           _course    = _new_course;
//           break;
//         case _GPS_SENTENCE_GPGGA:
//           _altitude  = _new_altitude;
//           _time      = _new_time;
//           _latitude  = _new_latitude;
//           _longitude = _new_longitude;
//           _numsats   = _new_numsats;
//           _hdop      = _new_hdop;
//           break;
//         }
// 
//         return true;
//       }
//     }
// 
// #ifndef _GPS_NO_STATS
//     else
//       ++_failed_checksum;
// #endif
//     return false;
//   }
// 
//   // the first term determines the sentence type
//   if (_term_number == 0)
//   {
//     if (!gpsstrcmp(_term, _GPRMC_TERM))
//       _sentence_type = _GPS_SENTENCE_GPRMC;
//     else if (!gpsstrcmp(_term, _GPGGA_TERM))
//       _sentence_type = _GPS_SENTENCE_GPGGA;
//     else
//       _sentence_type = _GPS_SENTENCE_OTHER;
//     return false;
//   }
// 
//   if (_sentence_type != _GPS_SENTENCE_OTHER && _term[0])
//     switch(COMBINE(_sentence_type, _term_number))
//   {
//     case COMBINE(_GPS_SENTENCE_GPRMC, 1): // Time in both sentences
//     case COMBINE(_GPS_SENTENCE_GPGGA, 1):
//       _new_time = parse_decimal();
//       _new_time_fix = millis();
//       break;
//     case COMBINE(_GPS_SENTENCE_GPRMC, 2): // GPRMC validity
//       _gps_data_good = _term[0] == 'A';
//       break;
//     case COMBINE(_GPS_SENTENCE_GPRMC, 3): // Latitude
//     case COMBINE(_GPS_SENTENCE_GPGGA, 2):
//       _new_latitude = parse_degrees();
//       _new_position_fix = millis();
//       break;
//     case COMBINE(_GPS_SENTENCE_GPRMC, 4): // N/S
//     case COMBINE(_GPS_SENTENCE_GPGGA, 3):
//       if (_term[0] == 'S')
//         _new_latitude = -_new_latitude;
//       break;
//     case COMBINE(_GPS_SENTENCE_GPRMC, 5): // Longitude
//     case COMBINE(_GPS_SENTENCE_GPGGA, 4):
//       _new_longitude = parse_degrees();
//       break;
//     case COMBINE(_GPS_SENTENCE_GPRMC, 6): // E/W
//     case COMBINE(_GPS_SENTENCE_GPGGA, 5):
//       if (_term[0] == 'W')
//         _new_longitude = -_new_longitude;
//       break;
//     case COMBINE(_GPS_SENTENCE_GPRMC, 7): // Speed (GPRMC)
//       _new_speed = parse_decimal();
//       break;
//     case COMBINE(_GPS_SENTENCE_GPRMC, 8): // Course (GPRMC)
//       _new_course = parse_decimal();
//       break;
//     case COMBINE(_GPS_SENTENCE_GPRMC, 9): // Date (GPRMC)
//       _new_date = gpsatol(_term);
//       break;
//     case COMBINE(_GPS_SENTENCE_GPGGA, 6): // Fix data (GPGGA)
//       _gps_data_good = _term[0] > '0';
//       break;
//     case COMBINE(_GPS_SENTENCE_GPGGA, 7): // Satellites used (GPGGA)
//       _new_numsats = (unsigned char)atoi(_term);
//       break;
//     case COMBINE(_GPS_SENTENCE_GPGGA, 8): // HDOP
//       _new_hdop = parse_decimal();
//       break;
//     case COMBINE(_GPS_SENTENCE_GPGGA, 9): // Altitude (GPGGA)
//       _new_altitude = parse_decimal();
//       break;
//   }
// 
//   return false;
// }
// 
// long gpsatol(const char *str)
// {
//   long ret = 0;
//   while (gpsisdigit(*str))
//     ret = 10 * ret + *str++ - '0';
//   return ret;
// }
// 
// int gpsstrcmp(const char *str1, const char *str2)
// {
//   while (*str1 && *str1 == *str2)
//     ++str1, ++str2;
//   return *str1;
// }
// 
// /* static */
// float distance_between (float lat1, float long1, float lat2, float long2) 
// {
//   // returns distance in meters between two positions, both specified 
//   // as signed decimal-degrees latitude and longitude. Uses great-circle 
//   // distance computation for hypothetical sphere of radius 6372795 meters.
//   // Because Earth is no exact sphere, rounding errors may be up to 0.5%.
//   // Courtesy of Maarten Lamers
//   float delta = radians(long1-long2);
//   float sdlong = sin(delta);
//   float cdlong = cos(delta);
//   lat1 = radians(lat1);
//   lat2 = radians(lat2);
//   float slat1 = sin(lat1);
//   float clat1 = cos(lat1);
//   float slat2 = sin(lat2);
//   float clat2 = cos(lat2);
//   delta = (clat1 * slat2) - (slat1 * clat2 * cdlong); 
//   delta = sq(delta); 
//   delta += sq(clat2 * sdlong); 
//   delta = sqrt(delta); 
//   float denom = (slat1 * slat2) + (clat1 * clat2 * cdlong); 
//   delta = atan2(delta, denom); 
//   return delta * 6372795; 
// }
// 
// float course_to (float lat1, float long1, float lat2, float long2) 
// {
//   // returns course in degrees (North=0, West=270) from position 1 to position 2,
//   // both specified as signed decimal-degrees latitude and longitude.
//   // Because Earth is no exact sphere, calculated course may be off by a tiny fraction.
//   // Courtesy of Maarten Lamers
//   float dlon = radians(long2-long1);
//   lat1 = radians(lat1);
//   lat2 = radians(lat2);
//   float a1 = sin(dlon) * cos(lat2);
//   float a2 = sin(lat1) * cos(lat2) * cos(dlon);
//   a2 = cos(lat1) * sin(lat2) - a2;
//   a2 = atan2(a1, a2);
//   if (a2 < 0.0)
//   {
//     a2 += TWO_PI;
//   }
//   return degrees(a2);
// }
// 
// const char *cardinal (float course)
// {
//   static const char* directions[] = {"N", "NNE", "NE", "ENE", "E", "ESE", "SE", "SSE", "S", "SSW", "SW", "WSW", "W", "WNW", "NW", "NNW"};
// 
//   int direction = (int)((course + 11.25f) / 22.5f);
//   return directions[direction % 16];
// }
// 
// // lat/long in MILLIONTHs of a degree and age of fix in milliseconds
// // (note: versions 12 and earlier gave this value in 100,000ths of a degree.
// void get_position(long *latitude, long *longitude, unsigned long *fix_age)
// {
//   if (latitude) *latitude = _latitude;
//   if (longitude) *longitude = _longitude;
//   if (fix_age) *fix_age = _last_position_fix == GPS_INVALID_FIX_TIME ? 
//    GPS_INVALID_AGE : millis() - _last_position_fix;
// }
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
// float f_altitude()    
// {
//   return _altitude == GPS_INVALID_ALTITUDE ? GPS_INVALID_F_ALTITUDE : _altitude / 100.0;
// }
// 
// float f_course()
// {
//   return _course == GPS_INVALID_ANGLE ? GPS_INVALID_F_ANGLE : _course / 100.0;
// }
// 
// float f_speed_knots() 
// {
//   return _speed == GPS_INVALID_SPEED ? GPS_INVALID_F_SPEED : _speed / 100.0;
// }
// 
// float f_speed_mph()   
// { 
//   float sk = f_speed_knots();
//   return sk == GPS_INVALID_F_SPEED ? GPS_INVALID_F_SPEED : _GPS_MPH_PER_KNOT * sk; 
// }
// 
// float f_speed_mps()   
// { 
//   float sk = f_speed_knots();
//   return sk == GPS_INVALID_F_SPEED ? GPS_INVALID_F_SPEED : _GPS_MPS_PER_KNOT * sk; 
// }
// 
// float f_speed_kmph()  
// { 
//   float sk = f_speed_knots();
//   return sk == GPS_INVALID_F_SPEED ? GPS_INVALID_F_SPEED : _GPS_KMPH_PER_KNOT * sk; 
// }
// 
// const float GPS_INVALID_F_ANGLE = 1000.0;
// const float GPS_INVALID_F_ALTITUDE = 1000000.0;
// const float GPS_INVALID_F_SPEED = -1.0;
// 






#ifndef kai_bao_tg_gps
#define kai_bao_tg_gps
u8 do1,do2;
u8 ph1,ph2;
u8 day1,day2;
u8 ngay1,ngay2;
u8 thag1,thag2;
u8 nam1,nam2;
u8 do0,ph0,day0,ngay0,thag0,nam0;

u8 ma_kt;
u8 dl;
u8 co_dl=0;
u8 tt_dl=0;
const u8 bag_ma_kt_m6[7] = {"$GPRMC,"};
#endif
const u8 bag_ma_kt_m8[7] = {"$GNRMC,"};
#ifndef thu_232_gps
#define thu_232_gps
ISR(USART_RXC_vect)
{
	#if  defined(__AVR_ATmega8__)  || defined(__AVR_ATmega16__) || defined(__AVR_ATmega32__) \
	|| defined(__AVR_ATmega8515__) || defined(__AVR_ATmega8535__) \
	|| defined(__AVR_ATmega323__)
	//co_232 = 1;
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
			do1=dl;
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
			do2=dl;
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
			ph1=dl;
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
			ph2=dl;
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
			day1=dl;
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
			day2=dl;
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
		{thag1=dl;co_dl=11;}break;
		case 11:
		if(dl==',')
		{
			co_dl=0;
			tt_dl=0;
		}
		else
		{thag2=dl;co_dl=12;}break;
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
u8 chuyen_doi_thoi_dan_m8()
{
	u8 loi=1;
	if(co_dl==14)
	{
		co_dl=0;
		if(so_sah_so(do1)&&so_sah_so(do2)&&so_sah_so(ph1)&&so_sah_so(ph2)&&
		so_sah_so(day1)&&so_sah_so(day2)&&so_sah_so(ngay1)&&so_sah_so(ngay2)&&
		so_sah_so(thag1)&&so_sah_so(thag2)&&so_sah_so(nam1)&&so_sah_so(nam2))
		{
			loi=0;
		}
		if(loi==0)
		{
			do0=(do1-0x30)*10+(do2-0x30);
			ph0=(ph1-0x30)*10+(ph2-0x30);
			day0=(day1-0x30)*10+(day2-0x30);
			ngay0=(ngay1-0x30)*10+(ngay2-0x30);
			thag0=(thag1-0x30)*10+(thag2-0x30);
			nam0=(nam1-0x30)*10+(nam2-0x30);
		}
		if(do0>23) loi=1;
		if(ph0>59) loi=1;
		if(day0>59) loi=1;
		if(ngay0>31) loi=1;
		if(thag0>12) loi=1;
		if(nam0<23) loi=1;
	}
	return loi;
}
//======================================== 
const int8 tss[] = {31,28,31,30,31,30,31,31,30,31,30,31};
unsigned char tinh_ngay_theo_thang_(unsigned char th,unsigned char na)
{
	unsigned char ntt;
	ntt=tss[th-1];
	if(na%4==0)
	{
		if(th==2)
		{
			ntt=29;
		}
	}
	return ntt;
}
//============================================= 
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
		if(ngay0>tinh_ngay_theo_thang_(thag0,nam0))
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