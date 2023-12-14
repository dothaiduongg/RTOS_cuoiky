/*
 * dht21.h - Library for DHT21/AM2301 digital temperature sensor
 * Create by Jack Tan <jianekemeng@gmail.com>
 * Released into the public domain.
 */

#ifndef	__DHT21_H__
#define	__DHT21_H__
#define LOW 0
#define HIGH 1
///---------------------------------------- 
#ifndef dht21_d
#define dht21_d dk_bit(DDRC,0)
#define dht21_i dk_bit(PINC,0)
#define dht21_o dk_bit(PORTC,0)
#endif
//---------------------------------------- 
/* DHT21 data pin */
u8 dht21_read_pin();
extern void dht21_write_pin(uint8_t level);
extern void dht21_pin_mode(uint8_t mode);
extern void delay_ms(uint16_t ms);
extern void delay_us(uint16_t us);
void doc_du_lieu_dht21();


/////////////////////////////////////////////////////

u8 RH_H, RH_L, T_H, T_L, CRC;
u8 dah,dal,ndh,ndl;
int16 do_am;
int16 nhiet_do;
u16 nd_21;
u16 da_21;

bool loi;

u8 doc_8_bit_dht21()
{
	u8 du_lieu;
	u8 i;
	u8 time;
	for (i = 8; i > 0; i--)
	{
		/* We are in low signal now, wait for high signal and measure time */
		time = 0;
		while (dht21_i==0&&loi==0) /* Wait high signal, about 57-63us long (measured with logic analyzer) */
		{
			if (time > 75)
			{
				loi=1;
			}
			time++;
			_delay_us(1);
		}
		/* High signal detected, start measure high signal, it can be 26us for 0 or 70us for 1 */
		time = 0;
		/* Wait low signal, between 26 and 70us long (measured with logic analyzer) */
		while (dht21_i==1&loi==0) {
			if (time > 90)
			{
				loi=1;
			}
			/* Increase time */
			time++;
			/* Wait 1 us */
			_delay_us(1);
		}
		du_lieu<<=1;
		if (time > 18 && time < 37)
		{
			//d[j]|=0;
			du_lieu |= 0;
		}
		else
		{
			/* We read 1 */
			du_lieu |= 1;
		}
		
	}
	
}


void doc_dht_21() 
{
	cam_ngat;
	u8 time;
	u8 i, j, d[5];
	dht21_d=ra;
	dht21_o=0;
	_delay_us(1000);
	dht21_o=1;
	_delay_us(30);
	dht21_d=vao;
	time = 0;
	/* Wait 20us for acknowledge, low signal */
	while (dht21_i==1&&loi==0) 
	{
		if (time > 20) 
		{
			loi=1;
		}
		time++;
		_delay_us(1);
	}
	time = 0;
	/* Wait high signal, about 80-85us long (measured with logic analyzer) */
	while (dht21_i==0&&loi==0) 
	{
		if (time > 85) 
		{
			loi=1;
		}
		time++;
		_delay_us(1);
	}
	time = 0;
	/* Wait low signal, about 80-85us long (measured with logic analyzer) */
	while (dht21_i==1&&loi==0) 
	{
		if (time > 85) 
		{
			loi=1;
		}
		/* Increase time */
		time++;
		_delay_us(1);
	}
	
	/* Read 5 bytes */
	for (j = 0; j < 5; j++) 
	{
		for (i = 8; i > 0; i--)
		{
			/* We are in low signal now, wait for high signal and measure time */
			time = 0;
			
			while (dht21_i==0&&loi==0) /* Wait high signal, about 57-63us long (measured with logic analyzer) */
			{
				if (time > 75) 
				{
					loi=1;
				}
				time++;
				_delay_us(1);
			}
			/* High signal detected, start measure high signal, it can be 26us for 0 or 70us for 1 */
			time = 0;
			/* Wait low signal, between 26 and 70us long (measured with logic analyzer) */
			while (dht21_i==1&loi==0) 
			{
				if (time > 90) 
				{
					loi=1;
				}
				/* Increase time */
				time++;
				/* Wait 1 us */
				_delay_us(1);
			}
			d[j]<<=1;
			if (time > 18 && time < 32) 
			{
				//d[j]|=0;
				d[j] |= 0;
			} 
			else 
			{
				/* We read 1 */
				d[j] |= 1;
			}
		}
	}
	cho_ngat;
	/* Check for parity */
	if ((d[0] + d[1] + d[2] + d[3]) != d[4]) 
	{
		loi=1;
	}
	
	/* Set humidity */
	//data->Hum = d[0] << 8 | d[1];
	da_21=d[0];
	da_21<<=8;
	da_21|=d[1];
	nd_21=d[2];
	nd_21<<=8;
	nd_21|=d[3];
// 	/* Negative temperature */
// 	if (d[2] & 0x80) 
// 	{
// 		//data->Temp = -((d[2] & 0x7F) << 8 | d[3]);
// 		nd_21= -((d[2] & 0x7F) << 8 | d[3]);
// 		} 
// 		else 
// 		{
// 		nd_21== (d[2]) << 8 | d[3];
// 		//data->Temp = (d[2]) << 8 | d[3];
// 	}
}







u8 doc_byte()
{
	int8 i;
	u8 a;
	int8 du_lieu;
	dht21_d=vao;
	dht21_o=1;
	for (i=0;i<8;i++)
	{
		while (dht21_i==0);
		delay_us(50); // tao thoi gian tre us 
		a=dht21_i;
		du_lieu<<=1;
		du_lieu=du_lieu|a;
		while(dht21_i==1);
	}
	return du_lieu;
}
	
//======================================== 
uint8_t dht21_read_8bits(void)
{
	uint8_t i, flag, data = 0;
	uint8_t temp;

	for(i=0; i<8; i++)
	{
		flag = 2;
		temp = 0;

		while((dht21_i == 0) && flag++);
		delay_us(30);

		if(dht21_i == 1) temp = 1;

		flag = 2;
		while((dht21_i == 1) && flag++);

		if(flag == 1) break;

		data <<= 1;
		data |= temp;

	}

	return data;
}
//======================================== 

uint8_t dht21_get_data(void)
{
	u8 out;
	u8 loi=0;
	uint8_t flag;
	cam_ngat;
	dht21_d=ra;
	dht21_o=0;
	delay_us(1000);
	dht21_o=1;
	dht21_d=vao;
	delay_us(30);
	out=0;
	while (dht21_i==1)
	{
		if (out > 20) {loi=1;}
		out++;
		delay_us(1);
	}
	if (dht21_i == 0)
	{
		flag = 2;
		/* waitting the ACK signal (Low, 80us) */
		while ((dht21_i == 0));// && flag++);

		flag = 2;
		/* waitting the DATA start signal (High, 80us) */
		while ((dht21_i == 1));// && flag++);

		dah = dht21_read_8bits();
		dal = dht21_read_8bits();
		ndh = dht21_read_8bits();
		ndl = dht21_read_8bits();
		CRC = dht21_read_8bits();
		
		dht21_d=ra;
		dht21_o=1;
		if((dah+dal+ndh+ndl)==CRC)
		{
			nd_21=ndh;
			nd_21<<=8;
			nd_21|=ndl;
			da_21=dal;
			da_21<<=8;
			da_21|=dah;
		}
	}
	cho_ngat;
}
//======================================== 
void doc_du_lieu_dht21()
{
	u8 out;
	cam_ngat;
	_delay_us(1020); // tao thoi gian tre us
	dht21_d=vao;
	dht21_o=1;
	_delay_us(50); // tao thoi gian tre us 
	
	out = 80;
	while ((dht21_i == 0) && out>0)
	{
		out--;
		delay_us(1); // tao thoi gian tre us
	}
	out = 80;
	while ((dht21_i == 1) && out>0)
	{
		out--;
		delay_us(1); // tao thoi gian tre us
	}
	dah=doc_byte();
	dal=doc_byte();
	ndh=doc_byte();
	ndl=doc_byte();
	CRC=doc_byte();
	cho_ngat;
	if((dah+dal+ndh+ndl)==CRC)
	{
		nd_21=ndh;
		nd_21<<=8;
		nd_21|=ndl;
		da_21=dal;
		da_21<<=8;
		da_21|=dah;
	}
}





//---------------Defination for sensor IO interface--------/

//-----------------------------------------------//
u8 U8FLAG;
u8 U8temp;
u8 U8comdata;
void rd8bit(void){
	u8 i;
	u8 U8FLAG;
	dht21_d=vao;
	dht21_o=1;
	for(i=0;i<8;i++){
		U8FLAG=2;
		while(dht21_i==0 && U8FLAG++);
		delay_us(30);
		U8temp=0;
		if(dht21_i==1) U8temp=1; // bit rd is 1, set U8temp=1
		U8FLAG=2;
		while(dht21_i==1 && U8FLAG++);
		if(U8FLAG==1)break;
		U8comdata<<=1;
		U8comdata|=U8temp;
	}
}

u8 dht21_kt;
void rdbus(void){
	cam_ngat;
	delay_ms(10);
	dht21_d=ra;
	dht21_o=0;
	delay_ms(1);
	dht21_o=1;
	delay_us(40);
	dht21_d=vao;
	dht21_o=1;
	if(dht21_i==0){
		U8FLAG=2;
		while(dht21_i==0&&U8FLAG++);
		U8FLAG=2;
		while(dht21_i==1&&U8FLAG++);
		rd8bit();
		dah=U8comdata;
		rd8bit();
		dal=U8comdata;
		rd8bit();
		ndh=U8comdata;
		rd8bit();
		ndl=U8comdata;
		rd8bit();
		dht21_kt=U8comdata;
		U8temp=(dah+dal+ndh+ndl);
		if(U8temp==dht21_kt){
// 			U8RH_data_H=U8RH_data_H_temp;
// 			U8RH_data_L=U8RH_data_L_temp;
// 			U8T_data_H=U8T_data_H_temp;
// 			U8T_data_L=U8T_data_L_temp;
// 			U8checkdata=U8checkdata_temp;
// 			U16RH_data<<=16;
// 			U16RH_data|=U8RH_data_H;
// 			U16RH_data<<=8;
// 			U16RH_data|=U8RH_data_L;
// 			U16T_data<<=8;
// 			U16T_data|=U8T_data_H;
// 			U16T_data<<=8;
// 			U16T_data|=U8T_data_L;
		}//CRC checked

	}//read data-bus.
	cho_ngat;

}//rdbus-end





u8 doc_8_bit(void){
	u8 i;
	u8 du_lieu;
	u8 tam;
	u8 out;
	for(i=0;i<8;i++){
		out=2;
		while(dht21_i==0 && out++);
		delay_us(30);
		tam=0;
		if(dht21_i==1) tam=1;     // bit rd is 1, set U8temp=1
		out=2;
		while((dht21_i==1) && out++);
		if(U8FLAG==1)break;
		du_lieu<<=1;
		du_lieu|=tam;
	}
}

void doc_dht21()
{
	u8 out;
	u8 kt;
	cam_ngat;
	dht21_d=ra;
	dht21_o=0;
	delay_us(500);
	dht21_o=1;
	delay_us(40);
	dht21_d=vao;
	if(!dht21_i==0)
	{
		out=2;
		while((!dht21_i==0)&&out++);
		out=2;
		while((dht21_i==1)&&out++);
		dah = doc_8_bit();
		dal = doc_8_bit();
		ndh = doc_8_bit();
		ndl = doc_8_bit();
		kt = doc_8_bit();
		cho_ngat;
		if((dah+dal+ndh+ndl)==kt)
		{
			nd_21=ndh;
			nd_21<<=8;
			nd_21|=ndl;
			da_21=dal;
			da_21<<=8;
			da_21|=dah;
		}
// 		U8temp=(U8T_data_H_temp+U8T_data_L_temp+U8RH_data_H_temp+U8RH_data_L_temp);
// 		if(U8temp==U8checkdata_temp){
// 			U8RH_data_H=U8RH_data_H_temp;
// 			U8RH_data_L=U8RH_data_L_temp;
// 			U8T_data_H=U8T_data_H_temp;
// 			U8T_data_L=U8T_data_L_temp;
// 			U8checkdata=U8checkdata_temp;
// 
// 			U16RH_data<<=8;
// 			U16RH_data|=U8RH_data_H;
// 			U16RH_data<<=8;
// 			U16RH_data|=U8RH_data_L;
// 			U16T_data<<=8;
// 			U16T_data|=U8T_data_H;
// 			U16T_data<<=8;
// 			U16T_data|=U8T_data_L;
		}//CRC checked
	//cho_ngat;
	}//read data-bus.


#endif
