#ifndef _cam_bien_c_
#define _cam_bien_c_
#include <!/! LDN.h>
u16 cn1;
u8 ncb1;
void doc_cb1()
{
	ncb1=cb1;
	if(ncb1==0&&cn1<100)
	{ 
		cn1++;
		ncb1=1;
	}
	else
	{
		if(ncb1==1)
		{
			cn1=0;   
		}
	}
}
//======================================== 
u16 cn2;
u8 ncb2;
void doc_cb2()
{
	ncb2=cb2;
	if(ncb2==0&&cn2<400)
	{ 
		cn2++; 
		ncb2=1;
	}
	else
	{
		if(ncb2==1)
		{
			cn2=0;
		}
	}
}
//========================================
#ifdef cb3
u16 cn3;
u8 nnrs;
void doc_nn()
{
	nnrs=cb3;
	if(nnrs==0&&cn3<800)
	{
		cn3++;
		nnrs=1;
	}
	else 
	{ 
		if(nnrs==1)
		{
			cn3=0;
		}
	}
}
#endif
//======================================== 
u16 sug_en=0;
u16 sug_en_n=0;
u8 ngi=0;
u8 nt=0;
u8 na=0;
u8 nb;
//========================================
void doc_en() // hàm đọc Encoder
{
	if(ncb2==0&&nb==1) // kiem tra canh xuong kenh b
	{
		nb=0;
		if(ncb1==0&&ngi==0) //
		{
			ngi=1;
		}
		if(ncb1==1&&nt==0) //
		{
			nt=1;
		}
	}
	if(ncb2==1&&nb==0) // kiem tra cạnh len kenh b
	{
		nb=1;
		if(ncb1==1&&ngi==0) //
		{
			ngi=1;
		}
		if(ncb1==0&&nt==0) //
		{
			nt=1;
		}
	}
	if(ncb1==0&&na==1) // canh xuong kenh a
	{
		na=0;
		if(ncb2==0&&nt==1) //
		{
			nt=0;
			sug_en++;
			if(sug_en>9999*2)
			{
				sug_en=0;
			}
		}
		if(ncb2==1&&ngi==1) //
		{
			ngi=0;
			sug_en--;
			if(sug_en>9999*2)
			{
				sug_en=9999*2;
			}
		}
	}
	if(ncb1==1&&na==0) // canh len kenh a
	{
		na=1;
		if(ncb2==1&&nt==1) //
		{
			nt=0;
			sug_en++;
			if(sug_en>9999*2)
			{
				sug_en=0;
			}
		}
		if(ncb2==0&&ngi==1) //
		{
			ngi=0;
			sug_en--;
			if(sug_en>9999*2)
			{
				sug_en=9999*2;
			}
		}
	}
	//return so;///2;
}
//========================================
void doc_cam_bien_en()
{
	doc_cb1();
	doc_cb2();
	doc_en();
}
#endif
