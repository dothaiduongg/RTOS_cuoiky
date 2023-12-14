/*
LCD12864
Created by Markos Kyritsis
This code is completely open source, and you may edit it however you like. 
Please support the Arduino community, and upload any bug fixes to the relative
page. 
Keep in mind that the code is for demonstration purposes only, I can't be
held responsible if your device suddenly zaps you into millions of little
atoms, and you live the rest of your existence in a quantum universe where
nothing makes sense anymore (you know, you exist in more than one place, changing
between matter and waves, while at the same time half your electrons are entangled
in some other point in space and time). 
Other than that, enjoy... =D
*/

#include <avr/pgmspace.h>
#include <inttypes.h>


 void Initialise(void);
 void selectCS1(void);
void setPins(uint8_t tRS, uint8_t tRW, uint8_t tD7, uint8_t tD6, uint8_t tD5, uint8_t tD4, uint8_t tD3, uint8_t tD2, uint8_t tD1, uint8_t tD0);
void delayns(void);
void VectorConverter(uint8_t vector);
void VectorConvertermany(uint8_t vector, uint8_t amount);

void Render(void);
void DrawPixel(uint8_t startX, uint8_t startY);
void DrawBrLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
void DrawCircle(uint8_t x0, uint8_t y0, uint8_t radius);
void DrawRectangle(uint8_t x0, uint8_t y0, uint8_t width, uint8_t height);
void FillRectangle(uint8_t x0, uint8_t y0, uint8_t width, uint8_t height);

void DrawScreenBuffer(uint8_t X,uint8_t Y);
void Duplicate(bool x);
void Draw(bool t, uint8_t x, uint8_t y);
void setdelay(uint8_t newtime);
void DrawSprite(uint8_t xPos, uint8_t yPos);

void RenderScreenBuffer(uint8_t screen);
void RenderScreenBuffer_(uint8_t startX, uint8_t startY, uint8_t maxX, uint8_t maxY);


void DumpScreenBuffer(void);
void DumpScreenBuffer_(uint8_t startX, uint8_t startY, uint8_t maxX, uint8_t maxY);


byte ScreenBuffer[16][32];


byte checkAND[8];


byte delaytime;
byte DEFAULTTIME;

// static const byte RS = 17; 
// static const byte RW = 16;  
// static const byte EN = 18;  
// static const byte D0  = 8;  
// static const byte D1  = 9; 
// static const byte D2  = 10;  
// static const byte D3  = 11;  
// static const byte D4  = 4; 
// static const byte D5  = 5;  
// static const byte D6  = 6;  
// static const byte D7  = 7; 
// static const byte CSEL1  = 14; 

#define lcd0 dk_bit(PORTB,0) //LCD's RS (DI) pin is connected to Pin0 of AVR
#define lcd0_d dk_bit(DDRB,0)
#define lcd1 dk_bit(PORTB,1) //LCD's r/w pin is connected to Pin1 of AVR
#define lcd1_d dk_bit(DDRB,1)
#define lcd2 dk_bit(PORTB,2) //LCD's e pin is connected to Pin2 of AVR
#define lcd2_d dk_bit(DDRB,2)
#define	lcd3 dk_bit(PORTB,3) //LCD's CS1 pin is connected to Pin5 of AVR
#define	lcd3_d dk_bit(DDRB,3)
#define	lcd4 dk_bit(PORTB,4) //LCD's CS2 pin is connected to Pin5 of AVR
#define	lcd4_d dk_bit(DDRB,4)
#define	lcd5 dk_bit(PORTB,5) //LCD's RST pin is connected to Pin3 of AVR
#define	lcd5_d dk_bit(DDRB,5)
#define	lcd6 dk_bit(PORTB,6) //LCD's CS2 pin is connected to Pin5 of AVR
#define	lcd6_d dk_bit(DDRB,6)
#define	lcd7 dk_bit(PORTB,7) //LCD's RST pin is connected to Pin3 of AVR
#define	lcd7_d dk_bit(DDRB,7)

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



byte currentXpos;
byte currentYpos;

byte temp[8];

