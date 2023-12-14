#include "i2csoft.c"
#include "!/1 thoi gian.h"
u8 bin2bcd(u8 binary_value); 
u8 bcd2bin(u8 bcd_value);
u8 doc_byte_1307(u8 diachi);
void ghi_byte_1307(u8 diachi,u8 dulieu); 
void ds1307_dat_GPG(u8 gio,u8 phut,u8 giay);                  
//========================================
void ds1307_init(void) // khoi tao cho ds1307 
{               
   ghi_byte_1307(7,0x90); // tao xung 1 hz tai chan sout DS1307
   u8 a; // byte luu tam gia tri o nho 0 cua ds
   a=doc_byte_1307(0); // doc o nho 0
   u8 b=a&0x80; // byte dung de so sanh
   if (b!=0)
   {
      a&=0x7f;
      ghi_byte_1307(0,a);
   }
}
//======================================== 
// void ds1307_dat_tgbt(u8 gio_bt,u8 phut_bt)
// {         
//    cli();  // khong cho phep ngat khi dang doc du lieu
//    SoftI2CStart();  
//    SoftI2CWriteByte(0xD0); // I2C write address 
//    SoftI2CWriteByte(0x20); // Start at REG 0 - Seconds 
//    SoftI2CWriteByte(gio_bt); // REG 0 
//    SoftI2CWriteByte(phut_bt); // REG 1 
//    SoftI2CStop(); 
//    sei(); // cho phep ngat hoat dong tro lai 
// }
//========================================
// void ds1307_doc_tgbt(u8 *gio_bt,u8 *phut_bt)
// {
//    cli();
//    SoftI2CStart();
//    SoftI2CWriteByte(0xD0);
//    SoftI2CWriteByte(0x20); // Start at REG 0 - Seconds
//    //SoftI2CStop();
//    SoftI2CStart();
//    SoftI2CWriteByte(0xD1);
//    gio_bt = SoftI2CReadByte(1);
//    phut_bt = SoftI2CReadByte(1);
//    SoftI2CStop(); 
//    sei(); 
// }
//========================================
u8 DS1307doc_byte(u8 dia_chi)
{
	#ifndef khong_cam_ngat_i2c
	cli();
	#endif
	SoftI2CStart();
	SoftI2CWriteByte(0xD0);
	SoftI2CWriteByte(dia_chi); // Start at REG 0 - Seconds
	SoftI2CStart();
	SoftI2CWriteByte(0xD1);
	dia_chi = SoftI2CReadByte(0);
	SoftI2CStop();
	#ifndef khong_cam_ngat_i2c
	sei();
	#endif
	return dia_chi;
}
//======================================== 
void DS1307ghi_byte(uint8_t dia_chi,uint8_t du_lieu)
{
	SoftI2CStart();
	SoftI2CWriteByte(0xD0);	//DS1307 address + W
	SoftI2CWriteByte(dia_chi);
	SoftI2CWriteByte(du_lieu);
	SoftI2CStop();
}
//======================================== 
void ds1307_dat_TNTN(u8 thu,u8 ngay,u8 thang,u8 nam)
{
   cli();
   SoftI2CStart();  
   SoftI2CWriteByte(0xD0); // I2C write address 
   SoftI2CWriteByte(0x03); // Start at REG 0 - Seconds 
   SoftI2CWriteByte(bin2bcd(thu)); // REG 0 
   SoftI2CWriteByte(bin2bcd(ngay)); // REG 0 
   SoftI2CWriteByte(bin2bcd(thang)); // REG 1 
   SoftI2CWriteByte(bin2bcd(nam)); // REG 2 
   SoftI2CWriteByte(0x90);            // REG 7 - Enable squarewave output pin 
   SoftI2CStop();   
   sei(); 
} 
//========================================
void ds1307_dat_NTN(u8 ngay,u8 thang,u8 nam)
{ 
   cli();
   SoftI2CStart();  
   SoftI2CWriteByte(0xD0); // I2C write address 
   SoftI2CWriteByte(0x04); // Start at REG 0 - Seconds 
   SoftI2CWriteByte(bin2bcd(ngay)); // REG 0 
   SoftI2CWriteByte(bin2bcd(thang)); // REG 1 
   SoftI2CWriteByte(bin2bcd(nam)); // REG 2 
   SoftI2CWriteByte(0x90);            // REG 7 - Enable squarewave output pin 
   SoftI2CStop(); 
   sei(); 
} 
//========================================
void ds1307_dat_GPG(u8 gio,u8 phut,u8 giay) 
{ 
	#ifndef khong_cam_ngat_i2c
   cli();
   #endif
  giay &= 0x7F; 
  gio &= 0x3F; 

   SoftI2CStart();  
   SoftI2CWriteByte(0xD0); // I2C write address 
   SoftI2CWriteByte(0x00); // Start at REG 0 - Seconds 
   SoftI2CWriteByte(bin2bcd(giay)); // REG 0 
   SoftI2CWriteByte(bin2bcd(phut)); // REG 1 
   SoftI2CWriteByte(bin2bcd(gio)); // REG 2 
   SoftI2CWriteByte(0x90);            // REG 7 - Enable squarewave output pin 
   SoftI2CStop(); 
   #ifndef khong_cam_ngat_i2c
   sei(); 
   #endif
} 
//========================================
void ds1307_set_date_time() 
{
	#ifndef khong_cam_ngat_i2c
   cli();
   #endif
	DS1307ghi_byte(0,bin2bcd(giay));
	delay_ms(1); // tao thoi gian tre ms 
	DS1307ghi_byte(1,bin2bcd(phut));
	delay_ms(1); // tao thoi gian tre ms 
	DS1307ghi_byte(2,bin2bcd(gio));
	delay_ms(1); // tao thoi gian tre ms 
	DS1307ghi_byte(4,bin2bcd(ngay));
	delay_ms(1); // tao thoi gian tre ms 
	DS1307ghi_byte(5,bin2bcd(thang));
	delay_ms(1); // tao thoi gian tre ms 
	DS1307ghi_byte(6,bin2bcd(nam));
	delay_ms(1); // tao thoi gian tre ms 
	#ifndef khong_cam_ngat_i2c
  sei(); 
  #endif
} 
//========================================
void ds1307_doc_giay()
{
   cli();
   SoftI2CStart();
   SoftI2CWriteByte(0xD0);
   SoftI2CWriteByte(0x00); // Start at REG 0 - Seconds
   SoftI2CStart();
   SoftI2CWriteByte(0xD1);
   giay = bcd2bin(SoftI2CReadByte(0));
   SoftI2CStop(); 
   sei(); 
}
//========================================
void ds1307_doc_phut()
{
	#ifndef khong_cam_ngat_i2c
	cli();
	#endif
	SoftI2CStart();
	SoftI2CWriteByte(0xD0);
	SoftI2CWriteByte(0x01); // Start at REG 0 - Seconds
	SoftI2CStart();
	SoftI2CWriteByte(0xD1);
	phut = bcd2bin(SoftI2CReadByte(0));
	SoftI2CStop();
	#ifndef khong_cam_ngat_i2c
	sei();
	#endif
}
//========================================
void ds1307_doc_gio()
{
	#ifndef khong_cam_ngat_i2c
	cli();
	#endif
	SoftI2CStart();
	SoftI2CWriteByte(0xD0); 
	SoftI2CWriteByte(0x02); // Start at REG 0 - Seconds
	SoftI2CStart();
	SoftI2CWriteByte(0xD1);
	gio = bcd2bin(SoftI2CReadByte(0));
	SoftI2CStop();
	#ifndef khong_cam_ngat_i2c
	sei();
	#endif
}
//========================================
void ds1307_get_time()
{ 
   u8 d,p,da;
   da=bcd2bin(DS1307doc_byte(0));
   p=bcd2bin(DS1307doc_byte(1));
   d=bcd2bin(DS1307doc_byte(2));
   if(da<60&&p<60&&d<24)
   {
	   giay = da;
	   phut = p;
	   gio = d;
   }
}
//========================================
void ds1307_get_date()
{ 
	u8 n,t,na;
	n=bcd2bin(DS1307doc_byte(4));
	t=bcd2bin(DS1307doc_byte(5));
	na=bcd2bin(DS1307doc_byte(6));
	if(n<32&&t<13&&n<100)
	{
		ngay = n;
		thang = t;
		nam = na;
	}
}
//========================================
u8 doc_byte_1307(u8 diachi)
{ 
	#ifndef khong_cam_ngat_i2c
   cli();
   #endif
   SoftI2CStart();
   SoftI2CWriteByte(0xD0); // ghi vao ds1307 chieu ghi
   SoftI2CWriteByte(diachi); // ghi dia chi can doc
   SoftI2CStart(); // start bit i2c 
   SoftI2CWriteByte(0xD1); // ghi vao ds1307 chieu doc
   diachi = SoftI2CReadByte(0);
   SoftI2CStop();
   return diachi;  
   #ifndef khong_cam_ngat_i2c
   sei(); 
   #endif
}
//========================================                                                         
void ghi_byte_1307(u8 diachi,u8 dulieu)
{
	#ifndef khong_cam_ngat_i2c
   cli();
   #endif
   SoftI2CStart();
   SoftI2CWriteByte(0xD0); // ghi vao ds1307 chieu ghi
   SoftI2CWriteByte(diachi); // ghi dia chi can doc
   SoftI2CWriteByte(dulieu); // 
   SoftI2CStop();
   #ifndef khong_cam_ngat_i2c
   sei();
   #endif
}
