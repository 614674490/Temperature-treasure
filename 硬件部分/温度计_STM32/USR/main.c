#include "pbdata.h"

/*************本代码 适用于 TM-Tem&Hum Recorder V0.2 2018/06/13 温湿度计****************/

void RCC_Configuration(void);

int main(void)
{			
	eMBErrorCode eStatus;
	
	RCC_Configuration();					/*系统时钟初始化*/
	
	Get_SerialNum();
	StartUp_Init();								/*读取系统参数*/

	eStatus = eMBInit(MB_RTU,Sys_Para_T.Addr,0,Sys_Para_T.Baud,Sys_Para_T.Parity); /*ModBus-RTU初始化*/
	eStatus = eMBEnable();
	if(eStatus != MB_ENOERR){};
		
	BEEP_GPIO_Configuration();
	BACK_GPIO_Configuration();
	LED_GPIO_Configuration(); 
	RELAY_GPIO_Configuration();  //继电器配置
	IO_GPIO_Configuration();
	TP4054_GPIO_Configuration(); 
	WIFIWakeUp_GPIO_Configuration();
	KEY_Init();			/*使用了TIM4*/ 
	I2C_Init();
	MessageInit();	/*必须放在 LCD初始化前边*/
	LCD_Init();
	DS1340_I2C_Init();
	DS1340_Init();
	SPI_Configuration();
	W25_GPIO_Configuration();
		
	StoreSysParamInit(&STOREPARAM_U);
	POWER_AD_Init();		
		
	DIS_SystemInit();
	
		
	while(1)
	{	
		(void)eMBPoll();
		
		ModBus_Message_Deal(&MB_Mes);
		
		Key_Action();
		
		USART_Recieve_Process();
	}
}

void RCC_Configuration(void)
{
  SystemInit();//8m
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

}
