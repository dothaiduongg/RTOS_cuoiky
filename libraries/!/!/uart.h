#ifndef UART_H_INCLUDED
#define UART_H_INCLUDED

/*  kniznica pre pracu s UART AVR
    made by: Luboss17 in 2011
    http://lubosweb.php5.sk                             */

#include <avr/io.h>
 
/******************************************************
    inicializacia
    - nastavenie baudRate - ako vstupna premenna
    - zapne vysielac a prijimac
    - 8 datovych a 1 stop bity
******************************************************/

extern void uart_init(u32 baud);

/******************************************************
    odosle bajt (znak)
******************************************************/

extern void uart_putc(unsigned char data);

/******************************************************
    odosle retazec bajtov (znakov)
******************************************************/

extern void uart_puts(char *s);

/******************************************************
    prijem bajt-u (znak)
******************************************************/

extern unsigned char uart_getc(void);
u8 doc_rs232(void);

/******************************************************
    vycistenie buffer-a
******************************************************/
void in_ts_so16(char *s,uint16_t so_16);
void in_ts_chuoi(char *s,char *chuoi_ts);

extern void uart_flush(void);
//void thu_uart();
void USART_SendByte(uint8_t u8Data);
#ifndef chuoi_size_uart
#define chuoi_size_uart 100
#endif
//#ifndef khong_mang_uart
char mang_dl_232[chuoi_size_uart];
char chuoi_so[10];
//#endif
//int8 mang_dli_232[chuoi_size_uart];
int8 do_dai=0; // tinh do dai khi thu du lieu 
u8 tong_byte=0;
int8 out_time_232=0;
int16 tong_byte_truyen=0;
int16 tong_tong_byte_truyen=0;
#define ma_dau "LDN"
#define ma_leh 'L'
#define ma_dl 'D'
#define bu_lai_uart 3

#if DEBUGPRINT_ENABLED
void debug_hex( uint32_t val, uint8_t digits );	// output `val` as hex number with N digits
void debug_dec( uint32_t val );					// output `val` as decimal number (variable length)
// Output val as fixed point number, with a fractional part of`nFract` bits
void debug_dec_fix( uint32_t val, const uint8_t nFract );
void debug_putc( uint8_t c );					// output the single character `c`
#define debug_str(s) debug_str_internal(PSTR(s))// output string `s`, which will be stored in program memory
void hexDump(uint8_t *buffer, uint16_t nBytes);	// output a pretty hex-dump of `buffer`
#else
#define debug_hex(val,digits)
#define debug_dec(val)
#define debug_dec_fix(val,nFract)
#define debug_str(s)
#define debug_putc(c)
#define hexDump(a,b)
#endif

#endif // UART_H_INCLUDED


