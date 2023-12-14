/******************************************************************************
  *Ten Tep       :     RF_MaHoa.h
  *Ngay          :     13/03/2014
  *Tac Gia       :     MinhHa R&D Team
  *Cong Ty       :     MinhHaGroup
  *Webside       :     mcu.banlinhkien.vn
  *Phien Ban     :     V1.0
  *Tom Tat       :     Khai bao cac ham su dung RF trong che do ma hoa
  *
  *
  ******************************************************************************
  * Chu Y        :   Phai dinh nghia chan Data cua RF 315(433)M vao file main.h
  * Vi Du        : 
  
    #define     RF_DATA_OUT     PORTB_2 
                              
  ******************************************************************************
**/
/*********************************** VI DU *************************************

  // Khai bao 1 mang ky tu de truyen di
  uint8_t str[16];
  // Gui 1 chuoi ky tu 
  sprintf(str,"MinhHaGroup");
  RF_SentFrame(str,11);  
  
********************************************************************************/
#ifndef __RF_MAHOA_H
#define __RF_MAHOA_H       24032014

//#include "Main\main.h"

/*----------------------------------------------------------------------------
Noi Dung    :   Ma hoa va gui di 1 bit du lieu.  
Tham Bien   :   i: bit du lieu can gui (bit 0 hoac bit 1). 
Tra Ve      :   Khong.
 -----------------------------------------------------------------------------*/
void RF_SentBit(uint8_t i);            

/*----------------------------------------------------------------------------
Noi Dung    :   Gui 1 byte du lieu. 
Tham Bien   :   byte: byte du lieu can gui.
Tra Ve      :   Khong.
 -----------------------------------------------------------------------------*/
void RF_SentByte(uint8_t Byte);        

/*----------------------------------------------------------------------------
Noi Dung    :   Gui 1 khung gom 3 byte 0xFF de lam sach duong truyen.   
Tham Bien   :   Khong.
Tra Ve      :   Khong.
 -----------------------------------------------------------------------------*/
void RF_FrameStart();          

/*----------------------------------------------------------------------------
Noi Dung    :   Gui 1 xung vuong co chu ky T=4ms de bat dau khung truyen.  
Tham Bien   :   Khong.
Tra Ve      :   Khong.
 -----------------------------------------------------------------------------*/
void RF_PulseStart();            

/*----------------------------------------------------------------------------
Noi Dung    :   Gui 1 xung vuong co chu ky T=6ms de ket thuc khung truyen.
Tham Bien   :   Khong.
Tra Ve      :   Khong.
 -----------------------------------------------------------------------------*/      
void RF_PulseFinish();       

/*----------------------------------------------------------------------------
Noi Dung    :   Gui nhieu byte du lieu.
Tham Bien   :   *array: con tro luu tru dia chi cac byte du lieu can truyen.
                length: so byte du lieu can truyen.
Tra Ve      :   Khong.
 -----------------------------------------------------------------------------*/
void RF_SentArray(uint8_t *Array,uint8_t Length);   

/*----------------------------------------------------------------------------
Noi Dung    :   Gui khung du lieu (FrameStart - PulseStart - Data - PulseFinish).
Tham Bien   :   *data: con tro luu tru dia chi du lieu can truyen.
                length: so byte du lieu can truyen.
Tra Ve      :   Khong.
 -----------------------------------------------------------------------------*/
void RF_SentFrame(uint8_t *Data,uint8_t Length);     

#endif 
/******************************KET THUC FILE*********************************
______________________________ MinhHa R&D Team______________________________*/