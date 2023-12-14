//#include "Xu ly.h"   
u8 doc_eeprom();
void luu_eeprom();


//======================================== 
u8 doc_eeprom()
{
	cli();
	u8 loi=0;
	//tg_1=eeprom_read_byte((u8*)0);
	tg_bat_1=eeprom_read_byte((u8*)1);
	//tg_2=eeprom_read_byte((u8*)2);
	//
	tg_tat_1=eeprom_read_byte((u8*)4); 
	#ifdef ds
	tg_bat_2=eeprom_read_byte((u8*)3);
	tg_tat_2=eeprom_read_byte((u8*)5);
	if(tg_bat_2>159) loi=1;
	if(tg_tat_2>200) loi=1;
	#else
	do_am_dat=eeprom_read_word((u16*)2);
	do_am_lech=eeprom_read_word((u16*)16);
	#ifdef dht22 
		dau_do_am_lech=eeprom_read_byte((u8*)12); 
	#endif
	if(do_am_dat>900)loi=1;
	if(do_am_lech>2000)loi=1;
	#endif
	dau_lech=eeprom_read_byte((u8*)6);
	do_lech=eeprom_read_byte((u8*)7); 
	nd_dat=eeprom_read_word((u16*)8);
	nd_dat_2=eeprom_read_word((u16*)18);
	sei();
	//if(tg_1>tg_bat_1) 
	//tg_1=0;
	//if(tg_2>tg_bat_2) 
	//tg_2=0;
	if(tg_bat_1>159) loi=1;
	//
	if(tg_tat_1>200) loi=1;
	
	if(dau_lech>1) loi=1;
	if(do_lech>20) loi=1;
	if(nd_dat>400) loi=1;
	if(loi==1)
	{
// 		mac_dinh();
// 		luu_eeprom();
	}
	return loi;
}
//======================================== 
void luu_eeprom()
{
	cli();
	//eeprom_write_byte((u8*)0,tg_1);
	eeprom_write_byte((u8*)1,tg_bat_1);
	//eeprom_write_byte((u8*)2,tg_2);
	
	eeprom_write_byte((u8*)4,tg_tat_1);
	#ifdef ds
	eeprom_write_byte((u8*)3,tg_bat_2);
	eeprom_write_byte((u8*)5,tg_tat_2);
	#else
	eeprom_write_word((u16*)2,do_am_dat);
	eeprom_write_word((u16*)16,do_am_lech);
	#endif
	eeprom_write_byte((u8*)6,dau_lech);
	eeprom_write_byte((u8*)7,do_lech);
 	eeprom_write_word((u16*)8,nd_dat);
	eeprom_write_word((u16*)18,nd_dat_2);
	#ifdef dht22
	 eeprom_write_byte((u8*)12,dau_do_am_lech);
	#endif
	sei();
}