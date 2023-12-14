/*
LCD12864R
www.DFRobot.com
*/

#ifndef _LCD12864R_h
#define _LCD12864R_h
//#include <avr/pgmspace.h>
//#include <inttypes.h>

void LCD12864R();

void khoi_tao_lcd(void);
void setPins();
void delayns(void);

void WriteCommand(u8 CMD); 
void WriteData(u8 CMD);


void glcd_c(void);
void DisplayString(int X,int Y,uchar *ptr,int dat);
void DisplaySig(int M,int N,int sig);
void DrawFullScreen(uchar *p);
void glcd_chen_8(u8 kt);
void glcd_tai_bieu_tuong_8 (u8 vi_tri,const char *data)	;
void glcd_icon8 (const char *data,u8 rong);
void glcd_in_dong(unsigned char *DData,u8 cot);
void glcd_tai_so_lon (u8 vi_tri,const char *data,u8 rong);


//u8 ScreenBuffer[16][32];

int DEFAULTTIME;


#define lcdrs dk_bit(PORTC,2) //LCD's RS (DI) pin is connected to Pin0 of AVR
#define lcdrs_d dk_bit(DDRC,2)
#define lcdrw dk_bit(PORTC,3) //LCD's r/w pin is connected to Pin1 of AVR
#define lcdrw_d dk_bit(DDRC,3)
#define lcde dk_bit(PORTC,4) //LCD's e pin is connected to Pin2 of AVR
#define lcde_d dk_bit(DDRC,4)
#define	lcdcs1 dk_bit(PORTA,2) //LCD's CS1 pin is connected to Pin5 of AVR
#define	lcdcs1_d dk_bit(DDRA,2)
// #define	lcdcs2 dk_bit(PORTA,1) //LCD's CS2 pin is connected to Pin5 of AVR
// #define	lcdcs2_d dk_bit(DDRA,1)
#define	lcdrst dk_bit(PORTA,0) //LCD's RST pin is connected to Pin3 of AVR
#define	lcdrst_d dk_bit(DDRA,0)


#define lcd0 dk_bit(PORTC,5) //LCD's RS (DI) pin is connected to Pin0 of AVR
#define lcd0_d dk_bit(DDRC,5)
#define lcd1 dk_bit(PORTC,6) //LCD's r/w pin is connected to Pin1 of AVR
#define lcd1_d dk_bit(DDRC,6)
#define lcd2 dk_bit(PORTC,7) //LCD's e pin is connected to Pin2 of AVR
#define lcd2_d dk_bit(DDRC,7)
#define	lcd3 dk_bit(PORTA,7) //LCD's CS1 pin is connected to Pin5 of AVR
#define	lcd3_d dk_bit(DDRA,7)
#define	lcd4 dk_bit(PORTA,6) //LCD's CS2 pin is connected to Pin5 of AVR
#define	lcd4_d dk_bit(DDRA,6)
#define	lcd5 dk_bit(PORTA,5) //LCD's RST pin is connected to Pin3 of AVR
#define	lcd5_d dk_bit(DDRA,5)
#define	lcd6 dk_bit(PORTA,4) //LCD's CS2 pin is connected to Pin5 of AVR
#define	lcd6_d dk_bit(DDRA,4)
#define	lcd7 dk_bit(PORTA,3) //LCD's RST pin is connected to Pin3 of AVR
#define	lcd7_d dk_bit(DDRA,3)

u8 lcd_data_byte;
u8 lcd_dk_byte; // byte chua dinh nghia các chan dieu khien
#define	dt0 dk_bit(lcd_data_byte,0)
#define	dt1 dk_bit(lcd_data_byte,1)
#define	dt2 dk_bit(lcd_data_byte,2)
#define	dt3 dk_bit(lcd_data_byte,3)
#define	dt4 dk_bit(lcd_data_byte,4)
#define	dt5 dk_bit(lcd_data_byte,5)
#define	dt6 dk_bit(lcd_data_byte,6)
#define	dt7 dk_bit(lcd_data_byte,7)
#define	dkrs dk_bit(lcd_dk_byte,0)
#define	dkrw dk_bit(lcd_dk_byte,1)
#define	dke dk_bit(lcd_dk_byte,2)

u8 column,line;

// 
// byte checkAND[8];
// int temp[8];

u8 hang_b[24] = {};
u8 hang_b2[24][16] = {};
u8 vi_tri_ghep;
u8 byte_ghep;

#define co_xoa_ht 0x01
#define co_ve_dau_dong 0x10
#define co_dat_dia_chi_ram_ht 0b10000000
#endif