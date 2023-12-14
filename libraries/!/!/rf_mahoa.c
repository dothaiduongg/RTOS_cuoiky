  
    #define     RF_DATA_OUT     PORTB_2 
/*********************************** VI DU *************************************

  // Khai bao 1 mang ky tu de truyen di
  uint8_t str[16];
  // Gui 1 chuoi ky tu 
  sprintf(str,"MinhHaGroup");
  RF_SentFrame(str,11);  
  
********************************************************************************/
#if (__RF_MAHOA_H!=24032014)
    #error "Include Sai File RF_MaHoa.h"
#endif

/*----------------------------------------------------------------------------
Noi Dung    :   Ma hoa va gui di 1 bit du lieu (1->10, 0->01, T=1ms).  
Tham Bien   :   i: bit du lieu can gui (bit 0 hoac bit 1). 
Tra Ve      :   Khong.
 -----------------------------------------------------------------------------*/

void RF_SentBit(uint8_t i)
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

/*----------------------------------------------------------------------------
Noi Dung    :   Gui 1 byte du lieu. 
Tham Bien   :   byte: byte du lieu can gui.
Tra Ve      :   Khong.
 -----------------------------------------------------------------------------*/

void RF_SentByte(uint8_t Byte)
{
    uint8_t i=0x80;
    while(i)  
    {
        RF_SentBit(Byte&i);
        i>>=1;
    }
}     

/*----------------------------------------------------------------------------
Noi Dung    :   Gui 1 khung gom 3 byte 0xFF de lam sach duong truyen.   
Tham Bien   :   Khong.
Tra Ve      :   Khong.
 -----------------------------------------------------------------------------*/

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