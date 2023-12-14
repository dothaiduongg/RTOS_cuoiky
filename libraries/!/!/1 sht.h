/** \file adc.h \brief Obs³uga czujnika sht11. */
/*

*/

//----------------------------------------------------------------------------------
//
// Sensirion SHTxx Humidity Sensor Library
//
// Library for using the SHT1x humidity and temperature
// sensors from Sensirion (http://www.sensirion.com).
// Based on Sensirion application note "Sample Code SHTxx".
//
// To use:
// - supply 5V to SHTxx (constants in calculations assume 5V, see ShtCalculate() and SHTxx datasheet)
// - connect the clock pin of the SHTxx to pin B1 (see Sht.h to change)
// - connect the data pin of the SHTxx to pin B2 (see Sht.h to change)
//
// - call ShtInit() to initialize pins, call when the processor starts
// - call ShtMeasure(MEASURE_TEMP) and ShtMeasure(MEASURE_HUMIDITY) to make the measurements
// - call ShtCalculate() to convert measurements to real-world units
//
// - call ShtReadStatus() and ShtWriteStatus() to modify the status register
//
//
// ToDo:
// - verify checksum digits sent from SHTxx
// - implement soft-reset
// - handle 12/8-bit temp/humidity readings
//
// History:
// 2003-Jul-03	BL	- Created
// 2008-Dec-11	Wojciech Walendziuk (walenw@pb.edu.pl) - Modified
//--------------------
/** \defgroup sht przetwornik Sht
 
 Zawiera funkcje obs³ugi czujnika sht11.
 \code
 #include "sht.h"
 \endcode 
 \ref config:
 
 W pliku \c "config.h" znajduj¹cym siê w katalogu projektu nale¿y umieœciæ nastêpuj¹c¹ zawartoœæ:
    	     
 \code
  #define SHT_DDR_CLOCK       DDRB     // Port with clock pin 
  #define SHT_PORT_CLOCK      PORTB    // Port with clock pin
  #define SHT_PIN_CLOCK       PINB     // Port with clock pin
  #define SHT_DDR_DATA        DDRB     // Port with data pin 
  #define SHT_PORT_DATA       PORTB    // Port with data pin
  #define SHT_PIN_DATA        PINB     // Port with data pin  
  #define SHT_CLOCK      1        // Pin used to output clock to SHT
  #define SHT_DATA       2        // Pin used to read/output data from/to SHT
 \endcode
 
 \note Wartoœci z \c #define mo¿na zmieniaæ w celu dostosowania 
 biblioteki do tworzonego urz¹dzenia i oprogramowania.
*/
#include <avr/io.h>
//#include "delay.h"
#include "./config.h"
//#include "global.h"

#ifndef SHT_H
#define SHT_H

#ifndef F_CPU
	#define F_CPU 1000000UL 		//Your clock speed in Hz (3Mhz here)
#endif


#define SHT_TEMPERATURE 0x03     // Measure temp - for ShtMeasure
#define SHT_HUMIDITY    0x05     // Measure humidity - for ShtMeasure
#define SHT_DELAY_TIME  25       // uS delay between clock rise/fall 25us
#define STATUS_REG_W    0x06     // Command to read status register
#define STATUS_REG_R    0x07     // Command to write status register
#define RESET           0x1e     // Command for soft reset (not currently used)
#define Sht_DELAY(us)   (Sht_delay(((us*(F_CPU/1000000))-16)/6))


void Sht_delay(unsigned long us);
void Sht_calculate(int *p_temperature, int *p_humidity);
void Sht_clock_high(void);
void Sht_clock_low(void);
void Sht_data_high(void);
void Sht_data_low(void);
void Sht_disable_data(void);
void Sht_enable_data(void);
void Sht_init(void);
int  Sht_measure(unsigned char mode);
char Sht_read_byte(void);
char Sht_read_status(unsigned char *p_value);
void Sht_reset(void);
void Sht_transfer(void);
char Sht_write_byte(unsigned char value);
char Sht_write_status(unsigned char value);


#endif
