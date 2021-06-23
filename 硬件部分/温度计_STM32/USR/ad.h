#ifndef AD_H
#define AD_H
#include "pbdata.h"

#define Channel_Num 1
#define Sample_Num  2

typedef struct AD
{
	float AD_IN_V;

}AD;
extern AD AD_INDATA_T;

extern vu16 ADC_ConvertedValue[Sample_Num][Channel_Num];


float ReadADCAverageValue(uint16_t Channel);
void POWER_AD_Init(void);



#endif
