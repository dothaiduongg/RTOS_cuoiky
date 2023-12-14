
#ifndef _coi_h_
#define _coi_h_

#ifndef coi_tat
#define coi_tat 0
#define coi_bat 1
#endif
#ifndef coi
#define coi dk_bit(PORTB,5)
#define coi_d dk_bit(DDRB,5)
#endif
u16 tg_coi;
void bat_coi(u16 tg)
{
	coi=coi_bat;
	tg_coi=tg;
}
void tat_coi(u16 tg)
{
	coi=coi_tat;
	tg_coi=tg;
}
#endif
