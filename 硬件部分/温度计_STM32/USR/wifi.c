#include "pbdata.h"

wifi_ WIFI_T;
int wifi_set=0;

void WIFIWakeUp_GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;	
	
	GPIO_InitStructure.GPIO_Pin=WIFIWakeUp_PORT;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(WIFIWakeUp_GPIO,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=WIFIPower_PORT;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(WIFIPower_GPIO,&GPIO_InitStructure);
	
	WIFI_PowerDown();
}

void WIFI_PowerDown(void)
{
	WIFI_PowerSet(0);
	WIFI_WakeUp(1);
}

void WIFI_PowerUp(void)
{
	WIFI_PowerSet(1);
	WIFI_WakeUp(1);
	delay_ms(5);
	WIFI_WakeUp(0);		/*一个上升沿唤醒*/
	delay_ms(5);
	WIFI_WakeUp(1);
}

/*
*AT指令发送函数，包含等待响应功能，非常好用
*入口参数：AT指令，待监测的响应指令，监测时长ms
*返回参数：0-无监测响应，1-响应正确，2-命令错误
*/
unsigned char WIFI_AT(char *SendStr,char *RespondStr,int RespondMSec,unsigned char isdis)
{
	int i=0;
	char buf[50];
	
	memset(&WIFI_T,0,sizeof(WIFI_T));
	memset(buf,0x0,sizeof(buf));
	
	if( strlen(SendStr)>0 )
	{
		sprintf(buf,"%s\r\n",SendStr);
		USART_PutStr(UART4,buf);
	}
		
	for(i=0;i<RespondMSec;i++)
	{
		if(strstr(WIFI_T.RecBuf,RespondStr))
		{
			return 1;
		}
		if(strstr(WIFI_T.RecBuf,"ERROR"))
		{
			return 2;
		}
		if(isdis == 1 )
			Wifi_SmartSta();
		
		delay_ms(1);
	}
	
	return 0;
}

void MessageInit(void)
{
	switch(Sys_Para_T.MessageMode)
	{
		case 0:				/*不通讯*/
			WIFI_PowerDown();		/*关闭WIFI电源*/
			break;
		case 1:				/*WIFI通讯*/
			WIFI_PowerUp();
			DIS_Wifi(1);
			WIFI_AT("AT+CWMODE=1","OK",100,0);  //STA
			WIFI_AT("ATE0","OK",100,0);       //关闭回显
			WIFI_AT("AT+CIPMUX=0","OK",100,0);   //单链接
			break;
		case 2:				/*GPRS通讯*/
			WIFI_PowerDown();
			DIS_GPRS(5);
			break;
	}
}

void CheckWifiLinkStatus(void)
{
	if(Sys_Para_T.MessageMode != 1) return;
	
	if( WIFI_AT("AT+CIPSTATUS","2",50,0) != 1)		/*WIFI没有连接*/
	{
		DIS_Wifi(1);
	}else
	{
		DIS_Wifi(5);
	}
}







