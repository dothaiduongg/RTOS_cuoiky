﻿#ifndef _dem_h_
#define _dem_h_
#define so_so 5


#define thoi_gian_1_so 0.027 //us
#define thoi_gian_dog_cho_phep_dem_dat 3000 // ms
#define thoi_gian_mo_cho_phep_dem_dat 10000 // ms

#define chu_ky_dog_cho_phep_dem_dat thoi_gian_dog_cho_phep_dem_dat/thoi_gian_1_so // ms
#define chu_ky_mo_cho_phep_dem_dat thoi_gian_mo_cho_phep_dem_dat/thoi_gian_1_so // ms
//#if chu_ky_dog_cho_phep_dem_dat>60000
//#endif

u8 cam_bien_nho[1]={0};
u8 cam_bien_trag_thai[1]={0};
u32 cam_bien_chu_ky[1]={0};
u16 cam_bien_chog_nhieu[1]={0}; 
//u8 dem[1]=0;
void doc_cb1()
{
	cam_bien_nho[0]=cb1;
	if(cam_bien_nho[0]==0&&cam_bien_chog_nhieu[0]<10)
	{
		cam_bien_chog_nhieu[0]++;
		cam_bien_nho[0]=1;
	}
	else
	{
		if(cam_bien_nho[0]==1)
		{
			cam_bien_chog_nhieu[0]=0;
		}
	}
	
	
	if(cam_bien_nho[0]==0) // co cam bien
	{
		if(cam_bien_trag_thai[0]==0)
		{
			cam_bien_chu_ky[0]++;
			if(cam_bien_chu_ky[0]>100000)
			{
				cam_bien_chu_ky[0]=0;
				cam_bien_trag_thai[0]=1;
			}
		}
		else
		if(cam_bien_trag_thai[0]!=1)
		{
			cam_bien_trag_thai[0]=0;
			cam_bien_chu_ky[0]=0;
		}
	}
	else
	{
		if(cam_bien_trag_thai[0]==1)
		{
			cam_bien_trag_thai[0]=2;
			cam_bien_chu_ky[0]=0;
		}
		else
		if(cam_bien_trag_thai[0]==2)
		{
			cam_bien_chu_ky[0]++;
			if(cam_bien_chu_ky[0]>100000) //  200000(10s)
			{
				cam_bien_chu_ky[0]=0;
				cam_bien_trag_thai[0]=3;
			}
		}
//		else
// 		if(cam_bien_trag_thai[0]!=3)
// 		{
// 			cam_bien_chu_ky[0]=0;
// 			//cam_bien_trag_thai[0]=0;
// 		}
	}

}

#if so_so>4
	u32 so_dem;
	u32 so_tong;
#endif
void kiem_tra_led()
{
	u8 i;
	so_dem=0;
	for(i=0;i<10;i++)
	{
		quet_led(so_dem);
		delay_ms(500);
		so_dem+=111111;
	}
	quet_led(123456);
	delay_ms(500);
}






const char du_lieu_so_dem[] __attribute__ ((progmem)) = {
	255,1,1,1,1,1,1,1,1,3,1,1,1,1,1,1
	,1,1,1,3,1,1,1,1,1,1,1,1,1,3,1,1
	,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1
	,1,171,1,1,1,1,1,1,1,1,1,3,1,1,1,1
	,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,3
	,1,1,1,1,1,1,1,1,1,3,1,1,1,1,1,1
	,1,1,1,1,255,0,0,240,248,140,140,248,240,0,0,252
	,252,0,0,252,252,0,0,4,252,252,68,196,252,56,0,0
	,255,8,0,0,0,0,0,0,0,8,0,0,0,0,0,0
	,0,0,0,8,0,0,0,0,0,0,0,0,0,8,0,0
	,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0
	,8,170,8,0,0,0,0,0,0,0,0,8,0,0,0,0
	,0,0,0,0,0,8,0,0,0,0,0,0,0,0,0,8
	,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0
	,0,0,0,8,255,0,0,199,39,32,192,7,7,0,0,1
	,3,6,6,3,1,0,0,4,7,7,0,0,7,7,0,0
	,255,32,0,0,0,0,0,0,0,32,0,0,0,0,0,0
	,0,0,0,32,0,0,0,0,0,0,0,0,0,32,0,0
	,0,0,0,0,0,0,0,32,0,0,0,0,0,0,0,0
	,32,170,32,0,0,0,0,0,0,0,0,32,0,0,0,0
	,0,0,0,0,0,32,0,0,0,0,0,0,0,0,0,32
	,0,0,0,0,0,0,0,0,0,32,0,0,0,0,0,0
	,0,0,0,32,255,0,0,25,34,34,28,0,30,33,33,33
	,0,30,33,33,30,0,255,33,33,30,0,30,41,41,46,0
	,255,128,0,128,0,128,0,128,0,192,0,128,0,128,0,128
	,0,128,0,192,0,128,0,128,0,128,0,128,0,192,0,128
	,0,128,0,128,0,128,0,192,0,128,0,128,0,128,0,128
	,0,170,0,128,0,128,0,128,0,128,0,192,0,128,0,128
	,0,128,0,128,0,192,0,128,0,128,0,128,0,128,0,192
	,0,128,0,128,0,128,0,128,0,192,0,128,0,128,0,128
	,0,128,0,128,255,0,40,32,40,32,40,0,0,0,0,0
	,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	,255,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0
	,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0
	,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0
	,0,170,0,0,0,0,0,0,0,0,0,1,0,0,0,0
	,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1
	,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0
	,0,0,0,0,255,0,16,8,16,32,16,0,0,0,0,0
	,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	,255,2,0,0,0,0,0,0,0,2,0,0,0,0,0,0
	,0,0,0,2,0,0,0,0,0,0,0,0,0,2,0,0
	,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0
	,2,170,2,0,0,0,0,0,0,0,0,2,0,0,0,0
	,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,2
	,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0
	,0,0,0,2,255,0,0,0,0,0,0,0,0,0,0,0
	,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	,255,8,0,0,0,0,0,0,0,8,0,0,0,0,0,0
	,0,0,0,8,0,0,0,0,0,0,0,0,0,8,0,0
	,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0
	,8,170,8,0,0,0,0,0,0,0,0,8,0,0,0,0
	,0,0,0,0,0,8,0,0,0,0,0,0,0,0,0,8
	,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0
	,0,0,0,8,255,0,0,124,20,4,0,124,20,104,0,124
	,84,68,0,56,68,68,120,0,0,0,0,0,0,0,0,0
	,255,128,128,128,128,128,128,128,128,160,128,128,128,128,128,128
	,128,128,128,160,128,128,128,128,128,128,128,128,128,160,128,128
	,128,128,128,128,128,128,128,160,128,128,128,128,128,128,128,128
	,128,170,128,128,128,128,128,128,128,128,128,160,128,128,128,128
	,128,128,128,128,128,160,128,128,128,128,128,128,128,128,128,160
	,128,128,128,128,128,128,128,128,128,160,128,128,128,128,128,128
	,128,128,128,128,255,0,0,0,0,0,0,0,0,0,0,0
	,0,0,0,0,0,0,0,124,16,124,0,72,104,88,0,0
};





#endif