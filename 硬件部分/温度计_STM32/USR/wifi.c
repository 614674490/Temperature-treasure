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
	WIFI_WakeUp(0);		/*һ�������ػ���*/
	delay_ms(5);
	WIFI_WakeUp(1);
}

/*
*ATָ��ͺ����������ȴ���Ӧ���ܣ��ǳ�����
*��ڲ�����ATָ���������Ӧָ����ʱ��ms
*���ز�����0-�޼����Ӧ��1-��Ӧ��ȷ��2-�������
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
		case 0:				/*��ͨѶ*/
			WIFI_PowerDown();		/*�ر�WIFI��Դ*/
			break;
		case 1:				/*WIFIͨѶ*/
			WIFI_PowerUp();
			DIS_Wifi(1);
			WIFI_AT("AT+CWMODE=1","OK",100,0);  //STA
			WIFI_AT("ATE0","OK",100,0);       //�رջ���
			WIFI_AT("AT+CIPMUX=0","OK",100,0);   //������
			break;
		case 2:				/*GPRSͨѶ*/
			WIFI_PowerDown();
			DIS_GPRS(5);
			break;
	}
}

void CheckWifiLinkStatus(void)
{
	if(Sys_Para_T.MessageMode != 1) return;
	
	if( WIFI_AT("AT+CIPSTATUS","2",50,0) != 1)		/*WIFIû������*/
	{
		DIS_Wifi(1);
	}else
	{
		DIS_Wifi(5);
	}
}







