    #define     RF_DATA_OUT     PORTB_2 
#define rf_out_p PORTB
#define rf_out_d DDRB
#define rf_out (1<<4)
#define t_rf 1100
u8 tg_phat_rf;

void rf_init()
{
	rf_out_d |= rf_out;
	rf_out_p &= ~rf_out;
}
//======================================== 
void RF_SentByte(uint8_t dat)
{
	u8 i;
	for(i = 0;i < 8;i++)
	{
		if(dat & 0x01)
		{
			rf_out_p |= rf_out;
			_delay_us(t_rf);
			rf_out_p &= ~rf_out;
			_delay_us(t_rf);
		}
		else
		{
			rf_out_p &= ~rf_out;
			_delay_us(t_rf);
			rf_out_p |= rf_out;
			_delay_us(t_rf);
		}
		dat = dat >> 1;
	}
}     
//======================================== 
void RF_FrameStart()
{
    RF_SentByte(0xff);
    RF_SentByte(0xff);
    RF_SentByte(0xff);    
}          
//======================================== 
void RF_PulseStart()
{
    rf_out_p |= rf_out;
    _delay_ms(2);  
    rf_out_p &= ~rf_out;
    _delay_ms(2);
}            
//========================================       
void RF_PulseFinish()
{
    rf_out_p |= rf_out;
    _delay_ms(3);  
    rf_out_p &= ~rf_out;
    _delay_ms(3);
}       
//======================================== 
void RF_SentArray(uint8_t *Array,uint8_t Length)
{
    uint8_t i=0;
    while(Length--)
    {
        RF_SentByte(Array[i]);
        i++;
    }    
} 
//======================================== 
void RF_SentFrame(uint8_t *Data,uint8_t Length)
{
    RF_FrameStart();
    RF_PulseStart();
    _delay_us(500); 
    RF_SentArray(Data,Length);
    RF_PulseFinish();  
}
//======================================== 


