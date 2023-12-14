//----------------------------------------------------------------------------------
//
// Sensirion SHT1x Humidity Sensor Library
//
//----------------------------------------------------------------------------------

#ifndef __sht_h
#define __sht_h

#define SHT_TEMPERATURE 	0x03		// Measure temp - for ShtMeasure
#define SHT_HUMIDITY 		0x05		// Measure humidity - for ShtMeasure

#define SHT_DDR				DDRC		// Port with clock and data pins
#define SHT_PORT			PORTC		// Port with clock and data pins
#define SHT_PIN				PINC		// Port with clock and data pins
#define SHT_CLOCK			2			// Pin used to output clock to SHT
#define SHT_DATA			0			// Pin used to read/output data from/to SHT

#define STATUS_REG_W 		0x06 		// Command to read status register
#define STATUS_REG_R 		0x07 		// Command to write status register
#define RESET 				0x1E 		// Command for soft reset (not currently used)

void ShtInit(void);
void ShtReset(void);
int  ShtMeasure(unsigned char mode);
void ShtCalculate(int *p_temperature, int *p_humidity);
char ShtReadStatus(unsigned char *p_value);
char ShtWriteStatus(unsigned char value);

#endif
