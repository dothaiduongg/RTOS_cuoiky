#ifndef _rf_c_
#define _rf_c_
#ifndef _dtg_
#define _dtg_
u16 dtg; // bien dem thoi gian
#endif
u8 t_rf[48];
//========================================//========================================
#if F_CPU == 16000000
#define rf155 s#ifdef rf155
#define rf_mi 19
#define rf_z 12#define sync 600
#define rf_lan_quet 40000
#endif

#else
#define rf155
#ifdef rf155
// #define rf_mi 8
// #define rf_z 4
// #define sync 286
#define rf_mi 9
#define rf_z 5
#define sync 300
#define rf_lan_quet 20000
#endif
#endif
u8 tg1=0;
//u8 tg2=0;
//u16 tg3=0;
//u16 tg4=0;
u8 sync_b=0;
u8 rf_st=0; // xac dinh start Bit
u8 vt=0;
u8 rf_loi=1; 
u8 rf_ma[12];
u8 truoc;
#define rf_truoc_dat 8;
//========================================
#ifndef rf_i
#define rf_i dk_bit(PORTD,6)
#define rf_i_d dk_bit(DDRD,6)
#define rf_i_p dk_bit(PIND,6)
#endif
u8 n_rf_i;
char chuoi[16];
u8 rf_giai_ma();
u32 dtg_2=0;
//----------------------------------------
u8 rf_bit_ngan(u8 trf)
{
	if(trf>rf_mi-rf_z&&trf<rf_mi+rf_z)
	{
		trf=1;
	}
	else
	{
		trf=0;
	}
	return trf;
}
//----------------------------------------
u8 rf_bit_dai(u8 trf)
{
	if(trf>rf_mi*3-rf_z*2&&trf<rf_mi*3+rf_z*2)
	{
		trf=1;
	}
	else
	{
		trf=0;
	}
	return trf;
}
//----------------------------------------
void rf_nhan() // nhan tin hieu RF
{
	u8 tgt;
	if(dtg<rf_mi*6)
	{
		tgt=dtg;
		if((rf_bit_dai(tgt)==1)||(rf_bit_ngan(tgt)==1))
		{
			if(rf_st!=0)
			{
				rf_st=2;
				t_rf[vt]=tgt;
				vt++;
			}
			if(tg1>tgt)
			{
				tg1=tgt;
			}
		}
		else
		{
			vt=0;
			rf_loi=1;
		}
		dtg=0;
	}
}
//----------------------------------------u8 rf_chuyen_ma()
{
	u8 i=0;
	u8 j=0;
	rf_loi=0;
	while(i<48)
	{
		if(rf_bit_ngan(t_rf[i])==1&&rf_bit_dai(t_rf[i+1])==1&&rf_bit_ngan(t_rf[i+2])==1&&rf_bit_dai(t_rf[i+3])==1)
		{
			rf_ma[j]=0;
		}
		else
		if(rf_bit_dai(t_rf[i])==1&&rf_bit_ngan(t_rf[i+1])==1&&rf_bit_dai(t_rf[i+2])==1&&rf_bit_ngan(t_rf[i+3])==1)
		{
			rf_ma[j]=1;
		}
		else
		if(rf_bit_ngan(t_rf[i])==1&&rf_bit_dai(t_rf[i+1])==1&&rf_bit_dai(t_rf[i+2])==1&&rf_bit_ngan(t_rf[i+3])==1)
		{
			rf_ma[j]=2;
		}
		else
		{
			rf_loi=1;
			break;
		}
		j++;
		i+=4;
	}
	return rf_loi;
}
//======================================== 
void rf_xoa()
{
	u8 i;
	for (i=0;i<48;i++)
	{
		t_rf[i]=0;
	}
}
//========================================
u8 rf_kt_dc_c(const u8*dc)
{
	u8 i;
	for(i=0;i<8;i++)
	{
		if(rf_ma[i]!=dc[i])
		{
			i=0;break;
		}
	}
	return i;
}
//======================================== 
u8 rf_kt_dc(u8*dc)
{
	u8 i;
	for(i=0;i<8;i++)
	{
		if(rf_ma[i]!=dc[i])
		{
			i=0;break;
		}
	}
	return i;
}
//========================================
u8 rf_kt_lenh_c(const u8*dc)
{
	u8 i;
	for(i=0;i<4;i++)
	{
		if(rf_ma[i+8]!=dc[i])
		{
			i=0;break;
		}
	}
	return i;
}
//========================================
u8 rf_kt_lenh(u8*dc)
{
	u8 i;
	for(i=0;i<4;i++)
	{
		if(rf_ma[i+8]!=dc[i])
		{
			i=0;break;
		}
	}
	return i;
}
//========================================
void rf_nhap_dc(u8*dc)
{
	u8 i;
	for(i=0;i<8;i++)
	{
		dc[i]=rf_ma[i];
	}
}
//----------------------------------------
u8 rf_giai_ma()
{
	u32 i;
	rf_i=0;
	rf_i_d=vao;
	timer1_001();

	//while(1)
	{
		if(dtg_2<1000000)
		dtg_2++;
		tg1=200;
//		tg1=tg2=200;
		//tg3=500;
//		tg4=500;
		rf_st=0;
		vt=0;
		rf_loi=1;
		for(i=0;i<rf_lan_quet;i++)
		{
			//if()
			if(n_rf_i!=rf_i_p)
			{
				n_rf_i=rf_i_p;
				rf_nhan();
				if(vt==48)
				{
					rf_loi=0;
					break;
				}
				if(rf_i_p==1)
				{
					if(dtg>sync-rf_z*7&&dtg<sync+rf_z*7)
					{
						sync_b=1;
						rf_st=1;
						vt=0;
					}
					dtg=0;
				}
			}
		}
		if(rf_loi==0)
		{
			rf_chuyen_ma();
			if(truoc>0&&truoc<4)
			{
				truoc=5;
			}
		}
		else
		{
			if(truoc>0)
			{
				truoc--;
				if(truoc==0)
				{
					rf_xoa();
				}
			}
		}
		return rf_loi;
//		l_toi_xy(1,1);
//		for(i=0;i<12;i++)
//		{
//			sprintf(chuoi,"%d",rf_ma[i]);
//			l_in(chuoi);
//		}
		//		l_in("     ");
		//		l_dl(sync_b+0x30);
		//		sprintf(chuoi,"  %d",tg4);
		//l_toi_xy(1,2);
		//		l_in(chuoi);
		//		l_in("     ");
		//----------------------------------------
//		l_toi_xy(1,2);
		//		for(i=0;i<4;i++)
		//		{
		//sprintf(chuoi,"%02d",rf_ma[i+8]);
		//l_in(chuoi);
		//		}
		//		l_in("     ");
		//		l_dl(loi+0x30);
		//		sync_b=0;
		//		sprintf(chuoi,"  %d",t_rf[1]);
		//l_toi_xy(1,2);
		//		l_in(chuoi);
		//		l_in("     ");
	}
}
//========================================//========================================
#define rf_p_p dk_bit(PORTD,7) // chan phat rf
#define rf_p_p_d dk_bit(DDRD,7)
#define rf_osc 40
#define ft_t_ngan rf_osc*4
#define ft_t_dai rf_osc*12
#define rf_t_s rf_osc*124
void rf_phat_b(u8 dn)
{
	u8 i;
	if(dn==0)
	{
		rf_p_p=1;
		_delay_us(ft_t_ngan);
		rf_p_p=0;
		_delay_us(ft_t_dai);
		rf_p_p=1;
		_delay_us(ft_t_ngan);
		rf_p_p=0;
		_delay_us(ft_t_dai);
	}
	else
	if(dn==1)
	{
		rf_p_p=1;
		_delay_us(ft_t_dai);
		rf_p_p=0;
		_delay_us(ft_t_ngan);
		rf_p_p=1;
		_delay_us(ft_t_dai);
		rf_p_p=0;
		_delay_us(ft_t_ngan);
	}
	else
	if(dn==2)
	{
		rf_p_p=1;
		_delay_us(ft_t_ngan);
		rf_p_p=0;
		_delay_us(ft_t_dai);
		rf_p_p=1;
		_delay_us(ft_t_dai);
		rf_p_p=0;
		_delay_us(ft_t_ngan);
	}
	//rf_p_p=0;
}
//======================================== 
void rf_phat()
{
	u8 i;
	rf_p_p_d=ra;
	TCCR1B=0;
	cam_ngat;
	for(i=0;i<10;i++)
	{
		rf_p_p=1;
		_delay_us(ft_t_ngan);
		rf_p_p=0;
		_delay_us(rf_t_s);
		rf_phat_b(2);
		rf_phat_b(1);
		rf_phat_b(2);
		rf_phat_b(0);
		rf_phat_b(0);
		rf_phat_b(2);
		rf_phat_b(1);
		rf_phat_b(2);
		rf_phat_b(0);
		rf_phat_b(0);
		rf_phat_b(0);
		rf_phat_b(1);
	}
	rf_p_p=0;
}

//========================================
ISR(TIMER1_COMPA_vect) // Vec to ngat timer1
{
	if(dtg<50000)
	dtg++;
// 	if(dtg_2<100000000)
// 	dtg_2++;
}


#endif