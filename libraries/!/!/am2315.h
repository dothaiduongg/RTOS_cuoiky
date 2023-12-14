/***************************************************
  This is a library for the AM2315 Humidity & Temp Sensor
  Designed specifically to work with the AM2315 sensor from Adafruit
  ----> https://www.adafruit.com/products/1293
  These displays use I2C to communicate, 2 pins are required to
  interface
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!
  Written by Limor Fried/Ladyada for Adafruit Industries.
  Additional improvements added by Daniel Sandoval/EasternStarGeek
  8 July, 2013.  (Parent Library: Adafruit_AM2315)
  BSD license, all text above must be included in any redistribution
 ****************************************************/
 #define SCLPORT	PORTD	//TAKE PORTD as SCL OUTPUT WRITE
 #define SCLDDR	DDRD	//TAKE DDRB as SCL INPUT/OUTPUT configure
 #define SCLPIN	PIND	//TAKE PORTD TO READ DATA

 #define SDAPORT	PORTD	//TAKE PORTD as SDA OUTPUT WRITE
 #define SDADDR	DDRD	//TAKE PORTD as SDA INPUT configure
 #define SDAPIN	PIND	//TAKE PORTD TO READ DATA


 #define SCL	7		//PORTD.0 PIN AS SCL PIN
 #define SDA	6		//PORTD.1 PIN AS SDA PIN


 #include "!/i2csoft.c"
 //#if (ARDUINO >= 100)
 //#include "Arduino.h"
 //#else
 //#include "WProgram.h"
// #endif
 //#include "Wire.h"
 #define AM2315_dia_chi      0xb8
 //#define AM2315_I2CADDR       0x5C
 #define AM2315_READREG       0x03
float nhiet_2315;
float am_2315;
// class SDL_ESP8266_HR_AM2315 {
//	 public:
//	 SDL_ESP8266_HR_AM2315();
	 //boolean begin(void);
//	 boolean readData(float *dataArray);
	 
//	 private:
//	 float humidity, temp;
// };
extern long AM2315BadCount;
#ifdef DEBUGPRINT
extern long AM2315TotalCount;
extern unsigned char FirstBadReply[10];

#endif

//#include "SDL_ESP8266_HR_AM2315.h"
//#include <util/delay.h>

//SDL_ESP8266_HR_AM2315::SDL_ESP8266_HR_AM2315() {
//}
//int delayByCPU(long delaycount);

//int I2C_ClearBus();
void ghi_dia_chi()
{
	SoftI2CStart();
	SoftI2CWriteByte(0xD0); // I2C write address
	SoftI2CWriteByte(0x00); // Start at REG 0 - Seconds
	//SoftI2CWriteByte(bin2bcd(giay)); // REG 0
	//SoftI2CWriteByte(bin2bcd(phut)); // REG 1
	//SoftI2CWriteByte(bin2bcd(gio)); // REG 2
	SoftI2CWriteByte(0x90);            // REG 7 - Enable squarewave output pin
	SoftI2CStop();
}


u8 readData(float *dataArray) 
{
	cli();
  uint8_t reply[10];

  // Wake up the sensor
 // SoftI2CStart();
  //_i2c->beginTransmission(AM2315_I2CADDR);
  //delay(2);
  //_i2c->endTransmission();

  //ETS_UART_INTR_DISABLE();
  //noInterrupts();
  //ETS_INTR_LOCK();
//  SoftI2CStart();
 // SoftI2CWriteByte(AM2315_dia_chi);
 // SoftI2CWriteByte(AM2315_READREG);
 // SoftI2CStop();
  //Wire.beginTransmission(AM2315_I2CADDR);
  //Wire.write(AM2315_READREG);
 // Wire.endTransmission();
  //delay(50);
  //delayByCPU(50);
  SoftI2C_tre=100;
  delay_ms(50);

  SoftI2CStart();
  SoftI2CWriteByte(AM2315_dia_chi);
  SoftI2CWriteByte(AM2315_READREG);
  SoftI2CWriteByte(0x00);
  SoftI2CWriteByte(0x00);
  SoftI2CWriteByte(0x00);
  SoftI2CStop();
 // Wire.beginTransmission(AM2315_I2CADDR);
 // Wire.write(AM2315_READREG);
 // Wire.write(0x00);  // start at address 0x0
 // Wire.write(4);  // request 4 bytes data
 // Wire.endTransmission();

  //delayByCPU(50);
  delay_ms(50);
  /*
  SoftI2CStart();
  //i2c_send_byte(AM2315_I2CADDR);
  SoftI2CWriteByte(AM2315_dia_chi+1);
  //Wire.requestFrom(AM2315_I2CADDR, 8);
  uint8_t i;
  for ( i = 0; i < 7; i++) 
  {
    reply[i] = SoftI2CReadByte(1);
    //Serial.println(reply[i], HEX);
  }
  reply[i] = SoftI2CReadByte(0);
  SoftI2CStop();
  */


  //interrupts();
  //ETS_UART_INTR_ENABLE();
  
  //yield();


  //if ((reply[0] == AM2315_READREG) &&
  //    (reply[1] == 4))  {
  reply[2]=SoftI2C_doc_1_byte(AM2315_dia_chi,6);
  reply[3]=SoftI2C_doc_1_byte(AM2315_dia_chi,7);
 reply[4]=SoftI2C_doc_1_byte(AM2315_dia_chi,8);
    reply[5]=SoftI2C_doc_1_byte(AM2315_dia_chi,9);
    am_2315 = reply[2];
    am_2315 *= 256;
    am_2315 += reply[3];
    am_2315 /= 10;

   // check for negative temperature

    bool negative;
    negative = false;

  //  if (reply[4] & 0x80)
  //  {
  //    negative = true;

 //   }

    dataArray[0] = am_2315;


    nhiet_2315 = reply[4] & 0x7F;
    nhiet_2315 *= 256;
    nhiet_2315 += reply[5];
    nhiet_2315 /= 10;

   // if (negative)
  //    nhiet_2315 = -nhiet_2315;

  sei();
}

int delayByCPU(long delaycount)
{
  unsigned long startMillis;
  unsigned long endMillis;

#define COUNT 100000



  startMillis = millis();

  long index;
  float test;
  long i;
  long j;

  for (i = 0; i < delaycount * 166; i++)
  {
    //Serial.println("outside loop");
    for (j = 0; j < 1000; j++)
    {
      for (index = 0; index < COUNT; index++)
      {

        test = 30.4 + i;
        test = test / 50.0;


      }
      test = test + j;
    }
  }

  endMillis = millis();



  return test;
}
