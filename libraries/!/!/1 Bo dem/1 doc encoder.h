#ifndef _doc_encoder_h_
#define _doc_encoder_h_
//========================================
#ifdef encoder
#include <!/1 Cam bien.h>
#include "!/1 Bo dem/1 Bo dem khai bao.h"
u8 en_buoc=0;
u8 tang_giam=0; // tang 0, giam 1
#define so_max ghtd
void encoder_xu_ly_2()
{
	if (en_buoc==0) // xac dinh thuan nghich
	{
		if(TTCB[0]==TC[0]&&TTCB[1]==TC[1]) // khong phu hop
		{
			en_buoc=0;
		}
		if(TTCB[0]==TC[0]&&TTCB[1]!=TC[1]) // thuan 01 (1)
		{
			tang_giam=0;
			en_buoc=1;
		}
		if(TTCB[0]!=TC[0]&&TTCB[1]==TC[1]) // nghich 10
		{
			tang_giam=1;
			en_buoc=10;
		}
	}
	else
	if (en_buoc==1) // thuan
	{
		if(TTCB[0]==TC[0]&&TTCB[1]==TC[1]) // thuan 00 (2)
		{
			en_buoc=2;
		}
		if(TTCB[0]!=TC[0]&&TTCB[1]!=TC[1]) // khong phu hop 11
		{
			//if(tang_giam==0)
			en_buoc=0;
		}
		if(TTCB[0]!=TC[0]&&TTCB[1]==TC[1]) // khong phu hop 10
		{
			if(tang_giam==0)
			{
				en_buoc=0;
			}
			else
			{
				en_buoc=2;
			}
		}
	}
	else
	if (en_buoc==2)
	{
		if(TTCB[0]!=TC[0]&&TTCB[1]==TC[1]) // thuan 10
		{
			en_buoc=3;
		}
		if(TTCB[0]!=TC[0]&&TTCB[1]!=TC[1]) // khong phu hop
		{
			//if(tang_giam==1)
			en_buoc=0;
		}
		if(TTCB[0]==TC[0]&&TTCB[1]!=TC[1]) // nghich 01 (1)
		{
			en_buoc=1;
		}
	}
	else
	if (en_buoc==3)
	{
		if(TTCB[0]!=TC[0]&&TTCB[1]!=TC[1]) // hoan thanh mot vong 11
		{
			en_buoc=0;
			so[so_dem_t]++;
			if (so[so_dem_t]>so_max)
			{
				so[so_dem_t]=0;
			}
			tang_giam=1;
		}
		if(TTCB[0]==TC[0]&&TTCB[1]==TC[1]) // nghich 00 (2)
		{
			en_buoc=2;
		}
		if(TTCB[0]==TC[0]&&TTCB[1]!=TC[1]) // khong phu hop
		{
			//if(tang_giam==1)
			en_buoc=0;
		}
	}
	else
	
	
	if (en_buoc==10) // nghich
	{
		if(TTCB[0]==TC[0]&&TTCB[1]==TC[1]) // thuan 00 (20)
		{
			en_buoc=20;
		}
		if(TTCB[0]!=TC[0]&&TTCB[1]!=TC[1]) // khong phu hop 11
		{
			//if(tang_giam==0)
			en_buoc=0;
		}
		if(TTCB[0]==TC[0]&&TTCB[1]!=TC[1]) // khong phu hop 01
		{
			if(tang_giam==1)
			{
				en_buoc=0;
			}
			else
			{
				en_buoc=20;
			}
		}
	}
	else
	if (en_buoc==20)
	{
		if(TTCB[0]==TC[0]&&TTCB[1]!=TC[1]) // thuan 01
		{
			en_buoc=30;
		}
		if(TTCB[0]!=TC[0]&&TTCB[1]!=TC[1]) // khong phu hop
		{
			//if(tang_giam==0)
			en_buoc=0;
		}
		if(TTCB[0]!=TC[0]&&TTCB[1]==TC[1]) // nghich 10 (10)
		{
			en_buoc=10;
		}
	}
	else
	if (en_buoc==30)
	{
		if(TTCB[0]!=TC[0]&&TTCB[1]!=TC[1]) // hoan thanh mot vong 11
		{
			en_buoc=0;
			so[so_dem_t]--;
			if (so[so_dem_t]>so_max)
			{
				so[so_dem_t]=so_max;
			}
			tang_giam=1;
		}
		if(TTCB[0]==TC[0]&&TTCB[1]==TC[1]) // nghich 00 (20)
		{
			en_buoc=20;
		}
		if(TTCB[0]!=TC[0]&&TTCB[1]==TC[1]) // khong phu hop
		{
			//if(tang_giam==0)
			en_buoc=0;
		}
	}
	if(TTCB[0]!=TC[0]&&TTCB[1]!=TC[1])
	{
		en_buoc=0;
	}
}

u8 nho_cb1=0;
u8 nho_cb2=0;
void encoder_xu_ly()
{
	if (TTCB[0]!=TC[0])
	{
		if (nho_cb1==0)
		{
			if(TTCB[1]==TC[1])
			{
				so[so_dem_t]++;
				if (so[so_dem_t]>so_max)
				{
					so[so_dem_t]=0;
				}
			}
		}
		nho_cb1=1;
	}
	if (TTCB[0]==TC[0])
	{
		nho_cb1=0;
	}
	
	if (TTCB[1]!=TC[1])
	{
		if (nho_cb2==0)
		{
			if(TTCB[0]==TC[0])
			{
				so[so_dem_t]--;
				if (so[so_dem_t]>so_max)
				{
					so[so_dem_t]=so_max;
				}
			}
		}
		nho_cb2=1;
	}
	if (TTCB[1]==TC[1])
	{
		nho_cb2=0;
	}
}
#endif
#endif

