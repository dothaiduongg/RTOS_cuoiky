#ifndef _luu_nho_h_
#define _luu_nho_h_
//========================================
#define GHE 511
void doc_HTK();
void tang_HTK();
u8 HKT;

#define tong_so_mang_tgtt 4
u16 tg_ton_tai_dat_mang[tong_so_mang_tgtt];
u16 tg_cho_dat_mang[tong_so_mang_tgtt];
#define dc_tg_ton_tai_dat_1 10 
#define dc_tg_ton_tai_dat_2 12
#define dc_tg_ton_tai_dat_3 14 
#define dc_tg_ton_tai_dat_4 16
#define dc_tg_cho_dat_1 18
#define dc_tg_cho_dat_2 20
#define dc_tg_cho_dat_3 22
#define dc_tg_cho_dat_4 24
#define dc_thong_so 30
//#define dc_tg_cho_dat 12 // 2 byte
//#define dc_bien_thong_so_1 14 // 2 byte
#define dc_so_dat_co_dinh 50 // 4 byte
//#define dc_thoi_gian_relay_bat_dat 20
#define dc_tu_re_set 54
#define dc_lap_bao_theo_boi 56
#define BDE 100 // dia chi bat dau su dung eeprom // cac dia chi truoc do de luu gia tri co dinh
#define DC_HKT BDE-1 // 
#define dc_so_dem 0 // 4 byte
#define dc_so_dem_dong 0 // 4 byte
#define dc_so_dat 8 // 4 byte
#define dc_so_en 12 // 2 byte
#define dc_so_encoder_dat 14 // 2 byte
//#define dc_so_encoder_dat 14 // 2 byte
u16 DCT;
#define che_do_mac_dih 0


#ifndef TDE
#define TDE 20 // tong do E // so eeprom su dung
#endif
#define GHHKT ((GHE-BDE)/TDE)-TDE // Gioi han kich thuc

#ifndef e_rieg // #define e_rieg

#define do_dai_mag_e_dem 10
u8 mag_e_dem[do_dai_mag_e_dem];
u8 mag_e_dem_nho[do_dai_mag_e_dem];

#define dc_nhanh_cham 12
//#define dc_so_dat 16
#define dc_tu_re 20
#define dc_che_do 24
#define dc_toc_do_cam_bien_dat 28
#define dc_so_tog 32
#define dc_td_ton_tai_dat 36
#define dc_so_dat1 40
#define dc_so_dat2 44
#define so_dc_mag_e 48

//#define BDE 8 // dia chi bat dau su dung eeprom
//#define TDE 60 // dia chi ket thuc su dung eeprom
//#define SED TDE-BDE // so eeprom su dung
#define GHHKT (GHE-BDE)/SED


// u32 so_luu_32[5];
// u16 so_luu_16[5];
// u8 so_luu_8[5];
#if so_so>4
u32 so_dem_n;
u32 so_dat_n;
u32 so_dat1_n;
u32 so_dat2_n;
u32 so_tog_n;
#else
u16 so_dem_n;
u16 so_dat_n;
u16 so_dat1_n;
u16 so_dat2_n;
u16 so_tog_n;
#endif
u8 tu_re_n;
u8 che_do_n;
u16 nhanh_cham_n;
u32 toc_do_cam_bien_dat;
u32 toc_do_cam_bien_dat_n;
u32 td_ton_tai_dat_n;
//u16 CPLE; // cho phep lu EE
void tron_da_tri_luu()
{
	so_dem_n=so_dem+1;
	so_dat_n=so_dat+1;
	so_dat1_n=so_dat1+1;
	so_dat2_n=so_dat2+1;
	so_tog_n=so_tog+1;
	tu_re_n=tu_re+1;
	nhanh_cham_n=nhanh_cham+1;
	toc_do_cam_bien_dat_n=toc_do_cam_bien_dat+1;
	td_ton_tai_dat_n=td_ton_tai_dat+1;
	che_do_n=che_do+1;
	u8 i;
	for (i=0;i<do_dai_mag_e_dem;i++)
	{
		mag_e_dem_nho[i]=mag_e_dem[i]+1;
	}
}

int8 doc_eeprom_lap()
{
	u8 loi=0;
	#if so_so>4
	so_dem_n=so_dem=eeprom_read_dword((u32*)(dc_so_dem+DCT));
	so_dat_n=so_dat=eeprom_read_dword((u32*)(dc_so_dat+DCT));
	so_dat1_n=so_dat1=eeprom_read_dword((u32*)(dc_so_dat1+DCT));
	so_dat2_n=so_dat2=eeprom_read_dword((u32*)(dc_so_dat1+DCT));
	so_tog_n=so_tog=eeprom_read_dword((u32*)(dc_so_tog+DCT));
	#else
	so_dem_n=so_dem=doc_e_16(dc_so_dem+DCT);
	so_dat_n=so_dat=doc_e_16(dc_so_dat+DCT);
	so_dat1_n=so_dat1=doc_e_16(dc_so_dat1+DCT);
	so_dat2_n=so_dat2=doc_e_16(dc_so_dat2+DCT);
	so_tog_n=so_tog=doc_e_16(dc_so_tog+DCT);
	#endif
	nhanh_cham_n=nhanh_cham=doc_e_16(dc_nhanh_cham+DCT);
	toc_do_cam_bien_dat_n=toc_do_cam_bien_dat=eeprom_read_dword((u32*)(dc_toc_do_cam_bien_dat+DCT));
	
	td_ton_tai_dat_n=td_ton_tai_dat=eeprom_read_dword((u32*)(dc_td_ton_tai_dat+DCT));
	tu_re_n=tu_re=doc_e_8(dc_tu_re+DCT);
	che_do_n=che_do=doc_e_8(dc_che_do+DCT);
	
	u8 i;
	for (i=0;i<do_dai_mag_e_dem;i++)
	{
		mag_e_dem_nho[i]=mag_e_dem[i]=doc_e_8(so_dc_mag_e+i+DCT);
	}
	if(so_dem>99999)loi=1;
	if(so_dat>99999)loi=1;
	if(so_tog>99999)loi=1;
	if(nhanh_cham>100)loi=1;
	if(tu_re>9)loi=1;
	if(toc_do_cam_bien_dat>50000)loi=1;
	if(td_ton_tai_dat>99999)loi=1;
	if(che_do>100)loi=1;
	return loi;
}
//========================================
void doc_eeprom()
{
	u16 SS;
	delay_ms(1500);
	doc_HTK();
	if(doc_eeprom_lap()==1)
	{
		so_dem=0;
		so_dat=0;
		so_dat1=0;
		so_dat2=0;
		so_tog=0;
		nhanh_cham=1;
		tu_re=0;
		che_do=che_do_mac_dih;
		toc_do_cam_bien_dat=200;
		td_ton_tai_dat=100;
		luu_eeprom();
	}
	tang_HTK();
	tron_da_tri_luu();
	luu_eeprom();
	luu_e_8(HKT,DC_HKT+BDE);
}
//====================================
void luu_eeprom_lap()
{
	if(so_dem_n!=so_dem)
	{
		#if so_so>4
		eeprom_write_dword((u32*)(dc_so_dem+DCT),so_dem);
		#else
		luu_e_16(so_dem,dc_so_dem+DCT);
		#endif
		so_dem_n=so_dem;
	}
	if(so_dat_n!=so_dat)
	{
		#if so_so>4
		eeprom_write_dword((u32*)(dc_so_dat+DCT),so_dat);
		#else
		luu_e_16(so_dat,dc_so_dat+DCT);
		#endif
		so_dat_n=so_dat;
	}
	
	if(so_dat1_n!=so_dat1)
	{
		#if so_so>4
		eeprom_write_dword((u32*)(dc_so_dat1+DCT),so_dat1);
		#else
		luu_e_16(so_dat1,dc_so_dat1+DCT);
		#endif
		so_dat1_n=so_dat1;
	}
	if(so_dat2_n!=so_dat2)
	{
		#if so_so>4
		eeprom_write_dword((u32*)(dc_so_dat2+DCT),so_dat2);
		#else
		luu_e_16(so_dat2,dc_so_dat2+DCT);
		#endif
		so_dat2_n=so_dat2;
	}
	
	if(so_tog_n!=so_tog)
	{
		#if so_so>4
		eeprom_write_dword((u32*)(dc_so_tog+DCT),so_tog);
		#else
		luu_e_16(so_tog,dc_so_tog+DCT);
		#endif
		so_tog_n=so_tog;
	}
	if(tu_re_n!=tu_re)
	{
		luu_e_8(tu_re,dc_tu_re+DCT);
		tu_re_n=tu_re;
	}
	if(nhanh_cham_n!=nhanh_cham)
	{
		luu_e_16(nhanh_cham,dc_nhanh_cham+DCT);
		nhanh_cham_n=nhanh_cham;
	}
	if(toc_do_cam_bien_dat_n!=toc_do_cam_bien_dat)
	{
		eeprom_write_dword((u32*)(dc_toc_do_cam_bien_dat+DCT),toc_do_cam_bien_dat);
		toc_do_cam_bien_dat_n=toc_do_cam_bien_dat;
	}
	if(td_ton_tai_dat_n!=td_ton_tai_dat)
	{
		eeprom_write_dword((u32*)(dc_td_ton_tai_dat+DCT),td_ton_tai_dat);
		td_ton_tai_dat_n=td_ton_tai_dat;
	}
	if(che_do_n!=che_do)
	{
		luu_e_8(che_do,dc_che_do+DCT);
		che_do_n=che_do;
	}
	u8 i;
	for (i=0;i<do_dai_mag_e_dem;i++)
	{
		if (mag_e_dem_nho[i]!=mag_e_dem[i])
		{
			luu_e_8(mag_e_dem[i],so_dc_mag_e+i+DCT);
			mag_e_dem_nho[i]=mag_e_dem[i];
		}
	}
}
//========================================
void luu_eeprom()
{
	luu_eeprom_lap();
}

void luu_so_dem_()
{
	if(so_dem_n!=so_dem)
	{
		#if so_so>4
		eeprom_write_dword((u32*)(dc_so_dem+DCT),so_dem);
		#else
		luu_e_16(so_dem,dc_so_dem+DCT);
		#endif
		so_dem_n=so_dem;
	}
}
#endif
//======================================== 
void tinh_DCT()
{
	if (HKT>=GHHKT)//||HKT==0)
	{
		HKT=0;
	}
	DCT=HKT;
	DCT*=TDE;
	DCT+=BDE; // Duoc tinh tu E bat dau
}
//======================================== 
void doc_HTK()
{
	delay_ms(1500);
	HKT=eeprom_read_byte((u8*)DC_HKT);
	tinh_DCT();
	#ifndef khong_dung_led_7_doan
	#if so_so == 22
	chuyen_doi_so_7_32_2(HKT,so_tinh[so_dat_t],0,0);
	#else
	chuyen_doi_so_7_32(HKT,0,0);
	#endif
	#endif
}
//======================================== 
void tang_HTK()
{
	HKT++;
	tinh_DCT();
}
//======================================== 
void luu_HTK()
{
	eeprom_write_byte((u8*)DC_HKT,HKT);
}
#endif

