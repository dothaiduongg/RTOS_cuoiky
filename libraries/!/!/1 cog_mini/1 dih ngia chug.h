#ifndef _dinh_nghia_chung_
#define _dinh_nghia_chung_
#define bu_c 1000 // bu do c de kog am
#ifdef phien_ban_6
#define bu_f 1000 // bu do c de kog am
#endif
#ifdef phien_ban_5
#define bu_f 1000 // bu do c de kog am
#endif
#ifdef phien_ban_4
#define bu_f 500 // bu do c de kog am
#endif


#define trang_thai_tat 0
#define trang_thai_ga_lon 1
#define trang_thai_de 2
//#define tt_cho_tat 3
#define trang_thai_bat 4 // may duoc bat chua no
//#define tt_cho_tat_tt 5
#define trang_thai_dang_bat 3
#define trang_thai_ga_nho 7
#define trang_thai_cho_tat 8
#define trang_thai_xa_da_khi_bat_nguon 9 
#define trang_thai_xa_da 10
#define trang_thai_cho_tat_de_bat_lai 11 // trang thai cho tat de sau do no lai khi thieu nhiet do
#define trang_thai_cho_bat_lai_sau_tu_tat 12
#define trang_thai_cho_de 13
#define trang_thai_mo_dau 14


#define dc_bao_sa_da 8
#define dc_dien_ap_t 9
#define dc_dien_ap_c 10
u8 bao_sa_da=0;
u16 td_sa_da;
u8 tg_de_dat;

//u16 nhiet_chenh_lech;
u16 td_cho_no_lai_dat; // Thoi gian cho no lai, neu dat =0 chi chay tho nhiet do
u16 nd_bat_dau_sa_da_dat; // Nhiet do bat dau sa da dat
u16 tg_cho_sa_da_dat; // Thoi gian cho sa da, neu = 0 vo hieu hoa sa da theo thoi dan
u16 td_sa_da_dat; // Thoi da sa da dat
//u16 nhiet_do_dat;
//u8 c_f=0; // 0 do C, 1 Do F
u8 thoi_gian_de;

//u8 nut_nhan=0;
u8 giay_100=0;
u8 du_1_giay;
u8 dem_100;
u8 du_100_ms;
//u8 nut_nhan_m=0;

#define nhiet_chenh_lech_td 500
#define nd_tat_xa_da_td 800+bu_f
#define tg_cho_xa_da_dat_td 10800+bu_f
#define tg_cho_xa_da_toi_da 30000
#define tg_cho_no_lai_toi_da 30000 // Don vi la giay
#define tg_xa_da_toi_da 1800 // 30 phutd
#define thoi_gian_cho_doi_trang_thai_dat 4 // don vi la giay

u8 thoi_gian_nhan; // thoi gian nhan tren lcd, neu = 0 tuc không nhận được dữ liệu
#define thoi_gian_nhan_dat 5 // 3 Giay

#define thoi_gian_cho_de_dat 5
u8 thoi_gian_cho_de;
#define thoi_gian_tre_ga_lon_dat 10
u8 thoi_gian_tre_ga_lon;
u8 thoi_gian_cho_doi_trang_thai;
#define thoi_gian_tu_chay_khi_bat_nguon_dat 10 // 10 giay
u8 thoi_gian_tu_chay_khi_bat_nguon=thoi_gian_tu_chay_khi_bat_nguon_dat;

#define thoi_gian_cho_tat_no_lai_dat 10
u8 thoi_gian_cho_tat_no_lai; // thoi gian cho tat tam thoi

//u16 nhiet_xa_da;
//u16 thoi_gian_cho_xa_da_dat;// 3600 // thoi gian cho xa da dat = 60 phut


//u16 thoi_gian_cho_no_lai_dat=0; 
u8 bat_dau_xa_da_boi_nhiet=0;


#ifdef _kt_
	#define thoi_gian_xac_dinh_cam_bien_khong_tot_dat 3 // 30 giay
#else
	#define thoi_gian_xac_dinh_cam_bien_khong_tot_dat 60 // 2 phut
#endif

u8 thoi_gian_xac_dinh_cam_bien_khong_tot=thoi_gian_xac_dinh_cam_bien_khong_tot_dat; // *10 giay

#define tg_chinh_out_dat 20
u8 tg_chinh_out;

#define tong_so_thoi_gian_giay 2
#define thoi_gian_xa_da_khi_bat 4;
#define thoi_gian_xa_da_khi_de 4;
//- 
#define thoi_gian_xa_da_t 0 // don vi la giay
#define thoi_gian_cho_xa_da_t 1
//u16 thoi_gian_xa_da_dat;
u16 thoi_gian_giay[tong_so_thoi_gian_giay];

#define thoi_gian_de_dat_toi_da 100
//u8 thoi_gian_de_dat;

u8 thoi_gian_mo_dau=0; // don vi laf 100m s

//u8 bbit=0; // byte chua cac bit
#define ho_tro_may dk_bit(bbit,0) // bit bao hoat dong o che do may hay che do bo, 1 che do may, 2 che do bo chon che do may hoac che do ldnam// = 0 chon che do may . = 1 chon che do ldnam
//#define tt_rl_xa_da dk_bit(bbit,1) // bit bao xa da
#define tu_no_tu_tat dk_bit(bbit,2) // bit bao tu dong
#define tu_chay_khi_bat_nguon dk_bit(bbit,3) // bit bao tu dong
//#define tu_chay_khi_bat_nguon dk_bit(bbit,4) 
#ifdef phien_ban_6
#define c_f dk_bit(bbit,7) // bit bao tu dong
#endif
#ifdef phien_ban_5
#define c_f dk_bit(bbit,7) // bit bao tu dong
#endif
#define chon_cam_bien dk_bit(bbit,6)
#define hien_thi_nhiet_dat dk_bit(bbit,4)
//#define 

#define xa_da_bit dk_bit(bbit,1) // bit bao xa da


u8 chuoi_thoi_gian_dem[18];
u8 chuoi_thoi_gian_dem_nho[18];


//u8 tg_coi;




u8 mode_n=99;
#ifdef phien_ban_6
#define tong_mode 16 // bao gom mode 0
#define mode_nhiet_dat 1
#define mode_nhiet_chenh_lech 2
#define mode_thoi_gian_cho_no_lai_dat 3
#define mode_nhiet_xa_da 4
#define mode_thoi_gian_cho_xa_da_dat 6
#define mode_thoi_gian_xa_da_dat 5
#define mode_hien_thi_c_f 7
#define mode_tu_no_tu_tat 8
#define mode_ho_tro_may 9

//#define mode_cai_dat_nang_cao 10
//#define mode_cai_dat_sau 11 // cai dat sau vao he thong
#define mode_hoi_cai_dat_nang_cao 11 // mode nang cao
#define mode_thoi_gian_de_dat 12
#define mode_tu_chay_khi_bat_nguon 13
#define mode_chon_cam_bien 14
#define mode_thoi_gian_mo_dau_dat 15
#define mode_chon_hien_thi_nhiet_dat 16
#endif
#ifdef phien_ban_5
#define tong_mode 16 // bao gom mode 0
#define mode_nhiet_dat 1
#define mode_nhiet_chenh_lech 2
#define mode_thoi_gian_cho_no_lai_dat 3
#define mode_nhiet_xa_da 4
#define mode_thoi_gian_cho_xa_da_dat 6
#define mode_thoi_gian_xa_da_dat 5
#define mode_hien_thi_c_f 7
#define mode_tu_no_tu_tat 8
#define mode_ho_tro_may 9

//#define mode_cai_dat_nang_cao 10
//#define mode_cai_dat_sau 11 // cai dat sau vao he thong
#define mode_hoi_cai_dat_nang_cao 10 // mode nang cao
#define mode_thoi_gian_de_dat 11
#define mode_tu_chay_khi_bat_nguon 12
#define mode_chon_cam_bien 13
#define mode_thoi_gian_mo_dau_dat 14
#define mode_chon_hien_thi_nhiet_dat 15
#endif
#ifdef phien_ban_4
#define mode_nhiet_dat 1
#define mode_nhiet_xa_da 2
#define mode_nhiet_xa_da_tat 3
#define mode_nhiet_chenh_lech 4
#define mode_hien_thi_cai_dat_nang_cao 5
#define mode_thoi_gian_cho_xa_da_dat 6
//#define mode_thoi_gian_cho_no_lai_dat 3
//#define mode_thoi_gian_xa_da_dat 5
//#define mode_hien_thi_c_f 7
//#define mode_tu_no_tu_tat 8
//#define mode_ho_tro_may 9
//#define mode_thoi_gian_de_dat 10
//#define mode_cai_dat_nang_cao 10
//#define mode_cai_dat_sau 11 // cai dat sau vao he thong

//#define mode_tu_chay_khi_bat_nguon 11
//#define mode_chon_cam_bien 12
#endif
u8 ma_nut_nhan_truyen;
u8 ma_nut_nhan_doc;
u8 ma_nut_nhan_nhan;

#define vi_tri_truyen_du_lieu 10
#define so_du_lieu_luu_nho 9
#define so_du_lieu_truyen_nhan 13
#define so_du_lieu_lam_viec 13
u16 mang_dl_16[so_du_lieu_lam_viec];
//---------------------------------------- Các dữ liệu truyền nhận, luu
#ifdef phien_ban_6
#define nhiet_do_dat_tro 0
#define nhiet_chenh_lech_tro 1
#define nhiet_xa_da_tro 2
#define thoi_gian_cho_xa_da_dat_tro 3
#define thoi_gian_xa_da_dat_tro 4
#define thoi_gian_cho_no_lai_dat_tro 5
#define thoi_gian_de_dat_tro 6
#define bbit_tro 7 // co the them 1 byte khác
#define thoi_gian_bom_dau_dat_tro 8 // Don vi la phut
//---------------------------------------- các dữ liệu truyền nhận không lưu
#define dien_ap_tro 9
#define nd_cong_tro 10
#define nd_dan_lanh_tro 11
#define thoi_gian_cho_no_lai_tro 12 // Don vi la giay

#endif

#ifdef phien_ban_5
#define nhiet_do_dat_tro 0
#define nhiet_chenh_lech_tro 1
#define nhiet_xa_da_tro 2
#define thoi_gian_cho_xa_da_dat_tro 3
#define thoi_gian_xa_da_dat_tro 4
#define thoi_gian_cho_no_lai_dat_tro 5
#define thoi_gian_de_dat_tro 6
#define bbit_tro 7 // co the them 1 byte khác
#define thoi_gian_bom_dau_dat_tro 8 // Don vi la phut
//---------------------------------------- các dữ liệu truyền nhận không lưu
#define dien_ap_tro 9
#define nd_cong_tro 10
#define nd_dan_lanh_tro 11
#define thoi_gian_cho_no_lai_tro 12 // Don vi la giay

#endif
#ifdef phien_ban_4
#define nhiet_do_dat_tro 0
#define nhiet_chenh_lech_tro 1
#define nhiet_xa_da_tro 2
#define nhiet_tat_xa_da_tro 4
#define thoi_gian_cho_xa_da_dat_tro 3
//#define thoi_gian_xa_da_dat_tro 4
#define thoi_gian_cho_no_lai_dat_tro 5
//#define thoi_gian_de_dat_tro 6
#define bbit_tro 7 // co the them 1 byte khác
//---------------------------------------- các dữ liệu truyền nhận không lưu
#define dien_ap_tro 8
#define nd_cong_tro 9
#define nd_dan_lanh_tro 10
#define thoi_gian_cho_no_lai_tro 11 // Don vi la giay
#endif
//#define nhiet_xa_da_tat_tro 7
//---------------------------------------- các dữ liệu chỉ sử dụng không truyền nhận không lưu
//======================================== 
#define so_du_lieu_8 8
u8 mang_dl_8[so_du_lieu_8];
#define giay_chay_tro 0
#define phut_chay_tro 1
#define gio_chay_tro 2
#define giay_dung_tro 3
#define phut_dung_tro 4
#define gio_dung_tro 5
#define mode_tro 6
#define trang_thai_tro 7
//#define bbit_tro8 8





//#define tg_bom_dau_dat 60 // 600s = 10P
u16 tg_bom_dau=0;
u8 mo_dau_xong=0;
#define thoi_gian_mo_dau_toi_da 3600 // giay
u8 bom_dau_moi_bat=0;

int1 bit_nhan_nut_de;
u8 tg_giu_nut_de;

u8 bit_nhan_nut_mo=0;
u8 tg_giu_nut_mo=0;

//#define truyen_nhan_dang_chuoi
#define ma_truyen_nhiet_do_doc "NDD"
#define ma_truyen_trang_thai "TT"
#define ma_truyen_chinh "CH"




void bat_bom_dau();
#endif



// kai bao ham
