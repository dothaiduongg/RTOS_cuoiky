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

/******************************************************
    vycistenie buffer-a
******************************************************/

extern void uart_flush(void);
void thu_uart();
void USART_SendByte(uint8_t u8Data);
#ifndef chuoi_size_uart
#define chuoi_size_uart 70
#endif
bool co_232=0; // co giu lieu nhan duoc 
int8 mang_dl_232[chuoi_size_uart];
int8 mang_dli_232[chuoi_size_uart];
int8 do_dai=0; // tinh do dai khi thu du lieu 
u8 tong_byte=0;
int8 out_time_232=0;

#define ma_dau "LDN"
#define ma_leh 'L'
#define ma_dl 'D'
#define bu_lai_uart 3
#endif // UART_H_INCLUDED
