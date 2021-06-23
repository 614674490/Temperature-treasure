#ifndef WIFI_H
#define WIFI_H

#include "pbdata.h"

#define WIFIWakeUp_GPIO GPIOC
#define WIFIWakeUp_PORT GPIO_Pin_5

#define WIFI_WakeUp(n)  ((n) ? (WIFIWakeUp_GPIO->BSRR = WIFIWakeUp_PORT):(WIFIWakeUp_GPIO->BRR = WIFIWakeUp_PORT))


#define WIFIPower_GPIO GPIOB
#define WIFIPower_PORT GPIO_Pin_5

#define WIFI_PowerSet(n)  ((n) ? (WIFIPower_GPIO->BSRR = WIFIPower_PORT):(WIFIPower_GPIO->BRR = WIFIPower_PORT))

#define MaxRecLen 512
typedef struct
{
	char RecBuf[MaxRecLen];
	int  RecLen;
	unsigned char isMsg;
}wifi_;

extern wifi_ WIFI_T;
extern int wifi_set;

unsigned char WIFI_AT(char *SendStr,char *RespondStr,int RespondMSec,unsigned char isdis);
void WIFIWakeUp_GPIO_Configuration(void);
void MessageInit(void);
void CheckWifiLinkStatus(void);
void WIFI_PowerDown(void);
void WIFI_PowerUp(void);

#endif
