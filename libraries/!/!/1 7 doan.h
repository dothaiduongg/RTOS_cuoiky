//#ifdef _7_b_
//#undef _7_doan_h_
//#ifndef _7_b_tc_ // dinh nghia ma 7 doan tuy chon
//#undef _7_doan_h_

//#endif 
//#endif

 
#ifndef _7_doan_h_
#define _7_doan_h_
#include <!/! LDN.h>

#ifndef ma7doan
	const char ma7doan[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90
		,0x88,0x83,0xC6,0xA1,0x86,0x8E,0xC2,0x89,0x7F,0xBF,0xFF};//-18 dau .
		// 19 dau tru
		// 20 tat het
#endif
#ifndef la
	#define la dk_bit(PORTB,1)
	#define la_d dk_bit(DDRB,1)
	#define lb dk_bit(PORTB,2)
	#define lb_d dk_bit(DDRB,2)
	#define lc dk_bit(PORTB,3)
	#define lc_d dk_bit(DDRB,3)
	#define ld dk_bit(PORTB,4)
	#define ld_d dk_bit(DDRB,4)
	#define le dk_bit(PORTB,5)
	#define le_d dk_bit(DDRB,5)
	#define lf dk_bit(PORTD,7)
	#define lf_d dk_bit(DDRD,7)
	#define lg dk_bit(PORTD,6)
	#define lg_d dk_bit(DDRD,6)
	#define lh dk_bit(PORTB,0)
	#define lh_d dk_bit(DDRB,0)
#endif
//========================================
u8 ma_7_b; // byte chua ma 7 doan
#define b7a dk_bit(ma_7_b,0)
#define b7b dk_bit(ma_7_b,1)
#define b7c dk_bit(ma_7_b,2)
#define b7d dk_bit(ma_7_b,3)
#define b7e dk_bit(ma_7_b,4)
#define b7f dk_bit(ma_7_b,5)
#define b7g dk_bit(ma_7_b,6)
#define b7h dk_bit(ma_7_b,7)

void khoi_tao_7_doan()
{
	la_d=lb_d=lc_d=le_d=lf_d=lg_d=lh_d=ld_d=ra;
}
void xuat_7(u8 ma) 
{
	la=(ma&0x1);
	ma>>=1;
	lb=(ma&0x1);
	ma>>=1;
	lc=(ma&0x1);
	#ifdef lc2
	lc2=(ma&0x1);
	#endif
	ma>>=1;
	ld=(ma&0x1);
	#ifdef ld2
	ld2=(ma&0x1);
	#endif
	ma>>=1;
	le=(ma&0x1);
	#ifdef le2
	le2=(ma&0x1);
	#endif
	ma>>=1;
	lf=(ma&0x1);
	ma>>=1;
	lg=(ma&0x1);
	ma>>=1;
	lh=(ma&0x1);
}
//========================================
void xuat_7_(u8 ma)
{
	la=!(ma&0x1);
	ma>>=1;
	lb=!(ma&0x1);
	ma>>=1;
	lc=!(ma&0x1);
	ma>>=1;
	ld=!(ma&0x1);
	ma>>=1;
	le=!(ma&0x1);
	ma>>=1;
	lf=!(ma&0x1);
	ma>>=1;
	lg=!(ma&0x1);
	ma>>=1;
	lh=!(ma&0x1);
}
//----------------------------------------  
#ifdef _7_b_
u8 xuat_7_b(u8 ma)
{
	b7a=(ma&0x1);
	ma>>=1;
	b7b=(ma&0x1);
	ma>>=1;
	b7c=(ma&0x1);
	ma>>=1;
	b7d=(ma&0x1);
	ma>>=1;
	b7e=(ma&0x1);
	ma>>=1;
	b7f=(ma&0x1);
	ma>>=1;
	b7g=(ma&0x1);
	ma>>=1;
	b7h=(ma&0x1);
	return ma_7_b;
}
//========================================
u8 xuat_7_b_(u8 ma)
{
	b7a=!(ma&0x1);
	ma>>=1;
	b7b=!(ma&0x1);
	ma>>=1;
	b7c=!(ma&0x1);
	ma>>=1;
	b7d=!(ma&0x1);
	ma>>=1;
	b7e=!(ma&0x1);
	ma>>=1;
	b7f=!(ma&0x1);
	ma>>=1;
	b7g=!(ma&0x1);
	ma>>=1;
	b7h=!(ma&0x1);
	return ma_7_b;
}
#endif
#endif
