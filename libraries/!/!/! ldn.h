#ifndef _ldn_h_
#define _ldn_h_
#include <avr/io.h> // include I/O definitions (port names, pin names, etc)
#include <stdint.h>
#include <avr/wdt.h> 
#include <string.h> 
typedef unsigned char int8; // Dinh nghia lai kieu du lieu
typedef unsigned int int16; // Dinh nghia lai kieu du lieu
typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;
typedef unsigned char uchar;
typedef unsigned char byte;

typedef uint64_t u64;
typedef unsigned long long u64;
typedef volatile unsigned char vu8;
typedef volatile unsigned int vu16;
typedef volatile unsigned long vu32;

u16 make16(u8 bt,u8 bc);
u8 make8(unsigned int du_lieu, u8 vi_tri);

// typedef static volatile unsigned char su8;
// typedef static volatile unsigned int su16;
// typedef static volatile unsigned long su32;
//#define khong_dung_eeprom //

#define NOOP asm volatile("nop" ::)
#define nop asm volatile("nop" ::)

#ifndef F_CPU
	//#define F_CPU 8000000
#endif
#include <stdbool.h>
#include <stdio.h>
typedef bool int1;	
#include <avr/interrupt.h>
#include <util/delay.h>

#ifdef uart
#include "!/uart.c"
#endif
#include <avr/wdt.h>
//#include <!/spi.c>
#ifndef cbi
#define cbi(port, bit) 	   (port) &= ~(1 << (bit))
#endif
#ifndef sbi
#define sbi(port, bit) 	   (port) |=  (1 << (bit))
#endif
//#define timer_0_rieng
typedef struct
{
	unsigned int bit0:1;
	unsigned int bit1:1;
	unsigned int bit2:1; 
	unsigned int bit3:1;
	unsigned int bit4:1;
	unsigned int bit5:1;
	unsigned int bit6:1;
	unsigned int bit7:1;
} _io_reg;
#define dk_bit(rg,bt) ((volatile _io_reg*)&rg)->bit##bt // dang ky 1 bit

typedef struct
{
	unsigned int bit0:1;
	unsigned int bit1:1;
	unsigned int bit2:1;
	unsigned int bit3:1;
	unsigned int bit4:1;
	unsigned int bit5:1;
	unsigned int bit6:1;
	unsigned int bit7:1;
	unsigned int bit8:1;
	unsigned int bit9:1;
	unsigned int bit10:1;
	unsigned int bit11:1;
	unsigned int bit12:1;
	unsigned int bit13:1;
	unsigned int bit14:1;
	unsigned int bit15:1;
} _io_reg_16;
#define dk_bit16(rg,bt) ((volatile _io_reg_16*)&rg)->bit##bt // dang ky 1 bit


#define BUTTON_PIN  dk_bit(PINB,3)
#define LED_PORT    dk_bit(PORTB,4)

#define BUTTON_DIR  dk_bit(DDRB,3)
#define LED_DIR     dk_bit(DDRB,4)
/*
uint8_t is_button = BUTTON_PIN;

LED_DIR = 1;
BUTTON_DIR = 0;

while (1) {
	LED_PORT = BUTTON_PIN;
}*/ 

u8 bbit; // byte chua ma 7 doan
#define bb0 dk_bit(bbit,0)
#define bb1 dk_bit(bbit,1)
#define bb2 dk_bit(bbit,2)
#define bb3 dk_bit(bbit,3)
#define bb4 dk_bit(bbit,4)
#define bb5 dk_bit(bbit,5)
#define bb6 dk_bit(bbit,6)
#define bb7 dk_bit(bbit,7)

/* Set a certain bit in any register */
#define bat_bit(REG,BIT) (REG|=(1<<BIT))

/* Clear a certain bit in any register */
#define tat_bit(REG,BIT) (REG&=(~(1<<BIT)))

/* Toggle a certain bit in any register */
#define dao_bit(REG,BIT) (REG^=(1<<BIT))
#define bit_thi_bat(REG,BIT) ( REG & (1<<BIT) )

/* Check if a specific bit is cleared in any register and return true if yes */
#define bit_thi_tat(REG,BIT) ( !(REG & (1<<BIT)) )
//---------------------------------------- 
#define vao 0
#define ra 1 

#define cam_ngat cli()
#define cho_ngat sei()
//========================================
#define bat_ngat_t0_at8 TIMSK= (1<<TOIE0) // Cho phép ngắt timer 0 

#define bu_dau_8 128
#define bu_dau_16 32768
//======================================== 
#ifndef khong_dung_eeprom
#include <avr/eeprom.h>
#include "!/! e_rom.h"
#endif
static inline void timer0_01(void);
static inline void timer2_01(void);
void giam_thoi_gian_uart(void);
//char* tach_chuoi_cuoi(char* chuoi_vao);
void khoi_tao()
{
	timer2_01();
}
//======================================== 
void delay_us(u16 tg)
{
	while(tg)
	{
		tg--;
		_delay_us(1);
	}
}
//======================================== 
void delay_ms(u16 tg)
{
	while(tg)
	{
		tg--;
		_delay_ms(1);
	}
}
//========================================
// ISR(TIMER1_COMPA_vect) // Vec to ngat timer1
// {
// 	if(dtg<50000)
// 	dtg++;
// }
//======================================== 
static inline void set_timer_1(u16 gt)
{
	#if F_CPU == 12000000
	gt*=1.5;
	#endif
	#if F_CPU == 16000000
	gt*=2;
	#endif
	
	#if  defined(__AVR_ATmega8__) || defined(__AVR_ATmega8A__) || defined(__AVR_ATmega16__)|| defined(__AVR_ATmega32__)
	TCCR1B |= 1<<WGM12 | 1<<CS11 | 1<<CS10;		//Start timer1 in CTC mode with prescaler of 64
	TIMSK |= 1<<OCIE1A;					//Enable compare match interrupt
	OCR1A = gt;
	#endif
	#if  defined(__AVR_ATmega328__) || defined(__AVR_ATmega168PA__)
	OCR1A = gt/4;///11;

	TCCR1B |= (1 << WGM12);
	// Mode 4, CTC on OCR1A
	TIMSK1 |= (1 << OCIE1A);
	//Set interrupt on compare match

	TCCR1B |= (1 << CS12);// | (1 << CS10);
	
	
	//TCCR0A |= (1 << WGM01);
	//TCCR0B |= (1 << CS02);
	//TIMSK0 |= (1 << OCIE0A); 
	//ICR1 = gt;
	//TCCR1B |= (1 << CS12);
	//TCCR1B |= (1 << WGM12);
	//TIMSK1 |= (1 << ICIE1);
	//TIMSK0 |= 1<<OCIE1A;					//Enable compare match interrupt
	#endif
	//0x005B;					//Set compare value for 500 mSec
	sei();						//Enable global interrupts	
}
static inline void timer1_500(void)	//Function used once to set up the timer
{
	set_timer_1(62499);	
}
static inline void timer1_10(void) // 1874 (12M)
{
	set_timer_1(1249);
}
//========================================
static inline void timer1_100(void)	//Function used once to set up the timer
{
	set_timer_1(12499);
}
//========================================
static inline void timer1_1(void)	//Function used once to set up the timer
{
	set_timer_1(124);
}
//========================================
static inline void timer1_01(void)	//Function used once to set up the timer
{
	set_timer_1(11);
}
//========================================
static inline void timer1_001(void)	//Function used once to set up the timer
{
	set_timer_1(1);
}
//========================================
u8 t0_dat=131;
#define cho_pep_gat_t0 TIMSK|=(1<<TOIE0)
static inline void timer0_1(void)	//Function used once to set up the timer
{
	u8 t=t0_dat;
	#if F_CPU == 12000000
	t/=1.5;
	t0_dat=t;
	#endif
	#if F_CPU == 16000000
	t*=2;
	#endif
	TCNT0=t; // 1mS
	#if  defined(__AVR_ATmega8__)|| defined(__AVR_ATmega8A__) || defined(__AVR_ATmega16__)|| defined(__AVR_ATmega32__)
	TCCR0|=(1<<CS01)|(1<<CS00);
	TIMSK|=(1<<TOIE0); //
	#endif
	#if  defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168PA__)
	TCCR0A |= (1 << WGM01);
	TCCR0B |= (1 << CS01) | (1 << CS00);
	//TCCR0B = (1<<CS02)|(1<<CS00); // Clock / 1024 // tần số xung / 1024
	TIMSK0= (1<<TOIE0); // Cho phép ngắt timer 0
	#endif
	sei(); // ISR(TIMER0_OVF_vect)
	//	TCNT0=-20;
	//	TCCR0|=(1<<CS01)|(1<<CS00);
	//	TIMSK= (1<<TOIE0); // Cho phép ngắt timer 0
}
//static inline void timer0_01(void)
//{
	//timer0_1();
	//t0_dat=13;
	//TCNT0=13;
//}
static inline void timer0_001(void)
{
	timer0_1();
}
long map(long x, long in_min, long in_max, long out_min, long out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
int map_u16(int x, int in_min, int in_max, int out_min, int out_max)
{
	long a=x;
	a=a-in_min;
	a=a*(out_max - out_min);
	return a/ (in_max - in_min) + out_min;
}
u32 map_u32(u32 x, u32 in_min, u32 in_max, u32 out_min, u32 out_max)
{
	long a=x;
	a=a-in_min;
	a=a*(out_max - out_min);
	return a/ (in_max - in_min) + out_min;
}

//========================================
u8 ci_tu_so(u8 ci_tu)
{
	if(ci_tu>=0x30&&ci_tu<=0x39)
	{
		ci_tu-=0x30;
	}
	else
	ci_tu=0;
	return ci_tu;
}

//========================================
u32 tag_thah_phan_32 (u32 in,u8 tp)
{
	u32 sbc=10000; // So bi chia
	if (tp==4)
	sbc=1000;
	else
	if (tp==3)
	sbc=100;
	else
	if (tp==2)
	sbc=10;
	else
	if (tp==1)
	sbc=1;
	if (in/sbc%10==9) in=in - (sbc*9);
	else in = in+sbc;
	return (in);
}
//========================================
u32 dam_thah_phan_32 (u32 in,u8 tp)
{
	u32 sbc=10000; // So bi chia
	if (tp==4)
	sbc=1000;
	else
	if (tp==3)
	sbc=100;
	else
	if (tp==2)
	sbc=10;
	else
	if (tp==1)
	sbc=1;
	if (in/sbc%10==0) in=in + (sbc*9);
	else in = in-sbc;
	return (in);
}
//========================================
//TCCR0 = (1<<CS02)|(1<<CS00); // Clock / 1024 // tần số xung / 1024
//TIMSK= (1<<TOIE0); // Cho phép ngắt timer 0

// TCCR0 = (1<<CS1); // Clock / 8 // tần số xung / 8
// TCCR0 = (1<<CS1)|(1<<CS0); // Clock / 64 // tần số xung / 64
// TCCR0 = (1<<CS2); // Clock / 256 // tần số xung / 256
// TCCR0 = (1<<CS0); // Clock / 1 // tần số xung / 1
// TCCR0 = 0; // dừng timer0
// TCCR0 = (1<<CS2)|(1<<CS1); // External clock source on T0 pin, Clock on Falling edge
// TCCR0 = (1<<CS2)|(1<<CS1)|(1<<CS0); // External clock source on T0 pin, Clock on rising edge
//========================================
u8 bin2bcd(u8 binary_value)//19
{
	u8 temp;
	u8 retval;
	temp = binary_value;
	retval = 0;
	while(true)
	{ // Get the tens digit by doing multiple subtraction
		if(temp >= 10) // of 10 from the binary value.
		{
			temp -= 10;
			retval += 0x10;
		}
		else // Get the ones digit by adding the remainder.
		{
			retval += temp;
			break;
		}
	}
	return(retval);
}
//========================================
u8 bcd2bin(u8 bcd_value) //19
{
	u8 tam;
	tam = bcd_value;
	tam >>= 1; // Shifting upper digit right by 1 is same as multiplying by 8.
	tam &= 0x78; // Isolate the bits for the upper digit.
	return(tam + (tam >> 2) + (bcd_value & 0x0f)); // Now return: (Tens * 8) + (Tens * 2) + Ones
	//return ( (bcd_val/16*10) + (bcd_val%16) );
}

void dik_trai_mag(u8 *s,u8 dl)
{
	u8 cik_thuoc=sizeof(s)-1;
	u8 i;
	for(i=0;i<cik_thuoc;i++)
	{
		s[i]=s[i+1];
	}
	s[i]=dl;
}
void dik_trai_mag16(u16 *s,u16 dl)
{
	u8 cik_thuoc=sizeof(s)-1;
	u8 i;
	for(i=0;i<cik_thuoc;i++)
	{
		s[i]=s[i+1];
	}
	s[i]=dl;
}
u16 trug_bih_cog_mag16(u16 *s)
{
	u8 cik_thuoc=sizeof(s);
	u8 i;
	u32 tog=0;
	for(i=0;i<cik_thuoc;i++)
	{
		tog+=s[i];
	}
	return tog/cik_thuoc;
}
u16 trug_bih_cog_mag_s16(signed int *s)
{
	u8 cik_thuoc=sizeof(s);
	u8 i;
	u32 tog=0;
	for(i=0;i<cik_thuoc;i++)
	{
		tog+=s[i];
	}
	return tog/cik_thuoc;
}

double adc_ntc_10k_do_c(u16 so_adc)
{
	long R;
	double Thermister;
	R=(((10230000)/(1023-so_adc)) - 10000);/* calculate the resistance */
	
	Thermister = log(R);	/* calculate natural log of resistance */
	/* Steinhart-Hart Thermistor Equation: */
	/*  Temperature in Kelvin = 1 / (A + B[ln(R)] + C[ln(R)]^3)		*/
	/*  where A = 0.001129148, B = 0.000234125 and C = 8.76741*10^-8  */
	Thermister = 1 / (0.001129148 + (0.000234125 * Thermister) + (0.0000000876741 * Thermister * Thermister * Thermister));
	Thermister = Thermister - 273.15;/* convert kelvin to °C */
	
	return Thermister;
}
//========================================
double dong;
long gia_tri_nhiet_tro;
long ap_adc;
double adc_ntc_10k_do_c_r4_7(u16 so_adc) // r 4.7k
{
	double Thermister;
	ap_adc=so_adc;
	dong=((1023-ap_adc)*1000)/4700; // Tính dòng trên 2 đầu điển trở 4,7k
	gia_tri_nhiet_tro=((ap_adc*1000)/dong);/* calculate the resistance */// tình điện trở của NTC
	Thermister = log(gia_tri_nhiet_tro);	/* calculate natural log of resistance */
	/* Steinhart-Hart Thermistor Equation: */
	/*  Temperature in Kelvin = 1 / (A + B[ln(R)] + C[ln(R)]^3)		*/
	/*  where A = 0.001129148, B = 0.000234125 and C = 8.76741*10^-8  */
	Thermister = 1 / (0.001129148 + (0.000234125 * Thermister) + (0.0000000876741 * Thermister * Thermister * Thermister));
	Thermister = Thermister - 273.15;/* convert kelvin to °C */
	return Thermister;
}

u8 dau; // Khai báo biến số nguyên không dấu 8-bit có tên là 'dau'

u16 f2c(u16 f) // Định nghĩa hàm 'f2c' nhận một số nguyên 16-bit không dấu 'f' làm đầu vào
{
	u16 nd_doi; // Khai báo biến số nguyên không dấu 16-bit có tên là 'nd_doi'
	if (dau == '+') // Kiểm tra giá trị của biến 'dau' (giả định là '+' hoặc '-')
	{
		if (f > 320)
		{
			nd_doi = (f - 320); // Trừ 320 từ 'f' và lưu kết quả vào 'nd_doi'
		}
		else
		{
			nd_doi = (320 - f); // Trừ 'f' từ 320 và lưu kết quả vào 'nd_doi'
			dau = '-'; // Cập nhật giá trị của 'dau' thành '-'
		}
	}
	else
	{
		nd_doi = f + 320; // Cộng 320 vào 'f' và lưu kết quả vào 'nd_doi'
	}
	return nd_doi * 10 / 18; // Chuyển đổi 'nd_doi' từ Fahrenheit sang Celsius sử dụng công thức (F - 32) * 5/9
}
// u16 c2f(u16 c)
// {
// 	
// 	float nht=c;
// 	nht-=1000;
// 	nht/=10;
// 	nht=(nht*1.8+32);
// 	if (nht>=0) dau ='+';
// 	else nht=0-nht;
// 	return nht*10;
// }
u16 c2f(u16 c)
{
	if (dau == '-')
	{
		if(c<178)
		{
			dau = '+';
			c=320-c*18/10;
		}
		else
		{
			c=c-178;
			c=c*18/10;
		}
	}
	else
	{
		c=c*18/10+320;
	}
	return c;
}
// u8 dau;
// u16 f2c(u16 f)
// {
// 	u16 nd_doi;
// 	if(dau=='+')
// 	{
// 		if(f>320)
// 		{
// 			nd_doi=(f-320);
// 		}
// 		else
// 		{
// 			nd_doi=(320-f);
// 			dau='-';
// 		}
// 	}
// 	else
// 	{
// 		nd_doi=f+320;
// 	}
// 	return nd_doi*10/18;
// }
//========================================
u16 tag_thah_phan_16 (u16 in,u8 tp)
{
	u16 sbc=10000; // So bi chia
	if (tp==4)
	sbc=1000;
	else
	if (tp==3)
	sbc=100;
	else
	if (tp==2)
	sbc=10;
	else
	if (tp==1)
	sbc=1;
	if (in/sbc%10==9) in=in - (sbc*9);
	else in = in+sbc;
	return (in);
}
//========================================
u16 dam_thah_phan_16 (u16 in,u8 tp)
{
	u16 sbc=10000; // So bi chia
	if (tp==4)
	sbc=1000;
	else
	if (tp==3)
	sbc=100;
	else
	if (tp==2)
	sbc=10;
	else
	if (tp==1)
	sbc=1;
	if (in/sbc%10==0) in=in + (sbc*9);
	else in = in-sbc;
	return (in);
}
u16 chinh_tang_so_16(u16 so_chinh,u8 vi_tri) // chinh tang so theo vi tri mot don vi
{
	u8 i;
	u16 so_chia=1;
	for (i=1;i<vi_tri;i++)
	{
		so_chia*=10;
	}
	so_chinh+=so_chia;
	if(so_chinh/so_chia%10==0)
	{
		so_chinh-=so_chia*10;
	}
	return so_chinh;
}
uint32_t chinh_tang_so_32(uint32_t so_chinh,uint8_t vi_tri) // chinh tang so theo vi tri mot don vi
{
	uint8_t i;
	uint32_t so_chia=1;
	for (i=1;i<vi_tri;i++)
	{
		so_chia*=10;
	}
	so_chinh+=so_chia;
	if(so_chinh/so_chia%10==0)
	{
		so_chinh-=so_chia*10;
	}
	return so_chinh;
}

//u8 bit_test_8 (u8 var, u8 bit)
//{
	//return (var & (1<<bit));
//}
//
//u8 bit_set (u8 var, u8 bit)
//{
	//return var |= (1<<bit);
//}
//u8 bit_clear (u8 var, u8 bit)
//{
	//return var &= ~(1<<bit);
//}

//========================================
u16 make16(u8 bt,u8 bc)
{
	u16 kq = (u16)bc;
	kq=kq<<8;
	return kq=kq|(u16)bt;
}
u8 make8(unsigned int du_lieu, u8 vi_tri)
{
	if(vi_tri==1)
	{
		du_lieu=(du_lieu>>8);
	}
	vi_tri=(unsigned char)(du_lieu & 0xFF);
	return (vi_tri);
}
//======================================== 
u8 tim_2_giong_8(u8 arr[], u8 size)
{
	u8 i, j;
	u8 kq=255;
	for(i = 0; i < size-1; i++)
	{
		for(j = i+1; j < size; j++)
		{
			if(arr[i] == arr[j])
			{
				kq=arr[i];
				return kq;
			}
		}
	}
	return kq;
}
//======================================== 
signed int tim_2_giong_s16(signed int *s)
{
	u8 cik_thuoc=sizeof(s);
	u8 so_so_giong=0;
	signed int kq=0;
	u8 i;
	u8 j;
	for(i = 0; i < cik_thuoc-1; i++)
	{
		for(j = i+1; j < cik_thuoc; j++)
		{
			if(s[i] == s[j])
			{
				so_so_giong++;
				if(so_so_giong>=cik_thuoc/2)
				{
					kq=s[i];
					return kq;
				}
			}
		}
	}
	return kq;
}
//========================================
signed int tim_2_trong_s16_cong_tru(signed int *s,u8 cong_tru)
{
	u8 cik_thuoc=sizeof(s);
	u8 so_so_giong=0;
	signed int kq=0;
	u8 i;
	u8 j;
	for(i = 0; i < cik_thuoc-1; i++)
	{
		for(j = i+1; j < cik_thuoc; j++)
		{
			if(s[i] < s[j]+cong_tru&&s[i] > s[j]-cong_tru)
			{
				so_so_giong++;
				if(so_so_giong>=cik_thuoc/3)
				{
					kq=s[i];
					return kq;
				}
			}
		}
	}
	return kq;
}
//========================================
u8 tim_2_giong_8_gioi_han(u8 arr[], u8 size,u8 gioi_han)
{
	u8 i, j;
	u8 kq=255;
	for(i = 0; i < size-1; i++)
	{
		for(j = i+1; j < size; j++)
		{
			if(arr[i] == arr[j] && arr[j]< gioi_han)
			{
				kq=arr[i];
				return kq;
			}
		}
	}
	return kq;
}
//========================================
u16 tim_2_giong_16_gioi_han(u16 arr[], u8 size,u16 gioi_han)
{
	u8 i, j;
	u16 kq=0xffff;
	for(i = 0; i < size-1; i++)
	{
		for(j = i+1; j < size; j++)
		{
			if(arr[i] == arr[j] && arr[j]<= gioi_han)
			{
				kq=arr[i];
				return kq;
			}
		}
	}
	return kq;
}
//========================================
u16 tim_3_giong_16_gioi_han(u16 arr[], u8 size,u16 gioi_han)
{
	u8 i, j, k;
	u16 kq=0xffff;
	for(i = 0; i < size-2; i++)
	{
		for(j = i+1; j < size; j++)
		{
			for(k = j+1; k < size; k++)
			{
				if(arr[i] == arr[j] && arr[i] == arr[k] && (arr[j]<= gioi_han||gioi_han==0))
				{
					kq=arr[i];
					return kq;
				}
			}
		}
	}
	return kq;
}
//========================================
void sao_chep_mang_8_16(u8 arr[], u16*mang_16_ra,u8 do_dai)
{
	u8 i;
	for(i = 0; i < do_dai; i++)
	{
		mang_16_ra[i] = arr[i];
	}
}
//========================================
/*
void tach_chuoi_cuoi(char *chuoi_vao, char *chuoi_ra) {
  int len = strlen(chuoi_vao);
  int i = len - 1;
  while (i >= 0 && chuoi_vao[i] != ',') {
    i--;
  }
  if (i >= 0) {
    chuoi_vao[i] = '\0';
    strcpy(chuoi_ra, &chuoi_vao[i+1]);
  } else {
    strcpy(chuoi_ra, chuoi_vao);
    chuoi_vao[0] = '\0';
  }
}*/

// hàm tách phần cuối cùng của chuỗi
/*
char* tach_chuoi_cuoi(char* chuoi_vao)
{
    char* chuoi = strdup(chuoi_vao); // tạo một bản sao của chuỗi để tránh thay đổi chuỗi gốc
    char* phan_tu_cuoi = strrchr(chuoi, ','); // tìm phần tử cuối cùng được phân tách bởi dấu phẩy
    if (phan_tu_cuoi == NULL) { // không tìm thấy dấu phẩy
        return NULL;
    }
    *phan_tu_cuoi = '\0'; // đặt ký tự kết thúc chuỗi cho phần tử cuối cùng
    return strdup(phan_tu_cuoi + 1); // trả về phần cuối cùng của chuỗi (phần phía sau dấu phẩy)
}
*/
void tach_chuoi_cuoi(char* chuoi_vao, char* chuoi_ra) { // để lại dấu phẩy
	char* p = strrchr(chuoi_vao, ',');
	if (p != NULL) {
		strcpy(chuoi_ra, p + 1);
		*p = '\0';
		} else {
		*chuoi_ra = '\0';
	}
}

void tach_chuoi_chuoi(char* chuoi_vao, char* chuoi_ra) {
	// Tìm vị trí đầu tiên của dấu phẩy
	char* p = strchr(chuoi_vao, ',');
	if (p != NULL) {
		// Sao chép chuỗi từ đầu đến vị trí đầu tiên của dấu phẩy vào chuỗi_ra
		strncpy(chuoi_ra, chuoi_vao, p - chuoi_vao);
		// Sao chép chuỗi từ vị trí tiếp theo sau dấu phẩy đến hết chuỗi vào chuoi_vao
		strcpy(chuoi_vao, p + 1);
		} else {
		// Nếu không tìm thấy dấu phẩy, sao chép toàn bộ chuỗi vào chuoi_ra và rỗng chuoi_vao
		strcpy(chuoi_ra, chuoi_vao);
		strcpy(chuoi_vao, "");
	}
	// Đảm bảo chuỗi_ra kết thúc bằng null
	chuoi_ra[p-chuoi_vao] = '\0';
}

void tach_chuoi_chuoi_(char* chuoi_vao, char* chuoi_ra) {
	// Sao chép chuỗi vào chuỗi_ra để không thay đổi chuỗi đầu vào
	strcpy(chuoi_ra, chuoi_vao);
	// Tìm vị trí của ký tự delimiter đầu tiên
	const char* p = strchr(chuoi_ra, ',');
	if (p == NULL) 
	{
		strcpy(chuoi_vao, "");
	}
	else
	{
		chuoi_ra[p - chuoi_ra] = '\0';
		strncpy(chuoi_vao,p - chuoi_ra,strlen(chuoi_vao));
	}
}

void tach_chuoi_chuoi__(const char* chuoi_vao, char* chuoi_ra, const char* delim) {
	// Sao chép chuỗi vào chuỗi_ra để không thay đổi chuỗi đầu vào
	strcpy(chuoi_ra, chuoi_vao);

	// Tìm vị trí của ký tự delimiter đầu tiên
	const char* p = strchr(chuoi_ra, *delim);
	if (p == NULL) {
		return -1;  // Không tìm thấy delimiter
	}

	// Thay thế delimiter bằng ký tự kết thúc chuỗi
	chuoi_ra[p - chuoi_ra] = '\0';

	// Trả về vị trí bắt đầu của chuỗi con được tách ra
	return p - chuoi_vao + 1;
}

void tach_chuoi_chuoi___(char* chuoi_vao, char* chuoi_ra, char* chuoi_phan_tach) {
	// Tach chuoi vao va luu gia tri tra ve cua strtok vao chuoi_ra
	char* token = strtok(chuoi_vao, chuoi_phan_tach);
	if (token != NULL) {
		strcpy(chuoi_ra, token);
		// Tim vi tri cua dau phay dau tien trong chuoi va sao chep chuoi con lai vao chuoi_vao
		char* p = strchr(chuoi_vao, ',');
		if (p != NULL) {
			strcpy(chuoi_vao, p+1);
			} else {
			strcpy(chuoi_vao, "");
		}
		} else {
		// Neu khong tim thay ky tu tach, thi gan chuoi_ra bang chuoi_vao
		strcpy(chuoi_ra, chuoi_vao);
		// Gan chuoi_vao ve rong
		strcpy(chuoi_vao, "");
	}
}

bool tach_chuoi_cuoi___(char *chuoi_vao, char *ma, char *delimiter) {
	char *token = strtok(chuoi_vao, delimiter);
	if (token == NULL) {
		return false;
	}

	while (token != NULL) {
		strcpy(ma, token);
		token = strtok(NULL, delimiter);
	}

	return true;
}

void tach_chuoi_cuoi____(char* chuoi_vao, char* chuoi_ra) 
{ // để lại dấu phẩy
	char* p = strrchr(chuoi_vao, '_');
	if (p != NULL) 
	{
		strcpy(chuoi_ra, p + 1);
		*p = '\0';
	} 
	else 
	{
		*chuoi_ra = '\0';
	}
}

bool tach_kt_tong(char *chuoi_vao) {
	bool kq = false;
	char ma[50];
	uint16_t tong_dai;
	uint16_t tong_dai_nhan;
	
	tach_chuoi_cuoi____(chuoi_vao, ma);
	//tach_chuoi_cuoi___(chuoi_vao, ma, "_");
	uint32_t tong_ma = 0;
	uint32_t ma_tong_nhan = atoi(ma);
	tach_chuoi_cuoi____(chuoi_vao, ma);
	//tach_chuoi_cuoi___(chuoi_vao, ma, "_");

	tong_dai_nhan = atoi(ma);
	tong_dai = strlen(chuoi_vao);

	for (int i = 0; i < tong_dai; i++) {
		tong_ma += chuoi_vao[i];
	}

	if (tong_ma == ma_tong_nhan && tong_dai == tong_dai_nhan) {
		kq = true;
	}

	return kq;
}
// tap hop bien dung chung cho tat cac cac chuong trinh

u8 lenh_tat_coi=0;
#ifndef khong_tg_luu
u8 tg_luu;
#endif
#ifndef khong_tg_giu
u16 tg_giu;
#endif
#ifndef khong_coi
u16 tg_coi;
#endif
#ifndef khong_milli
u32 mili_giay_32=0;
#endif
////========================================
#ifndef timer_0_rieng
u8 timer0_time;
void ldn_1ms(void); // ham bat buoc co trong chuong trinh
void ham_1ms()
{
	#ifndef khong_milli
	mili_giay_32++;
	#endif
	ldn_1ms();
	#ifndef khong_tg_luu
	if (tg_luu>1)
	{
		tg_luu--;
	}
	#endif
	#ifndef khong_tg_giu
	if(tg_giu<50000)
	{
		tg_giu++;
	}
	#endif
	#ifdef uart
	giam_thoi_gian_uart();
	#endif
}
//======================================== 
u8 timer2_time; 
static inline void set_timer_2(u8 tg)
{
	#if  defined(__AVR_ATmega328__) || defined(__AVR_ATmega168PA__)
	timer2_time=tg;
	TCNT2 = timer2_time;
	//OCR2 = timer2_time;//62;
	// TCCR2 |= (1 << WGM21);
	// Set to CTC Mode
	 TIMSK2 |= (1 << OCIE2B);
	//TIMSK |= (1 << TOIE2);
	//Set interrupt on compare match
	//TCCR2 |= (1 << CS21);
	TCCR2B |= (1 << CS21);
	// set prescaler to 64 and starts PWM
	#else
	timer2_time=tg;
	TCNT2 = timer2_time;
	//OCR2 = timer2_time;//62;
	// TCCR2 |= (1 << WGM21);
	// Set to CTC Mode
	TIMSK |= (1 << OCIE2);
	//TIMSK |= (1 << TOIE2);
	//Set interrupt on compare match
	TCCR2 |= (1 << CS21); 
	// set prescaler to 64 and starts PWM
	#endif
	sei();
}
////u32 aaa;
////========================================
static inline void timer2_01(void)	//Function used once to set up the timer
{
	//#if  defined(__AVR_ATmega328__)
	//#if F_CPU == 8000000
	//set_timer_2(137);
	//#endif
	//#if F_CPU == 12000000
	//set_timer_2(74);
	//#endif
	//#if F_CPU == 16000000
	//set_timer_2(11);
	//#endif
	//
	//#else
	
	#if F_CPU == 8000000
	set_timer_2(162);
	#endif
	#if F_CPU == 12000000
	set_timer_2(112);
	#endif
	#if F_CPU == 16000000
	set_timer_2(62);
	#endif
//	#endif
	//aaa=F_CPU;
}
////======================================== 
u8 time2_0001;
#ifndef timer_2_rieng
//u16 mili_giay_16=0;
#if defined(__AVR_ATmega328__) || defined(__AVR_ATmega168PA__)
ISR (TIMER2_COMPB_vect) // 170.
#else

ISR (TIMER2_COMP_vect) // 170.
#endif
{
	TCNT2 = timer2_time; // phai nap lai
	//#if  defined(__AVR_ATmega328__)
	//ham_1ms();
	//#else
	time2_0001++;
	if (time2_0001>=10)
	{
		time2_0001=0;
		ham_1ms();
	}
	//#endif
}
#endif
//======================================== 
static inline void set_timer_0(u8 tg)
{
	timer0_time=tg;
	TCNT0 = timer0_time;
	#if  defined(__AVR_ATmega8__)
	TCCR0|=(1<<CS01);//|(1<<CS00);
	TIMSK|=(1<<TOIE0); //
	#endif
	#if  defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168PA__)
	TCCR0A |= (1 << WGM01);
	TCCR0B |= (1 << CS01) | (1 << CS00); 
	//TCCR0B = (1<<CS02)|(1<<CS00); // Clock / 1024 // tần số xung / 1024
	TIMSK0= (1<<TOIE0); // Cho phép ngắt timer 0
	#endif
	sei();
}
static inline void timer0_01(void)	//Function used once to set up the timer
{
	#if F_CPU == 8000000
	set_timer_0(162);
	#endif
	#if F_CPU == 12000000
	set_timer_0(161);
	#endif
	#if F_CPU == 16000000
	set_timer_0(62);
	#endif
	sei();
}
#endif
#endif
