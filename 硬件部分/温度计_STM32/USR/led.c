#include "pbdata.h"

void LED_GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;	
	
	GPIO_InitStructure.GPIO_Pin=LED1_PORT | LED2_PORT;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(LED_GPIO,&GPIO_InitStructure);
	
	SET_LED1(0);
	SET_LED2(0);
}

//继电器GPIO口配置 CPIOC PC3
void RELAY_GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin=RELAY_PORT;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(RELAY_GPIO,&GPIO_InitStructure);
	
	SET_RELAY(0);  //处于常闭状态
}


