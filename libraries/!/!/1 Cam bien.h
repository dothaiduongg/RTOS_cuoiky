#ifndef _cam_bien_h_
#define _cam_bien_h_
#include <!/! LDN.h>
#ifndef SO_CB // so cam bien bao gom ca nut reset
	#define SO_CB 2
	# warning "SO_CB Can dinh nghia cho biet so cam bien ngo vao dang su dung mac dinh la 2"
#endif
#ifndef tg_ton_tai_md // so cam bien bao gom ca nut reset
#define tg_ton_tai_md 5
#endif
#ifndef tg_cho_md // so cam bien bao gom ca nut reset
#define tg_cho_md 5
#endif


//#define SO_CB 5
u8 CBMKD=1; // cam bien moi khoi dong
u8 TC[SO_CB+1]; // tich cuc
//u8 KTC[SO_CB+1];
u16 TGKTCD[SO_CB+1]; // thoi gian khong tích cực đăt
u16 TGTCD[SO_CB+1]; // thoi gian tich cực đặt
u16 TGDCB[SO_CB+1]; // thoi gian dem thuc cho cam bien
u8 TTCB[SO_CB+1];
u8 TTCBT[SO_CB+1];
//======================================== 
void DTC(u8 CB)
{
	if (TTCBT[CB]==TC[CB])
	{
		TGDCB[CB]=0;
	}
	else
	{
		if (TGDCB[CB]>TGKTCD[CB])
		{
			TTCB[CB]=!TC[CB];
			TGDCB[CB]=0;
		}
	}
}
//======================================== 
void CTC(u8 CB)
{
	if (TTCBT[CB]!=TC[CB])
	{
		TGDCB[CB]=0;
	}
	else
	{
		if (TGDCB[CB]>TGTCD[CB])
		{
			TTCB[CB]=TC[CB];
			TGDCB[CB]=0;
		}
	}
}
//======================================== 
void DOC_CB(u8 CB)
{
	TGDCB[CB]++;
	if (TTCB[CB]==TC[CB])
	{
		DTC(CB);
	}
	else
	{
		CTC(CB);
	}
}
//========================================
void doc_cam_bien()
{
	if (CBMKD==1)
	{
		CBMKD=0;
		u8 i;
		cb1_d=vao;
		#if SO_CB>1
		cb2_d=vao;
		#if SO_CB>2
		cb3_d=vao;
		#if SO_CB>3
		cb4_d=vao;
		#if SO_CB>4
		cb5_d=vao;
		#if SO_CB>5
		cb6_d=vao;
		#if SO_CB>6
		cb7_d=vao;
		#if SO_CB>7
		cb8_d=vao;
		#endif
		#endif
		#endif
		#endif
		#endif
		#endif
		#endif
		for(i=0;i<SO_CB;i++)
		{
			TC[i]=0; // trang thai cam bien tich cuc khoi tao la 0
			//KTC[i]=1;
			TTCB[i]=TTCBT[i]=!TC[i];
			TGDCB[i]=0;
			TGKTCD[i]=tg_cho_md;
			TGTCD[i]=tg_ton_tai_md; // thoi gian ton tai cam bien
		}
		TGKTCD[SO_CB]=5;
		TGTCD[SO_CB]=5; // thoi gian ton tai cam bien
	}
	TTCBT[SO_CB]=crs;
	DOC_CB(SO_CB);
	TTCBT[0]=cb1; // trang thai cam bien thuc
	DOC_CB(0);
	#if SO_CB>1
	TTCBT[1]=cb2;
	DOC_CB(1);
	#if SO_CB>2
	TTCBT[2]=cb3;
	DOC_CB(2);
	#if SO_CB>3
	TTCBT[3]=cb4;
	DOC_CB(3);
	#if SO_CB>4
	TTCBT[4]=cb5;
	DOC_CB(4);
	#if SO_CB>5
	TTCBT[5]=cb6;
	DOC_CB(5);
	#if SO_CB>6
	TTCBT[6]=cb7;
	DOC_CB(6);
	#if SO_CB>7
	TTCBT[7]=cb8;
	DOC_CB(7);
	#endif
	#endif
	#endif
	#endif
	#endif
	#endif
	#endif
}
#endif
