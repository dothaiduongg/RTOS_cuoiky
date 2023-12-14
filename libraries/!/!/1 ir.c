#ifndef _ir_c_
#define _ir_c_
#ifndef _dtg_
#define _dtg_
u16 dtg; // bien dem thoi gian
#endif
u8 t_rf[48];
//========================================//========================================
#if F_CPU == 16000000
#define ir_sony_1#ifdef ir_sony_1
#define ir_mi 75
#define ir_z 30#define ir_tg_start_b 300
#define ir_lan_quet 100000
#endif

#else
#define rf155
#ifdef rf155
// #define rf_mi 8
// #define rf_z 4
// #define sync 286
#define rf_mi 9
#define rf_z 10
#define sync 300
#define rf_lan_quet 20000
#endif
#endif
//u8 tg2=0;
//u16 tg3=0;
//u16 tg4=0;
#define rf_truoc_dat 8;
//========================================
#ifndef ir_i
#define ir_i dk_bit(PORTB,0)
#define ir_i_d dk_bit(DDRB,0)
#define ir_i_p dk_bit(PINB,0)
u8 n_ir_i;
#endif
u8 start_b=0;
u8 n_rf_i;
char chuoi[16];
u8 ir_giai_ma();
u8 ir_ad=0;
u8 ir_co=0;
//----------------------------------------
u8 ir_bit_ngan(u8 trf)
{
	if(trf>ir_mi-rf_z&&trf<ir_mi+rf_z)
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
u8 ir_bit_dai(u8 trf)
{
	if(trf>ir_mi*2-rf_z*2&&trf<ir_mi*2+rf_z*2)
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
void ir_nhan()
{
	u8 tgt;
	if(dtg<ir_tg_start_b-ir_z)
	{
		tgt=dtg;
		if((ir_bit_dai(tgt)==1)||(ir_bit_ngan(tgt)==1))
		{
			if(st!=0)
			{
				st=2;
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
	else
	if(dtg>ir_tg_start_b+ir_z)
	{
		{
			vt=0;
			rf_loi=1;
		}
		dtg=0;
	}
}
//----------------------------------------u8 ir_chuyen_ma()
{
	u8 i=1;
	u8 j=0;
	rf_loi=0;
	while(i<=25)
	{
		if(ir_bit_ngan(t_rf[0])==1)
		if(ir_bit_ngan(t_rf[i])==1&&ir_bit_ngan(t_rf[i+1])==1)
		{
			rf_ma[j]=0;
		}
		else
		if(ir_bit_dai(t_rf[i])==1&&ir_bit_ngan(t_rf[i+1])==1)
		{
			rf_ma[j]=1;
		}	
		else
		{
			rf_loi=1;
			break;
		}
		j++;
		i+=2;
	}
	ir_ad=0;
	for(i=0;i<5;i++)
	{
		ir_ad|=rf_ma[i+7]<<i;
	}
	ir_co=0;
	for(i=0;i<7;i++)
	{
		ir_co|=rf_ma[i]<<i;
	}
	
	return rf_loi;
}
//======================================== 
void ir_xoa()
{
	u8 i;
	for (i=0;i<25;i++)
	{
		t_rf[i]=0;
	}
}
//======================================== 
u8 ir_kt_dc(u8*dc)
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
u8 ir_kt_lenh(u8*dc)
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
//----------------------------------------
u8 ir_giai_ma()
{
	ir_i=0;
	ir_i_d=vao;
	timer1_001();
	u8 tg1=0;
	u8 tg2=0;
	u16 tg_st=0;
	u32 i;
	{
		tg1=tg2=200;
		tg_st=1000;
		st=0;
		vt=0;
		rf_loi=1;
		for(i=0;i<ir_lan_quet;i++)
		{
			if(n_ir_i!=ir_i_p)
			{
				n_ir_i=ir_i_p;
				ir_nhan();
				if(vt==24)
				{
					rf_loi=0;
					break;
				}
// 				if(ir_i_p==0)
// 				{
// // 					if(dtg>ir_tg_start_b-ir_z*10&&dtg<ir_tg_start_b+ir_z*10)
// // 					{
// // 						start_b=1;
// // 						st=1;
// // 						vt=0;
// // 						tg_st=dtg;
// // 					}
// 					if(tg1>dtg)
// 					{
// 						tg1=dtg;
// 					}
// 					dtg=0;
// 				}
				if(ir_i_p==1)
				{
					if(dtg>ir_tg_start_b-ir_z&&dtg<ir_tg_start_b+ir_z)
					{
						start_b=1;
						st=1;
						vt=0;
						tg_st=dtg;
					}
					dtg=0;
				}
			}
		}
// 		l_toi_xy(13,1);
// 		sprintf(chuoi," %02d ",rf_loi);
// 		l_in(chuoi);			
		if(rf_loi==0)
		{
			ir_chuyen_ma();
			if(truoc>0)
			{
				truoc=2;
			}
		}
		else
		{
			if(truoc>0)
			{
				truoc--;
				if(truoc==0)
				{
					ir_xoa();
				}
			}
		}
		
// 		sprintf(chuoi,"%d",tg1);
// 		l_toi_xy(1,1);
// 		l_in(chuoi);
// 		l_in("  ");
// 		sprintf(chuoi,"%d",tg2);
// 		
// 		l_in(chuoi);
// 		l_in("     ");
// 		
// 		sprintf(chuoi,"%d",tg_st);
// 		l_in(chuoi);
// 		l_in("     ");
		l_toi_xy(1,2);
		for(i=0;i<5;i++)
		{
			sprintf(chuoi,"%02d ",t_rf[i]);
			l_in(chuoi);
		}
		return rf_loi;
	}
}
//========================================//========================================






#endif