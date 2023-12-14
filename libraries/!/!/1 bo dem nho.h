#ifndef _bo_dem_h_
#define _bo_dem_h_
#include <!/! LDN.h>
#ifndef so_so
#define so_so 6
#endif
#ifndef l1
	#ifndef bo_v12 
	#define bo_v12
	#define l1 dk_bit(PORTD,2)
	#define l1_d dk_bit(DDRD,2)
	#define l2 dk_bit(PORTD,3)
	#define l2_d dk_bit(DDRD,3)
	#define l3 dk_bit(PORTD,4)
	#define l3_d dk_bit(DDRD,4)
	#define l4 dk_bit(PORTB,6)
	#define l4_d dk_bit(DDRB,6)
	#define l5 dk_bit(PORTB,7)
	#define l5_d dk_bit(DDRB,7)
	#define l6 dk_bit(PORTD,5)
	#define l6_d dk_bit(DDRD,5)
	
	
	#define la dk_bit(PORTB,1)
	#define la_d dk_bit(DDRB,1)
	#define lb dk_bit(PORTB,2)
	#define lb_d dk_bit(DDRB,2)
	#define lc dk_bit(PORTB,3)
	#define lc_d dk_bit(DDRB,3)
	#define ld dk_bit(PORTB,4)
	#define ld_d dk_bit(DDRB,4)
	#define le dk_bit(PORTB,5)
	#define le_d dk_bit(DDRB,5)
	#define lf dk_bit(PORTD,7)
	#define lf_d dk_bit(DDRD,7)
	#define lg dk_bit(PORTD,6)
	#define lg_d dk_bit(DDRD,6)
	#define lh dk_bit(PORTB,0)
	#define lh_d dk_bit(DDRB,0)
	
	#define cb1 dk_bit(PINC,0)
	#define cb1_d dk_bit(DDRC,0)
	#define cb2 dk_bit(PINC,1)
	#define cb2_d dk_bit(DDRC,1)
	#define cb3 dk_bit(PINC,2)
	#define cb3_d dk_bit(DDRC,2)
	
	
	#define nn1 dk_bit(PIND,0)
	#define nn1_d dk_bit(DDRD,0)
	#define nn2 dk_bit(PINC,5)
	#define nn2_d dk_bit(DDRC,5)
	#define nn3 dk_bit(PINC,4)
	#define nn3_d dk_bit(DDRC,4)
	#define nn4 dk_bit(PINC,3)
	#define nn4_d dk_bit(DDRC,3)
	
	#define dem_out dk_bit(PORTD,1)
	#define dem_out_d dk_bit(DDRD,1)
	#endif
#endif
u8 ngat_t0_10 = 0;
u8 lan_ngat_t0 = 0;
#include <!/1 7 doan.h>

void khoi_tao_dem()
{
	#if so_so <= 3
	l1_d=l2_d=l3_d=ra;
	#endif
	#if so_cb >=2
	cb2_d=vao;
	#endif
	#if so_cb >=1
	cb1_d=vao;
	#endif
	//l1_d=l2_d=l3_d=l4_d=l5_d=l6_d=ra; 
	//cb1_d=cb2_d=cb3_d=vao;
}
void quet_led_t0()
{
	lan_ngat_t0++;
	if(lan_ngat_t0>=10)
	{
		lan_ngat_t0=0;
		ngat_t0_10=1;
	}
	TCNT0=-30;
	lan_quet++;
	if (lan_quet>=so_so*2)
	{
		lan_quet=0;
	}
	//l1=l2=l3=l4=l5=0;
	if(lan_quet%2==1)
	{
		#if so_so<=3
		l1=l2=l3=0;
		#else
		l1=l2=l3=l4=0;//l5=0;//=l5=l6=0;
		#endif
		
		TCNT0=-20;
		//lan_ngat=1;
	}
	else
	{
		xuat_7_(mang7[lan_quet/2]);
		switch (lan_quet/2)
		{
			#if so_so <= 3
			case 0:
			l1=1;break;
			case 1:
			l2=1; break;
			case 2:
			l3=1;break;
			#endif
//			case 3:
			
// 			l4=1;break;
// 			case 4:
// 			l5=1;break;//;du_13_ms=1;break;
		}
	}
}


#define tg_on_ss 100



#endif
