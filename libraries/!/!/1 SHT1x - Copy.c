/**
 * SHT1x Library
 *
 * Copyright 2009 Jonathan Oxer <jon@oxer.com.au> / <www.practicalarduino.com>
 * Based on previous work by:
 *    Maurice Ribble: <www.glacialwanderer.com/hobbyrobotics/?p=5>
 *    Wayne ?: <ragingreality.blogspot.com/2008/01/ardunio-and-sht15.html>
 *
 * Manages communication with SHT1x series (SHT10, SHT11, SHT15)
 * temperature / humidity sensors from Sensirion (www.sensirion.com).
 */
#include "!/1 SHT1x.h"
#include <string.h>
#include <util/delay.h>
#include "math.h"

//----------------------------------------------------------------------------------------
// Calculates tempurature in ^C and humidity in %RH (temperature compensated)
// sht_measure() returns temp and humidity in ticks. Use this function to convert
// to compensated values in real world units.
//
// This function returns integers with 2 assumed decimal places. For example 2550
// means 25.50. This is to avoid including the floating point math library.
//
// input :	humi [Ticks] (12 bit)
// 			temp [Ticks] (14 bit)
// output: 	humi [%RH] (2 fixed decimals)
// 			temp [^C]  (2 fixed decimals)
//----------------------------------------------------------------------------------------
void Sht_calculate(int *p_temperature, int *p_humidity)
{
	const long D1x100 = -40 * 100;                       // for 5V power
	const long D2x100 = 0.01 * 100;                      // for 14bit temp
	const long C1x100 = -4 * 100;                        // for 12bit humidity
	const long C2x10000 = 0.0405 * 10000;                // for 12bit humidity
	const long C3x10000000 = -0.0000028 * 10000000;	     // for 12bit humidity
	const long T1x100000 = 0.01 * 100000;                // for 12bit humidity
	const long T2x100000 = 0.00008 * 100000;             // for 12bit humidity
	long t = *p_temperature;                             // temperatere in ticks from sensor
	long rh = *p_humidity;                               // humidity in ticks from sensor

	long t_C;                                            // temperature in celcius: 2 fixed decimals
	long rh_lin;                                         // relative humidity: 2 fixed decimals
	long rh_true;                                        // temp compensated humidity: 2 fixed decimals

	t_C = D1x100 + D2x100*t;                             // calculate tempurature in celcius from ticks

	rh_lin = (C3x10000000*rh*rh)/100000 + (C2x10000*rh)/100 + C1x100;
	rh_true = ((t_C-(25*100)) * (T1x100000 + T2x100000*rh))/100000 + rh_lin;

	if(rh_true>10000)rh_true=10000;                      //cut if the value is outside of
	if(rh_true<10)rh_true=10;                            //the physical possible range

	*p_temperature=(int)t_C;                             //return temperature [^C]
	*p_humidity=(int)rh_true;                            //return humidity[%RH]
}


//----------------------------------------------------------------------------------
// Read humidity or temperature from the sensor.
// Returns the value in ticks. Use sht_calc() to convert to real world units.
// Returns 0xFFFF if the measurment failed
//----------------------------------------------------------------------------------
int Sht_measure(unsigned char mode)
{
	unsigned int 	temp = 0xFFFF;
	unsigned char	checksum;
	unsigned char 	c;

	// Signal start of communications
	Sht_transfer();

	// Request measurement
	Sht_write_byte(mode);

	// Sensor lowers the data line when measurement
	// is complete. Wait up to 2 seconds for this.
	for (c=0; c<20; c++)
	{
		if (!bit_is_set(SHT_PIN_DATA, SHT_DATA))
		break;
		Sht_DELAY(1000000/10);
	}

	// Read the measurement
	if (!bit_is_set(SHT_PIN_DATA, SHT_DATA))
	{
		temp = Sht_read_byte();
		temp = temp << 8;
		temp += Sht_read_byte();
		checksum = Sht_read_byte();
	}

	return temp;
}
// ------------------------------------------------------------------
//	Quick and dirty Delay (Chris Efstathiou)
// ------------------------------------------------------------------
void Sht_delay(unsigned long us)
{
	// 6 cpu cycles per loop + 16 cycles overhead

	__asm__ volatile (
	"L_%=: \n\t" \
	"subi %A0,lo8(-(-1)) \n\t" \
	"sbci %B0,hi8(-(-1)) \n\t" \
	"sbci %C0,hlo8(-(-1)) \n\t" \
	"sbci %D0,hhi8(-(-1)) \n\t" \
	"brne L_%= \n\t" \
	: /* NO OUTPUT */ \
	: "r" (us) \
	); \

	return;
}
//----------------------------------------------------------------------------------
// Reads the status register with checksum (8-bit)
//----------------------------------------------------------------------------------
char Sht_read_status(unsigned char *p_value)
{
	unsigned char error=0;
	unsigned char checksum=0;

	Sht_transfer();                         //transmission start
	error = Sht_write_byte(STATUS_REG_R);   //send command to sensor
	*p_value = Sht_read_byte();             //read status register (8-bit)
	checksum = Sht_read_byte();             //read checksum (8-bit)
	return error;                           //error=1 in case of no response form the sensor
}
//----------------------------------------------------------------------------------
// reads a byte form the Sensibus and gives an acknowledge in case of "ack=1"
//----------------------------------------------------------------------------------
char Sht_read_byte(void)
{
	unsigned char i,val=0;
	Sht_disable_data();

	// Read in 8 bits, LSB first
	for (i=0x80;i>0;i/=2)
	{
		Sht_clock_high();
		Sht_DELAY(SHT_DELAY_TIME);
		if (bit_is_set(SHT_PIN_DATA, SHT_DATA))
		val=(val | i); //read bit
		Sht_clock_low();
	}

	// Send ACK
	Sht_enable_data();
	Sht_data_low();
	Sht_clock_high();
	Sht_DELAY(SHT_DELAY_TIME);
	Sht_clock_low();
	Sht_disable_data();

	return val;
}
//----------------------------------------------------------------------------------
// communication reset: DATA-line=1 and at least 9 SCK cycles followed by ->Sht_transfer
//       _____________________________________________________         ________
// DATA:                                                      |_______|
//          _    _    _    _    _    _    _    _    _        ___     ___
// SCK : __| |__| |__| |__| |__| |__| |__| |__| |__| |______|   |___|   |______
//----------------------------------------------------------------------------------
void Sht_reset(void)
{
	unsigned char i;
	Sht_enable_data();
	Sht_data_high();
	Sht_clock_low();
	for(i=0;i<10;i++) //9 SCK cycles
	{
		Sht_clock_high();
		Sht_delay(SHT_DELAY_TIME);
		Sht_clock_low();
		Sht_delay(SHT_DELAY_TIME);
	}
	Sht_transfer(); //transmission start
}

//----------------------------------------------------------------------------------
// generates a transmission start
//       _____         ________
// DATA:      |_______|
//           ___     ___
// SCK : ___|   |___|   |______
//
//----------------------------------------------------------------------------------
void Sht_transfer(void)
{
	Sht_enable_data();
	Sht_data_high();
	Sht_clock_low();
	Sht_DELAY(SHT_DELAY_TIME);
	Sht_DELAY(SHT_DELAY_TIME);

	Sht_clock_high();
	Sht_DELAY(SHT_DELAY_TIME);
	Sht_data_low();
	Sht_DELAY(SHT_DELAY_TIME);
	Sht_clock_low();
	Sht_DELAY(SHT_DELAY_TIME);
	Sht_DELAY(SHT_DELAY_TIME);
	Sht_clock_high();
	Sht_DELAY(SHT_DELAY_TIME);
	Sht_data_high();
	Sht_DELAY(SHT_DELAY_TIME);
	Sht_clock_low();
}

char Sht_write_byte(unsigned char value)
{
	unsigned char i;
	unsigned char error = 0;

	// Write each bit one at a time, LSB first
	Sht_enable_data();
	
	for (i=0x80;i>0;i/=2)
	{
		if (i & value)
		Sht_data_high();
		else
		Sht_data_low();

		Sht_clock_high();
		Sht_DELAY(SHT_DELAY_TIME);
		Sht_DELAY(SHT_DELAY_TIME);
		Sht_clock_low();

	}
	Sht_disable_data();

	// Read ACK
	Sht_clock_high();
	Sht_DELAY(SHT_DELAY_TIME);
	error = bit_is_set(SHT_PIN_DATA, SHT_DATA);
	Sht_clock_low();

	return error; //error=1 in case of no acknowledge
}
char Sht_write_status(unsigned char value)
{
	unsigned char error=0;
	Sht_transfer();                         //transmission start
	error += Sht_write_byte(STATUS_REG_W);  //send command to sensor
	error += Sht_write_byte(value);         //send value of status register
	return error;                           //error>=1 in case of no response form the sensor
}
void Sht_clock_high(void)
{
	SHT_PORT_CLOCK|=(1<<SHT_CLOCK);
} 	// CLOCK pin high

void Sht_clock_low(void)
{
	SHT_PORT_CLOCK&=~(1<<SHT_CLOCK);
}	// CLOCK pin low

void Sht_data_high(void)
{
	SHT_PORT_DATA|=(1<<SHT_DATA);
}	// DATA pin high
void Sht_data_low(void)
{
	SHT_PORT_DATA&=~(1<<SHT_DATA);
}	// DATA pin low
void Sht_enable_data(void)
{
	SHT_DDR_DATA|=(1<<SHT_DATA);
}	// Drive DATA pin
void Sht_disable_data(void)
{
	SHT_DDR_DATA&=~(1<<SHT_DATA);
	// Release DATA pin
	SHT_PORT_DATA|=(1<<SHT_DATA);
}
void Sht_init(void)
{
	SHT_DDR_CLOCK|=(1<<SHT_CLOCK);                // Set clock pin to output
	SHT_PORT_CLOCK&=~(1<<SHT_CLOCK);               // Turn off clock pin
	Sht_disable_data();
}

/* ================  Public methods ================ */

/**
 * Reads the current temperature in degrees Celsius
 */
float readTemperatureC()
{
  u16 _val;                // Raw value returned from sensor
  u16 _temperature;      // Temperature derived from raw value

  // Conversion coefficients from SHT15 datasheet
  const u16 D1 = -40.0;  // for 14 Bit @ 5V
  const u16 D2 =   0.01; // for 14 Bit DEGC

  // Fetch raw value
  _val = doc_nhiet_();

  // Convert raw value to degrees Celsius
  _temperature = (_val * D2) + D1;

  return (_temperature);
}

/**
 * Reads the current temperature in degrees Fahrenheit
 */
float readTemperatureF()
{
  int _val;                 // Raw value returned from sensor
  float _temperature;       // Temperature derived from raw value

  // Conversion coefficients from SHT15 datasheet
  const float D1 = -40.0;   // for 14 Bit @ 5V
  const float D2 =   0.018; // for 14 Bit DEGF

  // Fetch raw value
  _val = readTemperatureRaw();

  // Convert raw value to degrees Fahrenheit
  _temperature = (_val * D2) + D1;

  return (_temperature);
}

/**
 * Reads current temperature-corrected relative humidity
 */
float readHumidity()
{
  int _val;                    // Raw humidity value returned from sensor
  float _linearHumidity;       // Humidity with linear correction applied
  float _correctedHumidity;    // Temperature-corrected humidity
  float _temperature;          // Raw temperature value

  // Conversion coefficients from SHT15 datasheet
  const float C1 = -4.0;       // for 12 Bit
  const float C2 =  0.0405;    // for 12 Bit
  const float C3 = -0.0000028; // for 12 Bit
  const float T1 =  0.01;      // for 14 Bit @ 5V
  const float T2 =  0.00008;   // for 14 Bit @ 5V

  // Command to send to the SHT1x to request humidity
  int _gHumidCmd = 0b00000101;

  // Fetch the value from the sensor
  sendCommandSHT(_gHumidCmd);
  waitForResultSHT();
  _val = getData16SHT();
  skipCrcSHT();

  // Apply linear conversion to raw value
  _linearHumidity = C1 + C2 * _val + C3 * _val * _val;

  // Get current temperature for humidity correction
  _temperature = readTemperatureC();

  // Correct humidity value for current temperature
  _correctedHumidity = _temperature * (T1 + T2 * _val) + _linearHumidity;

  return (_correctedHumidity);
}

 
/* ================  Private methods ================ */

/**
 * Reads the current raw temperature value 
 */
u16 doc_nhiet_()
{
  u16 _val;

  // Command to send to the SHT1x to request Temperature
  u8 _gTempCmd  = 0b00000011;

  sendCommandSHT(_gTempCmd);
  waitForResultSHT();
  _val = getData16SHT();
  skipCrcSHT();

  return (_val);
}

/**
 */
int shiftIn(int _dataPin, int _clockPin, int _numBits)
{
  int ret = 0;
  int i;

  for (i=0; i<_numBits; ++i)
  {
     sck=1;
     delay_ms(10);  // I don't know why I need this, but without it I don't get my 8 lsb of temp
     ret = ret*2 + sda_i;
     sck=0;
  }

  return(ret);
}

/**
 */
void sendCommandSHT(u8 lenh)
{
	u8 ack;
	sda_d=ra;
	sck_d=ra;
	sda=1;
	sck=1;
	sda=0;
	sck=0;
	sck=1;
	sda=1;
	sck=0;
	u8 i;
	for(i=0;i<8;i++)
	{
		sda=(lenh&0x80)?0:1;
		sck=1;
		sck=0;
		lenh<<=1;
	}

  // The command (3 msb are address and must be 000, and last 5 bits are command)
 // shiftOut(_dataPin, _clockPin, MSBFIRST, _command);

  // Verify we get the correct ack
  sck=1;
  sda_d=vao;
  ack = sda_i;
  if (ack != 0) {
    //Serial.println("Ack Error 0");
  }
  sck=0;
  ack = sda_i;
  if (ack != 1) {
    //Serial.println("Ack Error 1");
  }
}

/**
 */
void waitForResultSHT(int _dataPin)
{
  int i;
  int ack;

  sda_d=vao;

  for(i= 0; i < 100; ++i)
  {
    delay_us(10);
    ack = sda_i;

    if (ack == 0) {
      break;
    }
  }

  if (ack == 1) {
    //Serial.println("Ack Error 2"); // Can't do serial stuff here, need another way of reporting errors
  }
}

/**
 */
int getData16SHT(int _dataPin, int _clockPin)
{
  int val;
	sda_d=vao;
  sck_d=ra;
  val = shiftIn(_dataPin, _clockPin, 8);
  val *= 256;

  // Send the required ack
  sda_d=ra;
  sda=1;
  sda=0;
  sck=1;
  sck=0;

  // Get the least significant bits
  sda_d=vao;
  val |= shiftIn(_dataPin, _clockPin, 8);

  return val;
}

/**
 */
void skipCrcSHT()
{
	sda_d=ra;
	sck_d=ra;
	sda=1;
	sck=1;
	sck=0;
}
