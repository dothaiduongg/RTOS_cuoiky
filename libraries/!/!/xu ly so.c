#ifndef _xu_ly_so
#define _xu_ly_so 
//=======================================


//=======================================
int8 make832(u32 du_lieu, int8 vi_tri)
{
	if(vi_tri==1)
	{
		du_lieu=(du_lieu>>8);
	}
	if(vi_tri==2)
	{
		du_lieu=(du_lieu>>16);
	}
	if(vi_tri==3)
	{
		du_lieu=(du_lieu>>24);
	}
	vi_tri=(unsigned char)(du_lieu & 0xFF);
	return (vi_tri);
}
//========================================
u32 make32(u8 b0,u8 b1,u8 b2, u8 b3)
{
	u32 kq=(u32)b3;
	kq<<=8;
	kq|=(u32)b2;
	kq<<=8;
	kq|=(u32)b1;
	kq<<=8;
	kq|=(u32)b0;
	kq<<=8;
	return kq;
}
//======================================== 
u16 chia_10(u16 so_bi_chia)
{
	u16 thuong;
	thuong= so_bi_chia/10;
	if(so_bi_chia%10>=5)
	{
		thuong++; 
	}
	return thuong;
}
//======================================== 
u16 ms10_s(u16 ms)
{
	return ms/10%60;
}
u16 ms10_m(u16 ms)
{
	return ms/10/60%60;
}
#endif