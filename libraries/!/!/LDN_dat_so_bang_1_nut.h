#define ldnam_test
uint32_t so_dat;
#define so_so_sanh 553354//453355
uint16_t tg_out=0;
uint16_t tg_thoat_nut=0; 
uint16_t tg_giu_nut=0;
uint16_t tg_nha_nut=0;
uint8_t mo=0;
uint8_t nnn=0;
uint8_t nrs=0;
uint8_t nnn1=0;
uint8_t ct=0;
uint8_t bct=0;
#define so_so 6
#define tg_thoat_nut_dat_ldn_1 10000
#define ghtd 999999
#define nhan_ 0
#define nha_ 1
uint8_t chuyen_nha=0;


uint8_t nut_nhan_;
void doc_nut_nhan(void);
void tac_dong_khi_nhan_nha_chuyen_so();
uint32_t chinh_tang_so_322(uint32_t so_chinh,uint8_t vi_tri);
void dat_so_bang_1_nut()
{
	#ifdef ldnam_test
		delay_ms(1);
	#endif
	if(BUTTON==nhan_)
	{
		tg_thoat_nut=tg_thoat_nut_dat;
		tg_nha_nut=0;
	}
	if(BUTTON==nha_)
	{
		if(tg_nha_nut<65000)
		{
			tg_nha_nut++;
		}
		//bat_dau_cai
		if(tg_nha_nut>3000)
		{
			if(chuyen_nha==1)
			{
				chuyen_nha=0;
				if(mo!=0)
				{
					tac_dong_khi_nhan_nha_chuyen_so();
				}
			}
		}
		//if(tg_nha_nut
	}
	//while(tg_thoat_nut>0)
	{
		//Timer0_Delay1ms(1);
		tg_thoat_nut--;
		if(tg_giu_nut<65000)
		{
			tg_giu_nut++;
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
	chop_led(100,3,1);
	so_dat=0;
	//coi=coi_bat;
	//tg_coi=tg_coi_dat*2;
	if (mo>0)
	{
		chuyen_nha=1;
		tg_nha_nut=0;
	}
}
//======================================== 
void tac_dong_khi_nhan_nha_chuyen_so()
{
	mo++;
	//nnn=1;
	//coi=coi_bat;
	//tg_coi=tg_coi_dat*2;
	//nrs=1;
	if(mo>so_so)
	{
		mo=0;
		#ifndef ldnam_test
		so_sanh();
		#endif
		//
		//chuyen_doi_so_7_32(so_dem,0,0);
		//tg_luu_cai_dat=tg_luu_dat;
	}
	chop_led(100,2,1);
	if (mo>0)
	{
		chuyen_nha=1;
		tg_nha_nut=0;
	}
}
//======================================== 
void tac_dong_nhan_nhanh_tang_so()
{
	if(mo>0)
	{
		so_dat=chinh_tang_so_322(so_dat,mo);
		//	coi=coi_bat;
		//tg_coi=tg_coi_dat;
		//				quet_led(so_dat);
		//tg_luu_cai_dat=tg_luu_dat;
		nnn1=0;
		ct=0;
		bct=0;
		chop_led(100,1,1);
		chuyen_nha=1;
	}
}
//======================================== 
void chi_tac_dong_nhan_don_thuan_khong_giu()
{
	nnn1=0;
	tg_thoat_nut=1;
}
//======================================== 
void doc_nut_nhan(void)
{
	nut_nhan_=BUTTON;
	if(nnn1==0)
	{ 
		if(nut_nhan_==nhan_)
		{
			nnn1=1;
			tg_giu_nut=0;
		}
	}
	else
	{
		if(nut_nhan_==nhan_&&tg_giu_nut>6000&&nnn==0)
		{
			if(mo==0)
			{
				tg_thoat_nut=tg_thoat_nut_dat;
				bat_dau_vao_dat_so();
			}
		}
		else
		if(nut_nhan_==nha_&&nrs==0&&(tg_giu_nut>2))
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
		if(nut_nhan_==nha_)
		{
			nnn1=0; 
			nnn=0; 
			nrs=0;
		}
	}
}
//======================================== 
uint32_t chinh_tang_so_322(uint32_t so_chinh,uint8_t vi_tri) // chinh tang so theo vi tri mot don vi
{
	uint8_t i;
	uint32_t so_chia=1;
	for (i=1;i<vi_tri;i++)
	{ 
		so_chia*=10;
	}
	so_chinh+=so_chia;
	if(so_chinh/so_chia%10==0)
	{
		so_chinh-=so_chia*10;
	}
	return so_chinh;
}
//========================================
#ifdef ldnam_test
void chop_led(uint16_t tre,uint8_t lan,uint8_t led_sang)
{
	uint8_t i;
	for(i=0;i<lan;i++)
	{
		led=1;
		delay_ms(tre);
		led=0;
		delay_ms(tre);
	}
	if(led_sang==1)
	{
		led=1;
	}
}
#endif