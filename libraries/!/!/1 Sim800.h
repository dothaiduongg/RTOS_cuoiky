#ifndef _sim800_h_
#define _sim800_h_
#include <!/! LDN.h>
#include "!/1 Chuoi.h"
#define cup_may "ATH"
#define tra_loi "ATA"
#define co_goi_den 2
#define ket_thuc_goi 10
#define co_tin_nhan 4
#define doc_tin 5
#define doc_so_goi_toi 6
#define co_dtmf 7

#define bat_dtmf "AT+DDET=1,0,0,0"
#define truyen_dtmf7 "AT+VTS=7"
#define truyen_dtmf9 "AT+VTS=9"
#define xoa_tn1 "AT+CMGD=1"
#define xoa_tn "AT+CMGD="
#define doc_tin_nhan1 "AT+CMGR=1"
#define dinh_dang_sms_text "AT+CMGF=1" 
#define co_tin_nhan_toi "+CMTI: "
#define xem_thong_tin_goi_den "AT+CLCC=1"
#define xuong_dong[2]={0x0d,0x0a};
#define rs_sim rs=0; rs_d=ra; delay_ms(10); rs_d=vao; rs=1
#define ma_so_goi_toi "+CLCC: "
u8 so_dien_thoai[80];
u8 noi_dung_tin_nhan[20];
u8 tin_nhan_so=0;
u8 ma_dtmf;

void tre_wd_100ms(u16 tre)
{
	u16 i;
	for(i=0;i<tre;i++)
	{
		delay_ms(100);
		//wdt_enable(WDTO_2S);
	}
}
//#define cuoc goi den so dien thoai "+CLCC: 1,1,0,0,0,"01693825006",129,"""
void at_wd(char *s,u16 tre)
{
	uart_puts(s);
	uart_puts("\n");
	tre_wd_100ms(tre);
}
//======================================== 
void xoa_sms(u8 so_tn)
{
	u8 i;
	u8 c[10];
	u8 c2[2];
	for (i=1;i<=so_tn;i++)
	{
		c2[0]=i+0x30;
		c2[1]=0;
		gan_chuoi(c,xoa_tn);
		noi_chuoi(c,c2);
		at_wd(c,3);
	}
}
//========================================
void gui_tin_nhan(const char *so,const char *tin)
{
	at_wd("AT+CMGF=1",10);
	uart_puts("AT+CMGS=\"");
	uart_puts(so);
	at_wd("\"",10);
	
	
 	//at("AT+CMGS=\"841292726419\"",1000);
	//delay_ms(1000);
	//wdt_reset();
	//delay_ms(1000);
	//uart_puts("\n\r");
	//at("\"",2000);
	uart_puts(tin);
	uart_putc(26);
	//at("AT+CMGS=\"" + SDT+"\"",2000);
	//at("Hshop test sim",1000);
	//sim808.write(26);     // ctlrZ
	
// 	at("AT+CMGF=1",1000);
// 	//at("AT+CSCS=\"GSM\"",1000);
// 	uart_puts("AT+CMGS=");
// 	uart_puts(so);
// 	delay_ms(1000);
// 	wdt_reset();
// 	delay_ms(1000);
// 	uart_puts("\n\r");
// 	//at("\"",2000);
// 	uart_puts(tin);
// 	uart_putc(26);
// 	//at("AT+CMGS=\"" + SDT+"\"",2000);
// 	//at("Hshop test sim",1000);
// 	//sim808.write(26);     // ctlrZ
}
//======================================== 
void tach_noi_dung_tin_nhan(char *noi_dung,const char *tin_nhan)
{
	u8 a;
	u8 vi_tri;
	u8 b[2]={0x0a,0};
	a=strlen(tin_nhan);
	if(a>20)
	{
		tin_nhan+=20;
		a=strlen(tin_nhan);
		vi_tri=chuoi_trong_chuoi(tin_nhan,b);
		if(vi_tri>0)
		{
			tach_chuoi(noi_dung,tin_nhan,vi_tri+1,a);
			strcpy(tin_nhan,noi_dung);
			vi_tri=chuoi_trong_chuoi(tin_nhan,b);
			if(vi_tri>0)
			{
				tach_chuoi(noi_dung,tin_nhan,0,vi_tri-1);
				noi_dung[vi_tri-1]=0;
			}
		}
		else
		{
			a=0;
		}
	}
	if(a==0)
		strcpy(noi_dung,"");
}
//========================================
void tach_so_nhan_toi(char *so,const char *ma)
{
	u8 a;
	u8 vi_tri;
	u8 b[2]={'"',0};
	a=strlen(ma);
	if(a>10)
	{
		ma+=10;
		a=strlen(ma);
		while(a>5)
		{
			a=strlen(ma);
			if(ma[0]=='"'&&ma[1]==','&&ma[2]=='"')
			{
				ma+=3;
				vi_tri=chuoi_trong_chuoi(ma,b);
				if(vi_tri>0)
				{
					tach_chuoi(so,ma,0,vi_tri);
					so[vi_tri]=0;
				}
				break;
			}
			ma++;
		}
		if(a<5)
		{
			a=0;
		}
	}
	if(a==0)
	strcpy(so,"");
}
//======================================== 
void tach_so_goi_toi(char *so,const char *ma)
{
	u8 a;
	u8 vi_tri;
	u8 b[2]={'"',0};
	a=strlen(ma);
	if(a>15)
	{
		ma+=15;
		a=strlen(ma);
		vi_tri=chuoi_trong_chuoi(ma,b);
		if(vi_tri>0)
		{
			tach_chuoi(so,ma,vi_tri+1,a);
			strcpy(ma,so);
			vi_tri=chuoi_trong_chuoi(ma,b);
			if(vi_tri>0) 
			{
				tach_chuoi(so,ma,0,vi_tri);
				so[vi_tri]=0;
			}
		}
		else
		{
			a=0;
		}
	}
	if(a==0)
	strcpy(so,"");
}
//========================================
void khoi_tao_sim()
{
	rs_sim;
	#ifndef mo_phog
	tre_wd_100ms(200);
	#endif
	at_wd("AT",10);
	wdt_reset();
	at_wd("AT",10);
	wdt_reset();
	at_wd("AT",10);
	wdt_reset();
	at_wd(bat_dtmf,8);
	//at(truyen_dtmf7,800);
	wdt_reset();
	at_wd(dinh_dang_sms_text,8);
	wdt_reset();
	at_wd(xem_thong_tin_goi_den,8);
	wdt_reset();
	xoa_sms(5);
}
//========================================
void goi_dien_khong_cup(const char *so)
{
	at_wd("AT",15);
	uart_puts("ATD");
	uart_puts(so);
	at_wd(";",1);
}
//======================================== 
void goi_dien_cup()
{
	at_wd("ATH",15);
}
//======================================== 
void goi_dien(const char *so)
{
  at_wd("AT",15);
  uart_puts("ATD");
  uart_puts(so);
  at_wd(";",500);
  at_wd("ATH",15);
}
void goi_dien_tg(const char *so,u16 tg_giay)
{
	at_wd("AT",10);
	uart_puts("ATD");
	uart_puts(so);
	at_wd(";",tg_giay*10);
	at_wd("ATH",10);
}
#endif
