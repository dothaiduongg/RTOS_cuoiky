#ifndef __NTC_MF58_H
#define __NTC_MF58_H

#include "main.h"

#define VREF            5000    //5v=5000mv




void NTC_MF58_Init(void);
float NTC_MF58_Read_TempK(void);
float NTC_MF58_Read_TempC(void);
extern unsigned int read_adc(unsigned char adc_input);








#endif      /*__NTC_MF58_H*/

