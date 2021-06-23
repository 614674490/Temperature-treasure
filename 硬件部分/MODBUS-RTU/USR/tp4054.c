#include "pbdata.h"

void TP4054_GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;	
	
	GPIO_InitStructure.GPIO_Pin=TP_PORT;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(TP_GPIO,&GPIO_InitStructure);
}



