/*******************************************************************************
TCS3200 Colour Sensor Library for AVR

Default Connection
******************

      | ATmega32
S2  -> PA0
S3  -> PA1
OUT -> PA2
LED -> PA3


NOTICE
--------
NO PART OF THIS WORK CAN BE COPIED, DISTRIBUTED OR PUBLISHED WITHOUT A
WRITTEN PERMISSION FROM EXTREME ELECTRONICS INDIA. THE LIBRARY, NOR ANY PART
OF IT CAN BE USED IN COMMERCIAL APPLICATIONS. IT IS INTENDED TO BE USED FOR
HOBBY, LEARNING AND EDUCATIONAL PURPOSE ONLY. IF YOU WANT TO USE THEM IN
COMMERCIAL APPLICATION PLEASE WRITE TO THE AUTHOR.


WRITTEN BY:
AVINASH GUPTA
gmail@avinashgupta.com (Yes ! Its correct !)
*******************************************************************************/


#ifndef TCS3200_H_
#define TCS3200_H_


#define s0 dk_bit(PORTC,4)
#define s0_d dk_bit(DDRC,4)
#define s1 dk_bit(PORTB,4)
#define s1_d dk_bit(DDRB,4)
#define s2 dk_bit(PORTD,2)
#define s2_d dk_bit(DDRD,2)
#define s3 dk_bit(PORTC,5)
#define s3_d dk_bit(DDRC,5)

#define led_s dk_bit(PORTB,1)
#define led_s_d dk_bit(DDRB,1)

//S2 Connection
#define TCS_S2_DDR DDRA
#define TCS_S2_PORT PORTA
#define TCS_S2_POS PA0

//S3 Connection
#define TCS_S3_DDR DDRA
#define TCS_S3_PORT PORTA
#define TCS_S3_POS PA1

//Out Connection
#define TCS_OUT_DDR DDRD
#define TCS_OUT_PORT PIND
#define TCS_OUT_POS PD3

//LED Connection
#define TCS_LED_DDR DDRB
#define TCS_LED_PORT PORTB
#define TCS_LED_POS PB1



#define	TCSS2High()	TCS_S2_PORT|=(1<<TCS_S2_POS)
#define	TCSS2Low()	TCS_S2_PORT&=~(1<<TCS_S2_POS)
#define	TCSS3High()	TCS_S3_PORT|=(1<<TCS_S3_POS)
#define	TCSS3Low()	TCS_S3_PORT&=~(1<<TCS_S3_POS)
#define TCSLEDOn()	TCS_LED_PORT|=(1<<TCS_LED_POS)
#define TCSLEDOff() TCS_LED_PORT&=~(1<<TCS_LED_POS)

void InitTCS3200();

void TCSSelectRed();
void TCSSelectGreen();
void TCSSelectBlue();
void TCSSelectClear();

uint32_t TCSMeasure();


#endif /* TCS3200_H_ */