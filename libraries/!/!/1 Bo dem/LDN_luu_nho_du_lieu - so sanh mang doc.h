#ifndef _LDN_luu_nho_du_lieu_ss_h_
#define _LDN_luu_nho_du_lieu_ss_h_
#include "1 Bo dem khai bao.h"
#include "1 Luu nho - so sanh mang doc.h"
void mac_dinh_thong_so_cai(void);
void luu_thoi_gian_ton_tai();
void doc_thoi_gian_ton_tai();
//======================================== 
u8 tg_luu_so_dat_;
u8 tg_luu_thong_so_cai_dat;
void quet_luu_nho_du_lieu()
{
	if(tg_luu==1)
	{
		//luu_chi_so_dem();
		
		//#ifdef luu_sp_dem_rieng
		//luu_so_dem();
		//#else
		//so[so_dem_t]++;
		//chuyen_doi_so_7_32(so[so_dem_t],0,0);
		luu_so_dem();
		tg_luu=0;
	}
	if(tg_luu_so_dat_==1)
	{
		luu_so_dat_co_dinh();
		tg_luu_so_dat_=0;
	}
	if(tg_luu_thong_so_cai_dat==1)
	{
		luu_thong_so_cai();
		tg_luu_thong_so_cai_dat=0;
	}
}
//========================================
#ifdef dat_dem_thong_so
//u16 bien_thong_so_1;
u8 nrs=0;
u8 nnn1; // nho co nhan phim lan dau
u8 nnn;
void luu_thong_so_cai()
{
	u16 i;
	u8 co_luu_tgtt=0;
	#ifndef khong_dem_bao_chong
	thong_so_16[bien_thong_so_1_t]=dem_bao_lien_ke;
	#endif
	thong_so_16[bien_thong_so_1_t]<<=2;
	thong_so_16[bien_thong_so_1_t]|=tac_dung_nut_reset_giu;
	thong_so_16[bien_thong_so_1_t]<<=2;
	thong_so_16[bien_thong_so_1_t]|=tich_cuc_cb_dat;
	for (i=0;i<tong_thong_so_16;i++)
	{
		if(thong_so_16_n[i]!=thong_so_16[i])
		{
			thong_so_16_n[i]=thong_so_16[i];
			eeprom_update_word((u16*)(dc_thong_so+i*2),thong_so_16[i]);
			if(i==thoi_gian_ton_tai_dat_t || i==thoi_gian_cho_dat_t)
			{
				co_luu_tgtt=1;
			}
		}
	}
	//eeprom_write_word((u16*)(dc_bien_thong_so_1),bien_thong_so_1);
	//========================================
	//eeprom_write_word((u16*)(dc_thoi_gian_relay_bat_dat),tg_relay_bat_dat);
	eeprom_update_byte((u8*)dc_tu_re_set,tu_re);
	eeprom_update_byte((u8*)dc_lap_bao_theo_boi,bao_theo_boi);
	luu_so_dat_co_dinh();
	if(co_luu_tgtt==1)
	{
		luu_thoi_gian_ton_tai();
	}
}
#ifndef khong_so_dat
void luu_so_dat_co_dinh()
{
	u16 i;
	for(i=0;i<tong_so_tinh;i++)
	{
		if (so_tinh_n[i]!=so_tinh[i])
		{
			so_tinh_n[i]=so_tinh[i];
			#if so_so<5
			eeprom_update_word((u16*)(dc_so_dat_co_dinh+i*2),so_tinh[i]);
			#else
			eeprom_update_dword((u32*)(dc_so_dat_co_dinh+i*4),so_tinh[i]);
			#endif
		}
	}
}
#endif
void luu_thoi_gian_ton_tai()
{
	eeprom_update_word((u16*)(dc_tg_ton_tai_dat_1),thong_so_16[thoi_gian_ton_tai_dat_t]);
	eeprom_update_word((u16*)(dc_tg_ton_tai_dat_2),thong_so_16[thoi_gian_ton_tai_dat_t]);
	eeprom_update_word((u16*)(dc_tg_ton_tai_dat_3),thong_so_16[thoi_gian_ton_tai_dat_t]);
	eeprom_update_word((u16*)(dc_tg_ton_tai_dat_4),thong_so_16[thoi_gian_ton_tai_dat_t]);
	
	eeprom_update_word((u16*)(dc_tg_cho_dat_1),thong_so_16[thoi_gian_cho_dat_t]);
	eeprom_update_word((u16*)(dc_tg_cho_dat_2),thong_so_16[thoi_gian_cho_dat_t]);
	eeprom_update_word((u16*)(dc_tg_cho_dat_3),thong_so_16[thoi_gian_cho_dat_t]);
	eeprom_update_word((u16*)(dc_tg_cho_dat_4),thong_so_16[thoi_gian_cho_dat_t]);
}

void doc_thoi_gian_ton_tai()
{
	u8 i;
	for (i=0;i<tong_so_mang_tgtt;i++)
	{
		tg_ton_tai_dat_mang[i]=eeprom_read_word((u16*)(dc_tg_ton_tai_dat_1+i*2));
		tg_cho_dat_mang[i]=eeprom_read_word((u16*)(dc_tg_cho_dat_1+i*2));
	}
}
//========================================
void mac_dinh_thong_so_cai(void)
{
	thong_so_16[bien_thong_so_1_t]=0;
	thong_so_16[thoi_gian_cho_dat_t]=10;
	thong_so_16[thoi_gian_ton_tai_dat_t]=10;
	thong_so_16[tg_relay_bat_khi_san_pham_di_qua_t]=0; 
	thong_so_16[tg_relay_bat_dat_t]=0;
	tg_luu_thong_so_cai_dat=tg_luu_dat;
	so_tinh[so_dat_t]=0;
}
//======================================== 
void doc_thong_so_cai(void)
{
	u8 co_luu_lai=0;
	u8 j;
	for (j=0;j<tong_thong_so_16;j++)
	{
		thong_so_16_n[j]=thong_so_16[j]=eeprom_read_word((u16*)(dc_thong_so+j*2));
	}
	u8 tro;
	for(tro=0;tro<2;tro++)
	{
		if (thong_so_16[tro]>65000||thong_so_16[tro]==0)
		{
			thong_so_16[tro]=10;
			co_luu_lai=1;
		}
	}
	doc_thoi_gian_ton_tai();
	u16 tim;
	tim=tim_2_giong_16_gioi_han(tg_ton_tai_dat_mang,tong_so_mang_tgtt,65000);
	if(tim<=65000)
	{
		if(thong_so_16[thoi_gian_ton_tai_dat_t]!=tim)
		{
			thong_so_16[thoi_gian_ton_tai_dat_t]=tim;
		}
	}
	else
	{
		if (thong_so_16[thoi_gian_ton_tai_dat_t]>65000||thong_so_16[thoi_gian_ton_tai_dat_t]==0)
		{
			thong_so_16[thoi_gian_ton_tai_dat_t]=10;
			co_luu_lai=1;
		}
	}
	
	tim=tim_2_giong_16_gioi_han(tg_cho_dat_mang,tong_so_mang_tgtt,65000);
	if(tim<=65000)
	{
		if(thong_so_16[thoi_gian_cho_dat_t]!=tim)
		{
			thong_so_16[thoi_gian_cho_dat_t]=tim;
		}
	}
	else
	{
		if (thong_so_16[thoi_gian_cho_dat_t]>65000||thong_so_16[thoi_gian_cho_dat_t]==0)
		{
			thong_so_16[thoi_gian_cho_dat_t]=10;
			co_luu_lai=1;
		}
	}
	
	
	//tich_cuc_cb_dat=thong_so_16[bien_thong_so_1_t]%10;
	tich_cuc_cb_dat=thong_so_16[bien_thong_so_1_t]&3;
	if (tich_cuc_cb_dat>1)
	{
		tich_cuc_cb_dat=0;
		co_luu_lai=1;
	}
	thong_so_16[bien_thong_so_1_t]>>=2; // con 14 bit
	//thong_so_16[bien_thong_so_1_t]/=10;
	tac_dung_nut_reset_giu=thong_so_16[bien_thong_so_1_t]&3;
	if (tac_dung_nut_reset_giu>2)
	{
		tac_dung_nut_reset_giu=0;
		co_luu_lai=1;
	}
	thong_so_16[bien_thong_so_1_t]>>=2; // con 12 bit
	#ifndef khong_dem_bao_chong
	dem_bao_lien_ke=thong_so_16[bien_thong_so_1_t]&3;
	if (dem_bao_lien_ke>2)
	{
		dem_bao_lien_ke=0;
		co_luu_lai=1;
	}
	#endif
	if (thong_so_16[tg_relay_bat_dat_t]>999)
	{
		thong_so_16[tg_relay_bat_dat_t]=0; 
		co_luu_lai=1;
	}
	if (thong_so_16[tg_relay_bat_khi_san_pham_di_qua_t]>999)
	{
		thong_so_16[tg_relay_bat_khi_san_pham_di_qua_t]=0;
		co_luu_lai=1;
	}
	tu_re=eeprom_read_byte((u8*)dc_tu_re_set);
	if (tu_re>1)
	{
		tu_re=0;
	}

	bao_theo_boi=eeprom_read_byte((u8*)dc_lap_bao_theo_boi);
	if (bao_theo_boi>1)
	{
		bao_theo_boi=0;
	}
	
	u16 i;
	//for(i=0;i<tong_thong_so_16;i++)
	//{
		//thong_so_16_n[i]=thong_so_16[i]=eeprom_read_word((u16*)(dc_tg_ton_tai_dat+i*2));
	//}
	//
	
	
	for(i=0;i<tong_so_tinh;i++)
	{
		#if so_so<5
		so_tinh_n[i]=so_tinh[i]=eeprom_read_word((u16*)(dc_so_dat_co_dinh+i*2));
		#else
		so_tinh_n[i]=so_tinh[i]=eeprom_read_dword((u32*)(dc_so_dat_co_dinh+i*4));
		#endif
	}
	if (so_tinh[so_dat_t]>ghtd)
	{
		so_tinh[so_dat_t]=0;
	}
	//eeprom_write_word((u16*)(dc_so_dat_co_dinh),so_dat);
	if(co_luu_lai==1)
	{
		tg_luu_thong_so_cai_dat=tg_luu_dat;
	}
}
#endif
//======================================== 
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
		eeprom_update_byte((u8*)(dc_e_id+i),id[i]);
	}
}
#endif

