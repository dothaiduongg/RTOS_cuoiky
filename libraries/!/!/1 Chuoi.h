#ifndef _chuoi_h_
#define _chuoi_h_
#include <!/! LDN.h>
#include "string.h"
u8 chuoi_trong_chuoi(char * chuoi_lon, const char * chuoi_nho);

void tach_chuoi(char * chuoi_ra, const char * chuoi_vao, size_t dau, size_t cuoi)
{
	strncpy (chuoi_ra,chuoi_vao+dau,cuoi-dau);
}

void gan_chuoi(char * chuoi_ra, const char * chuoi_vao)
{
	strcpy(chuoi_ra,chuoi_vao);
}
void bo_truoc_lay_sau_chuoi(char * chuoi_ra,const char * chuoi_vao,u8 vi_tri_bo)
{
	u8 do_dai=strlen(chuoi_vao);
	strncpy(chuoi_ra,chuoi_vao+vi_tri_bo,do_dai);
}
void cat_chuoi1(char * chuoi_ra,const char * chuoi_vao)
{
	chuoi_ra=strtok(chuoi_vao," ,.-");
}
//======================================== 
u32 tach_so_32_boi_dau(char * chuoi_vao, const char * chuoi_dau)
{
	u8 a,vi_tri;
	char c_n[10];
	a=strlen(chuoi_dau);
	vi_tri=chuoi_trong_chuoi(chuoi_vao,chuoi_dau);
	if (vi_tri==0)
	{
		vi_tri=strlen(chuoi_vao);
	}
	tach_chuoi(c_n,chuoi_vao,0,vi_tri);
	bo_truoc_lay_sau_chuoi(chuoi_vao,chuoi_vao,vi_tri+a-1);
	return atoi(c_n);
}
//========================================

// void tach_chuoi_chuoi(char * chuoi_vao, char * chuoi_ra)
// {
// 	u8 vi_tri;
// 	vi_tri=chuoi_trong_chuoi(chuoi_vao,',');
// 	if (vi_tri==0)
// 	{
// 		vi_tri=strlen(chuoi_vao);
// 	}
// 	tach_chuoi(chuoi_ra,chuoi_vao,0,vi_tri);
// 	bo_truoc_lay_sau_chuoi(chuoi_vao,chuoi_vao,vi_tri);
// }
//======================================== 
void bo_truoc_chuoi_boi_chuoi(char * chuoi_vao, const char * chuoi_dau)
{
	u8 a,vi_tri;
	a=strlen(chuoi_dau);
	vi_tri=chuoi_trong_chuoi(chuoi_vao,chuoi_dau);
	if (vi_tri==0)
	{
		vi_tri=strlen(chuoi_vao);
	}
	bo_truoc_lay_sau_chuoi(chuoi_vao,chuoi_vao,vi_tri+a-1);
}
//======================================== 
u8 chuoi_trong_chuoi(char * chuoi_lon, const char * chuoi_nho)
{
	u8 a;
	u8 i=0;
	u8 kq=1;
	u8 kq2=0; 
	a=strlen(chuoi_nho);
	while (*chuoi_lon)
	{
		if(*chuoi_lon==chuoi_nho[i])
		{
			i++;
			kq2++;
		}
		else
		{
			i=0;kq++;
			kq=kq+kq2;
		}
		if(i==a) break;
		chuoi_lon++;
		
	}
	if(i!=a)
	{
		kq=0;
	}
	return kq;
}
//======================================== 
u8 dem_ky_tu_trong_chuoi(char * chuoi_lon, const char ky_tu)
{
	//u8 kq=0;
	//u8 i=0;
	//while (chuoi_lon[i]!=0)
	//{
		//if (chuoi_lon[i]==ky_tu)
		//{
			//kq++;
		//}
		//i++;
	//}
	//return kq;
	u8 kq=0;
	while (*chuoi_lon)
	{
		if(*chuoi_lon==ky_tu)
		{
			kq++;
		}
		chuoi_lon++;
	}
	return kq;
}
//======================================== 
void noi_chuoi(char * chuoi_ra,const char * chuoi_vao)
{
	strcat(chuoi_ra,chuoi_vao);
}

#endif
