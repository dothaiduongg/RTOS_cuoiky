#ifndef sht1x_h
#define sht1x_h
#include <!/! ldn.h>

#define sck dk_bit(PORTC,2)
#define sck_d dk_bit(DDRC,2)

#define data dk_bit(PORTC,0)
#define data_i dk_bit(PINC,0)
#define data_d dk_bit(DDRC,0)

#define measure_temp 0x03
#define measure_humi 0x05
#define reset        0x1e
void sht_start(void)
{
	sck_d=ra;
	data_d = 1; // data is output

	data = 1;
	sck = 0;
	sck = 1;
	data = 0;
	sck = 0;
	sck = 1;
	data = 1;
	sck = 0;
}
//##########################################################################

u8 sht_write(u8 b)
{
	u8 i, error = 0;

	data_d = 1; // data is an output
	delay_us(5);
	for(i = 0x80; i > 0; i /= 2)
	{
		sck = 0;
		if(i & b)
		{
			data = 1;
		}
		else
		{
			data = 0;
		}
		sck = 1;
	}
	sck = 0;
	data_d = 0; // data is input
	sck = 1;
	error = data_i;
	sck = 0;

	return(error);
}
//###################################################
u8 sht_read(u8 ack)
{
	u8 i, val = 0;

	data_d = 0; // data is input

	for(i = 0x80; i > 0; i /= 2)
	{
		sck = 1;
		if(data_i)
		{
			val = val | i;
		}
		sck = 0;
	}
	data_d = 1; // data is output
	data = ! ack;
	sck = 1;
	sck = 0;

	return(val);
}
//########################################################
void connection_reset(void)
{
	u8 i;
	data_d=1;
	data=1;
	for (i=0;i<9;i++)
	{
		sck=1;
		delay_us(2);
		sck=0;
		delay_us(2);
	}
	data=1;
	sht_start();
	delay_ms(100);
}
//####################################################
void sht_reset()
{
	sht_start();
	sht_write(reset);

	delay_ms(100);
}
//#####################################################
// read the sensor value. reg is register to read from
u16 readsensor(int reg)
{
	u8 msb, lsb, crc;

	sht_start();
	sht_write(reg);

	while(data_i);

	msb = sht_read(1);
	lsb = sht_read(1);
	crc = sht_read(0);
	//make8(msb,lsb);

	return(((unsigned short) msb << 8) | (unsigned short) lsb);
}
//######################################################
float read_sensor(u8 am_nhiet)
{
	long int income,temp;
	float out,out0,t;
	switch(am_nhiet)
	{
		case 0:
		income = readsensor(measure_humi);
		out0=(-2.0468+(0.0367*income)+(-1.5955e-6*(income*income)));
		temp=income;
		_delay_ms(500);
		readsensor(measure_temp);
		t = -40.1 + 0.01*income;
		out=(t-25)*(0.01+0.00008*temp)+out0;
		break;
		case 1:
		income = readsensor(measure_temp);
		out = -40.1 + 0.01*income;
		break;
	}
	return(out);
}
#endif
// /**
//  * sht1x library
//  *
//  * copyright 2009 jonathan oxer <jon@oxer.com.au> / <www.practicalarduino.com>
//  * based on previous work by:
//  *    maurice ribble: <www.glacialwanderer.com/hobbyrobotics/?p=5>
//  *    wayne ?: <ragingreality.blogspot.com/2008/01/ardunio-and-sht15.html>
//  *
//  * manages communication with sht1x series (sht10, sht11, sht15)
//  * temperature / humidity sensors from sensirion (www.sensirion.com).
//  */

//
//     sht1x(int datapin, int clockpin);
//     float readhumidity();
//     float readtemperaturec();
//     float readtemperaturef();
//   private:
//     int _datapin;
//     int _clockpin;
//     int _numbits;
//     float readtemperatureraw();
//     int shiftin(int _datapin, int _clockpin, int _numbits);
//     void sendcommandsht(int _command, int _datapin, int _clockpin);
//     void waitforresultsht(int _datapin);
//     int getdata16sht(int _datapin, int _clockpin);
//     void skipcrcsht(int _datapin, int _clockpin);
// #endif

