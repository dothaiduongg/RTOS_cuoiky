#ifndef _bo_dem_h_
#define _bo_dem_h_
u8 nn;
u16 thoi_gian_ton_tai_dat; // thoi gian ton tai dat cho cam bien. duoc tinh bang ms. va phai chia 2 (yeu cau ham doc cam bien phai co trong ngat timer1 1ms)
u16 thoi_gian_cho_dat; 
u16 tg_truen_lai=0; // thoi gian truyen lại dược áp dụng cho việc truyền thông số hoặc số đếm qua uart
#define led_7_doan

#include <!/! LDN.h>
#include "1 Bo dem kai bao.h"
#include <!/1 Cam bien.h>
//-----------------------------------------------------
#define tg_luu_dat 50
u16 tg_luu_cai_dat;
//u16 tg_luu_thong_so;
u8 lenh_luu_cai_dat=0;
//u8 lenh_luu_thong_so=0;
u16 tg_coi;

u8 che_do_cam_bien=0;

u8 mo;
u16 tg_giu;

#define lenh_dat_che_do_cam_bien 6
u8 lenh=0;

#ifndef so_so
#define so_so 6
# warning "Can dinh nghia so so hien thi cho bo dem dang su dung. mac dinh la 6 so"
#endif
u8 mang7[so_so+2]; 
u8 b_sp2=0;
#define co_sp2 b_sp2=1
#define kog_sp2 b_sp2=0
u8 b_sp=0;
#define co_sp b_sp=1
#define kog_sp b_sp=0#ifndef cb1
	#define cb1 dk_bit(PINC,0)
	#define cb1_d dk_bit(DDRC,0)
	#define cb1_p dk_bit(PORTC,0)
	#define cb2 dk_bit(PINC,1)
	#define cb2_d dk_bit(DDRC,1)
	#define cb2_p dk_bit(PORTC,1)
	#define cb3 dk_bit(PINC,2)
	#define cb3_d dk_bit(DDRC,2)
	#define cb3_p dk_bit(PORTC,2)
	# warning "Can dinh nghia cam bien theo mau ben tren cho phu hop phan cung"
#endif
#ifndef l1
	#ifndef ok_led
	#ifndef bo_v12 
	#define bo_v12
	#define l1 dk_bit(PORTD,2)
	#define l1_d dk_bit(DDRD,2)
	#define l2 dk_bit(PORTD,3)
	#define l2_d dk_bit(DDRD,3)
	#define l3 dk_bit(PORTD,4)
	#define l3_d dk_bit(DDRD,4)
	#define l4 dk_bit(PORTB,6)
	#define l4_d dk_bit(DDRB,6)
	#define l5 dk_bit(PORTB,7)
	#define l5_d dk_bit(DDRB,7)
	#define l6 dk_bit(PORTD,5)
	#define l6_d dk_bit(DDRD,5)
	
	
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
	
	#define nn1 dk_bit(PIND,0)
	#define nn1_d dk_bit(DDRD,0)
	#define nn1_p dk_bit(PORTD,0)
	#define nn2 dk_bit(PINC,5)
	#define nn2_d dk_bit(DDRC,5)
	#define nn3 dk_bit(PINC,4)
	#define nn3_d dk_bit(DDRC,4)
	#define nn4 dk_bit(PINC,3)
	#define nn4_d dk_bit(DDRC,3)
	
	#define dem_out dk_bit(PORTD,1)
	#define dem_out_d dk_bit(DDRD,1)
	#endif
	#endif
	
	# warning "Can dinh nghia cac chan LED theo mau tren cho phu hop phan cung"
#endif
u8 ngat_t0_10 = 0;
u8 lan_ngat_t0 = 0;
u16 tg_rl;
u8 lenh_tat_relay=0;
#ifndef tg_rl_dat
#define tg_rl_dat 2500
#endif
#ifdef led_7_doan
#include <!/1 7 doan.h>
#endif

u16 tg_thoat_nut=0;
#ifndef tg_thoat_nut_dat
#define tg_thoat_nut_dat 8000 // mach dinh la 8 giay
#endif
u16 ct;
bool bct;



void doc_nut_nhan_cai(u8 cam_bien_so);
void doc_so_dem(void);
void luu_so_dem(void);
void luu_so_dat(void);

u8 id[10]; // id cua 1 bo dem la 10 ky tu
void khoi_tao_dem()
{
	#if so_so <= 2
	l1_d=l2_d=ra;
	#endif
	#if so_so == 3
	l1_d=l2_d=l3_d=ra;
	#endif
	#if so_cb ==3
	cb1_d=cb2_d=cb3=vao;
	cb1_p=cb2_p=cb3_p=1;
	#endif
	//l1_d=l2_d=l3_d=l4_d=l5_d=l6_d=ra; 
	//cb1_d=cb2_d=cb3_d=vao;
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
	
	khoi_tao_7_doan();
	timer1_1();
}
void quet_led_t0()
{
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
}
u8 che_do=0;
u32 so_nho[21];
//u16 so_nho[21];
#define tg_on_ss 50
void quet_led_htk(u16 so);

#define dc_e_id 10

int8 doc_e_id()
{
	delay_ms(1000);
	u8 i;
	for(i=0;i<10;i++)
	{
		id[i]=eeprom_read_byte((u8*)(dc_e_id+i));
	}
}
// ======================================== 
void luu_e_id()
{
	u8 i;
	for(i=0;i<10;i++)
	{
		eeprom_write_byte((u8*)(dc_e_id+i),id[i]); 
	}
} 
u8 tu_re=0;
u16 nhanh_cham=0; 
#ifndef nhieu_so
#if so_so>4
#ifndef _so_dem_
u32 so_dem; 
u32 so_tog;
u32 so_tong;
u32 so_dat;
u32 so_dat1;
u32 so_dat2;
#endif
#else
u16 so_dem;
u16 so_tog;
u16 so_tong;
u16 so_dat;
u16 so_dat1;
u16 so_dat2;
#endif
#endif
#ifdef nhieu_so
u8 so_chon=0;
u8 so_chon1=0;
#if so_so>4
u32 so_dem[nhieu_so];
u32 so_tong;
#else
u16 so_dem[nhieu_so];
u16 so_tong;
#endif
#endif

u32 td_ton_tai_dat;
u8 mdv; // nho ma don vi cho LED 7 doan
#include <!/1 Bo dem/1 Doc Encoder.h>
u8 encoder_cho_phep;
void luu_eeprom2();

u16 thoi_dan_led_dem=0;
u16 thoi_dan_led_dat=0;
u8 b_led=0;
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
	u8 i;
	so_dem=0;
	for(i=0;i<10;i++)
	{
		quet_led(so_dem,0);
		delay_ms(500);
		so_dem+=111111;
	}
	quet_led(123456,0);
	delay_ms(500);
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
u16 cn21;
u16 cn22;
u8 ncb21;
u8 ncb22;
//u8 ncb2;
void doc_cb2()
{
	ncb21=cb2;
	if(ncb21==0&&cn21<tg_cb20)
	{
		cn21++;
		ncb21=1;
	}
	else
	{
		if(ncb21==1)
		{
			cn21=0;
		}
		else
		{
			cn22=1;
		}
	} // ncb11 = 0 neu du tg, van = 1 neu kog du tg
	ncb22=ncb21;
	if(ncb22==1&&cn22<tg_cb21&&cn22>0)
	{
		cn22++;
		ncb21=0;
	}
	else
	{
		if(ncb21==0)
		{
			cn22=0;
		}
	}
}
#endif
//========================================
u8 tg_tre_test_dat=100;
void kiem_tra_phan_cung()
{
	//#if so_so>4
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
		chuyen_doi_so_7_32_2(so,so_tinh[so_dat_t],0,0);
		#else
		chuyen_doi_so_7_32(so,0,0);
		#endif
		j++;
		delay_ms(tg_tre_test_dat);
	}
}
//----------------------------------------
void ciem_tra_pan_cug_qet_led()
{
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
void chuyen_doi_so_7_32(u32 so,u8 chon) // khi chon la boi cua 10 se chuyen che do hien thi
{
	u8 mang7_tam[so_so]; // mang tam chua ma 7 doan day du [....tr.ch.dv]
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
	mdv=mang7[so_so-1]; // luu ma don vi de phup vu hien thi dau cham
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

void ldn_1ms()
{
	doc_cam_bien();
	if (tg_truen_lai>0)
	{
		tg_truen_lai--;
	}
	
	#ifdef encoder
	if (encoder_cho_phep)
	{
		encoder_xu_ly();
	}
	#endif
}
#ifndef ngat_timer_1_rieng // #define ngat_timer_1_rieng
ISR(TIMER1_COMPA_vect) // quet led dung ngat timet1 (1ms)
{
	
	if(tg_thoat_nut>0)
	{
		tg_thoat_nut--;
	}
	
	ct++;
	if (ct>500)
	{
		ct=0;
		bct=!bct;
	}
	
	if (tg_luu_cai_dat>0)
	{
		tg_luu_cai_dat--;
		if (tg_luu_cai_dat==0)
		{
			lenh_luu_cai_dat=1;
		}
	}
	
// 	if (tg_luu_thong_so>0)
// 	{
// 		tg_luu_thong_so--;
// 		if (tg_luu_cai_dat==0)
// 		{
// 			lenh_luu_thong_so=1;
// 		}
// 	}
	
	if (tg_rl>0)
	{
		tg_rl--;
		if (tg_rl==0)
		{
			lenh_tat_relay=1;
		}
	}
}
#endif

void cai_dat(u8 cam_bien_so) // Nut nhan duoc su dung
{
	tg_thoat_nut=tg_thoat_nut_dat;
	while (tg_thoat_nut>0)
	{
		//doc_cam_bien();
		doc_nut_nhan_cai(cam_bien_so);
		if(mo<6)
		{
			chuyen_doi_so_7_32(thoi_gian_ton_tai_dat,mo);
		}
		else
		{
			chuyen_doi_so_7_32(thoi_gian_cho_dat,mo-5);
		}
	}
	mo=0;
	luu_thong_so_cai();
}


#ifdef dat_dem_thong_so
u8 nrs=0;
u8 nnn1; // nho co nhan phim lan dau
u8 nnn;
void luu_thong_so_cai()
{
	eeprom_write_word((u16*)(dc_tg_ton_tai+DCT),thoi_gian_ton_tai_dat);
	eeprom_write_word((u16*)(dc_tg_cho+DCT),thoi_gian_cho_dat);
}
void doc_thong_so_cai()
{
	thoi_gian_ton_tai_dat=eeprom_read_word((u16*)(dc_tg_ton_tai+DCT));
	if (thoi_gian_ton_tai_dat>65000||thoi_gian_ton_tai_dat==0)
	{
		thoi_gian_ton_tai_dat=10;
	}
	thoi_gian_cho_dat=eeprom_read_word((u16*)(dc_tg_cho+DCT));
	if (thoi_gian_cho_dat>65000||thoi_gian_cho_dat==0)
	{
		thoi_gian_cho_dat=10;
	}
}
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
		if(TTCB[cam_bien_so]==TC[cam_bien_so]&&tg_giu>900&&nnn==0)
		{
			tg_thoat_nut=tg_thoat_nut_dat;
			if(mo==0)
			{
				mo=1;
				tg_coi=tg_coi_dat*2;
				nnn=1;
				nrs=1;
				//quet_led(so_dat);
			}
			else
			{
				mo++;
				nnn=1;
				tg_coi=tg_coi_dat*2;
				nrs=1;
				if(mo>10)
				{
					mo=0;
					luu_thong_so_cai();
					//quet_led(so_dem);
//					luu_eeprom();
				}
				
			}
		}
		else
		if(TTCB[cam_bien_so]==KTC[cam_bien_so]&&nrs==0&&(tg_giu>=1&&tg_giu<800))
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
				if(mo<6)
				{
					u32 so=chinh_tang_so_32(thoi_gian_ton_tai_dat,mo);
					if (so>65000)
					{
						so-=70000;
					}
					thoi_gian_ton_tai_dat=(u16)so;
				}
				else
				{
					u32 so=chinh_tang_so_32(thoi_gian_cho_dat,mo-5);
					if (so>65000)
					{
						so-=70000;
					}
					thoi_gian_cho_dat=(u16)so;
				}

				

				tg_coi=tg_coi_dat;
 				tg_luu_cai_dat=tg_luu_dat;
 				che_do=0;
 				nnn1=0;

 				ct=0;
 				bct=0;
			}
			
		}
		else
		if(TTCB[cam_bien_so]==KTC[cam_bien_so])
		{
			nnn1=0;
			nnn=0;
			nrs=0;
		}
	}
}
#endif

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
#include <!/1 Bo dem/1 Luu nho.h>
#endif

