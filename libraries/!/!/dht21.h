#ifndef _DHT21_H_
#define _DHT21_H_
u16 da_dht21;
u16 nd_dht21;
//
//    FILE: dht.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.09
// PURPOSE: DHT Temperature & Humidity Sensor library for Arduino
//     URL: http://arduino.cc/playground/Main/DHTLib
//
// HISTORY:
// see dht.cpp file
//

#define DHTLIB_OK				0
#define DHTLIB_ERROR_CHECKSUM	-1
#define DHTLIB_ERROR_TIMEOUT	-2
#define DHTLIB_INVALID_VALUE	-999

typedef struct {
    volatile uint8_t *port_out;
    const volatile uint8_t *port_in;
    volatile uint8_t *port_dir;
    uint8_t port_mask;

    uint16_t humidity;
    uint16_t temperature;
    int16_t error;

    uint8_t buffer[5];
} dht21_sensor_t;

void dht21_init(dht21_sensor_t *dht,
                volatile uint8_t *p_out,
                const volatile uint8_t *p_in,
                volatile uint8_t *p_dir,
                int pin);

int dht_read(dht21_sensor_t *dht);
int dht21_read(dht21_sensor_t *dht);//uint8_t pin)

unsigned int humidity;
unsigned int temperature;

uint8_t bits[5];  // buffer to receive data



unsigned char AM2301_ReadByte(unsigned char *pvData)
{
	u8 i,lvCount,lvBit;
	u8 loi;
	loi=0;
	for(i=0;i<8;i++) // vong lap thu 8 bit
	{
		lvCount=1;
		while(dht21_i==0 && lvCount>0 ) //判断丛机是否发来50us的低电平信号，若超时返回2
		lvCount++;
		if(lvCount==0)
		{
			loi=2;
			break;
		}
		_delay_us(35); //延时35us
		//判断数据是0或1
		lvBit=0;
		if(dht21_i==1)
		lvBit=1;
		lvCount=1;
		while(dht21_i==1  && lvCount>0 ) //判断丛机是否发来26-28us的高电平信号，若超时返回2
		lvCount++;
		if(lvCount==0)
		{
			loi=2;
			break;
		}

		//把得到的每一位数据保存于pvData中
		if(lvBit)
		*pvData |= 1<<(7-i);
		else
		*pvData &= ~1<<(7-i);

	}

	return loi;
}
//======================================== 
u8 AM2301_CollectCharData()
{
	u8 loi;
	u8 lvCount;
	unsigned int  lvTemp16;
	int lvTemp;

	unsigned char lvHumidityHigh; //湿度高位
	unsigned char lvHumidityLow;          //湿度低位
	unsigned char lvTemperatureHigh; //温度高位
	unsigned char lvTemperatureLow; //温度低位
	unsigned char lvCheck; //校验位
	loi=0;
	dht21_d=ra;
	dht21_o=0;
	_delay_us(500); //持续500us
	dht21_o=1;
	dht21_d=vao;
	cam_ngat;
	_delay_us(40);

	if(dht21_i==0)
	{
		lvCount=1;
		while(dht21_i==0 && lvCount >0)  //判断丛机是否发送了80us的高电平信号
		lvCount++;
		if(lvCount==0)
		loi = 3;

		lvCount=1;
		while(dht21_i==1&& lvCount >0)  //判断丛机是否发送了80us的高电平信号
		lvCount++;
		if(lvCount==0)loi = 3;

		if(AM2301_ReadByte(&lvHumidityHigh)) //获得湿度高位
		loi = 2;

		if(AM2301_ReadByte(&lvHumidityLow)) //获得湿度高位
		loi = 2;

		if(AM2301_ReadByte(&lvTemperatureHigh)) //获得湿度高位
		loi = 2;

		if(AM2301_ReadByte(&lvTemperatureLow)) //获得湿度高位
		loi = 2;

		if(AM2301_ReadByte(&lvCheck)) //获得湿度高位
		loi = 2;
		cho_ngat;
		lvCount=lvHumidityHigh+lvHumidityLow+lvTemperatureHigh+lvTemperatureLow;//计算湿度高位+湿度低位+温度高位+温度低位的和
		if(lvCount==lvCheck) //数据校验，若正确则获得正确的湿度和温度，并返回1
		{
			//lvTemperatureHigh |=0x80;
			//把湿度的高位和地位组合，得到完整的湿度
			lvTemp16=lvHumidityHigh;
			lvTemp16 <<=8;
			lvTemp16 |= lvHumidityLow;
			da_dht21=lvTemp16;
			//把温度的高位和地位组合，得到完整的温度
			lvTemp16=lvTemperatureHigh;
			lvTemp16 <<=8;
			lvTemp16 |= lvTemperatureLow;
			if(lvTemp16 & 0x8000) //如果温度是负值，则转化
			{
				lvTemp16 &=0x7FFF;
				lvTemp=0-lvTemp16;
				da_dht21=lvTemp ;
			}
			else
			{
				nd_dht21=lvTemp16;
			}
		}
		else //数据校验，若错误，则返回1
			loi=1;
	}
	else
		loi=1;
	cho_ngat;
	return loi;
}
#endif
