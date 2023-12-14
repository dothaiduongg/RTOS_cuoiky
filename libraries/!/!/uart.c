#ifndef uart_c
#define uart_c
#include "uart.h"
#ifndef _uart_c 
#define _uart_c
#include <avr/pgmspace.h>
#include "string.h"
#include "stdlib.h"
u8 truen_lan_dau=0;
u8 leh=0;
//#define DEBUGPRINT_ENABLED 1

#ifndef tg_cho_232
#define tg_cho_232 10
#endif 
#ifndef tg_out_232

#warning "Dinh nghia tg out nhan chuoi UART #define tg_out_232 10"
#define tg_out_232 10
#endif
//========================================  
void uart_init(u32 baud)
{
	#if  defined(__AVR_ATmega8__)  || defined(__AVR_ATmega16__) || defined(__AVR_ATmega32__) \
	|| defined(__AVR_ATmega8515__) || defined(__AVR_ATmega8535__) \
	|| defined(__AVR_ATmega323__)
    short int ubrr = F_CPU/16/baud-1; 
	
	if ( ubrr & 0x8000 )
	{
		UCSRA = (1<<U2X);  //Enable 2x speed
		ubrr &= ~0x8000;
	}
	
	UBRRH = (unsigned char) (ubrr>>8);
	UBRRL = (unsigned char) ubrr;

	//#if  defined(__AVR_ATmega8__)
	UCSRB = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE);

	//nastav format ramca: 8data, 1stop bity
	UCSRC = (1<<URSEL)|(3<<UCSZ0);
	
	//#endif
	/*
	#if  defined(__AVR_ATmega32__)
	 // Enable receiver and transmitter 
	 UCSRA = (0<<U2X);
	 UCSRB = (1<<RXEN)|(1<<TXEN)|(0<<UCSZ2);

	 // Set frame format: 8 bit, no parity, 1 stop bit 
	 UCSRC = (1<<URSEL)|(0<<UPM1)|(0<<UPM0)|(0<<USBS)|(1<<UCSZ1)|(1<<UCSZ0);
	 #endif
	*/
	
	//UCSRC=(1<<URSEL)|(0<<UMSEL)|(0<<UPM1)|(0<<UPM0)|
	//(0<<USBS)|(0<<UCSZ2)|(1<<UCSZ1)|(1<<UCSZ0);
	//Enable Transmitter and Receiver and Interrupt on receive complete
	//UCSRB=(1<<TXEN);
	//UBRRH=0;
	//UBRRL=35;
	//UCSRA|=(1<<U2X); 
	#endif
	#if  defined(__AVR_ATmega328__) || defined(__AVR_ATmega168PA__)
	short int ubrr = F_CPU/16/baud-1;
	UBRR0H = (unsigned char) (ubrr>>8);
	UBRR0L = (unsigned char) ubrr;
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
	#endif
}

/*Very Important - change F_CPU to match target clock 
  Note: default AVR CLKSEL is 1MHz internal RC
  This program transmits continously on USART. Interrupt is used for 
	Receive charactor, which is then transmitted instead. LEDs are used 
	as a test. Normal RX routine is included but not used.
  Change USART_BAUDRATE constant to change Baud Rate
*/
// Define baud rate
#define USART_BAUDRATE 38400   
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

volatile unsigned char value;  
/* This variable is volatile so both main and RX interrupt can use it.
It could also be a uint8_t type */

/* Interrupt Service Routine for Receive Complete 
NOTE: vector name changes with different AVRs see AVRStudio -
Help - AVR-Libc reference - Library Reference - <avr/interrupt.h>: Interrupts
for vector names other than USART_RXC_vect for ATmega32 */



void khoi_tao_uart(void){
   	#if  defined(__AVR_ATmega8__)  || defined(__AVR_ATmega16__) || defined(__AVR_ATmega32__) \
   	|| defined(__AVR_ATmega8515__) || defined(__AVR_ATmega8535__) \
   	|| defined(__AVR_ATmega323__)
   UBRRL = BAUD_PRESCALE;// Load lower 8-bits into the low byte of the UBRR register
   UBRRH = (BAUD_PRESCALE >> 8); 
	 /* Load upper 8-bits into the high byte of the UBRR register
    Default frame format is 8 data bits, no parity, 1 stop bit
  to change use UCSRC, see AVR datasheet*/ 

  // Enable receiver and transmitter and receive complete interrupt 
  UCSRB = ((1<<TXEN)|(1<<RXEN) | (1<<RXCIE));
  #endif
	#if  defined(__AVR_ATmega328__) || defined(__AVR_ATmega168PA__)
	UBRR0L = BAUD_PRESCALE;// Load lower 8-bits into the low byte of the UBRR register
	UBRR0H = (BAUD_PRESCALE >> 8);
	UCSR0B = ((1<<TXEN0)|(1<<RXEN0) | (1<<RXCIE0));
	#endif
}
/******************************************************
    odosle bajt (znak)
******************************************************/
int uart_putchar(char data) {
	//while (!(UCSRA & (1<<UDRE))) {};
	if (data == '\n') {
		(void)uart_putchar('\r');
	}
	#if  defined(__AVR_ATmega8__)  || defined(__AVR_ATmega16__) || defined(__AVR_ATmega32__) \
	|| defined(__AVR_ATmega8515__) || defined(__AVR_ATmega8535__) \
	|| defined(__AVR_ATmega323__)
	//PORTD |= 1<<5;
	while (!(UCSRA & (1<<UDRE))) {};
	//PORTD &= (uint8_t)(~(1<<5));

	UDR = (uint8_t)data;
	#endif
	//======================================== 
	#if  defined(__AVR_ATmega328__) || defined(__AVR_ATmega168PA__)
	while (!(UCSR0A & (1<<UDRE0))) {};
	UDR0 = (uint8_t)data;
	#endif
	return 0;
}
void uart_putc(unsigned char data)
{
	tong_tong_byte_truyen+=data;
	#if  defined(__AVR_ATmega8__)  || defined(__AVR_ATmega16__) || defined(__AVR_ATmega32__) \
	|| defined(__AVR_ATmega8515__) || defined(__AVR_ATmega8535__) \
	|| defined(__AVR_ATmega323__)
	while (!( UCSRA & (1<<UDRE)));
	 
	//vloz data do buffer-a a odosli
	UDR = data;
	#endif
	#if  defined(__AVR_ATmega328__) || defined(__AVR_ATmega168PA__)
	while (!(UCSR0A & (1<<UDRE0))) {}; 
	UDR0 = data;
	#endif
}
//======================================== 
void uart_putc_u(u8 data)
{
	#if  defined(__AVR_ATmega8__)  || defined(__AVR_ATmega16__) || defined(__AVR_ATmega32__) \
	|| defined(__AVR_ATmega8515__) || defined(__AVR_ATmega8535__) \
	|| defined(__AVR_ATmega323__)
	while (!( UCSRA & (1<<UDRE)));

	//vloz data do buffer-a a odosli
	UDR = data;
	#endif
	#if defined(__AVR_ATmega328__) || defined(__AVR_ATmega168PA__)
	while (!(UCSR0A & (1<<UDRE0))) {};
	UDR0 = data;
	#endif 
}

/******************************************************
    odosle retazec bajtov (znakov)
******************************************************/
void uart_put_so_32(u32 so)
{
	char snum[10];
	itoa(so, snum, 10);
	uart_puts(snum);
}
void uart_put_so_16(u16 so)
{
	char snum[10];
	itoa(so, snum, 10);
	uart_puts(snum);
}
void uart_puts(char *s)
{
    while (*s)
	{
		tong_byte_truyen++;
      uart_putc(*s++);
	}
}
void uart_puts_b(u8 *s)
{
	while (*s)
	{
		uart_putc(*s++);
	}
}
void uart_puts_b_s(u8 *s,u16 so_byte)
{
	u16 i;
	while(i<so_byte)
	{
		uart_putc(*s++);
		i++;
	}
}
//======================================== 
void in_ts_chuoi(char *s,char *chuoi_ts)
{
	uart_puts(s);
	uart_puts("``");
	uart_puts(chuoi_ts);
	uart_puts("``");
}
//========================================
void in_ts_chuoi_xem(char *s,char *chuoi_ts)
{
	uart_puts(s);
	uart_puts("``");
	uart_puts("~1");
	uart_puts(chuoi_ts);
	uart_puts("``");
}
//========================================
void in_ts_chuoi_nut(char *s)
{
	uart_puts(s);
	uart_puts("``");
	uart_puts("~20");
	uart_puts("``");
}
//======================================== 
void in_ts_so16(char *s,uint16_t so_16)
{
	itoa(so_16, chuoi_so, 10);
	in_ts_chuoi(s,chuoi_so);
}
//========================================
void in_ts_so16_xem(char *s,uint16_t so_16)
{
	itoa(so_16, chuoi_so, 10);
	in_ts_chuoi_xem(s,chuoi_so);
}
//======================================== 
/******************************************************
    prijem bajt-u (znak)
******************************************************/
unsigned char uart_getc(void)
{
	#if  defined(__AVR_ATmega8__)  || defined(__AVR_ATmega16__) || defined(__AVR_ATmega32__) \
	|| defined(__AVR_ATmega8515__) || defined(__AVR_ATmega8535__) \
	|| defined(__AVR_ATmega323__)
	while (!(UCSRA & (1<<RXC)));

	//zober data z buffer-a
	return UDR;
	#endif
	#if  defined(__AVR_ATmega328__) || defined(__AVR_ATmega168PA__)
	while (!(UCSR0A & (1<<RXC0))) {};
	return UDR0;
	#endif
}

/******************************************************
    vycistenie buffer-a
******************************************************/
/*
void uart_flush(void)
{
	unsigned char dummy;

	while ( UCSRA & (1<<RXC) ) dummy = UDR;
}*/
void USART_SendByte(uint8_t u8Data)
{
  #if  defined(__AVR_ATmega8__)  || defined(__AVR_ATmega16__) || defined(__AVR_ATmega32__) \
  || defined(__AVR_ATmega8515__) || defined(__AVR_ATmega8535__) \
  || defined(__AVR_ATmega323__)
  while((UCSRA &(1<<UDRE)) == 0);

  // Transmit data
  UDR = u8Data;
  #endif
  #if  defined(__AVR_ATmega328__) || defined(__AVR_ATmega168PA__)
  while((UCSR0A &(1<<UDRE0)) == 0);
  UDR0 = u8Data;
  #endif
} 


// not being used but here for completeness 
      // Wait until a byte has been received and return received data 
uint8_t USART_ReceiveByte()
{
	#if  defined(__AVR_ATmega8__)  || defined(__AVR_ATmega16__) || defined(__AVR_ATmega32__) \
	|| defined(__AVR_ATmega8515__) || defined(__AVR_ATmega8535__) \
	|| defined(__AVR_ATmega323__) 
  while((UCSRA &(1<<RXC)) == 0);
  return UDR;
  #endif
  #if  defined(__AVR_ATmega328__) || defined(__AVR_ATmega168PA__)
  while((UCSR0A &(1<<RXC0)) == 0);
  return UDR0; 
  #endif
}
//========================================
#ifndef ngat_uart_rieng
ISR(USART_RXC_vect)
{
	#if  defined(__AVR_ATmega8__)  || defined(__AVR_ATmega16__) || defined(__AVR_ATmega32__) \
	|| defined(__AVR_ATmega8515__) || defined(__AVR_ATmega8535__) \
	|| defined(__AVR_ATmega323__)
	mang_dl_232[do_dai] = UDR; // TB co gia tri du lieu nhan duoc
	if(do_dai<chuoi_size_uart-1)
	{
		do_dai++;
	}
	out_time_232 = tg_out_232; // thoi gian out cho 1 chuoi du lieu la 50 ms
	
	#endif
} 
#endif
#ifndef ngat_uart_rieng
#if  defined(__AVR_ATmega328__)||defined(__AVR_ATmega328A__) || defined(__AVR_ATmega168PA__)
ISR(USART_RX_vect)
{ 
	mang_dl_232[do_dai] = UDR0; // TB co gia tri du lieu nhan duoc
	//UDR0=mang_dl_232[do_dai];
	if(do_dai<chuoi_size_uart-1)
	{
		do_dai++;
	}
	out_time_232 = tg_out_232; // thoi gian out cho 1 chuoi du lieu la 50 ms
}
#endif
#endif


//ISR(USART_RX_vect)
//{
	//#if  defined(__AVR_ATmega328__)||defined(__AVR_ATmega328A__)
	//co_232 = 1;
	//dl = UDR0; // TB co gia tri du lieu nhan duoc
	//out_time_232 = tg_out_232; // thoi gian out cho 1 chuoi du lieu la 50 ms
	//#endif
//}
//#endif
//======================================== 
void giam_thoi_gian_uart() // 1ms // duoc goi boi ngat timer2 LDNam
{
	if (out_time_232>0)
	{
		out_time_232--;
		{
			if (out_time_232==0)
			{
				tong_byte=do_dai;
				do_dai=0;
			}
		}
	}
}
//======================================== 
u8 doc_rs232(void)
{
	u8 tb = 0;
	if (tong_byte>0)
	{
		tb=tong_byte;
		tong_byte=0;
		mang_dl_232[tb]=0;
	}
	return tb;
}
//======================================== 
void uart_hex_dump(int8_t d)
{
	uint8_t byte = '0';
	(((d>>4)&0x0F)<=9) ? (byte='0'+((d>>4)&0x0F)) : (byte='A'+ ((d>>4)&0x0F)-0x0A);
	uart_putc(byte);
	
	((d&0x0F)<=9) ? (byte='0'+ (d&0x0F)) : (byte='A'+ (d&0x0F)-0x0A);
	uart_putc(byte);
}
#define cong_so_truyen
u16 tong_cua_cac_don_vi_truyen=0;
//========================================
void uart_in_so_don_vi(u8 so)
{
	tong_cua_cac_don_vi_truyen+=so%10;
	uart_putc_u(so%10+0x30);
}
//========================================
void uart_in_so_2(u8 so)
{
	uart_in_so_don_vi(so/10);
	uart_in_so_don_vi(so);
}
//========================================
void uart_in_so_3(u16 so)
{
	uart_in_so_don_vi(so/100);
	uart_in_so_2(so);
}
//========================================
void uart_in_so_4(u16 so)
{
	uart_in_so_don_vi(so/1000);
	uart_in_so_3(so);
}
//========================================
void uart_in_so_5(u16 so)
{
	uart_in_so_don_vi(so/10000);
	uart_in_so_4(so);
}
//========================================
void uart_in_so_32(u32 so)
{
	uart_putc_u(so/10000%10+0x30);
	uart_putc_u(so/1000%10+0x30);
	uart_putc_u(so/100%10+0x30);
	uart_putc_u(so/10%10+0x30);
	uart_putc_u(so/1%10+0x30);
	uart_putc_u('\n');
}
//======================================== 
void uart_in_so(u32 so)
{
	uart_putc_u(' ');
	uart_in_so_32(so);
	uart_putc_u(';');
}

//void uart_in_so(u32 so)
//{
	//uart_putc_u(' ');
	//for (int i = 0; i < 5; i++)
	//{
		//uart_putc_u(so%10+0x30);
		//so/=10;
	//}
	//uart_putc_u(';');
//}
// ========================================
// void uart_in_16(u16 so)
// {
// 	uart_putc_u('-');
// 	uart_putc_u(so/10000%10+0x30);
// 	uart_putc_u(so/1000%10+0x30);
// 	uart_putc_u(so/100%10+0x30);
// 	uart_putc_u(so/10%10+0x30);
// 	uart_putc_u(so/1%10+0x30); 
// 	uart_putc_u(';');
// }
void xoa_uart()
{
	u8 i;
	for (i=0;i<chuoi_size_uart;i++)
	{
		mang_dl_232[i]=0;
	}
	do_dai=0;
}

#ifdef khug_truen
#define so_khug 4
// Khung truyen du lieu v10 ldnam
// 1 ma dau LDN
// 2 du lieu 50kt
// 3 ma xor 10kt dau
// 4 ma xor 10kt tiep
// 5 ma xor 10kt tiep
// 6 ma xor 10kt tiep
// 7 ma xor 10kt tiep
// 8 ma cuoi am
// 9 0x0a,0x0d
// tong khug du lieu 3+50+5+2+2 = 62 kt
u8 dl_truen[so_khug*10];
u8 dl_nhan[so_khug*10];
u8 con_tro_khung_truyen=0;
u8 con_tro_khung_nhan=0;
void  dat_con_tro_khung_truyen(u8 gia_tri)
{
	con_tro_khung_truyen=gia_tri;
}
void  dat_con_tro_khung_nhan(u8 gia_tri)
{
	con_tro_khung_nhan=gia_tri;
}
void them_du_lieu_truyen(u8 du_lieu)
{
	dl_truen[con_tro_khung_truyen]=du_lieu;
	con_tro_khung_truyen++;
}
void them_du_lieu_truyen_16(u16 dl)
{
	dl_truen[con_tro_khung_truyen]=make8(dl,0);
	dl_truen[con_tro_khung_truyen+1]=make8(dl,1);
	con_tro_khung_truyen+=2;
}
u16 doc_du_lieu_nhan_16()
{
	u16 dl;
	dl = tao_16_bit(dl_nhan[con_tro_khung_nhan],dl_nhan[con_tro_khung_nhan+1]);
	con_tro_khung_nhan+=2;
	return dl;
}
u8 doc_du_lieu_nhan_8()
{
	u8 dl;
	dl = dl_nhan[con_tro_khung_nhan];
	con_tro_khung_nhan++;
	return dl;
}
void truyen_v10()
{
	u8 xo[so_khug];
	u8 a=0;//u8 b=0;u8 c=0;u8 d=0;u8 e=0;u8 f=0;
	u8 i;//,k;
	for(i=0;i<so_khug;i++)
	{
		xo[i]=0;
	}
	uart_putc_u('L'); // 1
	uart_putc_u('D'); // 2
	uart_putc_u('N'); // 3
	for(i=0;i<so_khug*10;i++)
	{
		a=dl_truen[i]; 
		uart_putc_u(a); //53
		xo[i/10]^=a;
	}
	for(i=0;i<so_khug;i++)
	{
		if(xo[i]==0)
		{
			xo[i]=0xff;
		}
		uart_putc_u(xo[i]);//58
	}
	uart_putc_u('a'); //59
	uart_putc_u('m'); // 60
	uart_putc_u(0xa);
	uart_putc_u(0xd);
}

//======================================== 
u8 kiem_tra_xo()
{
	u8 xo[so_khug];
	u8 i;
	u8 xo_tam=0;
	u8 ket_qua;
	u8 xo_doc;
	for(i=0;i<so_khug;i++)
	{
		xo[i]=0;
	}
	for(i=0;i<so_khug*10;i++)
	{
		xo_tam=mang_dl_232[i+3];
		xo[i/10]^=xo_tam;
		dl_nhan[i]=xo_tam;
	}
	ket_qua=1;
	for(i=0;i<so_khug;i++)
	{
		if(xo[i]==0)
		{
			xo[i]=0xff;
		}
		xo_doc=mang_dl_232[i+so_khug*10+3];
		if(xo[i]!=xo_doc)
		{
			ket_qua=0;
			break;
		}
	}
	return ket_qua;
}
u8 nhan_v10()
{
	u8 c=0; u8 d=0;
	u8 i;
	if(doc_rs232()>0)
	{
		if((mang_dl_232[0]=='L')&&(mang_dl_232[1]=='D')&&(mang_dl_232[2]=='N'))
		if((mang_dl_232[so_khug*10+so_khug+3]=='a')&&(mang_dl_232[so_khug*10+so_khug+4]=='m'))
		{
			if(kiem_tra_xo()==1)
			{
				leh=dl_nhan[so_khug*10-2];
				truen_lan_dau=dl_nhan[so_khug*10-1];
				xoa_uart();
				return 1;
			}
		}
	}
	return 0;
}
#endif










#if DEBUGPRINT_ENABLED

void debugInit() {
	// Init UART
	//     PRR &= ~(1<<PRUSART0);
	//     UCSR0B |= (1<<TXEN0) | (1<<RXEN0);
	//     UBRR0H = UBRRH_VALUE;
	//     UBRR0L = UBRRL_VALUE;
	//     #if USE_2X
	//         UCSR0A |= (1<<U2X0);
	//     #else
	//         UCSR0A &= ~(1<<U2X0);
	//     #endif
}

void debug_putc( uint8_t c ) 
{
	USART_SendByte(c);
}

uint8_t hex2Nibble( uint8_t c ){
	if(  c>='a' && c<='f' ){
		return( c - 'a' + 10 );
	}
	if(  c>='0' && c<='9' ){
		return( c - '0' );
	}
	return 0xFF;
}

// Print string from flash
void debug_str_internal( const char *p ){
	uint8_t c;
	while (( c=pgm_read_byte( p++ ) )){
		debug_putc( c );
		if( c=='\n' ){
			debug_putc('\r');
		}
	}
}

void debug_dec( uint32_t val ){
	char buffer[10];
	char *p = buffer;
	while (val || p == buffer) {
		*(p++) = val % 10;
		val = val / 10;
	}
	while (p != buffer) {
		debug_putc( '0' + *(--p) );
	}
}

void debug_dec_fix( uint32_t val, const uint8_t nFract ){
	uint32_t fractMask = ((1<<nFract)-1);   //For masking the fractional part
	debug_dec( val>>nFract );               //Print the integer part
	debug_putc('.');
	val &= fractMask;                       //Convert to fractional part
	while( val > 0 ) {
		val *= 10;
		debug_putc( '0' + (val>>nFract) );  //Print digit
		val &= fractMask;                   //Convert to fractional part
	}
}

void debug_hex( uint32_t val, uint8_t digits ){
	for (int i = (4*digits)-4; i >= 0; i -= 4)
	debug_putc( "0123456789ABCDEF"[(val >> i) % 16] );
}

// Print a pretty hex-dump on the debug out
void hexDump( uint8_t *buffer, uint16_t nBytes ){
	for( uint16_t i=0; i<nBytes; i++ ){
		if( (nBytes>16) && ((i%16)==0) ){
			debug_str("\n    ");
			debug_hex(i, 4);
			debug_str(": ");
		}
		debug_hex(*buffer++, 2);
		debug_str(" ");
	}
}

#endif


#endif
#endif
