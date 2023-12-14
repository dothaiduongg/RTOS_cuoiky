#ifndef _dfplayer_h_
#define _dfplayer_h_
#define DFPLAYER_SEND_LENGTH 10
#define Stack_ACK 4
u8 _sending[DFPLAYER_SEND_LENGTH] = {0x7E, 0xFF, 06, 0x0F, 00, 01, 01, 00, 00, 0xEF};
bool _isSending = false;
u8 vol=0x0C; //(0x00-0x1E)
unsigned int i,ads,cmd,bt,cti,ib;
unsigned char eq,rpt,ifd;
//u8 _sending[DFPLAYER_SEND_LENGTH] = {0x7E, 0xFF, 06, 00, 01, 00, 00, 00, 00, 0xEF};
// /*  kniznica pre pracu s UART AVR
//     made by: Luboss17 in 2011
//     http://lubosweb.php5.sk                             */
// 
// #include <avr/io.h>
// 
// /******************************************************
//     inicializacia
//     - nastavenie baudRate - ako vstupna premenna
//     - zapne vysielac a prijimac
//     - 8 datovych a 1 stop bity
// ******************************************************/
// 
// extern void uart_init(u32 baud);
// 
// /******************************************************
//     odosle bajt (znak)
// ******************************************************/
// 
// extern void uart_putc(unsigned char data);
// 
// /******************************************************
//     odosle retazec bajtov (znakov)
// ******************************************************/
// 
// extern void uart_puts(char *s);
// 
// /******************************************************
//     prijem bajt-u (znak)
// ******************************************************/
// 
// extern unsigned char uart_getc(void);
// 
// /******************************************************
//     vycistenie buffer-a
// ******************************************************/
// 
// extern void uart_flush(void);
// void thu_uart();
// void USART_SendByte(uint8_t u8Data);
// #ifndef chuoi_size_uart
// #define chuoi_size_uart 70
// #endif
// bool co_232=0; // co giu lieu nhan duoc 
// int8 mang_dl_232[chuoi_size_uart];
// int8 mang_dli_232[chuoi_size_uart];
// int8 do_dai=0; // tinh do dai khi thu du lieu 
// u8 tong_byte=0;
// int8 out_time_232=0;
// 




void DF_sendStack()
{
	if (_sending[Stack_ACK]) {  //if the ack mode is on wait until the last transmition
		//while (_isSending) 
		{
			delay_ms(500);
			//available();
		}
	}

	#ifdef _DEBUG
	Serial.println();
	Serial.print(F("sending:"));
	for (int i=0; i<DFPLAYER_SEND_LENGTH; i++) {
		Serial.print(_sending[i],HEX);
		Serial.print(F(" "));
	}
	Serial.println();
	#endif
	uart_puts_b_s(_sending, DFPLAYER_SEND_LENGTH);
	//_timeOutTimer = millis();
	_isSending = _sending[Stack_ACK];
	
	if (!_sending[Stack_ACK]) { //if the ack mode is off wait 10 ms after one transmition.
		delay_ms(10);
	}
}

void DF_dat_am_luog(uint8_t volume)
{
  DF_sendStack(0x06, volume);
}
void DF_play(int fileNumber)
{
	DF_sendStack(0x03, fileNumber);
}

void ope6(unsigned char dfcmd6)
{
	//Start Ver Length Cmd Res End
	uint8_t data[]={0x7E,0xFF,0x04,dfcmd6,0x00,0xEF};
	uart_puts_b_s(data,6);
	_delay_ms(200);
}
void ope8(unsigned char dfcmd8,unsigned char value){
	//Start Ver Length Cmd Res byteH byteL End
	uint8_t data[]={0x7E,0xFF,0x06,dfcmd8,0x00,0x00,value,0xEF};
	uart_puts_b_s(data,8);
}
void pat_nhac(u8 ten_bai)
{
	ope8(0x03,ten_bai);
}
void dug_nhac()
{
	ope6(0x0E); //Stop
}

#endif // UART_H_INCLUDED
