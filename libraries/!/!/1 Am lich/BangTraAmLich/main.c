#include"main.h"
#include"LunarCalendar.h"
#include<stdio.h>

sbit LED_PIN = P3^1;

void main()
{
	unsigned char LunarDay, LunarMonth;
	unsigned int LunarYear;

	SCON  = 0x50;		        /* SCON: mode 1, 8-bit UART, enable rcvr      */
    TMOD |= 0x20;               /* TMOD: timer 1, mode 2, 8-bit reload        */
    TH1   = -3;                /* TH1:  reload value for 9600 baud @ 11.0592MHz   */
    TR1   = 1;                  /* TR1:  timer 1 run                          */
    TI    = 1;                  /* TI:   set TI to send first char of UART    */

	Solar2Lunar(31, 12, 2099, &LunarDay, &LunarMonth, &LunarYear);

	printf("Lunar Date: %u/%u/%u",(int)LunarDay, (int)LunarMonth, (int)LunarYear);

	while(1)
	{
			
	}
}