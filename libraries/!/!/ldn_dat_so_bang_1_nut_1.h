uint32_t so_dat;
#define so_so_sanh 453355
uint16_t tg_out=0;
uint16_t tg_thoat_nut=0;
uint16_t tg_giu=0;
uint8_t mo=0;
uint8_t nnn=0;
uint8_t nrs=0;
uint8_t nnn1=0;
uint8_t ct=0;
uint8_t bct=0;
#define so_so 6
#define tg_thoat_nut_dat 10000
#define ghtd 999999
#define nhan_ 0
#define nha_ 1

uint8_t nut_nhan;
void doc_nut_nhan(void);

void dat_so_bang_1_nut()
{
	if(BUTTON==nhan_)
	{
		tg_thoat_nut=tg_thoat_nut_dat;
	}
	while(tg_thoat_nut>0)
	{
		delay_ms(1);
		tg_thoat_nut--;
		if(tg_giu<65000)
		{
			tg_giu++;
		}
		doc_nut_nhan();
	}
}

//======================================== 
void bat_dau_vao_dat_so()
{
	mo=1;
	nnn=1;
	nrs=1;
	//coi=coi_bat;
	//tg_coi=tg_coi_dat*2;
}
//======================================== 
void tac_dong_khi_nhan_giu_chuyen_so()
{
	mo++;
	nnn=1;
	//coi=coi_bat;
	//tg_coi=tg_coi_dat*2;
	nrs=1;
	if(mo>so_so)
	{
		mo=0;
		//chuyen_doi_so_7_32(so_dem,0,0);
		//tg_luu_cai_dat=tg_luu_dat;
	}
}
//======================================== 
void tac_dong_nhan_nhanh_tang_so()
{
	so_dat=chinh_tang_so_32(so_dat,mo);
	coi=coi_bat;
	//tg_coi=tg_coi_dat;
//				quet_led(so_dat);
	//tg_luu_cai_dat=tg_luu_dat;
	nnn1=0;
	ct=0;
	bct=0;
}
//======================================== 
void chi_tac_dong_nhan_don_thuan_khong_giu()
{
	//so_dem=0;
	//coi=coi_bat;
	//tg_coi=tg_coi_dat;
	//so_dem_n=0;
	//chuyen_doi_so_7_32(so_dem,0,0);
	//truyen_so_dem();
	//tg_luu=tg_luu_dat;
	nnn1=0;
}
//======================================== 

void doc_nut_nhan(void)
{
	nut_nhan=BUTTON;
	if(nnn1==0)
	{ 
		if(nut_nhan==nhan_)
		{
			nnn1=1;
			tg_giu=0;
		}
	}
	else
	{
		if(nut_nhan==nhan_&&tg_giu>600&&nnn==0)
		{
			tg_thoat_nut=tg_thoat_nut_dat;
			if(mo==0)
			{
				bat_dau_vao_dat_so();
			}
			else
			{
				tac_dong_khi_nhan_giu_chuyen_so();
			}
		}
		else
		if(nut_nhan==nha_&&nrs==0&&(tg_giu>1&&tg_giu<500))
		{
			tg_thoat_nut=tg_thoat_nut_dat;
			if(mo==0)
			{
				chi_tac_dong_nhan_don_thuan_khong_giu();
			}
			if (mo>0&&mo<=so_so)
			{
				tac_dong_nhan_nhanh_tang_so();
			}
		}
		else
		if(nut_nhan==nha_)
		{
			nnn1=0; 
			nnn=0; 
			nrs=0;
		}
	}
}