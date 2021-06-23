#ifndef DISDATA_H
#define DISDATA_H

#include "pbdata.h"

#define VoltageMax 4.2
#define VoltageMin 3.3
#define VoltageRange 0.9 /* VoltageMax - VoltageMin */

void DIS_TempHumi(float temp,float humi);
void DIS_Time(time_ tt);
void DIS_Voltage(float val);
void DIS_RTU_Addr(unsigned char val);
void DIS_SystemInit(void);
void DIS_MenNum(unsigned char val);
void DIS_SensorChl(unsigned char num,unsigned char val);
void DIS_NODATA(unsigned char val);
void Wifi_SmartSta(void);
void DataStoreSta(void);

#endif
