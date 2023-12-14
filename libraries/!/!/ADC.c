
#define	AREF_MODE	0						//dien ap tham chieu ngoai, dien ap tren chan Vref
#define	AVCC_MODE	(1<<REFS0)				//dung dien ap chan AVcc lam dien ap tham chieu, chan Vref gan voi 1 tu dien
#define	INT_MODE	(1<<REFS1)|(1<<REFS0)	//dung dien ap tham chieu noi 2.56V,  chan Vref gan voi 1 tu dien
#define ADC_VREF_TYPE AVCC_MODE        		//dinh nghia dien ap tham chieu
#define ADC_8_bit 0b01100000   // PA0 -> ADC0, ADLAR=1 (8-bit)
#ifndef ADC_CHE_DO 
#define	ADC_CHE_DO AVCC_MODE
#endif
//======================================== 
unsigned int read_adc(unsigned char adc_channel) 
{//chuong trinh con doc ADC theo tung channel
	#ifdef aref
	ADMUX=adc_channel|aref;//(1<<REFS0);
	#else
	ADMUX=adc_channel|ADC_CHE_DO;//(1<<REFS0);
	#endif
	ADCSRA|=(1<<ADSC); 					//bat dau chuyen doi
	loop_until_bit_is_set(ADCSRA,ADIF); //cho den khi nao bit ADIF==1
	return ADCW;
}
//========================================
unsigned int read_adc_5(unsigned char adc_channel)
{//chuong trinh con doc ADC theo tung channel
	#ifdef aref
	ADMUX=adc_channel|ADC_CHE_DO;//(1<<REFS0);
	#else 
	ADMUX=adc_channel|ADC_CHE_DO;//(1<<REFS0);
	#endif
	ADCSRA|=(1<<ADSC); 					//bat dau chuyen doi
	loop_until_bit_is_set(ADCSRA,ADIF); //cho den khi nao bit ADIF==1
	return ADCW;
}
unsigned int doc_adc_lap(u8 kenh, u8 lan_lap)
{
	unsigned int i;
	unsigned long gia_tri_adc=0;
	#ifdef aref
	ADMUX=kenh|aref;//(1<<REFS0);
	#else
	ADMUX=kenh|ADC_CHE_DO;//(1<<REFS0);
	#endif
	for(i=0;i<lan_lap;i++)
	{
		ADCSRA|=(1<<ADSC); 					//bat dau chuyen doi
		_delay_us(100);
		loop_until_bit_is_set(ADCSRA,ADIF); //cho den khi nao bit ADIF==1
		gia_tri_adc=gia_tri_adc+ADCW;
	}
	return ((unsigned int)(gia_tri_adc/lan_lap));
}
//======================================== 
unsigned char read_adc_8(unsigned char adc_channel)
{//chuong trinh con doc ADC theo tung channel
	ADMUX=adc_channel|ADC_8_bit;
	ADCSRA|=(1<<ADSC); 					//bat dau chuyen doi
	loop_until_bit_is_set(ADCSRA,ADIF); //cho den khi nao bit ADIF==1
	return ADCH;
}
//========================================
unsigned int read_adc_lap(unsigned char adc_channel)
{//chuong trinh con doc ADC theo tung channel
	unsigned int i;
	unsigned long gia_tri_adc=0;
	#ifdef aref
	ADMUX=adc_channel|aref;//(1<<REFS0);
	#else
	ADMUX=adc_channel|ADC_CHE_DO;//(1<<REFS0);
	#endif
	for(i=0;i<400;i++)
	{
		ADCSRA|=(1<<ADSC); 					//bat dau chuyen doi
		_delay_us(100);
		loop_until_bit_is_set(ADCSRA,ADIF); //cho den khi nao bit ADIF==1
		gia_tri_adc=gia_tri_adc+ADCW;
	}
	return ((unsigned int)(gia_tri_adc/400));
}
//======================================== 
void ADC_init (void)
{
	ADMUX = ADC_CHE_DO; // dung dien ap chan AVcc lam dien ap tham chieu, chan Vref gan voi 1 tu dien
	//ADMUX=0;
	//ADCSRA=(1<<ADEN)|(1<<ADSC) |(1<<ADPS2)|(1<<ADPS0); 	//enable ADC, khong dung interrupt
	ADCSRA |= ((1<<ADEN) | (1<<ADSC) | (1<<ADPS1)); // ADC prescaler at 4
	//ADCSRA |= ((1<<ADEN) | (1<<ADSC) | (1<<ADPS0)); // Xung nhip chia 2
}
void adc_khoi_tao_5V ()
{
	
	ADMUX = AVCC_MODE; // dung dien ap chan AVcc lam dien ap tham chieu, chan Vref gan voi 1 tu dien
	//ADMUX=0;
	ADCSRA=(1<<ADEN)|(1<<ADSC) |(1<<ADPS2)|(1<<ADPS0); 	//enable ADC, khong dung interrupt
	//ADCSRA |= ((1<<ADEN) | (1<<ADSC) | (1<<ADPS1)); // ADC prescaler at 4
	//ADCSRA |= ((1<<ADEN) | (1<<ADSC) | (1<<ADPS0)); // Xung nhip chia 2
}
//========================================
unsigned int read_adc_256 (unsigned char adc_channel)
{//chuong trinh con doc ADC theo tung channel
	#ifdef aref
	ADMUX=adc_channel|aref;//(1<<REFS0);
	#else
	ADMUX=adc_channel|INT_MODE;//(1<<REFS0);
	#endif
	ADCSRA|=(1<<ADSC); 					//bat dau chuyen doi
	loop_until_bit_is_set(ADCSRA,ADIF); //cho den khi nao bit ADIF==1
	return ADCW;
}

void ADC_init_256 (void)
{
	ADMUX = INT_MODE; // dung dien ap chan AVcc lam dien ap tham chieu, chan Vref gan voi 1 tu dien
	//ADMUX=0;
	//ADCSRA=(1<<ADEN)|(1<<ADSC) |(1<<ADPS2)|(1<<ADPS0); 	//enable ADC, khong dung interrupt
	ADCSRA |= ((1<<ADEN) | (1<<ADSC) | (1<<ADPS1)); // ADC prescaler at 4
	//ADCSRA |= ((1<<ADEN) | (1<<ADSC) | (1<<ADPS0)); // Xung nhip chia 2
}
