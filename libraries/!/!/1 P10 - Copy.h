#ifndef _p10_h_
#define _p10_h_

//#define oe_cao
#define cieu_qet c1_4
#ifndef d1
	#define d1 dk_bit(PORTD,2)
	#define d1_d dk_bit(DDRD,2)
#endif

#define s1 dk_bit(PORTD,2)
#define s1_d dk_bit(DDRD,2)
#define d2 dk_bit(PORTD,3)
#define d2_d dk_bit(DDRD,3)
#define s2 dk_bit(PORTD,3)
#define s2_d dk_bit(DDRD,3)

#define d21 dk_bit(PORTD,2)
#define d21_d dk_bit(DDRD,2)
#define s21 dk_bit(PORTD,2)
#define s21_d dk_bit(DDRD,2)
#define d22 dk_bit(PORTD,3)
#define d22_d dk_bit(DDRD,3)
#define s22 dk_bit(PORTD,3)
#define s22_d dk_bit(DDRD,3)

#define cqa dk_bit(PORTD,5) // chan quet a
#define cqa_d dk_bit(DDRD,5)
#define cqb dk_bit(PORTD,6)
#define cqb_d dk_bit(DDRD,6)
#define cqc dk_bit(PORTD,7)
#define cqc_d dk_bit(DDRD,7)
#define cqd dk_bit(PORTB,0) // chan quet d
#define cqd_d dk_bit(DDRB,0)

#define ck dk_bit(PORTB,1)
#define ck_d dk_bit(DDRB,1)
#define oe dk_bit(PORTB,3)
#define oe_d dk_bit(DDRB,3)
#define la dk_bit(PORTB,2)
#define la_d dk_bit(DDRB,2)

#ifndef rog
#define rog 64
#endif
#ifndef cao
#define cao 32
#endif
#define b_rog rog/8
#define GFX_CHAR_SPACING 3
#define cic_thuoc b_rog*cao

uint8_t p10_vram_d[cic_thuoc];
uint8_t p10_vram_s[cic_thuoc];

void p10_chon_ceh(uint8_t ch);
INT8 GFXWriteStringXY_s(INT8 x,INT8 y,const char *string,UINT8 color);
INT8 GFXWriteStringXY_d(INT8 x,INT8 y,const char *string,UINT8 color);
int8_t GFXPutCharXY_d(int8_t x, int8_t y,char c,uint8_t mau);
INT8 GFXGetCharWidth(char c);
INT8 GFXWriteStringXY(INT8 x,INT8 y,const char *string,UINT8 color);

//#define c1_4
#define kieu_quet 16
uint8_t kenh_chon=0;
void P10Clear()
{
	for(u16 i=0;i<cic_thuoc;i++)
	{
		p10_vram_d[i]=0xff;
		p10_vram_s[i]=0xff;
	}
}

//u8 cieu_qet;
void p10_soa_diem_d(int8_t x,int8_t y)
{
	if(x<0 || x>=rog || y<0 || y>=cao) return;
	x=rog-x-1;
	uint8_t xx=x/8;
	uint8_t d=p10_vram_d[xx*cao+y];
	uint8_t dd=x%8;
	dd=7-dd;
	d|=(1<<dd);
	p10_vram_d[xx*cao+y]=d;
}

void p10_soa_diem_s(int8_t x,int8_t y)
{
	if(x<0 || x>=rog || y<0 || y>=cao) return;
	x=rog-x-1;
	uint8_t xx=x/8;
	uint8_t d=p10_vram_s[xx*cao+y];
	uint8_t dd=x%8;
	dd=7-dd;
	d|=(1<<dd);
	p10_vram_s[xx*cao+y]=d;
}

void P10PutPixel_d(int8_t x,int8_t y)
{
	if(x<0 || x>=rog || y<0 || y>=cao) return;
	x=rog-x-1;
	uint8_t xx=x/8;
	uint8_t d=p10_vram_d[xx*cao+y];
	uint8_t dd=x%8;
	dd=7-dd;
	d&=~(1<<dd);
	p10_vram_d[xx*cao+y]=d;
}

void P10PutPixel_s(int8_t x,int8_t y)
{
	if(x<0 || x>=rog || y<0 || y>=cao) return;
	x=rog-x-1;
	uint8_t xx=x/8;
	uint8_t d=p10_vram_s[xx*cao+y];
	uint8_t dd=x%8;
	dd=7-dd;
	d&=~(1<<dd);
	p10_vram_s[xx*cao+y]=d;
}

int8_t GFXPutCharXY_s(int8_t x, int8_t y,char c,uint8_t mau)
{

	uint8_t width = 0;
	uint8_t height = __GFXReadFontData(FONT_OFFSET_HEIGHT);
	uint8_t bytes = (height+7)/8;
	uint8_t firstChar = __GFXReadFontData(FONT_OFFSET_FIRSTCHAR);
	uint8_t charCount = __GFXReadFontData(FONT_OFFSET_CHARCOUNT);
	
	UINT16 index = 0;
	
	if(c < firstChar || c >= (firstChar+charCount)) {
		return -1;//Error
	}
	
	c-= firstChar;
	
	// read width data, to get the index
	for(uint8_t i=0; i<c; i++) {
		index += __GFXReadFontData(FONT_OFFSET_WTABLE+i);
	}
	index =index*bytes+charCount+FONT_OFFSET_WTABLE;
	width = __GFXReadFontData(FONT_OFFSET_WTABLE+c);


	//Draw
	int8_t _x,_y,fx,fy,b;
	
	UINT16 address;
	
	_y=y;


	uint8_t shift_val;
	shift_val=(bytes*8)-height;

	bytes--;
	
	for(b=0;b<bytes;b++)
	{
		uint8_t mask=0b00000001;
		for(fy=0;fy<8;fy++)
		{

			if((_y+fy)>(cao-1))
			break;

			address=(index+b*width);

			for(_x=x,fx=0;fx<width;fx++,_x++)
			{
				if(_x>(rog-1))	break;

				uint8_t data=__GFXReadFontData(address);

				uint8_t bit= (data & mask);

				if(bit)
				{
					if(mau==1)
					{
						P10PutPixel_s(_x,_y+fy);
					}
					else if(mau==0)
					{
						p10_soa_diem_s(_x,_y+fy);
					}
				}
				if(mau==2)
				{
					p10_soa_diem_s(_x,_y+fy);
				}
				
				//else
				//GFXRawPutPixel(_x,_y+fy,color_invert);
				address++;

			}
			mask=mask<<1;
			
		}
		_y+=8;
	}

	//Last Byte May require shifting so draw it separately

	uint8_t mask=0b00000001<<shift_val;
	for(fy=0;fy<(8-shift_val);fy++)
	{
		if((_y+fy)>(cao-1))
		break;
		
		address=(index+b*width);

		for(_x=x,fx=0;fx<width;fx++,_x++) 
		{
			if(_x>(rog-1))	break;

			uint8_t data=__GFXReadFontData(address);

			uint8_t bit= (data & mask);

			if(bit)
			{
				if(mau==1)
				{
					P10PutPixel_s(_x,_y+fy);
				}
				else if(mau==0)
				{
					p10_soa_diem_s(_x,_y+fy);
				}
			}
			if(mau==2)
			{
				p10_soa_diem_s(_x,_y+fy);
			}
			//else
			//GFXRawPutPixel(_x,_y+fy,color_invert);

			address++;

		}
		mask=mask<<1;
		
	}
	return 1;
}


INT8 GFXWriteStringXY_d(INT8 x,INT8 y,const char *string,UINT8 color)
{
	INT8 w;
	while(*string!='\0')
	{
		if(GFXPutCharXY_d(x,y,*string,color)==-1)
		return -1;
		w=GFXGetCharWidth(*string);
		if(w==-1)
		return -1;
		x+=w;
		x+=GFX_CHAR_SPACING; //Blank Line after each char
		string++;
	}
	return 1;
}

INT8 GFXWriteStringXY_s(INT8 x,INT8 y,const char *string,UINT8 color)
{
	INT8 w;
	while(*string!='\0')
	{
		if(GFXPutCharXY_s(x,y,*string,color)==-1)
		return -1;
		w=GFXGetCharWidth(*string);
		if(w==-1)
		return -1;
		x+=w;
		x+=GFX_CHAR_SPACING; //Blank Line after each char
		string++;
	}
	return 1;
}

int8_t GFXPutCharXY_d(int8_t x, int8_t y,char c,uint8_t mau) // mau = 1 hien thi, mau = 2 soa diem, 3 soa vug
{

	uint8_t width = 0;
	uint8_t height = __GFXReadFontData(FONT_OFFSET_HEIGHT);
	uint8_t bytes = (height+7)/8;
	uint8_t firstChar = __GFXReadFontData(FONT_OFFSET_FIRSTCHAR);
	uint8_t charCount = __GFXReadFontData(FONT_OFFSET_CHARCOUNT);
	
	UINT16 index = 0;
	
	if(c < firstChar || c >= (firstChar+charCount)) {
		return -1;//Error
	}
	
	c-= firstChar;
	
	// read width data, to get the index
	for(uint8_t i=0; i<c; i++) {
		index += __GFXReadFontData(FONT_OFFSET_WTABLE+i);
	}
	index =index*bytes+charCount+FONT_OFFSET_WTABLE;
	width = __GFXReadFontData(FONT_OFFSET_WTABLE+c);


	//Draw
	int8_t _x,_y,fx,fy,b;
	
	UINT16 address;
	
	_y=y;


	uint8_t shift_val;
	shift_val=(bytes*8)-height;

	bytes--;
	
	for(b=0;b<bytes;b++)
	{
		uint8_t mask=0b00000001;
		for(fy=0;fy<8;fy++)
		{
			if((_y+fy)>(cao-1))
			break;
			address=(index+b*width);
			for(_x=x,fx=0;fx<width;fx++,_x++)
			{
				if(_x>(rog-1))	break;
				uint8_t data=__GFXReadFontData(address);
				uint8_t bit= (data & mask);
				if(bit)
				{
					if(mau==1)
					{
						P10PutPixel_d(_x,_y+fy);
					}
					else if(mau==0)
					{
						p10_soa_diem_d(_x,_y+fy);
					}
				}
				
				if(mau==2)
				{
					p10_soa_diem_d(_x,_y+fy);
				}
				//else
				//GFXRawPutPixel_d(_x,_y+fy,color_invert);
				address++;

			}
			mask=mask<<1;
			
		}
		_y+=8;
	}

	//Last Byte May require shifting so draw it separately

	uint8_t mask=0b00000001<<shift_val;
	for(fy=0;fy<(8-shift_val);fy++)
	{
		if((_y+fy)>(cao-1))
		break;
		
		address=(index+b*width);
		
		for(_x=x,fx=0;fx<width;fx++,_x++)
		{
			if(_x>(rog-1))	break;

			uint8_t data=__GFXReadFontData(address);

			uint8_t bit= (data & mask);

			if(bit)
			{
				if(mau==1)
				{
					P10PutPixel_d(_x,_y+fy);
				}
				else
				{
					p10_soa_diem_d(_x,_y+fy);
				}
			}
			if(mau==2)
			{
				p10_soa_diem_d(_x,_y+fy);
			}
			
			//else
			//GFXRawPutPixel(_x,_y+fy,color_invert);
			address++;
		}
		mask=mask<<1;
	}
	return 1;
}

INT8 GFXGetCharWidth(char c)
{

	UINT8 firstChar = __GFXReadFontData(FONT_OFFSET_FIRSTCHAR);
	UINT8 charCount = __GFXReadFontData(FONT_OFFSET_CHARCOUNT);
	
	
	if(c < firstChar || c >= (firstChar+charCount)) {
		return -1;//Error
	}
	
	c-= firstChar;
	
	return __GFXReadFontData(FONT_OFFSET_WTABLE+c);
}

INT16 GFXGetStringWidth(const char *string)
{
	INT16 w,r;

	w=0;
	while(*string!='\0')
	{
		r=GFXGetCharWidth(*string);
		if(r==-1) return -1;

		w+=r;
		w+=GFX_CHAR_SPACING;//Extra Spacing Between Chars
		
		string++;
	}
	
	return w;
}
INT16 GFXGetStringWidthN(const char *string,UINT8 n)
{
	INT16 w,r;
	INT8 i=0;

	w=0;
	while(*string!='\0')
	{
		r=GFXGetCharWidth(*string);
		if(r==-1) return -1;

		w+=r;
		w+=GFX_CHAR_SPACING;//Extra Spacing Between Chars

		string++;
		
		if(i==n) break; else i++;
	}

	return w;
}
uint8_t CharIndexOfPixel(const char *s, uint16_t pixel)
{
	uint8_t index=0;
	
	while(1)
	{
		if(pixel<GFXGetStringWidthN(s,index))
		return index;
		else
		index++;
	}
	
}



void ScrollMsg(const char *msg)
{
	uint16_t msg_pixel_len=GFXGetStringWidth(msg);
	
	msg_pixel_len-=rog;
	
	//msg_pixel_len+=4;
	
	for(uint16_t scroll=0; scroll<msg_pixel_len;scroll++)
	{
		uint8_t start_char=CharIndexOfPixel(msg,scroll);
		
		char temp_string[18];
		
		strncpy(temp_string,msg+start_char,17);
		
		uint8_t first_char_width=GFXGetCharWidth(temp_string[0]);
		
		first_char_width+=GFX_CHAR_SPACING;
		
		for(uint8_t scroll2=0;scroll2<first_char_width;scroll2++)
		{
			P10Clear();
			GFXWriteStringXY(-scroll2,0,temp_string,0);
			
			
			if(scroll==0)
			{
				_delay_ms(3000);//was 500
			}
			else
			{
				_delay_ms(25);
			}
			
			scroll++;
			
		}
		
	}
	
}

void p10_koi_tao()
{
	d1_d=s1_d=d2_d=s2_d=ra;
	d21_d=s21_d=d22_d=s22_d=ra;
	cqa_d=cqb_d=cqc_d=ra;
	#if kieu_quet >= 16
	cqd_d=ra; 
	#endif
	ck_d=oe_d=la_d=ra;
	p10_chon_ceh(8);
}

void p10_sug()
{
	ck=1;
	ck=0;
}

void p10_of()
{
#ifdef oe_cao
	oe=0;
#else
	oe=1;
#endif
}

void p10_on()
{
#ifdef oe_cao
	oe=1;
#else
	oe=0;
#endif
}

void p10_lat()
{
	la=1;
	_delay_loop_1(1);
	la=0;
	_delay_loop_1(1);
}

void p10_chon_ceh(uint8_t ch)
{
	cqa=cqb=cqc=0;
	cqa=ch&1;
	ch>>=1;
	cqb=ch&1;
	ch>>=1;
	cqc=ch&1;
	#if kieu_quet >= 16
	ch>>=1;
	cqd=ch&1;
	#endif
}

void HC595Write(uint8_t data)
{
	//Send each 8 bits serially

	//Order is MSB first
	for(uint8_t i=0;i<8;i++)
	{
		//Output the data on DS line according to the
		//Value of MSB
		if(data & 0b00000001)
		{
			//MSB is 1 so output high
			d1=0;
			d21=0;
			//d2=0;
			// d1=0;
			
		}
		else
		{
			d1=1;
			d21=0;
			//d2=1;
			// d1=1;
		}

		p10_sug();  //Pulse the Clock line
		data=data>>1;  //Now bring next bit at MSB position

	}

	//Now all 8 bits have been transferred to shift register
	//Move them to output latch at one
	//HC595Latch();
}
void p10_hc595_2b(u8 data1,u8 data2,u8 mau)
{
	//Send each 8 bits serially

	//Order is MSB first
	for(uint8_t i=0;i<8;i++)
	{
		//Output the data on DS line according to the
		//Value of MSB
		d1=0;
		s1=0;
		d2=0;
		s2=0;
		d21=0;
		s21=0;
		d22=0;
		s22=0;
		if(!(data1 & 0b00000001))
		{
			if(mau==0)
			{
				d1=1;
				d21=1;
			}
			if(mau==1)
			{
				s1=1;
				s21=1;
			}
			if(mau>1)
			{
				d1=s1=1;
				d21=s21=1;
			}
		}
		data1=data1>>1;  //Now bring next bit at MSB positio
		if(!(data2 & 0b00000001))
		{
			if(mau==0)
			{
				d2=1;
				d22=1;
			}
			if(mau==1)
			{
				s2=1;
				s22=1;
			}
			if(mau>1)
			{
				d2=s2=1;
				d22=s22=1;
			}
		}
		data2=data2>>1;  //Now bring next bit at MSB position
		p10_sug();  //Pulse the Clock line
	}
	//Now all 8 bits have been transferred to shift register
	//Move them to output latch at one
	//HC595Latch();
}
void p10_hc595_2bx2(u8 data1,u8 data2,u8 data21,u8 data22,u8 mau)
{
	//Send each 8 bits serially

	//Order is MSB first
	for(uint8_t i=0;i<8;i++)
	{
		//Output the data on DS line according to the
		//Value of MSB
		d1=0;
		s1=0;
		d2=0;
		s2=0;
		d21=0;
		s21=0;
		d22=0;
		s22=0;
		if(!(data1 & 0b00000001))
		{
			if(mau==0)
			{
				d1=1;
				//d21=1;
			}
			if(mau==1)
			{
				s1=1;
				//s21=1;
			}
			if(mau>1)
			{
				d1=s1=1;
				//d21=s21=1;
			}
		}
		data1=data1>>1;  //Now bring next bit at MSB positio
		if(!(data2 & 0b00000001))
		{
			if(mau==0)
			{
				d2=1;
				//d22=1;
			}
			if(mau==1)
			{
				s2=1;
				//s22=1;
			}
			if(mau>1)
			{
				d2=s2=1;
				//d22=s22=1;
			}
		}
		data2=data2>>1;
		
		if(!(data21 & 0b00000001))
		{
			if(mau==0)
			{
				//d1=1;
				d21=1;
			}
			if(mau==1)
			{
				//s1=1;
				s21=1;
			}
			if(mau>1)
			{
				//d1=s1=1;
				d21=s21=1;
			}
		}
		data21=data21>>1;  //Now bring next bit at MSB positio
		if(!(data22 & 0b00000001))
		{
			if(mau==0)
			{
				//d2=1;
				d22=1;
			}
			if(mau==1)
			{
				//s2=1;
				s22=1;
			}
			if(mau>1)
			{
				//d2=s2=1;
				d22=s22=1;
			}
		}
		data22=data22>>1;  //Now bring next bit at MSB position
		p10_sug();  //Pulse the Clock line
	}
	//Now all 8 bits have been transferred to shift register
	//Move them to output latch at one
	//HC595Latch();
}

void p10_hc595_2bx2_mau(u8 data_d1,u8 data_d2,u8 data_d21,u8 data_d22, u8 data_s1,u8 data_s2,u8 data_s21,u8 data_s22)
{
	//Send each 8 bits serially

	//Order is MSB first
	for(uint8_t i=0;i<8;i++)
	{
		//Output the data on DS line according to the
		//Value of MSB
		d1=0;
		s1=0;
		d2=0;
		s2=0;
		d21=0;
		s21=0;
		d22=0;
		s22=0;
		if(!(data_d1 & 0b00000001))
		{
			d1=1;
		}
		data_d1=data_d1>>1;  //Now bring next bit at MSB positio
		if(!(data_d2 & 0b00000001))
		{
			d2=1;
		}
		data_d2=data_d2>>1;
		
		if(!(data_d21 & 0b00000001))
		{
			d21=1;
		}
		data_d21=data_d21>>1;  //Now bring next bit at MSB positio
		if(!(data_d22 & 0b00000001))
		{
			d22=1;
		}
		data_d22=data_d22>>1;  //Now bring next bit at MSB position
		//-----------------------------------------------
		if(!(data_s1 & 0b00000001))
		{
			s1=1;
		}
		data_s1=data_s1>>1;  //Now bring next bit at MSB positio
		if(!(data_s2 & 0b00000001))
		{
			s2=1;
		}
		data_s2=data_s2>>1;
		
		if(!(data_s21 & 0b00000001))
		{
			s21=1;
		}
		data_s21=data_s21>>1;  //Now bring next bit at MSB positio
		if(!(data_s22 & 0b00000001))
		{
			s22=1;
		}
		data_s22=data_s22>>1;  //Now bring next bit at MSB position
		
		p10_sug();  //Pulse the Clock line
	}
	//Now all 8 bits have been transferred to shift register
	//Move them to output latch at one
	//HC595Latch();
}


void qet_p10_1_mau()
{
	static uint8_t ch=0;
	for(uint8_t i=0;i<cao;i++)
	{
		HC595Write(p10_vram_d[(15-i)*4+ch]);
	}
	p10_of();
	p10_lat();
	p10_chon_ceh(ch);
	p10_on();
	ch++;
	if(ch>3)
	ch=0;
}

//void qet_p10_1_mau()
//{
	//unsigned char so_byte_rog=rog/8;
	//static unsigned int ch=0;
	//for(unsigned int i=0;i<so_byte_rog;i++)
	//{
		//p10_hc595_2b(p10_vram_d[(so_byte_rog-1-i)*cao+ch],p10_vram_d[(so_byte_rog-1-i)*cao+ch+32]);
		////HC595Write(p10_vram_d[(15-i)*31+ch]);
		////p10_hc595_2bx2(p10_vram[(so_byte_rog-1-i)*cao+ch],p10_vram[(so_byte_rog-1-i)*cao+ch+8],p10_vram[(so_byte_rog-1-i)*cao+ch+16],p10_vram[(so_byte_rog-1-i)*cao+ch+8+16],0);
	//}
	//p10_of();
	//p10_lat();
	//p10_chon_ceh(ch);
	//p10_on();
	//ch++;
	//if(ch>31)
	//ch=0;
//}
void qet_p10_2_mau()
{
	static uint8_t ch=0;
	for(uint8_t i=0;i<b_rog;i++)
	{
		//p10_hc595_2b(p10_vram[(so_byte_rog-1-i)*cao+ch],p10_vram[(so_byte_rog-1-i)*cao+ch+8],0);
		//p10_hc595_2bx2(p10_vram[(so_byte_rog-1-i)*cao+ch],p10_vram[(so_byte_rog-1-i)*cao+ch+8],p10_vram[(so_byte_rog-1-i)*cao+ch+16],p10_vram[(so_byte_rog-1-i)*cao+ch+8+16],0);
		p10_hc595_2bx2_mau(p10_vram_d[(b_rog-1-i)*cao+ch],p10_vram_d[(b_rog-1-i)*cao+ch+8],p10_vram_d[(b_rog-1-i)*cao+ch+16],p10_vram_d[(b_rog-1-i)*cao+ch+8+16],
		p10_vram_s[(b_rog-1-i)*cao+ch],p10_vram_s[(b_rog-1-i)*cao+ch+8],p10_vram_s[(b_rog-1-i)*cao+ch+16],p10_vram_s[(b_rog-1-i)*cao+ch+8+16]);
		//p10_hc595_2b(p10_vram[(7-i)*2+ch],p10_vram[(7-i)*4+ch]);
	}
	p10_of();
	p10_lat();
	p10_chon_ceh(ch);
	p10_on();
	ch++;
	if(ch>7)
	ch=0;
}

void p10_hc595_1_mau(u8 data_d1,u8 data_d2,u8 data_d21,u8 data_d22, u8 data_s1,u8 data_s2,u8 data_s21,u8 data_s22)
{
	//Send each 8 bits serially

	//Order is MSB first
	for(uint8_t i=0;i<8;i++)
	{
		//Output the data on DS line according to the
		//Value of MSB
		d1=0;
		//s1=0;
		d2=0;
		//s2=0;
		//d21=0;
		//s21=0;
		//d22=0;
		//s22=0;
		if(!(data_d1 & 0b00000001))
		{
			d1=1;
		}
		data_d1=data_d1>>1;  //Now bring next bit at MSB positio
		if(!(data_d2 & 0b00000001))
		{
			d2=1;
		}
		data_d2=data_d2>>1;
		
		//if(!(data_d21 & 0b00000001))
		//{
			//d21=1;
		//}
		//data_d21=data_d21>>1;  //Now bring next bit at MSB positio
		//if(!(data_d22 & 0b00000001))
		//{
			//d22=1;
		//}
		//data_d22=data_d22>>1;  //Now bring next bit at MSB position
		//-----------------------------------------------
		//if(!(data_s1 & 0b00000001))
		//{
			//s1=1;
		//}
		//data_s1=data_s1>>1;  //Now bring next bit at MSB positio
		//if(!(data_s2 & 0b00000001))
		//{
			//s2=1;
		//}
		//data_s2=data_s2>>1;
		
		//if(!(data_s21 & 0b00000001))
		//{
			//s21=1;
		//}
		//data_s21=data_s21>>1;  //Now bring next bit at MSB positio
		//if(!(data_s22 & 0b00000001))
		//{
			//s22=1;
		//}
		//data_s22=data_s22>>1;  //Now bring next bit at MSB position
		
		p10_sug();  //Pulse the Clock line
	}
	//Now all 8 bits have been transferred to shift register
	//Move them to output latch at one
	//HC595Latch();
}
//#define c1_8
void quet_p10_1_mau()
{
	static uint8_t ch=0;
	u8 so_byte_rog=rog/8;
	for(uint8_t i=0;i<so_byte_rog;i++)
	{
		//p10_hc595_2b(p10_vram[(so_byte_rog-1-i)*cao+ch],p10_vram[(so_byte_rog-1-i)*cao+ch+8],0);
		//p10_hc595_2bx2(p10_vram[(so_byte_rog-1-i)*cao+ch],p10_vram[(so_byte_rog-1-i)*cao+ch+8],p10_vram[(so_byte_rog-1-i)*cao+ch+16],p10_vram[(so_byte_rog-1-i)*cao+ch+8+16],0);
		p10_hc595_1_mau(p10_vram_d[(so_byte_rog-1-i)*cao+ch],p10_vram_d[(so_byte_rog-1-i)*cao+ch+8],p10_vram_d[(so_byte_rog-1-i)*cao+ch+16],p10_vram_d[(so_byte_rog-1-i)*cao+ch+8+16],
		p10_vram_s[(so_byte_rog-1-i)*cao+ch],p10_vram_s[(so_byte_rog-1-i)*cao+ch+8],p10_vram_s[(so_byte_rog-1-i)*cao+ch+16],p10_vram_s[(so_byte_rog-1-i)*cao+ch+8+16]);
		//p10_hc595_2b(p10_vram[(7-i)*2+ch],p10_vram[(7-i)*4+ch]);
	}
	p10_of();
	p10_lat();
	p10_chon_ceh(ch);
	p10_on();
	ch++;
	if(ch>7)
	ch=0;
}


void p10_hc595_1_mau3264(u8 data_d1,u8 data_d2,u8 data_d21,u8 data_d22, u8 data_s1,u8 data_s2,u8 data_s21,u8 data_s22)
{
	//Send each 8 bits serially

	//Order is MSB first
	for(uint8_t i=0;i<8;i++)
	{
		//Output the data on DS line according to the
		//Value of MSB
		d1=0;
		//s1=0;
		d2=0;
		//s2=0;
		//d21=0;
		//s21=0;
		//d22=0;
		//s22=0;
		if(!(data_d1 & 0b00000001))
		{
			d1=1;
		}
		data_d1=data_d1>>1;  //Now bring next bit at MSB positio
		if(!(data_d2 & 0b00000001))
		{
			d2=1;
		}
		data_d2=data_d2>>1;
		
		//if(!(data_d21 & 0b00000001))
		//{
		//d21=1;
		//}
		//data_d21=data_d21>>1;  //Now bring next bit at MSB positio
		//if(!(data_d22 & 0b00000001))
		//{
		//d22=1;
		//}
		//data_d22=data_d22>>1;  //Now bring next bit at MSB position
		//-----------------------------------------------
		//if(!(data_s1 & 0b00000001))
		//{
		//s1=1;
		//}
		//data_s1=data_s1>>1;  //Now bring next bit at MSB positio
		//if(!(data_s2 & 0b00000001))
		//{
		//s2=1;
		//}
		//data_s2=data_s2>>1;
		
		//if(!(data_s21 & 0b00000001))
		//{
		//s21=1;
		//}
		//data_s21=data_s21>>1;  //Now bring next bit at MSB positio
		//if(!(data_s22 & 0b00000001))
		//{
		//s22=1;
		//}
		//data_s22=data_s22>>1;  //Now bring next bit at MSB position
		
		p10_sug();  //Pulse the Clock line
	}
	//Now all 8 bits have been transferred to shift register
	//Move them to output latch at one
	//HC595Latch();
}
//#define c1_8
void quet_p10_1_mau3264(uint8_t lap)
{
	uint8_t j;
	
	for (j=0;j<lap;j++)
	{
		for(uint8_t i=0;i<b_rog;i++)
		{
			//p10_hc595_2b(p10_vram[(so_byte_rog-1-i)*cao+ch],p10_vram[(so_byte_rog-1-i)*cao+ch+8],0);
			//p10_hc595_2bx2(p10_vram[(so_byte_rog-1-i)*cao+ch],p10_vram[(so_byte_rog-1-i)*cao+ch+8],p10_vram[(so_byte_rog-1-i)*cao+ch+16],p10_vram[(so_byte_rog-1-i)*cao+ch+8+16],0);
			p10_hc595_1_mau3264(
			p10_vram_d[(b_rog-1-i)*cao+kenh_chon],p10_vram_d[(b_rog-1-i)*cao+kenh_chon+16],p10_vram_d[(b_rog-1-i)*cao+kenh_chon+16],p10_vram_d[(b_rog-1-i)*cao+kenh_chon+8+16],
			p10_vram_s[(b_rog-1-i)*cao+kenh_chon],p10_vram_s[(b_rog-1-i)*cao+kenh_chon+8],p10_vram_s[(b_rog-1-i)*cao+kenh_chon+16],p10_vram_s[(b_rog-1-i)*cao+kenh_chon+8+16]);
			//p10_hc595_2b(p10_vram[(7-i)*2+ch],p10_vram[(7-i)*4+ch]);
		}
		p10_of();
	}
	
	//p10_of();
	p10_lat();
	p10_chon_ceh(kenh_chon);
	p10_on();
	kenh_chon++;
	if(kenh_chon>kieu_quet-1)
	kenh_chon=0;
}
#endif

