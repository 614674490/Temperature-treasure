#include "pbdata.h"

void BEEP_GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;	
	
	GPIO_InitStructure.GPIO_Pin=BEEP_PORT;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(BEEP_GPIO,&GPIO_InitStructure);
	
	BEEP_Speek(SpeekTime,SpeekFre);
}

void BEEP_Speek(int time,int fre)
{
	int n=0;
	
	for(n=0;n<time;n++)
	{
		SET_BEEP(1);
		delay_us(fre);
		SET_BEEP(0);
		delay_us(fre);
	}
	
	
}

