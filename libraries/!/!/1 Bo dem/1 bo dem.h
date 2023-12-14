#ifndef _bo_dem_h_
#define _bo_dem_h_

#ifndef khong_dung_led_7_doan
#define led_7_doan
#endif
#include <!/! LDN.h>
#include "1 Bo dem dinh nghia.h"
#include "1 Bo dem khai bao.h"
#include <!/1 Cam bien.h>
//-----------------------------------------------------


#define lenh_dat_che_do_cam_bien 6
u8 lenh=0;

#if so_so!=22
u8 mang7[so_so+2]; 
#else
u8 mang7[4+2]; 
#endif
u8 b_sp2=0;
#define co_sp2 b_sp2=1
#define kog_sp2 b_sp2=0
u8 b_sp=0;
#define co_sp b_sp=1
#define kog_sp b_sp=0
u8 ngat_t0_10 = 0;
u8 lan_ngat_t0 = 0;
#ifdef co_rl
//u16 tg_rl;
//u8 che_do_relay=0;
u8 lenh_tat_relay=0;
//u8 che_do_relay=0;
#endif
#ifdef rl_100ms
//u16 tg_rl;
//u8 lenh_tat_relay=0;

#endif
#ifndef tg_rl_dat
#define tg_rl_dat 2500
#endif
#ifdef led_7_doan
#include <!/1 7 doan.h>
#endif


#ifdef dem_thoi_gian_giam
u32 thoi_gian=99000; 
u8 chay_dung=0;
#endif


u8 tg_thoat_nut=0;
#ifndef tg_thoat_nut_dat
#define tg_thoat_nut_dat 80 // mach dinh la 8 giay
#endif

u8 dau_cham=2;



void khoi_tao_dem()
{
	#if so_so <= 2
	l1_d=l2_d=ra;
	#endif
	//#if so_so == 3
	//l1_d=l2_d=l3_d=ra;
	//#endif
	#if so_cb ==3
	cb1_d=cb2_d=cb3=vao;
	cb1_p=cb2_p=cb3_p=1;
	#endif
	//l1_d=l2_d=l3_d=l4_d=l5_d=l6_d=ra; 
	//cb1_d=cb2_d=cb3_d=vao;
	#ifndef khong_dung_led_7_doan
	#if so_so == 6
	l1_d=l2_d=l3_d=l4_d=l5_d=l6_d=ra;
	#endif
	#if so_so==5
	l1_d=l2_d=l3_d=l4_d=l5_d=ra;
	#endif
	#if so_so==4
	l1_d=l2_d=l3_d=ra;//l4_d=ra;
	#endif
	#if so_so==3
	l1_d=l2_d=l3_d=ra;
	#endif
	#if so_so==2
	l1_d=l2_d=ra;
	#endif
	#if so_so == 8
	l1_d=l2_d=l3_d=l4_d=l5_d=l6_d=l7_d=l8_d=ra;
	#endif
	#if so_so==7
	l1_d=l2_d=l3_d=l4_d=l5_d=l6_d=l7_d=ra;
	#endif
	#endif
	
	khoi_tao_7_doan();
	//timer1_1();
}
//======================================== 
void quet_led_t0()
{
	#ifndef khong_dung_led_7_doan
	lan_ngat_t0++;
	if(lan_ngat_t0>=10)
	{
		lan_ngat_t0=0;
		ngat_t0_10=1;
	}
	TCNT0=-30;
	lan_quet++;
	if (lan_quet>=so_so*2)
	{
		lan_quet=0;
	}
	//l1=l2=l3=l4=l5=0;
	if(lan_quet%2==1)
	{
		#if so_so<=2
		l1=l2=0;
		#endif
		#if so_so==3
		l1=l2=l3=0;
		#endif
		#if so_so==4
		l1=l2=l3=0;//l4=0;//l5=0;//=l5=l6=0;
		#endif
		
		TCNT0=-20;
		//lan_ngat=1;
	}
	else
	{
		xuat_7_(mang7[lan_quet/2]);
		switch (lan_quet/2)
		{
			#if so_so <= 2
			case 0:
			l1=1;break;
			case 1:
			l2=1; break;
			#endif
			
			#if so_so == 3
			case 0:
			l1=1;break;
			case 1: 
			l2=1; break;
			case 2:
			l3=1;break;
			#endif
//			case 3:
			
// 			l4=1;break;
// 			case 4:
// 			l5=1;break;//;du_13_ms=1;break;
		}
	} 
	#endif
}
u8 che_do=0;
//u32 so_nho[21];
//u16 so_nho[21];
#define tg_on_ss 50

#ifndef so_sanh_mang_doc
#include "LDN_luu_nho_du_lieu.h"
#endif
#ifdef so_sanh_mang_doc
#include "LDN_luu_nho_du_lieu - so sanh mang doc.h"
#endif
void dat_led()
{
	thoi_dan_led_dem++;
	if(thoi_dan_led_dat==0)b_led=0;
	if(thoi_dan_led_dat==1)b_led=1;
	if(thoi_dan_led_dat>1)
	if (thoi_dan_led_dem>thoi_dan_led_dat)
	{
		thoi_dan_led_dem=0;
		if (b_led==1)
		{
			b_led=0;
		}
		else
		{
			b_led=1;
		}
	}
}

#ifdef cet_noi_pc
#include <!/1 cet noi pc.h>
#endif
#ifdef led_7_doan
u8 them_cham(u8 ma_vao)
{
	ma_vao&=~ma7doan[8];
	return ma_vao;
}
#endif

//#ifndef tg_cb10
#ifndef doc_cb_rieg
u16 dem_cn11;
u16 dem_cn10;
u8 dem_ncb1;


//if(nho_cam_bien[0]==0&&nho_cam_bien[1]==0)
//{
	//mang7[4]&=~ma7doan[8];
//}
//else
//{
	//mang7[4]=mdv;
//}

void kiem_tra_led()
{
	#ifndef khong_dung_led_7_doan
	u8 i;
	so[so_dem_t]=0;
	for(i=0;i<10;i++)
	{
		#if so_so == 22
		chuyen_doi_so_7_32_2(so[so_dem_t],so_tinh[so_dat_t],0,0);
		#else
		chuyen_doi_so_7_32(so[so_dem_t],0,0);
		#endif
		delay_ms(500);
		so[so_dem_t]+=111111;
	}
	#if so_so == 22
	chuyen_doi_so_7_32_2(12,34,0,0);
	#else
	chuyen_doi_so_7_32(123456,0,0);
	#endif
	delay_ms(500);
	#endif
}

#define tg_cb10 200
#define tg_cb11 200
u16 cn11;
u16 cn12;
u8 ncb11;
u8 ncb12;
//u8 ncb1;
void doc_cb1()
{
	ncb11=cb1;
	if(ncb11==0&&cn11<tg_cb10)
	{
		cn11++;
		ncb11=1;
	}
	else
	{
		if(ncb11==1)
		{
			cn11=0;
		}
		else
		{
			cn12=1;
		}
	} // ncb11 = 0 neu du tg, van = 1 neu kog du tg
	ncb12=ncb11;
	if(ncb12==1&&cn12<tg_cb11&&cn12>0)
	{
		cn12++;
		ncb12=0;
	}
	else
	{
		if(ncb12==0)
		{
			cn12=0;
		}
	}
}

#define tg_cb20 200
#define tg_cb21 200
//u16 cn21;
//u16 cn22;
//u8 ncb21;
//u8 ncb22;
////u8 ncb2;
//void doc_cb2()
//{
	//ncb21=cb2;
	//if(ncb21==0&&cn21<tg_cb20)
	//{
		//cn21++;
		//ncb21=1;
	//}
	//else
	//{
		//if(ncb21==1)
		//{
			//cn21=0;
		//}
		//else
		//{
			//cn22=1;
		//}
	//} // ncb11 = 0 neu du tg, van = 1 neu kog du tg
	//ncb22=ncb21;
	//if(ncb22==1&&cn22<tg_cb21&&cn22>0)
	//{
		//cn22++;
		//ncb21=0;
	//}
	//else
	//{
		//if(ncb21==0)
		//{
			//cn22=0;
		//}
	//}
//}
#endif
//========================================
u8 tg_tre_test_dat=100;
void kiem_tra_phan_cung()
{
	//#if so_so>4
	#ifndef khong_dung_led_7_doan
	u32 so;
	//#else
	//u16 so;
	//#endif
	u8 j=0;
	so=0;
	while (j<so_so*9)
	{
		if(j<9)
		{
			so+=1;
		}
		else
		if(j<2*9)
		{
			so+=10;
		}
		#if so_so != 22
		else
		if(j<3*9)
		{
			so+=100;
		}
		#ifdef so_so>3
		else
		if(j<4*9)
		{
			so+=1000;
		}
		#endif
		#ifdef so_so>4
		else
		if(j<5*9)
		{
			so+=10000;
		}
		#endif
		#ifdef so_so>5
		else
		if(j<6*9)
		{
			so+=100000;
		}
		#endif
		#ifdef so_so>6
		else
		if(j<7*9)
		{
			so+=1000000;
		}
		#endif
		#ifdef so_so>7
		else
		if(j<8*9)
		{
			so+=10000000;
		}
		#endif
		#endif
		#if so_so == 22
		chuyen_doi_so_7_32_2(so,so,0,0);
		#else
		chuyen_doi_so_7_32(so,0,0);
		#endif
		j++;
		delay_ms(tg_tre_test_dat);
	}
	#endif
}
//----------------------------------------
void ciem_tra_pan_cug_qet_led()
{
	#ifndef khong_dung_led_7_doan
	u32 so;
	u8 j=0;
	so=0;
	while (j<so_so*9)
	{
		if(j<9)
		{
			so+=1;
		}
		else
		if(j<2*9)
		{
			so+=10;
		}
		else
		if(j<3*9)
		{
			so+=100;
		}
		else
		if(j<4*9)
		{
			so+=1000;
		}
		else
		if(j<5*9)
		{
			so+=10000;
		}
		#ifdef so_so>5
		else
		if(j<6*9)
		{
			so+=100000;
		}
		#endif
		#ifdef so_so>6
		else
		if(j<7*9)
		{
			so+=1000000;
		}
		#endif
		#ifdef so_so>7
		else
		if(j<8*9)
		{
			so+=10000000;
		}
		#endif
		#ifndef dem_4
		quet_led(so,0);
		#endif
		#ifdef dem_4
		quet_led(so,j);
		#endif
		j++;
		delay_ms(500);
	}
	#endif
}
//========================================
void soa_mag_7()
{
	u8 i;
	for (i=0;i<so_so;i++)
	{
		mang7[i]=0xff;
	}
}
//========================================
#ifndef khong_dung_led_7_doan
//void chuyen_doi_so_7_16_don(u16 so) // khi chon la boi cua 10 se chuyen che do hien thi
//{
	//u8 mang7_tam[so_so]; // mang tam chua ma 7 doan day du [....tr.ch.dv]
	//u8 dich_so=so_so;
	//u8 chon_chop=chon; // chon so chop, neu = 1 là hàng đơn vi
	//u8 so_day=0; // neu so hien thi trong pham vi
	//u8 i;
	//u32 so_chia=1;
	//
	//if(chon<10&&chon>so_so) // hien thi tren du so nhưng day so qua phai
	//{
		//chon_chop=so_so; // chon LED cuoi khi ra khoi pham vi lua chon
		//so_day=chon-so_so;
	//}
	//
	//i=0;
	//while (i<dich_so)
	//{
		//if (so_day==0)
		//{
			//mang7_tam[dich_so-1-i]=ma7doan[so/so_chia%10];
			//i++;
		//}
		//else
		//{
			//so_day--;
		//}
		//so_chia*=10;
	//}
	//
	//for (i=0;i<dich_so;i++) // di tu 0 den so bị day
	//{
//
		//if (chon>=10)  // khi mo >10
		//{
			//chon-=(10+so_so);
			//if (chon_chop==dich_so-i)
			//{
				//if(!(bct))
				//{
					//mang7[i]=mang7_tam[i];
				//}
				//else
				//{
					//mang7[i]=0xff;
				//}
			//}
			//else
			//{
				//mang7[i]=0xff;
			//}
		//}
		//else // khi mo duoi 10
		//{
			//if(!(bct&&(chon_chop==dich_so-i)))
			//{
				//mang7[i]=mang7_tam[i];
			//}
			//else
			//{
				//mang7[i]=0xff;
			//}
		//}
	//}
	//if (vi_tri_cham>0)
	//{
		//mang7[so_so-vi_tri_cham]&=~ma7doan[8];
	//}
	//
	//mdv=mang7[so_so-1]; // luu ma don vi de phup vu hien thi dau cham
//}
#endif
//========================================
#if so_so!=22
#ifndef khong_dung_led_7_doan
void chuyen_doi_so_7_32(u32 so,u8 chon,u8 vi_tri_cham) // khi chon la boi cua 10 se chuyen che do hien thi
{
	u8 mang7_tam[so_so]; // mang tam chua ma 7 doan day du [....tr.ch.dv]
	u8 dich_so=so_so;
	u8 chon_chop=chon; // chon so chop, neu = 1 là hàng đơn vi
	u8 so_day=0; // neu so hien thi trong pham vi
	u8 i;
	u32 so_chia=1;
	#ifdef khong_hien_thi_0
	if(chon==0)
	{
		so_chia=pow(10,(so_so-1));
		i=0;
		u8 lon_hon_0=0;
		while (i<dich_so)
		{
			if (so_day==0)
			{
				u8 so_le=so/so_chia%10;
				if(so_le==0&&lon_hon_0==0&&so_chia!=1)
				{
					mang7[i]=0xff;
				}
				else
				{
					lon_hon_0=1;
					mang7[i]=ma7doan[so_le]; // lấy hàng cao nhất trước
				}
				i++;
			}
			else
			{
				so_day--;
			}
			so_chia/=10;
		}
	}
	else
	#endif
	{
		if(chon<10&&chon>so_so) // hien thi tren du so nhưng day so qua phai
		{
			chon_chop=so_so; // chon LED cuoi khi ra khoi pham vi lua chon
			so_day=chon-so_so;
		}
		
		i=0;
		while (i<dich_so)
		{
			if (so_day==0)
			{
				mang7_tam[dich_so-1-i]=ma7doan[so/so_chia%10];
				i++;
			}
			else
			{
				so_day--;
			}
			so_chia*=10;
		}
		
		for (i=0;i<dich_so;i++) // di tu 0 den so bị day
		{

			if (chon>=10)  // khi mo >10
			{
				chon-=(10+so_so);
				if (chon_chop==dich_so-i)
				{
					if(!(bct))
					{
						mang7[i]=mang7_tam[i];
					}
					else
					{
						mang7[i]=0xff;
					}
				}
				else
				{
					mang7[i]=0xff;
				}
			}
			else // khi mo duoi 10
			{
				if(!(bct&&(chon_chop==dich_so-i)))
				{
					mang7[i]=mang7_tam[i];
				}
				else
				{
					mang7[i]=0xff;
				}
			}
		}
		if (vi_tri_cham>0)
		{
			mang7[so_so-vi_tri_cham]&=~ma7doan[8];
		}
	}
	mdv=mang7[so_so-1]; // luu ma don vi de phup vu hien thi dau cham
}
#endif
//========================================
void chuyen_doi_so_truyen(u32 so,u8 chon,u8 vi_tri_cham) // khi chon la boi cua 10 se chuyen che do hien thi
{
	chuyen_doi_so_chuoi(so,chon,chuoi_so_truyen);
	u8 chuoi_so_truyen_tam[10]; // mang tam chua ma 7 doan day du [....tr.ch.dv]
	u8 dich_so=so_so;
	u8 chon_chop=chon; // chon so chop, neu = 1 là hàng đơn vi
	u8 so_day=0; // neu so hien thi trong pham vi
	u8 i;
	u32 so_chia=1; 
	
	if(chon<10&&chon>so_so) // hien thi tren du so nhưng day so qua phai
	{
		chon_chop=so_so; // chon LED cuoi khi ra khoi pham vi lua chon
		so_day=chon-so_so;
	}
	
	i=0;
	while (i<dich_so)
	{
		if (so_day==0)
		{
			chuoi_so_truyen_tam[dich_so-1-i]=so/so_chia%10+0x30;
			i++;
		}
		else
		{
			so_day--;
		}
		so_chia*=10;
	}
	
	for (i=0;i<dich_so;i++) // di tu 0 den so bị day
	{

		if (chon>=10)  // khi mo >10
		{
			chon-=(10+so_so);
			if (chon_chop==dich_so-i)
			{
				if(!(bct))
				{
					chuoi_so_truyen[i]=chuoi_so_truyen_tam[i];
				}
				else
				{
					chuoi_so_truyen[i]='9'+1;
				}
			}
			else
			{
				chuoi_so_truyen[i]='9'+1;
			}
		}
		else // khi mo duoi 10
		{
			if(!(bct&&(chon_chop==dich_so-i)))
			{
				chuoi_so_truyen[i]=chuoi_so_truyen_tam[i];
			}
			else
			{
				chuoi_so_truyen[i]='9'+1;
			}
		}
	}
	chuoi_so_truyen[so_so]=0;
}
#else
#ifndef khong_dung_led_7_doan
void chuyen_doi_so_7_32_2(u32 so,u32 so2,u8 chon,u8 vi_tri_cham) // khi chon la boi cua 10 se chuyen che do hien thi
{
	u8 ssss=2;
	u8 mang7_tam[2]; // mang tam chua ma 7 doan day du [....tr.ch.dv]
	u8 dich_so=2;
	u8 chon_chop=chon; // chon so chop, neu = 1 là hàng đơn vi
	u8 so_day=0; // neu so hien thi trong pham vi
	u8 i;
	u32 so_chia=1;
	
	if(chon<10&&chon>ssss) // hien thi tren du so nhưng day so qua phai
	{
		chon_chop=ssss; // chon LED cuoi khi ra khoi pham vi lua chon
		so_day=chon-ssss;
	}
	
	i=0;
	while (i<dich_so)
	{
		if (so_day==0)
		{
			mang7_tam[dich_so-1-i]=ma7doan[so2/so_chia%10];
			i++;
		}
		else
		{
			so_day--;
		}
		so_chia*=10;
	}
	
	for (i=0;i<dich_so;i++) // di tu 0 den so bị day
	{

		if (chon>=10)  // khi mo >10
		{
			chon-=(10+ssss);
			if (chon_chop==dich_so-i)
			{
				if(!(bct))
				{
					mang7[i]=mang7_tam[i];
				}
				else
				{
					mang7[i]=0xff;
				}
			}
			else
			{
				mang7[i]=0xff;
			}
		}
		else // khi mo duoi 10
		{
			if(!(bct&&(chon_chop==dich_so-i)))
			{
				mang7[i]=mang7_tam[i];
			}
			else
			{
				mang7[i]=0xff;
			}
		}
	}
	if (vi_tri_cham>0)
	{
		mang7[ssss-vi_tri_cham]&=~ma7doan[8];
	}
	
	//mdv=mang7[ssss-1]; // luu ma don vi de phup vu hien thi dau cham
	mang7[3]=ma7doan[so%10];
	mang7[2]=ma7doan[so/10%10];
	//mang7[1]=ma7doan[so2%10];
	//mang7[0]=ma7doan[so2/10%10];
	mdv=mang7[3];
	mang7[1]&=~ma7doan[8];
}
#endif
#endif
//========================================
void chuyen_doi_so_chuoi(u32 so,u8 chon,u8 *chuoi_ra) // khi chon la boi cua 10 se chuyen che do hien thi
{
	u8 chuoi_so_tam[10]; // mang tam chua ma 7 doan day du [....tr.ch.dv]
	u8 dich_so=so_so;
	u8 chon_chop=chon; // chon so chop, neu = 1 là hàng đơn vi
	u8 so_day=0; // neu so hien thi trong pham vi
	u8 i;
	u32 so_chia=1;
	
	if(chon<10&&chon>so_so) // hien thi tren du so nhưng day so qua phai
	{
		chon_chop=so_so; // chon LED cuoi khi ra khoi pham vi lua chon
		so_day=chon-so_so;
	}
	
	i=0;
	while (i<dich_so)
	{
		if (so_day==0)
		{
			chuoi_so_tam[dich_so-1-i]=so/so_chia%10+0x30;
			i++;
		}
		else
		{
			so_day--;
		}
		so_chia*=10;
	}
	
	for (i=0;i<dich_so;i++) // di tu 0 den so bị day
	{

		if (chon>=10)  // khi mo >10
		{
			chon-=(10+so_so);
			if (chon_chop==dich_so-i)
			{
				if(!(bct))
				{
					chuoi_ra[i]=chuoi_so_tam[i];
				}
				else
				{
					chuoi_ra[i]='9'+1;
				}
			}
			else
			{
				chuoi_ra[i]='9'+1;
			}
		}
		else // khi mo duoi 10
		{
			if(!(bct&&(chon_chop==dich_so-i)))
			{
				chuoi_ra[i]=chuoi_so_tam[i];
			}
			else
			{
				chuoi_ra[i]='9'+1;
			}
		}
	}
	chuoi_ra[so_so]=0;
}
//========================================
#ifdef uart
#ifdef ket_noi_may_tinh
void che_do_dat_id()
{
	u8 ok=0;
	u8 i;
	tg_luu=10000;
	lenh_luu=0;
	while(ok==0)
	{
		if(nhan_v10()==1)
		{
			truyen_v10();
			if(leh==1)
			{
				for(i=0;i<10;i++)
				{
					id[i]=dl_nhan[i];
				}
				luu_e_id();
			}
			ok=1;
		}
		if (lenh_luu==1)
		{
			lenh_luu=0;
			ok=1;
		}
	}
}
#endif
#endif
//========================================
//void chuyen_doi_so_7_32(u32 so)
//{
	//u8 mang7_tam[5];
	//u8 dich_so=3;
	//if (mo==4)
	//{
		//dich_so=4;
	//}
	//u8 i;
	//u16 so_chia=1;
	//for (i=0;i<dich_so;i++)
	//{
		//mang7_tam[dich_so-1-i]=ma7doan[so/so_chia%10];
		//so_chia*=10;
	//}
	//
	//for (i=0;i<dich_so;i++)
	//{
		//if(!(bct&&(mo==dich_so-i)))
		//{
			//mang7[i]=mang7_tam[i];
		//}
		//else
		//{
			//mang7[i]=0xff;
		//}
	//}
//}
//========================================
u8 dem_1000ms;
void bo_dem_1000ms()
{
	#ifdef dung_encoder
	if(tg_tra_ve_dem_binh_thuong>0)
	{
		tg_tra_ve_dem_binh_thuong--;
		if (tg_tra_ve_dem_binh_thuong==0)
		{
			chon_che_do_dem=0;
		}
	}
	#endif
}
//========================================
u8 dem_100ms; 
void bo_dem_100ms()
{
	if(tg_thoat_nut>0)
	{
		tg_thoat_nut--;
	}
	if(tg_truyen_lai_>0)
	{
		tg_truyen_lai_--;
	}
	#ifdef co_rl
	if (tg_relay_bat>0)
	{
		tg_relay_bat--;
		if(tg_relay_bat==0)
		{
			rl=0;
		}
	}
	#endif
}
//========================================
u8 dem_10ms;
void bo_dem_10ms()
{
	ct++;
	if (ct>50)
	{ 
		ct=0;
		bct=!bct;
	}

	//----------------------------------------
	if (tg_luu_so_dat_>1)
	{
		tg_luu_so_dat_--;
	}
	//----------------------------------------
	if (tg_luu_thong_so_cai_dat>1)
	{
		tg_luu_thong_so_cai_dat--;
	}
}
//======================================== 
void ldn_1ms()
{
	doc_cam_bien();
	du_1_ms=1;
	#ifdef encoder
	if (encoder_cho_phep)
	{
		encoder_xu_ly();
	}
	#endif
	#ifdef co_rl
	if (tg_rl>0)
	{
		tg_rl--;
		if (tg_rl==0)
		{
			lenh_tat_relay=1;
		}
	}
	#endif
	//---------------------------------------- 
	
	
	//======================================== 
	tg_truyen++;
	if(tg_truyen>50)
	{
		tg_truyen=0;
		cho_truyen=1;
	}
	//---------------------------------------- 
	dem_10ms++;
	{
		if (dem_10ms>9)
		{
			dem_10ms=0;
			bo_dem_10ms();
			dem_100ms++;
			if (dem_100ms>9)
			{
				dem_100ms=0;
				bo_dem_100ms();
				dem_1000ms++;
				if (dem_1000ms>9)
				{
					dem_1000ms=0;
					bo_dem_1000ms();
				}
			}
		}
	}

	ngat_1ms();
}
#ifndef ngat_timer_1_rieng // #define ngat_timer_1_rieng
ISR(TIMER1_COMPA_vect) // quet led dung ngat timet1 (1ms)
{
// 	if (tg_luu_thong_so>0)
// 	{
// 		tg_luu_thong_so--;
// 		if (tg_luu_cai_dat==0)
// 		{
// 			lenh_luu_thong_so=1;
// 		}
// 	}
}
#endif
u8 so_sanh_nhap_hai_chuoi(u8 * chuoi_ra, const u8 * chuoi_vao)
{
	u8 i,kqss;
	kqss=0;
	for(i=0;i<10;i++)
	{
		if(chuoi_ra[i]!=chuoi_vao[i])
		{
			chuoi_ra[i]=chuoi_vao[i];
			kqss=1;
		}
	}
	return kqss;
}
//======================================== 
void cai_dat(u8 cam_bien_so) // Nut nhan duoc su dung
{
	tg_thoat_nut=tg_thoat_nut_dat;
	mo=0;
	while (tg_thoat_nut>0)
	{
		doc_nut_nhan_cai(cam_bien_so);
		#ifndef khong_dung_led_7_doan
		if(mo<6)
		{
			#if so_so == 22
			chuyen_doi_so_7_32_2(thong_so_16[thoi_gian_ton_tai_dat_t],so_tinh[so_dat_t],mo,0);
			#else
			chuyen_doi_so_7_32(thong_so_16[thoi_gian_ton_tai_dat_t],mo,0); // cảm biến 
			#endif
		}
		else
		if(mo<11)
		{
			#if so_so == 22
			chuyen_doi_so_7_32_2(thong_so_16[thoi_gian_cho_dat_t],so_tinh[so_dat_t],mo-5,0);
			#else
			chuyen_doi_so_7_32(thong_so_16[thoi_gian_cho_dat_t],mo-5,0); // cảm biến 
			#endif
		}
		else
		if(mo<12)
		{
			#if so_so == 22
			chuyen_doi_so_7_32_2(tich_cuc_cb_dat,so_tinh[so_dat_t],mo-10,0);
			#else
			chuyen_doi_so_7_32(tich_cuc_cb_dat,mo-10,0); // cảm biến 
			#endif
		}
		else
		{
			#if so_so == 22
			chuyen_doi_so_7_32_2(tac_dung_nut_reset_giu,so_tinh[so_dat_t],mo-11,0);
			#else
			chuyen_doi_so_7_32(tac_dung_nut_reset_giu,mo-11,0); 
			#endif
		}
		#else
		if(mo<6)
		{
			chuyen_doi_so_truyen(thong_so_16[thoi_gian_ton_tai_dat_t],mo,0);
		}
		else
		if(mo<11)
		{
			chuyen_doi_so_truyen(thong_so_16[thoi_gian_cho_dat_t],mo-5,0);
		}
		else
		if(mo<12)
		{
			chuyen_doi_so_truyen(tich_cuc_cb_dat,mo-10,0);
		}
		else
		if(mo<13)
		{
			chuyen_doi_so_truyen(tac_dung_nut_reset_giu,mo-10,0);
		}
		else
		{
			#ifndef khong_dem_bao_chong
			chuyen_doi_so_truyen(dem_bao_lien_ke,mo-12,0);
			#endif
		}
		
		if(so_sanh_nhap_hai_chuoi(chuoi_so_nho,chuoi_so_truyen)==1)
		{
			delay_ms(50);
			uart_puts_b(chuoi_so_truyen);		
			#ifdef phien_ban_2
			uart_putc(',');
			#endif
			uart_putc(dau_cham);
		}
		#endif
	}
	mo=0;
}
//========================================
void cai_dat_1ic(u8 cam_bien_so,u8*chuoi_ra) // Nut nhan duoc su dung
{
	tg_thoat_nut=tg_thoat_nut_dat;
	mo=0;
	while (tg_thoat_nut>0)
	{
		doc_nut_nhan_cai(cam_bien_so);
		#ifndef khong_dung_led_7_doan
		if(mo<6)
		{
			#if so_so == 22
			chuyen_doi_so_7_32_2(thong_so_16[thoi_gian_ton_tai_dat_t],so_tinh[so_dat_t],mo,0);
			#else
			chuyen_doi_so_7_32(thong_so_16[thoi_gian_ton_tai_dat_t],mo,0); // cảm biến
			#endif
		}
		else
		if(mo<11)
		{
			#if so_so == 22
			chuyen_doi_so_7_32_2(thong_so_16[thoi_gian_cho_dat_t],so_tinh[so_dat_t],mo-5,0);
			#else
			chuyen_doi_so_7_32(thong_so_16[thoi_gian_cho_dat_t],mo-5,0); // cảm biến
			#endif
		}
		else
		if(mo<12)
		{
			#if so_so == 22
			chuyen_doi_so_7_32_2(tich_cuc_cb_dat,so_tinh[so_dat_t],mo-10,0);
			#else
			chuyen_doi_so_7_32(tich_cuc_cb_dat,mo-10,0); // cảm biến
			#endif
		}
		else
		{
			#if so_so == 22
			chuyen_doi_so_7_32_2(tac_dung_nut_reset_giu,so_tinh[so_dat_t],mo-11,0);
			#else
			chuyen_doi_so_7_32(tac_dung_nut_reset_giu,mo-11,0);
			#endif
		}
		#else
		if(mo<6)
		{
			chuyen_doi_so_truyen(thong_so_16[thoi_gian_ton_tai_dat_t],mo,0);
		}
		else
		if(mo<11)
		{
			chuyen_doi_so_truyen(thong_so_16[thoi_gian_cho_dat_t],mo-5,0);
		}
		else
		if(mo<12)
		{
			chuyen_doi_so_truyen(tich_cuc_cb_dat,mo-10,0);
		}
		else
		if(mo<13)
		{
			chuyen_doi_so_truyen(tac_dung_nut_reset_giu,mo-10,0);
		}
		else
		{
			#ifndef khong_dem_bao_chong
			chuyen_doi_so_truyen(dem_bao_lien_ke,mo-12,0);
			#endif
		}
		
		if(so_sanh_nhap_hai_chuoi(chuoi_so_nho,chuoi_so_truyen)==1)
		{
			u8 i;
			for(i=0;i<so_so;i++)
			{
				chuoi_ra[i]=chuoi_so_truyen[i];
			}
		}
		#endif
	}
	mo=0;
}
//======================================== 

#ifdef dat_dem_thong_so
//======================================== 
void doc_nut_nhan_cai(u8 cam_bien_so)
{
	if(nnn1==0) 
	{
		if(TTCB[cam_bien_so]==TC[cam_bien_so])
		{
			nnn1=1;
			tg_giu=0;
		}
	}
	else
	{
		if(TTCB[cam_bien_so]==TC[cam_bien_so]&&tg_giu>700&&nnn==0)
		{
			tg_thoat_nut=tg_thoat_nut_dat;
			if(mo==0)
			{
				mo=1;
				//tg_coi=tg_coi_dat*2;
				nnn=1;
				nrs=1;
				//quet_led(so_dat);
			}
			else
			{
				mo++;
				nnn=1;
				//tg_coi=tg_coi_dat*2;
				nrs=1;
				if(mo>13)
				{
					mo=0;
					//tg_luu_cai_dat=tg_luu_dat;
					//luu_thong_so_cai();
				}
				
			}
		}
		else
		if(TTCB[cam_bien_so]!=TC[cam_bien_so]&&nrs==0&&(tg_giu>=1&&tg_giu<600))
		{
			tg_thoat_nut=tg_thoat_nut_dat;
			if(mo==0)
			{
				//so_dem=0;  
				//tg_coi=tg_coi_dat;
				////so_dem_n=0;
				//quet_led(so_dem);
				//tg_luu=tg_luu_dat;
				//luu=0;
				//che_do=0;
				//nnn1=0;
			}
			if (mo>0)
			{
				u8 tro=250;
				if(mo<6)
				{
					tro=thoi_gian_ton_tai_dat_t;
				}
				else
				if(mo<11)
				{
					tro=thoi_gian_cho_dat_t;
				}
				else
				if(mo<12)
				{
					tich_cuc_cb_dat=chinh_tang_so_16(tich_cuc_cb_dat,mo-10); 
					if (tich_cuc_cb_dat>1)
					{
						tich_cuc_cb_dat=0;
					}
					//
				}
				else
				if(mo<13)
				{
					tac_dung_nut_reset_giu=chinh_tang_so_16(tac_dung_nut_reset_giu,mo-11);
					if (tac_dung_nut_reset_giu>2)
					{
						tac_dung_nut_reset_giu=0;
					}
				}
				else
				if(mo<14)
				{
					#ifndef khong_dem_bao_chong
					dem_bao_lien_ke=chinh_tang_so_16(dem_bao_lien_ke,mo-12);
					if (dem_bao_lien_ke>1)
					{
						dem_bao_lien_ke=0;
					}
					#endif
				}
				if (tro!=250)
				{
					u32 so=chinh_tang_so_32(thong_so_16[tro],mo-tro*5);
					if (so>65000)
					{
						so-=70000;
					}
					thong_so_16[tro]=(u16)so;
				}
				#ifndef khong_coi
				tg_coi=tg_coi_dat;
				#endif
 				//tg_luu_thong_so=tg_luu_dat;
				tg_luu_thong_so_cai_dat=tg_luu_dat;
 				che_do=0;
 				nnn1=0;
 				ct=0;
 				bct=0;
			}
			
		}
		else
		if(TTCB[cam_bien_so]!=TC[cam_bien_so])
		{
			nnn1=0;
			nnn=0;
			nrs=0;
		}
	}
}
#endif
//======================================== 
#ifdef uart
#ifdef ket_noi_may_tinh
u8 so_sah_id()
{
	u8 i;
	u8 kq=1;
	for (i=0;i<10;i++)
	{
		if(id[i]!=dl_nhan[i])kq=0;
	}
	return kq;
}
#endif
#endif
#ifndef so_sanh_mang_doc
#include <!/1 Bo dem/1 Luu nho.h>
#else
#include <!/1 Bo dem/1 Luu nho - so sanh mang doc.h>
#endif
#endif

