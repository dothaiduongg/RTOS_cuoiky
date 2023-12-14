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

/*----------------------------------------------------------------------------
Noi Dung    :   Ma hoa va gui di 1 bit du lieu (1->10, 0->01, T=1ms).  
Tham Bien   :   i: bit du lieu can gui (bit 0 hoac bit 1). 
Tra Ve      :   Khong.
 -----------------------------------------------------------------------------*/

void RF_SentBit(uint8_t i)
{
    if(i)  
    {
        rf_out_p |= rf_out;
        _delay_us(500);  
        rf_out_p &= ~rf_out;
        _delay_us(500);
    }                     
    else 
    {
        rf_out_p &= ~rf_out;
        _delay_us(500);    
        rf_out_p |= rf_out;
        _delay_us(500);
    }                
}   
//========================================         
void truyen_bit_rf(uint8_t i)
{
	if(i==1)
	{

	}
	else
	{
		rf_out_p |= rf_out;
		_delay_us(t_rf*2);
		rf_out_p &= ~rf_out;
		_delay_us(t_rf);
	}
}


/*----------------------------------------------------------------------------
Noi Dung    :   Gui 1 byte du lieu. 
Tham Bien   :   byte: byte du lieu can gui.
Tra Ve      :   Khong.
 -----------------------------------------------------------------------------*/

void RF_SentByte(u8 dat)
{
//     uint8_t i=0x80;
//     while(i)  
//     {
//         truyen_bit_rf(Byte&i);
//         i>>=1;
//     }
	unsigned char i;
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
			rf_out_p |= rf_out;
			_delay_us(t_rf*2);
			rf_out_p &= ~rf_out;
			_delay_us(t_rf);
		}
		dat = dat >> 1;
	}
}     
//========================================
void truyen_bit_st_rf()
{
	RF_SentByte(0xff);
	RF_SentByte(0xff);
	RF_SentByte(0xff);
	rf_out_p |= rf_out;
	_delay_us(t_rf*4);
	rf_out_p &= ~rf_out;
	_delay_us(t_rf);
}
//========================================
void truyen_bit_t_rf()
{
	rf_out_p |= rf_out;
	_delay_us(t_rf);
	rf_out_p &= ~rf_out;
	_delay_us(t_rf);
}
/*----------------------------------------------------------------------------
Noi Dung    :   Gui 1 khung gom 3 byte 0xFF de lam sach duong truyen.   
Tham Bien   :   Khong.
Tra Ve      :   Khong.
 -----------------------------------------------------------------------------*/

void RF_FrameStart()
{
    RF_SentByte(0);
   // RF_SentByte(0xff);
   // RF_SentByte(0xff);    
}          

/*----------------------------------------------------------------------------
Noi Dung    :   Gui 1 xung vuong co chu ky T=4ms de bat dau khung truyen.  
Tham Bien   :   Khong.
Tra Ve      :   Khong.
 -----------------------------------------------------------------------------*/

void RF_PulseStart()
{
    rf_out_p |= rf_out;
    _delay_ms(2);  
    rf_out_p &= ~rf_out;
    _delay_ms(2);
}            

/*----------------------------------------------------------------------------
Noi Dung    :   Gui 1 xung vuong co chu ky T=6ms de ket thuc khung truyen.
Tham Bien   :   Khong.
Tra Ve      :   Khong.
 -----------------------------------------------------------------------------*/
      
void RF_PulseFinish()
{
    rf_out_p |= rf_out;
    _delay_ms(3);  
    rf_out_p &= ~rf_out;
    _delay_ms(3);
}       

/*----------------------------------------------------------------------------
Noi Dung    :   Gui nhieu byte du lieu.
Tham Bien   :   *array: con tro luu tru dia chi cac byte du lieu can truyen.
                length: so byte du lieu can truyen.
Tra Ve      :   Khong.
 -----------------------------------------------------------------------------*/

void RF_SentArray(uint8_t *Array,uint8_t Length)
{
    uint8_t i=0;
    while(Length--)
    {
        RF_SentByte(Array[i]);
        i++;
    }    
}  

/*----------------------------------------------------------------------------
Noi Dung    :   Gui khung du lieu (FrameStart - PulseStart - Data - PulseFinish).
Tham Bien   :   *data: con tro luu tru dia chi du lieu can truyen.
                length: so byte du lieu can truyen.
Tra Ve      :   Khong.
 -----------------------------------------------------------------------------*/

void truyen_1_rf(uint8_t dl)
{
	RF_FrameStart();
	RF_PulseStart();
	_delay_us(500);
	RF_SentByte(dl);
	RF_PulseFinish();
}
//========================================
void truyen_khung_rf(uint8_t *Data,uint8_t Length)
{
    RF_FrameStart();
    RF_PulseStart();
    _delay_us(500); 
    RF_SentArray(Data,Length);
    RF_PulseFinish();  
}
//======================================== 
void truyen_nhiet_do_rf(u16 gia_tri)
{
	//if(tg_phat_rf==0)
	{
		truyen_bit_st_rf();
		//RF_FrameStart();
		//RF_PulseStart();
		//_delay_us(500);
		if(loi!=0)mau=mau_do;
		RF_SentByte('n');
		RF_SentByte('d');
		RF_SentByte('make8(gia_tri,0)');
		RF_SentByte('make8(gia_tri,1)');
		RF_SentByte(mau);
		RF_SentByte(loi);
		RF_SentByte(mode);
		RF_SentByte(guong);
		RF_SentByte(tu_dong);
		RF_SentByte('e');
		truyen_bit_t_rf();
		//tg_phat_rf=50;
	}
}
//======================================== 
void RF_SentBit(u8 i)
{
	if(i)
	{
		RF_DATA_OUT=1;
		_delay_us(500);
		RF_DATA_OUT=0;
		_delay_us(500);
	}
	else
	{
		RF_DATA_OUT=0;
		_delay_us(500);
		RF_DATA_OUT=1;
		_delay_us(500);
	}
}
//======================================== 
void RF_SentByte(uint8_t Byte)
{
    uint8_t i=0x80;
    while(i)  
    {
        RF_SentBit(Byte&i);
        i>>=1;
    }
}     
//======================================== 

void RF_FrameStart()
{
    RF_SentByte(0xff);
    RF_SentByte(0xff);
    RF_SentByte(0xff);    
}          

/*----------------------------------------------------------------------------
Noi Dung    :   Gui 1 xung vuong co chu ky T=4ms de bat dau khung truyen.  
Tham Bien   :   Khong.
Tra Ve      :   Khong.
 -----------------------------------------------------------------------------*/

void RF_PulseStart()
{
    RF_DATA_OUT=1;
    delay_ms(2);  
    RF_DATA_OUT=0;
    delay_ms(2);
}            

/*----------------------------------------------------------------------------
Noi Dung    :   Gui 1 xung vuong co chu ky T=6ms de ket thuc khung truyen.
Tham Bien   :   Khong.
Tra Ve      :   Khong.
 -----------------------------------------------------------------------------*/
      
void RF_PulseFinish()
{
    RF_DATA_OUT=1;
    delay_ms(3);  
    RF_DATA_OUT=0;
    delay_ms(3);
}       

/*----------------------------------------------------------------------------
Noi Dung    :   Gui nhieu byte du lieu.
Tham Bien   :   *array: con tro luu tru dia chi cac byte du lieu can truyen.
                length: so byte du lieu can truyen.
Tra Ve      :   Khong.
 -----------------------------------------------------------------------------*/

void RF_SentArray(uint8_t *Array,uint8_t Length)
{
    uint8_t i=0;
    while(Length--)
    {
        RF_SentByte(Array[i]);
        i++;
    }    
}  

/*----------------------------------------------------------------------------
Noi Dung    :   Gui khung du lieu (FrameStart - PulseStart - Data - PulseFinish).
Tham Bien   :   *data: con tro luu tru dia chi du lieu can truyen.
                length: so byte du lieu can truyen.
Tra Ve      :   Khong.
 -----------------------------------------------------------------------------*/

void RF_SentFrame(uint8_t *Data,uint8_t Length)
{
    RF_FrameStart();
    RF_PulseStart();
    _delay_us(500); 
    RF_SentArray(Data,Length);
    RF_PulseFinish();  
}

/******************************KET THUC FILE*********************************
______________________________ MinhHa R&D Team______________________________*/