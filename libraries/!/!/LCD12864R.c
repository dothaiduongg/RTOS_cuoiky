#include "LCD12864R.h"

//#include "LCDSprite.h"

//#include <wiring.h> 
#include <inttypes.h>
#include <stdio.h>  //not needed yet
#include <string.h> //needed for strlen()
#include <avr/pgmspace.h>

void setPins() 
{
  lcde=1;  
  delayns();
  lcdrs=dkrs;
  lcdrw=dkrw;
  lcd7=dt7;
  lcd6=dt6;
  lcd5=dt5;
  lcd4=dt4;
  lcd3=dt3;
  lcd2=dt2;
  lcd1=dt1;
  lcd0=dt0; 
  delayns();
  lcde=0;
  delayns();

}
void xua_dl()
{
	lcd7=dt7;
	lcd6=dt6;
	lcd5=dt5;
	lcd4=dt4;
	lcd3=dt3;
	lcd2=dt2;
	lcd1=dt1;
	lcd0=dt0;
}

//*********************Sự chậm trễ chức năng************************//
void delayns(void)
{   
	_delay_us(100);
}

void WriteCommand(u8 CMD)
{ 
   delayns();
   delayns();
   lcd_data_byte=CMD;
   dkrs=0;
   dkrw=0;
   setPins(); //WriteCommand
}



void WriteData(u8 CMD)
{  
   delayns();
   delayns();
   lcd_data_byte = CMD;
   dkrs=1;
   dkrw=0;
   setPins(); //WriteData
}


void write_data_lcd(unsigned char WDLCD)
{
	delay_us(300);						// LUU Y SU CAN THIET CUA KHOANG THOI GIAN DELAY NAY
	lcdrs = 1;
	lcdrw = 0;
	lcd_data_byte = WDLCD;
	xua_dl();
	lcde = 1;
	lcde = 0;
}
// ==============================================================================
void write_command_lcd(unsigned char WCLCD,unsigned char BuysC)
{
	if (BuysC)
	delay_us(300);						// LUU Y SU CAN THIET CUA KHOANG THOI GIAN DELAY NAY
	lcdrs = 0;
	lcdrw = 0;
	lcd_data_byte = WCLCD;
	xua_dl();
	lcde = 1;
	lcde = 1;
	lcde = 1;
	lcde = 0;
}

void khoi_tao_lcd(void) 
{
	lcdrs_d=ra; 
	lcdrw_d=ra;
	lcde_d=ra;
	lcd0_d=ra;
	lcd1_d=ra;
	lcd2_d=ra;
	lcd3_d=ra;
	lcd4_d=ra;
	lcd5_d=ra;
	lcd6_d=ra;
	lcd7_d=ra;
	lcdcs1_d=ra;
	lcdcs1=1;
	lcdrst=1;
	lcdrst_d=ra;
	delayns();
	WriteCommand(0x30); // Chuc nang set tu
	WriteCommand(0x0c); // kiểm soát chuyển đổi hiển thị từ 
	WriteCommand (0x01); // Rõ ràng kiểm soát màn hình từ 
	WriteCommand (0x06); // nhập từ điều khiển điểm đặt
}



void glcd_xoa_ht(void)
{  
    WriteCommand(0x30);//
    WriteCommand(0x01);// Xoa hien thi
}

void glcd_chen_8(u8 kt)
{
	Scroll_Char(kt);
	glcd_ghep_dong_5();
}

void DisplayString(int X,int Y,uchar *ptr,int dat)
{
  int i;

  switch(X)
   {
     case 0:  Y|=0x80;break;

     case 1:  Y|=0x90;break;

     case 2:  Y|=0x88;break;

     case 3:  Y|=0x98;break;

     default: break;
   }
  WriteCommand(Y); // Định vị địa chỉ hiển thị bắt đầu

  for(i=0;i<dat;i++)
    { 
      WriteData(ptr[i]); // hiển thị các ký tự đang có giá trị lưu ý, hai mã liên tiếp đại diện cho một nhân vật
    }
}
//========================================
void glcd_ghep_dong_8() // ghep dong cho cac ky tu 5x7
{
	u8 i;
	for(i = 0; i < 8; i++)
	{
		hang_b2[i][byte_ghep]=hang_b[i];
	}
	byte_ghep++;
}
//========================================
void glcd_ghep_dong_5() // ghep dong cho cac ky tu 5x7
{
	u8 i;
	if(vi_tri_ghep+6<8)
	{
		for(i = 0; i < 8; i++)
		{
			hang_b2[i][byte_ghep]|=hang_b[i]>>vi_tri_ghep;
		}
		vi_tri_ghep+=6;
		//byte_ghep++;
	}
	else
	{
		if(vi_tri_ghep==2)
		{
			for(i = 0; i < 8; i++)
			{
				hang_b2[i][byte_ghep]|=hang_b[i]>>2;
			}
		}
		else
		for(i = 0; i < 8; i++)
		{
			hang_b2[i][byte_ghep]|=hang_b[i]>>vi_tri_ghep;
			hang_b2[i][byte_ghep+1]|=hang_b[i]<<8-vi_tri_ghep;
		}
		vi_tri_ghep=vi_tri_ghep-2;
		byte_ghep++;
	}
}
//======================================== 
void glcd_xoa_dem()
{
	u8 i,j;
	for(j=0;j<16;j++)
	{
		for (i=0;i<24;i++)
		{
			hang_b2[i][j]=0;
		}
	}
}
// ==============================================================================
void glcd_in_dong(unsigned char *DData,u8 cot)
{
	unsigned char ListLength,X2;
	vi_tri_ghep=cot;
	byte_ghep=0;
	ListLength = 0;
	glcd_xoa_dem();
	while (DData[ListLength]>=0x20 && DData[ListLength]<0x58)
	{
		Scroll_Char(DData[ListLength]);
		ListLength++;
		if(vi_tri_ghep>=128)
			break;
		
		glcd_ghep_dong_5();
		//vi_tri_ghep++;
	}
}
// ==============================================================================
void glcd_in_dong_(unsigned char *DData)
{
	unsigned char ListLength;
	ListLength = 0;
	while (DData[ListLength]>=0x20 && DData[ListLength]<0x58)
	{
		Scroll_Char(DData[ListLength]);
		ListLength++;
		glcd_ghep_dong_5();
	}
}
//====================================================================
void glcd_icon8 (const char *data,u8 rong)
{
	u8 i=0;
	while(i<rong)
	{
		glcd_tai_bieu_tuong_8 (i,data);
		glcd_ghep_dong_8();
		i++;
	}
}

// ==============================================================================
void glcd_hien_thi_dong(u8 dong)
{
	u8 j,k;
	for(j = dong; j <dong+8; j++)
	{
		LCD_dinh_vi_hang(j);
		for(k=0;k<16;k++)
		{
			write_data_lcd(hang_b2[j-dong][k]);
		}
	}
}
//======================================== 
void DisplaySig(int M,int N,int sig)
{
  switch(M)
   {
     case 0:  N|=0x80;break;

     case 1:  N|=0x90;break;

     case 2:  N|=0x88;break;

     case 3:  N|=0x98;break;

     default: break;
   }
  WriteCommand(N); // định vị địa chỉ hiển thị bắt đầu 
  WriteData (sig); // ra một nhân vật duy nhất
 }

void xoa_ht2()
{
	unsigned char x,y,i;
	write_command_lcd(0x34,1);
	for(i=0;i<9;)
	{
		for(x=0;x<32;x++)
		{
			write_command_lcd((0x80+x),1);
			write_command_lcd((0x80+i),1);
			for(y=0;y<16;y++)
				write_data_lcd(0);
		}
		i+=8;
	}
	write_command_lcd(0x36,1);
	write_command_lcd(0x30,1);
	glcd_xoa_ht(); 
	write_command_lcd(0x34,1);
	write_command_lcd(0x30,1);
	
}

void xoa_ht()
{
	int ygroup,x,y,i;
	int temp;
	int tmp;
	
	for(ygroup=0;ygroup<64;ygroup++) // Viet 1 phan nua cua hinh anh
	{                          // Viet toa do
		if(ygroup<32)
		{
			x=0x80;
			y=ygroup+0x80;
		}
		else
		{
			x=0x88;
			y=ygroup-32+0x80;
		}
		WriteCommand(0x34); // Lenh ghi huong dan mo rong
		WriteCommand(y);  // // ghi truc y phoi hop
		WriteCommand (x); // ghi x-trục tọa độ
		WriteCommand (0x30); // viet lenh chi dan co ban
		for(i=0;i<16;i++)
		{
			WriteData(0xff);
		}
	}
	write_command_lcd(0x36,1);
	write_command_lcd(0x30,1);
}

void LCD_dinh_vi_hang(u8 hang)
{
	u8 x,y;
	if(hang<32)
	{
		x=0x80;
		y=hang+0x80;
	}
	else
	{
		x=0x88;
		y=hang-32+0x80;
	}
	WriteCommand(0x34); // Lenh ghi huong dan mo rong
	WriteCommand(y);  // // ghi truc y phoi hop
	WriteCommand (x); // ghi x-trục tọa độ
	WriteCommand (0x36);
	//WriteCommand (0x30); // viet lenh chi dan co ban
}
void LCD_dinh_vi_diem(u8 hang,u8 cot)
{
	u8 x,y;
	if(hang<32)
	{
		x=0x80;
		y=hang+0x80;
	}
	else
	{
		x=0x88;
		y=hang-32+0x80;
	}
	WriteCommand(0x34); // Lenh ghi huong dan mo rong
	WriteCommand(y);  // // ghi truc y phoi hop
	WriteCommand (x|cot); // ghi x-trục tọa độ
	WriteCommand (0x30); // viet lenh chi dan co ban
}

void DrawFullScreen(uchar *p)
{
      int ygroup,x,y,i;
      int temp;
      int tmp;
             
      for(ygroup=0;ygroup<64;ygroup++) // Viet 1 phan nua cua hinh anh
        {                           // Viet toa do
           if(ygroup<32)
            {
             x=0x80;
             y=ygroup+0x80;
            }
           else 
            {
              x=0x88;
              y=ygroup-32+0x80;    
            }         
           WriteCommand(0x34); // Lenh ghi huong dan mo rong
           WriteCommand(y);  // // ghi truc y phoi hop
           WriteCommand (x); // ghi x-trục tọa độ
           WriteCommand (0x30); // viet lenh chi dan co ban
           tmp=ygroup*16;
           for(i=0;i<16;i++)
		 {
		    temp=p[tmp++];
		    WriteData(temp);
               }
          }
        WriteCommand (0x34); // phần mở rộng lệnh hướng dẫn viết
        WriteCommand (0x36); // hiển thị hình ảnh
}
//======================================== 
// void DrawScreenBuffer(uint8_t X, uint8_t Y) 
// {
// 
// 	int xpos = X/8;
// 	int ypos = (Y-128);
// 
// 	int leftX = X%8;
// 	int orit = checkAND[leftX];
// 
// 	//ScreenBuffer[xpos][ypos] |= orit;
// 
// }
//======================================== 
// void DrawScreenBuffer(uint8_t X, uint8_t Y) {
// 
// 	int xpos = X/8;
// 	int ypos = (Y-128);
// 
// 	int leftX = X%8;
// 	int orit = checkAND[leftX];
// 
// 	ScreenBuffer[xpos][ypos] |= orit;
// 
// }
// ==============================================================================
// ==============================================================================
void lcd_putchar(unsigned char X, unsigned char Y, unsigned char DData)
{
	if(Y<1)
	Y=1;
	if(Y>4)
	Y=4;
	X &= 0x0F;
	switch(Y)
	{
		case 1:X|=0X80;break;
		case 2:X|=0X90;break;
		case 3:X|=0X88;break;
		case 4:X|=0X98;break;
	}
	write_command_lcd(X, 0);
	write_data_lcd(DData);
}
// ==============================================================================
void lcd_puts(unsigned char X, unsigned char Y, unsigned char *DData)
{
	unsigned char ListLength,X2;

	ListLength = 0;
	X2=X;
	if(Y<1)
	Y=1;
	if(Y>4)
	Y=4;
	X &= 0x0F;
	switch(Y)
	{
		case 1:X2|=0X80;break;
		case 2:X2|=0X90;break;
		case 3:X2|=0X88;break;
		case 4:X2|=0X98;break;
	}
	write_command_lcd(X2,1);
	while (DData[ListLength]>=0x20)
	{
		if (X <= 0x0F)
		{
			write_data_lcd(DData[ListLength]);
			ListLength++;
			X++;
			delay_ms(5);
		}
	}
}
//======================================== 
//---------------------------------------- 
void lcd_display_image  (unsigned char *DData)
{
	unsigned char x,y,i;
	unsigned int tmp=0;
	for(i=0;i<9;)
	{
		for(x=0;x<32;x++)
		{
			write_command_lcd(0x34,1);
			write_command_lcd((0x80+x),1);
			write_command_lcd((0x80+i),1);
			write_command_lcd(0x30,1);
			for(y=0;y<16;y++)
			write_data_lcd(DData[tmp+y]);
			tmp+=16;
		}
		i+=8;
	}
	write_command_lcd(0x36,1);
	write_command_lcd(0x30,1);
}

// MODE 8 bit ------------------------------------------------------
void lcd_init(void)
{
	// Function set
	write_command_lcd(0x30,1); 					// Chon che do truyen 8 bit
	delay_us(150);											// delay > 100us
	write_command_lcd(0x30,1); 					// Chon che do truyen 8 bit
	delay_us(50);												// delay > 37us
	
	// Display ON/OFF control
	write_command_lcd(0x0C,1); 					// Cho phep hien thi ra LCD 128x64
	delay_us(120);											// delay > 100us
	
	// Clear LCD
	write_command_lcd(0x01,1); 					// Xoa man hinh
	delay_ms(40);												// delay > 10ms
	 
	// Entry mode set
	write_command_lcd(0x06,1); 					// Chon che do hien thi ki tu ra man hinh LCD 128x64 (Ki tu sau xuat hien ben phai ki tu truoc)
}

void shift_row_buffer_left(u8 columns)	//Function that shifts all rows a given amount to the left
{
	for (u8 buffer_index=0; buffer_index<8; buffer_index++)
	{
		hang_b[buffer_index] <<= columns;
	}
}

void glcd_tai_bieu_tuong_8 (u8 vi_tri,const char *data)	//Function that scrolls a character onto the display from right to left
{
	char temp;
	//shift_row_buffer_left(1);  	//Put a blank column before each new letter.
	//Delay_ms(ScrollSpeed);
	for (u8 i=0; i<8; i++)	//Read one column of char at a time
	{
		shift_row_buffer_left(1);
		temp = pgm_read_byte((char *)((int)data + (8 * vi_tri) + i));	//Get column from progmem
		for (u8 j=0; j<8; j++)						//Cycle through each bit in column
		{
			//Write bits to appropriate row_buffer location
			if (temp & (1<<j))
			hang_b[j] |= 1<<0;
			else
			hang_b[j] &= ~(1<<0);
		}
	}
}
// ==============================================================================
void glcd_hien_thi_dong_16(u8 dong)
{
	u8 j,k;
	for(j = dong; j <dong+16; j++)
	{
		LCD_dinh_vi_hang(j);
		for(k=0;k<16;k++)
		{
			write_data_lcd(hang_b2[j-dong][k]);
		}
	}
}
//========================================
void glcd_ghep_dong_16() // ghep dong cho cac ky tu 5x7
{
	u8 i;
	for(i = 0; i < 16; i++)
	{
		hang_b2[i][byte_ghep]=hang_b[i];
	}
	byte_ghep++;
}
//====================================================================
void glcd_so_lon (const char *data,u8 rong)
{
	u8 i=0;
	while(i<rong)
	{
		glcd_tai_so_lon(i,data,rong);
		glcd_ghep_dong_16();
		i++;
	}
}
// ==============================================================================
void glcd_hien_thi_dong_24(u8 dong)
{
	u8 j,k;
	for(j = dong; j <dong+24; j++)
	{
		LCD_dinh_vi_hang(j);
		for(k=0;k<16;k++)
		{
			write_data_lcd(hang_b2[j-dong][k]);
		}
	}
}
//========================================
void glcd_ghep_dong_24() // ghep dong cho cac ky tu 5x7
{
	u8 i;
	for(i = 0; i < 24; i++)
	{
		hang_b2[i][byte_ghep]=hang_b[i];
	}
	byte_ghep++;
}
//========================================
void glcd_tai_so_24 (u8 vi_tri,const char *data,u8 rong)	//Function that scrolls a character onto the display from right to left
{
	char temp;
	//shift_row_buffer_left(1);  	//Put a blank column before each new letter.
	//Delay_ms(ScrollSpeed);
	for (u8 i=0; i<24; i++)	//Read one column of char at a time
	{
		//shift_row_buffer_left(1);
		temp = pgm_read_byte((char *)((int)data + (vi_tri)+i*rong));	//Get column from progmem
		hang_b[i]=temp;
		//for (u8 j=0; j<8; j++)						//Cycle through each bit in column
		{
			//Write bits to appropriate row_buffer location
			//if (temp & (1<<j))
			//hang_b[j] |= 1<<0;
			//else
			//hang_b[j] &= ~(1<<0);
		}
	}
}
//====================================================================
void glcd_so_24 (const char *data,u8 rong)
{
	u8 i=0;
	while(i<rong)
	{
		glcd_tai_so_24(i,data,rong);
		glcd_ghep_dong_24();
		i++;
	}
}
//======================================== 
void glcd_tai_so_lon (u8 vi_tri,const char *data,u8 rong)	//Function that scrolls a character onto the display from right to left
{
	char temp;
	//shift_row_buffer_left(1);  	//Put a blank column before each new letter.
	//Delay_ms(ScrollSpeed);
	for (u8 i=0; i<16; i++)	//Read one column of char at a time
	{
		//shift_row_buffer_left(1);
		temp = pgm_read_byte((char *)((int)data + (vi_tri)+i*rong));	//Get column from progmem
		hang_b[i]=temp;
		//for (u8 j=0; j<8; j++)						//Cycle through each bit in column
		{
			//Write bits to appropriate row_buffer location
			//if (temp & (1<<j))
			//hang_b[j] |= 1<<0;
			//else
			//hang_b[j] &= ~(1<<0);
		}
	}
}

void Scroll_Char (char myChar)	//Function that scrolls a character onto the display from right to left
{
	myChar -= 32;			//Adjust char value to match our font array indicies
	char temp;
	//shift_row_buffer_left(1);  	//Put a blank column before each new letter.
	//Delay_ms(ScrollSpeed);
	for (u8 i=0; i<5; i++)	//Read one column of char at a time
	{
		shift_row_buffer_left(1);
		temp = pgm_read_byte((char *)((int)font5x7 + (5 * myChar) + i));	//Get column from progmem
		for (u8 j=0; j<8; j++)						//Cycle through each bit in column
		{
			//Write bits to appropriate row_buffer location
			if (temp & (1<<j))
				hang_b[j] |= 1<<0;
			else 
				hang_b[j] &= ~(1<<0);
		}
	}
	for (u8 j=0; j<8; j++)						//Cycle through each bit in column
	{
		hang_b[j]=hang_b[j] <<3;
	}
}