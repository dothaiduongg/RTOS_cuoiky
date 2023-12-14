#ifndef sht1x_h
#define sht1x_h
#include <!/! ldn.h>
// #ifndef sck 
// 	#define sck dk_bit(PORTC,2)
// 	#define sck_d dk_bit(DDRC,2)
// #endif
// #ifndef sda
// 	#define sda dk_bit(PORTC,0)
// 	#define sda_i dk_bit(PINC,0)
// 	#define sda_d dk_bit(DDRC,0)
// #endif

/*!
 * \brief Reads the temperature and humidity values from the sensor.
 * \param fT Pointer where to store the temperature.
 * \param fRH Pointer where to store the humidity.
 * \return Error code, ERR_OK if everything is ok.
 */
uint8_t SHT11_Read(float *fT, float *fRH);

/*!
 * \brief Performs a softreset of the device
 * \return Error code, ERR_OK if everything is ok.
 */
uint8_t SHT11_SoftReset(void);
#endif

