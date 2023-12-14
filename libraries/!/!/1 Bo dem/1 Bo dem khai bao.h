#ifndef _bo_dem_khai_bao_h_
#define _bo_dem_khai_bao_h_
u8 nn;
u8 du_1_ms;
#ifdef dung_encoder
u8 chon_che_do_dem;
u8 tg_tra_ve_dem_binh_thuong=0;
#endif
//u16 thoi_gian_ton_tai_dat; // thoi gian ton tai dat cho cam bien. duoc tinh bang ms. va phai chia 2 (yeu cau ham doc cam bien phai co trong ngat timer1 1ms)
//u16 thoi_gian_cho_dat;
//u16 tg_truen_lai=0; // thoi gian truyen lại dược áp dụng cho việc truyền thông số hoặc số đếm qua uart

u8 tg_truyen_lai_=0;
//u16 tg_relay_bat_dat;
//u16 tg_relay_bat_khi_san_pham_di_qua;
u16 tg_relay_bat;
u8 bao_theo_boi;

u8 ct;
u8 bct;

u8 chuoi_so_truyen[20];
u8 chuoi_so_nho[20];
u8 id[10]; // id cua 1 bo dem la 10 ky tu
u8 cho_truyen=0;
u8 tg_truyen=50;

u8 encoder_cho_phep;
u16 thoi_dan_led_dem=0;
u16 thoi_dan_led_dat=0;
u8 b_led=0;

u16 nhanh_cham=0;

#define tong_so 2
#define tong_so_tinh 2
#ifndef nhieu_so
#ifndef _so_dem_
#ifdef lam_nhe_ct
#if so_so<=4
#ifndef bo_dem_thoi_gian
u16 so[tong_so];
u16 so_n[tong_so];
#else
u32 so[tong_so];
u32 so_n[tong_so];
#define tong_so_cai 50
#define so_moc_toi_da 20
u16 so_cai[tong_so_cai];
u16 so_cai_n[tong_so_cai];
#endif
#ifdef nhan_ban_phim_v1
u16 so_dat_tam;
u32 so_dat_nhan;
u8 mang_dat_tam[10];
#endif
u16 so_tinh[tong_so_tinh];
u16 so_tinh_n[tong_so_tinh];
#endif
#if so_so!=22
	#if so_so>4
	u32 so[tong_so];
	u32 so_n[tong_so];
	u32 so_tinh[tong_so_tinh];
	u32 so_tinh_n[tong_so_tinh];
	#endif
#else
	u16 so[tong_so];
	u16 so_n[tong_so];
	u16 so_tinh[tong_so_tinh];
	u16 so_tinh_n[tong_so_tinh];
#endif

#define so_dem_t 0
#ifdef dem_tong
#define so_tong_t 1
#endif
//======================================== 
#define tong_thong_so_16 5
u16 thong_so_16[tong_thong_so_16];
u16 thong_so_16_n[tong_thong_so_16];
#define thoi_gian_ton_tai_dat_t 0
#define thoi_gian_cho_dat_t 1
#define bien_thong_so_1_t 2
#define tg_relay_bat_dat_t 3
#define tg_relay_bat_khi_san_pham_di_qua_t 4

#define TDE tong_so*4

#define so_dat_t 0
#else
//u32 so_dem;
//u32 so_tog;
#endif
//u32 so_dat;
u32 so_dat1;
u32 so_dat2;
#endif
#endif
#ifdef nhieu_so
u8 so_chon=0;
u8 so_chon1=0;
#if so_so>4
u32 so_dem[nhieu_so];
//u32 so_tong;
#else
u16 so_dem[nhieu_so];
u16 so_tong;
#endif
#endif

u32 td_ton_tai_dat;
u8 mdv; // nho ma don vi cho LED 7 doan

u8 tich_cuc_cb_dat=0; // 0 là =0 thì tích cực
u8 tac_dung_nut_reset_giu=0; // 0 la nhán giu thi hien thi tong, 1 hien cai dat so dat nạp về 0, 2 là hiện thị số đặt nạp về số đặt
#ifndef khong_dem_bao_chong
u8 dem_bao_lien_ke=0;
#endif
u8 mo;
u8 tu_re=0;
#ifdef ket_noi_wifi
u8 lan_truyen=0x30;
#endif

#ifdef co_rl
u16 tg_rl=0;
#endif

#ifdef rl_dao_khi_du
u8 tt_rl=0; // trang thai relay
#endif

u8 da_dem=0;



void doc_nut_nhan_cai(u8 cam_bien_so);
void doc_so_dem(void);
//void luu_so_dem(u8 a);
void luu_chi_so_dem(void);
void luu_eeprom2();
void quet_led_htk(u16 so);
void chuyen_doi_so_7_32(u32 so,u8 chon,u8 vi_tri_cham);
void chuyen_doi_so_7_32_2(u32 so,u32 so2,u8 chon,u8 vi_tri_cham);
void chuyen_doi_so_7_16_don(u16 so); // khi chon la boi cua 10 se chuyen che do hien thi
void ngat_1ms(void);


#include <!/1 Bo dem/1 Doc Encoder.h>


#endif