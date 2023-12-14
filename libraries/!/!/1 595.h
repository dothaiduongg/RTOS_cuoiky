#ifndef _595_h_
#define _595_h_
#include <!/! LDN.h>
#ifndef da_595
	#define da_595 dk_bit(PORTD,4)
	#define da_595_d dk_bit(DDRD,4)
	#define st_595 dk_bit(PORTD,3)
	#define st_595_d dk_bit(DDRD,3)  
	#define sh_595 dk_bit(PORTD,0)
	#define sh_595_d dk_bit(DDRD,0)
#endif
//========================================
void khoi_tao_595()
{
	da_595_d=st_595_d=sh_595_d=ra;
	#ifdef da_i_595
	da_i_595_d=vao;
	#endif
}
void out_595()
{
	st_595=1;
	st_595=0;
}
void xuat_595(u8 du_lieu)
{
	u8 i;
	for(i=0;i<8;i++)
	{
		da_595=(du_lieu&0x80)?1:0;
		sh_595=1;
		sh_595=0;
		du_lieu<<=1;
	}
}
//========================================
#ifdef da_i_595
u8 doc_ngo_vao_595() // truyen du lieu ra thanh ghi dich
{
	u8 du_lieu=0;
	u8 i;
	da_i_595_d=vao;
	da_595=0;
	sh_595=1;
	sh_595=0;
	da_595=1;
	sh_595=1;
	sh_595=0;
	for (u8 i=0; i<8; i++)
	{
		_delay_us(80); // tao thoi gian tre ms
		du_lieu=du_lieu>>1;
		if(da_i_595==1)
		{
			du_lieu |= 0x80;
		}
		sh_595=1;
		sh_595=0;
	}
	return du_lieu;
}
#endif
#endif
