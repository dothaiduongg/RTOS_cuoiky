#ifndef sht1x_h
#define sht1x_h
#include <!/! ldn.h>
	#define sck dk_bit(PORTC,2)
	#define sck_d dk_bit(DDRC,2)

	#define sda dk_bit(PORTC,0)
	#define sda_i dk_bit(PINC,0)
	#define sda_d dk_bit(DDRC,0)

    //sht1x(int datapin, int clockpin);
    float readhumidity();
    float readtemperaturec();
    float readtemperaturef();
    int _datapin;
    int _clockpin;
    int _numbits;
    u16 readtemperatureraw();
	u16 doc_nhiet_();
    int shiftin(int _datapin, int _clockpin, int _numbits);
    void sendcommandsht(int _command, int _datapin, int _clockpin);
    void waitforresultsht();
    int getdata16sht(int _datapin, int _clockpin);
    void skipcrcsht(int _datapin, int _clockpin);
#endif

