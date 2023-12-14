#include "../inc/ntc_mf58.h"

float Vin=5.0;     // [V]
float Rt=10000;    // Resistor t [ohm]
float R0=10000;    // value of rct in T0 [ohm]
float T0=298.15;   // use T0 in Kelvin [K]
float Vout=0.0;    // Vout in A0 
float Rout=0.0;    // Rout in A0
// use the datasheet to get this data.
float T1=273.15;      // [K] in datasheet 0º C
float T2=373.15;      // [K] in datasheet 100° C
float RT1=35563;   // [ohms]  resistence in T1
float RT2=549;    // [ohms]   resistence in T2
float beta=0.0;    // initial parameters [K]
float Rinf=0.0;    // initial parameters [ohm]   







void NTC_MF58_Init(void)
{
    beta=(log(RT1/RT2))/((1/T1)-(1/T2));
    Rinf=R0*exp(-beta/T0);
}


float NTC_MF58_Read_TempK(void)
{
    float TempK=0.0;   // variable output
    
    Vout=Vin*((float)(read_adc(0))/1024.0); // calc for ntc
    Rout=(Rt*Vout/(Vin-Vout));

    TempK=(beta/log(Rout/Rinf)); // calc for temperature
         
    return  TempK;
}

float NTC_MF58_Read_TempC(void)
{
    float TempC=0.0;   // variable output
    
    TempC=NTC_MF58_Read_TempK()-273.15;     
    return  TempC;
}

