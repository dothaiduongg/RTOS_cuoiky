/**********************************************************

Software I2C Library for AVR Devices.

Copyright 2008-2012
eXtreme Electronics, India
www.eXtremeElectronics.co.in
**********************************************************/
#ifndef _i2csoft_c
#define _i2csoft_c
#include <avr/io.h>
#include <util/delay.h>
#include "!/! ldn.h" 
#include "!/i2csoft.h"
#define I2C_READ    1
#define I2C_WRITE   0

u16 SoftI2C_tre=1;


#define Q_DEL _delay_loop_2(3*SoftI2C_tre)
#define H_DEL _delay_loop_2(5*SoftI2C_tre)

void SoftI2CInit()
{
	SDAPORT&=(1<<SDA);
	SCLPORT&=(1<<SCL);
	SOFT_I2C_SDA_HIGH;	
	SOFT_I2C_SCL_HIGH;	
}
void SoftI2CStart()
{
	SOFT_I2C_SCL_HIGH;
	H_DEL;
	SOFT_I2C_SDA_LOW;	
	H_DEL;  	
}

void beginTransmission(uint8_t dia_chi)
{

}
uint8_t SoftI2C_doc_1_byte(uint8_t ma_thiet_bi,uint8_t dia_chi)
{
	cli();
	SoftI2CStart();
	SoftI2CWriteByte(ma_thiet_bi); // ghi vao ds1307 chieu ghi
	SoftI2CWriteByte(dia_chi); // ghi dia chi can doc
	SoftI2CStart(); // start bit i2c
	SoftI2CWriteByte(ma_thiet_bi+1); // ghi vao ds1307 chieu doc
	dia_chi = SoftI2CReadByte(0);
	SoftI2CStop();
	sei();
	return dia_chi;
}

void SoftI2CStop()
{
	 SOFT_I2C_SDA_LOW;
	 H_DEL;
	 SOFT_I2C_SCL_HIGH;
	 Q_DEL;
	 SOFT_I2C_SDA_HIGH;
	 H_DEL;
}

uint8_t SoftI2CWriteByte(uint8_t data)
{
	u16 ngoai_thoi_dan=0;
	 uint8_t i;
	 for(i=0;i<8;i++)
	 {
		SOFT_I2C_SCL_LOW;
		Q_DEL;
		
		if(data & 0x80)
			SOFT_I2C_SDA_HIGH;
		else
			SOFT_I2C_SDA_LOW;	
		
		H_DEL;
		
		SOFT_I2C_SCL_HIGH;
		H_DEL;
		
		while((SCLPIN & (1<<SCL))==0&&ngoai_thoi_dan<20000)
		{
			ngoai_thoi_dan++;
		}
			
		data=data<<1;
	}
	 
	//The 9th clock (ACK Phase)
	SOFT_I2C_SCL_LOW;
	Q_DEL;
		
	SOFT_I2C_SDA_HIGH;		
	H_DEL;
		
	SOFT_I2C_SCL_HIGH;
	H_DEL;	
	
	uint8_t ack=!(SDAPIN & (1<<SDA));
	
	SOFT_I2C_SCL_LOW;
	H_DEL;
	
	return ack;
	 
}
 
 
uint8_t SoftI2CReadByte(uint8_t ack)
{
	u16 ngoai_thoi_dan=0;
	uint8_t data=0x00;
	uint8_t i;
			
	for(i=0;i<8;i++)
	{
			
		SOFT_I2C_SCL_LOW;
		H_DEL;
		SOFT_I2C_SCL_HIGH;
		H_DEL;
			
		while((SCLPIN & (1<<SCL))==0&&ngoai_thoi_dan<20000)
		{
			ngoai_thoi_dan++;
		}
		
		if(SDAPIN &(1<<SDA))
			data|=(0x80>>i);
			
	}
		
	SOFT_I2C_SCL_LOW;
	Q_DEL;						//Soft_I2C_Put_Ack
	
	if(ack)
	{
		SOFT_I2C_SDA_LOW;	
	}
	else
	{
		SOFT_I2C_SDA_HIGH;
	}	
	H_DEL;
	
	SOFT_I2C_SCL_HIGH;
	H_DEL;
	
	SOFT_I2C_SCL_LOW;
	H_DEL;
			
	return data;
	
}











void SoftI2CInit2()
{
	SDAPORT2&=(1<<SDA2);
	SCLPORT2&=(1<<SCL2);
	SOFT_I2C_SDA_HIGH2;
	SOFT_I2C_SCL_HIGH2;
}
void SoftI2CStart2()
{
	SOFT_I2C_SCL_HIGH2;
	H_DEL;
	SOFT_I2C_SDA_LOW2;
	H_DEL;
}

void SoftI2CStop2()
{
	SOFT_I2C_SDA_LOW2;
	H_DEL;
	SOFT_I2C_SCL_HIGH2;
	Q_DEL;
	SOFT_I2C_SDA_HIGH2;
	H_DEL;
}
//= 
uint8_t SoftI2CWriteByte2(uint8_t data)
{
	u16 ngoai_thoi_dan=0;
	uint8_t i;
	for(i=0;i<8;i++)
	{
		SOFT_I2C_SCL_LOW2;
		Q_DEL;
		
		if(data & 0x80)
		SOFT_I2C_SDA_HIGH2;
		else
		SOFT_I2C_SDA_LOW2;
		
		H_DEL;
		
		SOFT_I2C_SCL_HIGH2;
		H_DEL;
		
		while((SCLPIN2 & (1<<SCL2))==0&&ngoai_thoi_dan<1000)
		{
			ngoai_thoi_dan++;
		}
		
		data=data<<1;
	}
	
	//The 9th clock (ACK Phase)
	SOFT_I2C_SCL_LOW2;
	Q_DEL;
	
	SOFT_I2C_SDA_HIGH2;
	H_DEL;
	
	SOFT_I2C_SCL_HIGH2;
	H_DEL;
	
	uint8_t ack=!(SDAPIN2 & (1<<SDA2));
	
	SOFT_I2C_SCL_LOW2;
	H_DEL;
	
	return ack;
	
}


uint8_t SoftI2CReadByte2(uint8_t ack)
{
	u16 ngoai_thoi_dan=0;
	uint8_t data=0x00;
	uint8_t i;
	
	for(i=0;i<8;i++)
	{
		
		SOFT_I2C_SCL_LOW2;
		H_DEL;
		SOFT_I2C_SCL_HIGH2;
		H_DEL;
		
		while((SCLPIN2 & (1<<SCL2))==0&&ngoai_thoi_dan<1000)
		{
			ngoai_thoi_dan++;
		}
		
		if(SDAPIN2 &(1<<SDA2))
		data|=(0x80>>i);
		
	}
	
	SOFT_I2C_SCL_LOW2;
	Q_DEL;						//Soft_I2C_Put_Ack
	
	if(ack)
	{
		SOFT_I2C_SDA_LOW2;
	}
	else
	{
		SOFT_I2C_SDA_HIGH2;
	}
	H_DEL;
	
	SOFT_I2C_SCL_HIGH2;
	H_DEL;
	
	SOFT_I2C_SCL_LOW2;
	H_DEL;
	
	return data;
	
}
#endif















