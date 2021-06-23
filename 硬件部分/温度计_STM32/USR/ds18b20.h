#ifndef _DS18B20_H
#define _DS18B20_H

#include "pbdata.h"


#define GPIO_DS18B20 GPIOC

#define DS18B20_DQ_High  GPIO_SetBits(GPIO_DS18B20,IO_DS18B20)
#define DS18B20_DQ_Low   GPIO_ResetBits(GPIO_DS18B20,IO_DS18B20)



void DS18B20_IO_IN(void);
void DS18B20_IO_OUT(void);
u8 DS18B20_Read_Byte(void);
void DS18B20_Write_Byte(u8 dat);
void DS18B20_Reset(void);
double DS18B20_Get_wd(u8 id);

uint16_t GetDs18B20_ID(u8 DS18B20_ID);

typedef struct DS18B20
{
	double Temp_1;
	
}DS18B20;
extern DS18B20 Ds18_T;

#endif
