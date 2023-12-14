#ifndef _thoi_gian
#define _thoi_gian 
#include <!/! LDN.h>
u8 thu,ngay,thang,nam,gio,phut,giay;
u8 gio0,phut0,giay0,ngay0,thang0,nam0;
u8 m_day;
//int8 gio_bin;
//#bit b_f_gio=gio_bin.6  
//#bit b_am_pm=gio_bin.5
//========================================

//========================================
const int8 d_thang[] = {0,0,3,3,6,1,4,6,2,5,0,3,5};
void tinh_thu() 
{
   int8 a;
   int8 b;
   b=nam+5;//31/12/1999: THU 6
   a=nam&0xFC;
   a=a>>2;
   b=a+b;
   if(nam%4==0) // nam nhuan
   {
      if(thang>=3)
      {
         b++;
      }
      b--;
   }
   b=d_thang[thang]+b;
   a=ngay+b;
   a=a%7;
   thu=a+2;
}
//========================================
u8 so_sanh_trong_khoang_phut(u16 phut_thap, u16 phut_cao)
{
	u8 kq=0;
	u16 phut_ss=gio;
	phut_ss*=60;
	phut_ss+=phut;
	if(phut_thap<phut_cao)
	{
		if(phut_ss>=phut_thap&&phut_ss<phut_cao)
		{
			kq=1;
		}
	}
	else
	{
		if(phut_ss>=phut_thap||phut_ss<phut_cao)
		{
			kq=1;
		}
	}
	return kq;
}
//========================================
u8 bit_coi=0;
u8 lan_bao_coi=0;
u16 ngat_bao_coi=0;
u8 bao_coi=0;
void bao_do()
{
	if(bit_coi!=1)
	{
		if(gio<22&&gio>5&&phut==0&&giay==0)
		{
			bit_coi=1;
			ngat_bao_coi=0;
			bao_coi=1;
			if(gio>12)
			{
				lan_bao_coi=(gio%12);
			}
			else
			lan_bao_coi=gio;
			lan_bao_coi=lan_bao_coi*2;
		}
	}
	if(giay==1)
	{
		bit_coi=0;
	}
}
#ifndef doi_zone_gps
#define doi_zone_gps
void doi_zone_utc_7c()
{
	u8 cog=0;
	gio0=gio0+7;
	if(gio0>=24)
	{
		gio0=gio0-24;
		ngay0++;
		if(ngay0>tinh_ngay_theo_thag(thang0,nam0))
		{
			ngay0=1;
			thang0++;
			if(thang0>12)
			{
				thang0=1;
				nam0++;
			}
		}
	}
}
#endif
//========================================
#define neu_du_giay if(bit_giay==1){bit_giay=0;
#endif