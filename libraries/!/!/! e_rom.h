#ifndef _e_rom
#define _e_rom
#include <avr/eeprom.h>
#include <!/xu ly so.c>

//#define co_mag_e


#ifdef co_mag_e
#ifndef dai_mag_e
#define dai_mag_e 30
#endif
#ifndef bu_mag_e
#define bu_mag_e 30
#endif
u8 mag_e[dai_mag_e];
#endif

//eeprom_write_byte((u8*)dc
//eeprom_write_word((u16*)dc
//eeprom_read_word((u16*)dc);
void luu_mang_e_16(u16*mang_can_luu,u16*mang_nho, u16 dia_chi_bat_dau,u16 so_byte)
{
	u16 do_dai_mang=so_byte;
	u8 i;
	//do_dai_mang=sizeof(mang_can_luu)/sizeof(mang_can_luu[0]);
	//do_dai_mang = sizeof(mang_can_luu);
	for(i=0;i<do_dai_mang;i++)
	{
		if(mang_nho[i]!=mang_can_luu[i])
		{
			mang_nho[i]=mang_can_luu[i];
			eeprom_write_word((u16*)(i*2+dia_chi_bat_dau),mang_can_luu[i]);
		}
	}
}
void cap_nhat_mang_e_16(u16*mang_can_luu, u16 dia_chi_bat_dau,u16 so_byte)
{
	u8 i;
	for(i=0;i<so_byte;i++)
	{
		eeprom_update_word((u16*)(i*2+dia_chi_bat_dau),mang_can_luu[i]);
	}
}
void cap_nhat_e_16_1(u16 gt, u16 dia_chi_bat_dau,u16 so_byte)
{
	u8 i;
	for(i=0;i<so_byte;i++)
	{
		eeprom_update_word((u16*)(i*2+dia_chi_bat_dau),gt);
	}
}
void doc_mang_e_16(u16*mang_can_doc,u16*mang_nho, u16 dia_chi_bat_dau,u16 so_byte)
{
	u16 do_dai_mang=so_byte;
	u8 i;
	//do_dai_mang=sizeof mang_can_doc / sizeof *mang_can_doc;
	//do_dai_mang=sizeof(mang_can_doc)/sizeof(mang_can_doc[0]);
	//do_dai_mang = sizeof(mang_can_doc[0]);
	for(i=0;i<do_dai_mang;i++)
	{
		mang_nho[i]=mang_can_doc[i]=eeprom_read_word((u16*)(i*2+dia_chi_bat_dau));
	}
}
void doc_mang_e_16_1(u16*mang_can_doc, u16 dia_chi_bat_dau,u16 so_byte)
{
	u8 i;
	for(i=0;i<so_byte;i++)
	{
		mang_can_doc[i]=eeprom_read_word((u16*)(i*2+dia_chi_bat_dau));
	}
}
void doc_mang_e_8(u8*mang_can_doc, u16 dia_chi_bat_dau,u8 so_byte)
{
	u8 i;
	for(i=0;i<so_byte;i++)
	{
		mang_can_doc[i]=eeprom_read_byte((u8*)(i+dia_chi_bat_dau));
	}
}
void doc_mang_e_8_16(u16*mang_can_doc, u16 dia_chi_bat_dau,u8 so_byte)
{
	u8 i;
	for(i=0;i<so_byte;i++)
	{
		mang_can_doc[i]=eeprom_read_byte((u8*)(i+dia_chi_bat_dau));
	}
}
void luu_e_8(u8 dl, u16 dc)
{
	eeprom_write_byte((u8*)dc,dl);
}
int8 doc_e_8(u16 dc)
{
	return eeprom_read_byte((u8*)dc);
}
void cap_nhat_e_8_1(u8 gt, u16 dia_chi_bat_dau,u16 so_byte)
{
	u8 i;
	for(i=0;i<so_byte;i++)
	{
		eeprom_update_byte((u8*)(i+dia_chi_bat_dau),gt);
	}
}
void luu_e_16(u16 dl, u16 dc)
{ 
	eeprom_write_byte((u8*)dc,make8(dl,0));
	eeprom_write_byte((u8*)dc+1,make8(dl,1));
}
void luu_e_162(u16 dl, u16 dc)
{
	eeprom_write_word((u16*)dc,dl);
}
int16 doc_e_16(u16 dc)  // doc eeprom noi 16 bit
{
	return make16(eeprom_read_byte((u8*)dc),eeprom_read_byte((u8*)dc+1));
}

int16 doc_e_162(u16 dc)  // doc eeprom noi 16 bit
{
	return eeprom_read_word((u16*)dc);
}
void luu_e_32(u32 dl, u16 dc)
{
	eeprom_write_dword((u32*)(dc),dl);
}
u32 doc_e_32(u16 dc)
{
	return eeprom_read_dword((u32*)(dc));
}


#ifdef co_mag_e
#if  defined(__AVR_ATmega8__) 
void doc_mag_e()
{
	u16 i;
	for(i=0;i<dai_mag_e;i++)
	{
		mag_e[i]=eeprom_read_byte((u8*)i+bu_mag_e);
	}
}
void luu_mag_e()
{
	u16 i;
	for(i=0;i<dai_mag_e;i++) 
	{
		eeprom_write_byte((u8*)i+bu_mag_e,mag_e[i]);
	}
}
#endif
#if  defined(__AVR_ATmega328__) || defined(__AVR_ATmega168PA__)
u8 mag_e_nho[dai_mag_e];
void doc_mag_e()
{
	u16 i;
	for(i=0;i<dai_mag_e;i++)
	{
		mag_e_nho[i]=mag_e[i]=eeprom_read_byte((u8*)i+bu_mag_e);
	}
}
void luu_mag_e()
{
	u16 i;
	for(i=0;i<dai_mag_e;i++)
	{
		if (mag_e_nho[i]!=mag_e[i])
		{
			mag_e_nho[i]=mag_e[i];
			eeprom_write_byte((u8*)i+bu_mag_e,mag_e[i]);
		}
	}
}
#endif
void nhap_mag_e(u8*dl,u16 vt,u8 sb)
{
	u8 i;
	for(i=0;i<sb;i++)
	{
		mag_e[i+vt]=dl[i];
	}
}
void tach_mag_e(u8*dl,u16 vt,u8 sb)
{
	u8 i;
	for(i=0;i<sb;i++)
	{
		dl[i]=mag_e[i+vt];
	}
}
#endif

#endif
