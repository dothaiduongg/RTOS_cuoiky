#ifndef _lcd_hp_h_
#define _lcd_hp_h_
#include <!/! LDN.h>
#define black 1
#define white 0
#define LCDWIDTH 128
#define LCDHEIGHT 64
#define COL_LSB 0x00
#define COL_MSB 0x10
#define SET_PAGE 0xB0
#define SET_BIAS_9 0xA2
#define INVERT 0xA7
#define UNINVERT 0xA6
#define DISPLAY_ON 0xAF
#define DISPLAY_OFF 0xAE
#define SOFTWARE_RESET 0x2E
#define POWER_CONTROL 0x2F

#define CMD_NONE_ALL_PIXEL 0xA4		//màn hình bình thường
#define CMD_ALL_PIXEL 0xA5			//buộc màn hình hiển thị tất cả điểm ảnh có trên lcd
#define NO_MIRROR 0					/** buộc màn hình hiển thị tất cả điểm ảnh có trên lcd
*/
//lựa chọn font chữ số
#define ASCII_NUMBER 0
#define CASIO_NUMBER 1
#define STYLE_NUMBER 2

#define swap(a,b) {uint8_t t =a; a =b; b =t;}

//class homephone: public Print {
//public:
	//homephone(int8_t sdin, int8_t slk, int8_t a, int8_t rst, int8_t cs): sdin (sdin), slk(slk), a(a), rst(rst), cs(cs) {}
	//homephone(uint8_t sdin, uint8_t slk, uint8_t a,uint8_t rst, uint8_t cs);

	void begin(void);				// Tuong ung ham ON
	void setContrast(uint8_t c);	// Tuong ung ham SET

	void display();
	void noDisplay();
	void clear();	
	void lcdWrite(uint8_t command, byte c);
	void drawPixel(uint8_t x, uint8_t y, uint8_t color);

	void AllPixel(uint8_t val);
	bool GetPixel(int16_t x, int16_t y);	
	void drawLine (uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color);
	void drawHorizontalLine( long x1, long x2, long y0, bool color); 	//duong_nam_ngang
	void drawVerticalLine(long x0, long y1, long y2, bool color); 		//duong_thang_dung

	void drawCircle (uint8_t x, uint8_t y, uint8_t r, uint8_t color);
	void fillCircle (uint8_t x, uint8_t y, uint8_t r, uint8_t color);

	void drawRect (uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color);
	void fillRect (uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t color);

	void drawTriangle (uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t color);
	void fillTriangle (uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t color);

	void drawCorner( int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, int16_t color);
	void fillCorner( int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, int16_t color);

	void setCursor(uint8_t x, uint8_t y);
	void setTextColor(uint8_t color, uint8_t bgColor);
	void drawChar(uint8_t x, uint8_t y, unsigned char c, uint8_t color, uint8_t bg);

	void drawBitmap(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint8_t *bitmap, uint8_t color);
	//Ham ascii
	void ascChar(int16_t x1, int16_t y1, unsigned char c, int16_t color);
	void ascString(int16_t x1, int16_t y1, const char *s , int16_t color); 
	
	void Plot4EllipsePoint16_ts(uint8_t cx, uint8_t  cy, uint8_t x, uint8_t y, uint8_t color, uint8_t fill);
	void DrawEllipse_private(uint8_t cx, uint8_t  cy, uint8_t xradius, uint8_t yradius, uint8_t color, uint8_t fill);
	void drawElip(uint8_t xcenter, uint8_t  ycenter, uint8_t xradius,  uint8_t  yradius, uint8_t color);
	void fillElip(uint8_t xcenter, uint8_t  ycenter, uint8_t xradius, uint8_t yradius, uint8_t color);
	void Plus_Bitmap(uint8_t x0, uint8_t y0, uint8_t w, uint8_t h, const uint8_t *bitmap , uint8_t goc, uint8_t mirror, uint8_t color);
	void draw_single_number(int16_t x1, int16_t y1, int16_t single_number, int16_t select_font, int16_t color);
	int16_t Keep_Angle(int16_t goc);
	void Find_XY_Elip(int16_t x0, int16_t y0,  int16_t a,  int16_t b, int16_t goc_alpha) ;
	int16_t X_Elip() ;
	int16_t Y_Elip();
	void Find_XY_Sphere( int16_t x0, int16_t y0, int16_t a0, int16_t b0, int16_t goc_alpha, int16_t goc_beta);
	int16_t X_Sphere();
	int16_t Y_Sphere();	
	void Zoom_In(int16_t x0, int16_t y0, uint16_t w0, uint16_t h0, uint8_t he_so_phong_to, int16_t color); 
	void Asc_Char_Zoom(int16_t x1, int16_t y1, unsigned char c, int16_t he_so_phong_to, int16_t color);		
	void Asc_String_Zoom(int16_t x1, int16_t y1, const char *s , int16_t he_so_phong_to, int16_t color);
	void Uni_Char(int16_t x1, int16_t y1, int16_t c, int16_t color);
	void Uni_Char_Zoom(int16_t x1, int16_t y1, int16_t c, byte he_so_phong_to, int16_t color);
	void RunStatus( int16_t x, int16_t y, byte a, uint16_t t, const char *c, int16_t color) ;
	void Number_Long(int16_t x, int16_t y, long a, byte select_font, bool color);
	void Number_Long_p(int16_t x, int16_t y, long a, byte select_font, byte he_so_phong_to, bool color);
	void Number_Ulong(int16_t x, int16_t y, unsigned long a, byte select_font,  bool color);
	void Number_Ulong_p(int16_t x, int16_t y, unsigned long a, byte select_font, byte he_so_phong_to, bool color);
	void Number_Float(int16_t x, int16_t y, float a, byte n, byte select_font,  bool color);
	void Number_Float_p(int16_t x, int16_t y, float a, byte n, byte select_font, byte he_so_phong_to, bool color);

	void Analog( int16_t x, int16_t y, int16_t w, int16_t h,  int16_t value, bool color);
	void spiwrite(uint8_t c);
	byte tim_thu_tu( int16_t  c);
	
	//virtual 
	size_t write(uint8_t);

//private:
	uint8_t  cs;
	#ifndef lcda
	//const char *str;
	#define lcda dk_bit(PORTD,5) //LCD's RS (DI) pin is connected to Pin0 of AVR
	#define lcda_d dk_bit(DDRD,5)
	#define lcd_rst dk_bit(PORTD,5) //LCD's RS (DI) pin is connected to Pin0 of AVR
	#define lcd_rst_d dk_bit(DDRD,5)
	#define lcd_sdin dk_bit(PORTD,5) //LCD's RS (DI) pin is connected to Pin0 of AVR
	#define lcd_sdin_d dk_bit(DDRD,5)
	#define lcd_slk dk_bit(PORTD,5) //LCD's RS (DI) pin is connected to Pin0 of AVR
	#define lcd_slk_d dk_bit(DDRD,5)
	#define lcd_cs dk_bit(PORTD,5) //LCD's RS (DI) pin is connected to Pin0 of AVR
	#define lcd_cs_d dk_bit(DDRD,5)
	#endif
	uint8_t lcdBuffer[100];

//protected:
	uint8_t cursor_x;
	uint8_t cursor_y;
	uint8_t textColor;
	uint8_t textBgColor;

//};
#endif
