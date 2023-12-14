/* As graphic LCD used the DEM128064A model (128x64 pixels).

   Created by Serasidis Vassilis and finished at 03.Aug.2007
   Home: http://www.serasidis.gr
   e-mail: info@serasidis.gr and avrsite@yahoo.gr

   -- glcd V1.01 : (by Anantha Narayanan at 27.Jun.2008) fixed an optimitation problem with the delay routine.
   -- glcd V1.00 : (by Vassilis Serasidis at 03.Aug.2007) initial version created 

   This code is ditributed under GPL v3 (General Public License).
*/

#include "glcd.h"
#include "font5x7.h"
//#include "font3x6.h"
//#include "font5x8.h"
#include <util/delay.h>
#include <string.h>

//======================================== 
void glcd_init(u8 mode)
{
	lcdrst=1;
	lcde=0;
	lcdcs1=0;
	lcdcs2=0;
// 
// 	output_low(GLCD_DI);                 // Set for instruction
// 	glcd_writeByte(GLCD_LEFT,  0xC0);    // Specify first RAM line at the top
// 	glcd_writeByte(GLCD_RIGHT, 0xC0);    //   of the screen
// 	glcd_writeByte(GLCD_LEFT,  0x40);    // Set the column address to 0
// 	glcd_writeByte(GLCD_RIGHT, 0x40);
// 	glcd_writeByte(GLCD_LEFT,  0xB8);    // Set the page address to 0
// 	glcd_writeByte(GLCD_RIGHT, 0xB8);
// 
// 	if(mode == ON)
// 	{
// 		glcd_writeByte(GLCD_LEFT,  0x3F); // Turn the display on
// 		glcd_writeByte(GLCD_RIGHT, 0x3F);
// 	}
// 	else
// 	{
// 		glcd_writeByte(GLCD_LEFT,  0x3E); // Turn the display off
// 		glcd_writeByte(GLCD_RIGHT, 0x3E);
// 	}
// 
// 	glcd_fillScreen(OFF);                // Clear the display
// 
// 	#ifdef FAST_GLCD
// 	glcd_update();
// 	#endif
}

//========================================
u8 lcd_doc() // truyen du lieu ra thanh ghi dich
{
	u8 du_lieu=0;
	du_lieu|=lcd_da7_i;
	du_lieu<<=1;
	du_lieu|=lcd_da6_i;
	du_lieu<<=1;
	du_lieu|=lcd_da5_i;
	du_lieu<<=1;
	du_lieu|=lcd_da4_i;
	du_lieu<<=1;
	du_lieu|=lcd_da3_i;
	du_lieu<<=1;
	du_lieu|=lcd_da2_i;
	du_lieu<<=1;
	du_lieu|=lcd_da1_i;
	du_lieu<<=1;
	du_lieu|=lcd_da0_i;
	return du_lieu;
}
//======================================== 

void xuat_lcd(u8 ma)
{
	lcd_da0=(ma&0x1);
	ma>>=1;
	lcd_da1=(ma&0x1);
	ma>>=1;
	lcd_da2=(ma&0x1);
	ma>>=1;
	lcd_da3=(ma&0x1);
	ma>>=1;
	lcd_da4=(ma&0x1);
	ma>>=1;
	lcd_da5=(ma&0x1);
	ma>>=1;
	lcd_da6=(ma&0x1);
	ma>>=1;
	lcd_da7=(ma&0x1);
}
void lcd_vao_ra(u8 ma)
{
	lcd_da0_d=(ma);
	lcd_da1_d=(ma);
	lcd_da2_d=(ma);
	lcd_da3_d=(ma);
	lcd_da4_d=(ma);
	lcd_da5_d=(ma);
	lcd_da6_d=(ma);
	lcd_da7_d=(ma);
}
//======================================== 
void glcdInit (void)
{ 
	//data_port_pins = 0;  //DATA Port Low
	lcd_vao_ra(ra);
  //ctrl_port = 0;   //CONTROL Port Low

  lcdrst_d=1;
  lcdrst=1;
  lcdcs1_d=1;
  lcdcs1=1;   //Enable the CS1 of the display
  lcdcs2_d=1;
  lcdcs2=1;   //Enable the CS2 of the display
  lcdrs_d=1;
  lcdrs=0;        //Clear RS  \_
  lcdrw_d=1;
  lcdrw=0;        //Clear RW  /  Command mode
  lcde_d=1;

   
	_delay_us(50);
	xuat_lcd(0b11000000);   //Display start line = 0 (0-63)
	eStrobe();
 

   
	_delay_us(50);
	xuat_lcd(0b01000000);   //Set address = 0 (0-63)
	eStrobe();

   
	_delay_us(50);
	xuat_lcd(0b10111000);   //Set page = 0 (0-7)
	eStrobe();

	_delay_us(50);
   
	xuat_lcd(0b00111111);   //Display ON
	eStrobe();

	lcdcs1=0;  //Disable the CS1 of display
	lcdcs2=0;  //Disable the CS2 of display
}

void LCD_Init_4bit()
{
	glcdInit();
}
//====================================================================
//  create "welcome" screen
//====================================================================
void createWelcomeScreen (void)
{ 
	unsigned int i;
	const char *data = welcomeScreen;
	column = 0;
	line =0;

	gLCDgotoXY(line,column);

	for (i = 0; i<1024; i++)
		sendDataOnLCD(pgm_read_byte(data++));

}
//====================================================================
void icon8 (u8 rong,const char *data)
{
	unsigned int i;
	for (i = 0; i<rong; i++)
	sendDataOnLCD(pgm_read_byte(data++));
}
//======================================== 
void glcd_c (void)
{
	unsigned int i;
	column = 0;
	line =0;
	gLCDgotoXY(line,column);
	for (i = 0; i<1024; i++)
		sendDataOnLCD(0);
}
void xoa_lcd_4_bit(void)
{
	glcd_c();
}
void LCD_EnableGraphics()
{
	
}
void glcd_ghi_ky_tu_5x7(u8 x, u8 y,u8 ki_tu, u8 size)
{
	glcd_text57(x,y,ki_tu,size,1);
}
void glcd_ghi_chuoi_5x7(u8 x, u8 y, char* textptr, u8 size)
{
	lx=x;
	for(; *textptr != '\0'; ++textptr, ++lx)// Loop through the passed string
	{
		glcd_ghi_ky_tu_5x7(lx,y,*textptr,size);
	}
}
//====================================================================
// create the raster screen (IS USED)
//====================================================================
void createRaster (void)
{ 
	unsigned int i;
	const char *data = LcdRaster;
	column = 0;
	line =0;

	gLCDgotoXY(line,column);

	for (i = 0; i<1024; i++)
		sendDataOnLCD(pgm_read_byte(data++));

}
//====================================================================
// (IS USED)
//====================================================================
void gLCDgotoXY (unsigned char lineData, unsigned char columnData)
{
	if(columnData < 64)   // If column is at address 0-63...
		enable_cs1();     // ...select the first half of LCD
	else
	{                     // ...or else...
		enable_cs2();     // ...select the second half of LCD.
		columnData-=64;
	}

	lcdrw=0;   //Clear RW. Command mode
	lcdrs=0;   //Clear RS. Command mode

	lineData |= 0b10111000;
	xuat_lcd(lineData);    //Select page (0-7)
	eStrobe();
		
	columnData |= 0b01000000;
	xuat_lcd(columnData);  //Set column address (0-63)
	eStrobe();

	lcdrw=0;   //Clear RW. 
	lcdrs=1;    //Set RS. write data mode
	
}

//====================================================================
//
//====================================================================

void fillDataLcdBuffer (unsigned char address, unsigned char data)
{
	dataLcdBuffer[address] = data;
}

//====================================================================
// (IS USED)
//====================================================================
unsigned char readDataFromLCD (void)
{
	unsigned char data;

	if (column < 64)
		enable_cs1();
	
	if(column >= 64)
		gLCDgotoXY(line,column);

	lcd_vao_ra(0);

	lcdrw=1;lcdrs=1; // "DATA SEND" mode
	_delay_us(5); 
	lcde=1;
	_delay_us(5); 
	lcde=0;
	_delay_us(5);

	lcde=1;
	_delay_us(5); 
	data=lcd_doc();
	lcde=0;
	_delay_us(5);
	lcd_vao_ra(ra);
	gLCDgotoXY(line,column);
	return data;
}

//====================================================================
// (IS USED)
//====================================================================
void sendDataOnLCD (unsigned char data)
{
	if (column < 64)
		enable_cs1();
	
	if(column >= 64)
		gLCDgotoXY(line,column);

	if(column == 128)
	{
		column = 0;
		line++;

		if (line == 8)
			line = 0;
		gLCDgotoXY(line,column);
	}
	_delay_us(5);
	lcdrs=1; // "DATA SEND" mode
	lcdrw=0; 
	xuat_lcd(data);
	eStrobe();

	column++;     // increase column (maximum 128).
}

//====================================================================
// Write the data for 1 waveform to the buffer dataLcdBuffer.
//====================================================================
void createWave (void)
{
 unsigned char data;
 unsigned char byte;
 unsigned char i;

	for (i=0; i<100; i++)
	{
		line=7;
		column=0;
		byte = 0b10000000;

		for(data=dataLcdBuffer[i]; data>7; data-=8)
			line--;
		
		for(;data>0; data--)
			byte >>= 1; 

		column=i;
		gLCDgotoXY(line,column);
		data=readDataFromLCD();
		dataLcdBackupBuffer[i*2]=line;     //Backup the line position (0-7)
		dataLcdBackupBuffer[(i*2)+1]=data; //Backup the data which are on the current LCD possition.

		gLCDgotoXY(line,column);
		sendDataOnLCD(byte | data);	
	}
}

//====================================================================
void restoreRaster (void)
{
 unsigned char data, i;

	for (i=0; i<100; i++)
	{	
		column=i;
		line = dataLcdBackupBuffer[i*2];
		data = dataLcdBackupBuffer[(i*2)+1];
		gLCDgotoXY(line,column);		
		sendDataOnLCD(data);
	}
}
//====================================================================
void enable_cs1 (void) 
{
	lcdcs1=1;   //Enable the CS1 of the display
	lcdcs2=0;   //Disable the CS2 of the display
}
//====================================================================
void enable_cs2 (void)
{
	lcdcs2=1;   //Enable the CS2 of the display
	lcdcs1=0;   //Disable the CS1 of the display
}

//====================================================================
// 
void eStrobe (void)
{
   _delay_us(5);
   lcde=1;   //lcd 'E' pin high
   _delay_us(5);
   lcde=0;  //lcd 'E' pin low
   _delay_us(5);
}
//====================================================================
void GLCD_WriteChar(char charToWrite)
{
	unsigned char i=0;
	for(i = 0; i < 5; i++) 
		//sendDataOnLCD(pgm_read_byte(&font3x6[((charToWrite - 0x20) * 3) + i]));
		sendDataOnLCD(pgm_read_byte(&font5x7[((charToWrite - 0x20) * 5) + i]));
	sendDataOnLCD(0x00);
}
//======================================== 
void GLCD_Puts (char *s)
{
	while (*s)
	{
		GLCD_WriteChar(*s);
		s++;
	}
}
//======================================== 
void Glcd_Set_Side(u8 Side)
{
	if (Side < 64) // side 1
	{
		enable_cs2();
	}
	else // side 2
	{
		enable_cs1();
	}
}
//======================================== 
void Glcd_Set_X(unsigned char x)
{
	// GDM12864B Set Address (Y Address)command
	//		0 - 0 - 01AA - AAAA where AA-AAAA is page 0-63
	// note we call this the "X" axis
	lcdrs=0;
	lcdrw=0;
	xuat_lcd((unsigned char)((unsigned char)0x40 | ((unsigned char)0x3F & x)));
	eStrobe();
}
//======================================== 
void Glcd_Set_Page(unsigned char Page)
{
	// GDM12864B Set Page (X Address)command
	//		0 - 0 - 1011 1PPP where ppp is page 0-7
	// note we call this the "Y" axis
	lcdrs = 0;
	lcdrw = 0;
	xuat_lcd(0xB8 | (0x07 & Page));
	eStrobe();
}

void glcd57(u8 x, u8 y, char textptr, u8 size, bool color)
{
	u8 i;
	u8 j, k, l, m;                       // Loop counters
	u8 pixelData[5];                     // Stores character data
		for(i = 0; i < 5; i++)
			pixelData[i]=(pgm_read_byte(&font5x7[((textptr-0X20) * 5) + i]));
			
		if(x+5*size >= GLCD_WIDTH)          // Performs character wrapping
		{
			x = 0;                           // Set x at far left position
			y += 7*size + 1;                 // Set y at next position down
		}
		for(j=0; j<5; ++j, x+=size)         // Loop through character byte data
		{
			for(k=0; k < 7; ++k)             // Loop through the vertical pixels
			{
				if((pixelData[j] & (1<<k)) != 0) // Check if the pixel should be set
				{
					for(l=0; l < size; ++l)    // These two loops change the
					{                          // character's size
						for(m=0; m < size; ++m)
						{
							glcd_pixel(x+m, y+k*size+l, 1); // Draws the pixel
						}
					}
				}
				else
				{
					for(l=0; l < size; ++l)    // These two loops change the
					{                          // character's size
						for(m=0; m < size; ++m)
						{
							glcd_pixel(x+m, y+k*size+l, 0); // Draws the pixel
						}
					}
				}
			}
		}
	}

void glcd_text57(u8 x, u8 y, char* s, u8 size, bool color)
{
	u8 i; 
	u8 j, k, l, m;                       // Loop counters
	u8 pixelData[5];                     // Stores character data
	
	while (*s)
	{
		GLCD_WriteChar(*s);
		for(i = 0; i < 5; i++)
			pixelData[i]=(pgm_read_byte(&font5x7[((*s-0x20) * 5) + i]));
		s++;
		

		// Handles newline and carriage returns
// 		switch(*textptr)
// 		{
// 			case '\n':
// 			y += 7*size + 1;
// 			continue;
// 			case '\r':
// 			x = 0;
// 			continue;
// 		}

		if(x+5*size >= GLCD_WIDTH)          // Performs character wrapping
		{
			x = 0;                           // Set x at far left position
			y += 7*size + 1;                 // Set y at next position down
		}
		for(j=0; j<5; ++j, x+=size)         // Loop through character byte data
		{
			for(k=0; k < 7; ++k)             // Loop through the vertical pixels
			{
				if((pixelData[j] & (1<<k)) != 0) // Check if the pixel should be set
				{
					for(l=0; l < size; ++l)    // These two loops change the
					{                          // character's size
						for(m=0; m < size; ++m)
						{
							glcd_pixel(x+m, y+k*size+l, color); // Draws the pixel
						}
					}
				}
			}
		}
	}
}
//======================================== 
void glcd_pixel(u8 x, u8 y, bool color)
{
	   u8 data;
	   bool side = GLCD_LEFT;  // Stores which chip to use on the LCD
	   if(x > 63)              // Check for first or second display area
	   {
		   x -= 64;
		   side = GLCD_RIGHT;
	   }
		lcdrs=0;
	   //output_low(GLCD_DI);                         // Set for instruction
	   x &= ~(1<<7);
	   //bit_clear(x,7);                              // Clear the MSB. Part of an instruction code
	   x |= (1<<6);
	   //bit_set(x,6);                                // Set bit 6. Also part of an instruction code
	   
	   glcd_writeByte(side, x);                     // Set the horizontal address
	   glcd_writeByte(side, (y/8 & 0xBF) | 0xB8);   // Set the vertical page address
	   lcdrs=1;
	   //output_high(GLCD_DI);                        // Set for data
	   glcd_readByte(side);                         // Need two reads to get data
	   data = glcd_readByte(side);                  //  at new address

	   if(color == 1)
		data |= (1<<y%8);
		//bit_set(data, y%8);        // Turn the pixel on
	   else     
		data &= ~(1<<y%8);                     // or
		//bit_clear(data, y%8);      // turn the pixel off
		lcdrs=0;
	   //output_low(GLCD_DI);          // Set for instruction
	   glcd_writeByte(side, x);      // Set the horizontal address
	   lcdrs=1;
	   //output_high(GLCD_DI);         // Set for data
	   glcd_writeByte(side, data);   // Write the pixel data
}
// Purpose:    Write a byte of data to the specified chip
// Inputs:     1) chipSelect - which chip to write the data to
//             2) data - the byte of data to write
void glcd_writeByte(bool side, char data)
{
	//set_tris_d(0x00);
	//data_port_ddr = 0x00;
	lcdrw=0;
	//output_low(GLCD_RW);       // Set for writing
	if(side)                   // Choose which side to write to
		lcdcs2=1;
		//output_high(GLCD_CS2);
	else
		lcdcs1=1;
		//output_high(GLCD_CS1);

	delay_us(1); 
	xuat_lcd(data);
	//output_d(data);            // Put the data on the port
	delay_us(1);
	lcde=1;
	//output_high(GLCD_E);       // Pulse the enable pin
	delay_us(1);
	lcde=0;
	//output_low(GLCD_E);
	lcdcs1=0;
	lcdcs2=0;
	//output_low(GLCD_CS1);      // Reset the chip select lines
	//output_low(GLCD_CS2);
}
//======================================== 
char glcd_readByte(bool side)
{
	char data;                 // Stores the data read from the LCD
	lcd_vao_ra(0);
	//set_tris_d(0xFF);          // Set port d to input
	lcdrw=1;
	//output_high(GLCD_RW);      // Set for reading
	if(side) 
		lcdcs2=1;                  // Choose which side to write to
		//output_high(GLCD_CS2);
	else
		lcdcs1=1;
		//output_high(GLCD_CS1);

	delay_us(1);
	lcde=1;
	//output_high(GLCD_E);       // Pulse the enable pin
	delay_us(1);
	data = lcd_doc();          // Get the data from the display's output register
	lcde=0;
	//output_low(GLCD_E);

	//output_low(GLCD_CS1);      // Reset the chip select lines
	//output_low(GLCD_CS2);
	lcdcs1=0;
	lcdcs2=0;
	lcd_vao_ra(ra);
	return data;               // Return the read data
}
