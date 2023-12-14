void truyen(void);
u8 mang7_2[6];
bool co=0; // co giu lieu nhan duoc
//u8 a;
u8 lenh;
u8 cho_truen=0;
u16 tg_truen;
#define tg_truen_dat 1000
#if so_so<5
u16 so_dat_tam;
u16 so_dat_nhan;
u16 so_dem_tam;
#endif
#if so_so==5
u32 so_dat_tam;
u32 so_dat_nhan;
u32 so_dem_tam;
#endif
#ifndef kog_dat
void nhap_so_dat()
{
	so_dat_tam=ci_tu_so(dl_nhan[so_khug*10-15]);
	so_dat_tam*=10000;
	so_dat_nhan=ci_tu_so(dl_nhan[so_khug*10-14]);
	so_dat_nhan*=1000;
	so_dat_tam+=so_dat_nhan;
	so_dat_nhan=ci_tu_so(dl_nhan[so_khug*10-13]);
	so_dat_nhan*=100;
	so_dat_tam+=so_dat_nhan;
	so_dat_nhan=ci_tu_so(dl_nhan[so_khug*10-12]);
	so_dat_nhan*=10;
	so_dat_tam+=so_dat_nhan;
	so_dat_nhan=ci_tu_so(dl_nhan[so_khug*10-11]);
	so_dat_tam+=so_dat_nhan;
	so_dat=so_dat_tam;
	quet_led(so_dem);
	chuen_doi_truen(so_dem);
	truyen_v10();
}
void nhap_so_dem()
{
	so_dem_tam=ci_tu_so(dl_nhan[so_khug*10-15]);
	so_dem_tam*=10000;
	so_dat_nhan=ci_tu_so(dl_nhan[so_khug*10-14]);
	so_dat_nhan*=1000;
	so_dem_tam+=so_dat_nhan;
	so_dat_nhan=ci_tu_so(dl_nhan[so_khug*10-13]);
	so_dat_nhan*=100;
	so_dem_tam+=so_dat_nhan;
	so_dat_nhan=ci_tu_so(dl_nhan[so_khug*10-12]);
	so_dat_nhan*=10;
	so_dem_tam+=so_dat_nhan;
	so_dat_nhan=ci_tu_so(dl_nhan[so_khug*10-11]);
	so_dem_tam+=so_dat_nhan;
	so_dem=so_dem_tam;
	//quet_led(so_dem);
	//chuen_doi_truen(so_dem);
	//truyen_v10();
}
#endif
u8 doc232()
{
	#define dinh_vi 18
	u8 ok=0;
	u8 a=0;u8 c=0; u8 d=0;
	u8 i;
	lenh=0;
	//if(doc_rs232()==1)
	{
		for (i=0;i<10;i++)
		{
			a=a^mang_dl_232[i]; // #define tg_out_232 700 #define uart
		}
		for (i=10;i<20;i++)
		{
			c=c^mang_dl_232[i];
		}
		for (i=20;i<32;i++)
		{
			d=d^mang_dl_232[i];
		}
		//if(a==mang_dl_232[dinh_vi+14]&&c==mang_dl_232[dinh_vi+15]&&d==mang_dl_232[dinh_vi+16])
		if((mang_dl_232[0]=='l')&&(mang_dl_232[1]=='d')&&(mang_dl_232[2]=='n'))
		{
// 			a=make16(mang_dl_232[2],mang_dl_232[3])/60;
// 			a=make16(mang_dl_232[4],mang_dl_232[5]);
// 			a=make16(mang_dl_232[6],mang_dl_232[7]);
// 			a=make16(mang_dl_232[8],mang_dl_232[9]);
// 			a=make16(mang_dl_232[10],mang_dl_232[11]);
// 			a=make16(mang_dl_232[12],mang_dl_232[13]); 
// 			a=make16(mang_dl_232[14],mang_dl_232[15]);
// 			a=make16(mang_dl_232[16],mang_dl_232[17]);
// 			if(mang_dl_232[3]=='0'||mang_dl_232[3]=='1'||mang_dl_232[3]=='2'||mang_dl_232[3]=='3'||mang_dl_232[3]=='4'||
// 			mang_dl_232[3]=='5'||mang_dl_232[3]=='6'||mang_dl_232[3]=='7'||mang_dl_232[3]=='8'||mang_dl_232[3]=='9')
// 			{
// 				mang_dat_tam[4]=mang_dat_tam[3];
// 				mang_dat_tam[3]=mang_dat_tam[2];
// 				mang_dat_tam[2]=mang_dat_tam[1];
// 				mang_dat_tam[1]=mang_dat_tam[0];
// 				mang_dat_tam[0]=mang_dl_232[3];
// 				so_dat_nhan=(mang_dat_tam[4]-0x30);//*10000;
// 				so_dat_nhan*=10000;
// 				so_dat_nhan+=(mang_dat_tam[3]-0x30)*1000;
// 				so_dat_nhan+=(mang_dat_tam[2]-0x30)*100; 
// 				so_dat_nhan+=(mang_dat_tam[1]-0x30)*10;
// 				so_dat_nhan+=(mang_dat_tam[0]-0x30);
// 				so_dat_tam=so_dat_nhan;
// 			}
// 			else
			{
				lenh=mang_dl_232[3];
			}
			if(mang_dl_232[3]=='e')
			{
				//so_dat=so_dat_tam;
			}
			if(mang_dl_232[3]=='s')
			{
				so_dat_tam=0;
// 				mang_dat_tam[4]=0x30;
// 				mang_dat_tam[3]=0x30;
// 				mang_dat_tam[2]=0x30;
// 				mang_dat_tam[1]=0x30;
// 				mang_dat_tam[0]=0x30;
			}
			//mang7_2[4]=(ma7doan[so_dat_tam/10000%10]);
			//mang7_2[3]=(ma7doan[so_dat_tam/1000%10]);
			//mang7_2[2]=(ma7doan[so_dat_tam/100%10]);
			//mang7_2[1]=(ma7doan[so_dat_tam/10%10]);
			//mang7_2[0]=(ma7doan[so_dat_tam/1%10]);
			truyen();
			tg_luu=tg_luu_dat;
			luu=0;
			so_dat=so_dat_tam;
			//mang7_2[1]=mang_dl_232[dinh_vi+1];
			//mang7_2[2]=mang_dl_232[dinh_vi+2];
			//mang7_2[3]=mang_dl_232[dinh_vi+3];
			//mang7_2[4]=mang_dl_232[dinh_vi+4];
			//mang7_2[5]=mang_dl_232[dinh_vi+5];
// 			a=mang_dl_232[dinh_vi+6];
// 			a|=mang_dl_232[dinh_vi+7];
// 			a=make16(mang_dl_232[dinh_vi+8],mang_dl_232[dinh_vi+9]);
// 			a=make16(mang_dl_232[dinh_vi+10],mang_dl_232[dinh_vi+11]);
// 			a=make16(mang_dl_232[dinh_vi+12],mang_dl_232[dinh_vi+13]);
		}
		u8 i;
		for (i=0;i<20;i++)
		{
			mang_dl_232[i]=0;
		}
		ok=1;

		
	}
	return ok;
}

void truyen()
{
	//delay_ms(5);
	u8 a=0;u8 c=0;u8 d=0;
	u8 b;
	b='n';
	uart_putc_u(b); // 1
	a=a^b;
	b='d';
	uart_putc_u(b); // 2
	a=a^b;
	b=(1);
	uart_putc_u(b); // 3
	a=a^b;
	b=(1);
	uart_putc_u(b); // 4
	a=a^b;
	b=(1);
	uart_putc_u(b); // 5
	a=a^b;
	b=(1);
	uart_putc_u(b); // 6
	a=a^b;
	b=(1);
	uart_putc_u(b); // 7
	a=a^b;
	b=(1);
	uart_putc_u(b); // 8
	a=a^b;
	b=(1);
	uart_putc_u(b);
	a=a^b; //9
	b=(1);
	uart_putc_u(b);
	a=a^b; // 10
	b=(1);
	uart_putc_u(b);
	c=c^b; // 11
	b=(1);
	uart_putc_u(b); // 12
	c=c^b;
	b=(1);
	uart_putc_u(b); // 13
	c=c^b;
	b=(1);
	uart_putc_u(b);  // 14
	c=c^b;
	b=(1);
	uart_putc_u(b); // 15
	c=c^b;
	b=(1);
	uart_putc_u(b); // 16
	c=c^b;
	b=(1);
	uart_putc_u(b); // 17
	c=c^b;
	b=(1);
	uart_putc_u(b); // 18
	c=c^b;
	b=(mang7_2[0]);
	uart_putc_u(b); // 19
	c=c^b;
	b=(mang7_2[1]);
	uart_putc_u(b); // 20
	c=c^b;
	b=(mang7_2[2]);
	uart_putc_u(b); // 21
	d=d^b;
	b=(mang7_2[3]);
	uart_putc_u(b); // 22
	d=d^b;
	b=(mang7_2[4]);
	uart_putc_u(b); // 23
	d=d^b;
	b=(mang7_2[5]);
	uart_putc_u(b); // 24
	d=d^b;
	b=(mang7_2[6]);
	uart_putc_u(b); // 25
	d=d^b;
	b=(1);
	uart_putc_u(b); // 26
	d=d^b;
	b=(1);
	uart_putc_u(b); // 27
	d=d^b;
	b=(1);
	uart_putc_u(b); // 28
	d=d^b;
	b=(1);
	uart_putc_u(b); // 29
	d=d^b;
	b=(1);
	uart_putc_u(b); // 30
	d=d^b;
	b=(1);
	uart_putc_u(b); // 31
	d=d^b;
	b=(1);
	uart_putc_u(b); // 32
	d=d^b;
	uart_putc_u(a); // 33
	uart_putc_u(c); // 34
	uart_putc_u(d); // 35
	uart_putc_u('e'); //36
}
//========================================
void che_do_dat_id()
{
	u8 ok=0;
	u8 i;
	while(ok==0)
	{
		if(nhan_v10()==1)
		{
			truyen_v10();
			if(leh==1)
			{
				for(i=0;i<10;i++)
				{
					id[i]=dl_nhan[i];
				}
				luu_e_id();
			}
			ok=1;
		}
	}
}
//= 

void khoi_tao_cet_noi_pc()
{
	u8 i;
	uart_init(38400);
	for (i=0;i<so_khug*10;i++)
	{
		dl_truen[i]='0';
	}
	if(n_rs==0)
	{
		mo=0;
//		quet_led(0);
//		delay_ms(500);
		quet_led(12345);
//		delay_ms(500);
//		quet_led(22222);
//		delay_ms(500);
		che_do_dat_id();
		quet_led(67890);
//		delay_ms(500);
//		quet_led(44444);
//		delay_ms(500);
//		quet_led(55555);
		delay_ms(500);
	}
}
//========================================
void chuen_doi_truen(u32 so)
{
	u8 i; 
	for(i=0;i<10;i++)
	{
		dl_truen[i]=id[i];
	}
	dl_truen[15]=((so/10000%10)+0x30);
	dl_truen[16]=((so/1000%10)+0x30);
	dl_truen[17]=((so/100%10)+0x30);
	dl_truen[18]=((so/10%10)+0x30);
	dl_truen[19]=((so/1%10)+0x30);
	
	dl_truen[25]=((so_dat_tam/10000%10)+0x30);
	dl_truen[26]=((so_dat_tam/1000%10)+0x30);
	dl_truen[27]=((so_dat_tam/100%10)+0x30);
	dl_truen[28]=((so_dat_tam/10%10)+0x30);
	dl_truen[29]=((so_dat_tam/1%10)+0x30);
}

u8 so_sah_id()
{
	u8 i;
	u8 kq=1;
	for (i=0;i<10;i++)
	{
		if(id[i]!=dl_nhan[i])kq=0;
	}
	return kq;
}