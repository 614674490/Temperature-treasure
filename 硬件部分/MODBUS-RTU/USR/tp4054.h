#ifndef TP4054_H
#define TP4054_H

#include "pbdata.h"

#define TP_GPIO GPIOC
#define TP_PORT	GPIO_Pin_4

#define READ_TP	 GPIO_ReadInputDataBit(TP_GPIO,TP_PORT)

void TP4054_GPIO_Configuration(void);

#endif


