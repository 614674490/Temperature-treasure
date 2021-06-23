#include "pbdata.h"

uint16_t IO_DS18B20;
DS18B20 Ds18_T;

/*DS18B20 ������������*/
void DS18B20_IO_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin=IO_DS18B20;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIO_DS18B20,&GPIO_InitStructure);
}

/*DS18B20 �����������*/
void DS18B20_IO_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin=IO_DS18B20;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIO_DS18B20,&GPIO_InitStructure);
}

/*��ָ���� DS18B20 ��ȡһ���ֽڵ�����*/
u8 DS18B20_Read_Byte()
{
	u8 i=0,TempData=0;
	
	for(i=0;i<8;i++)
	{
    TempData>>=1;
		
		DS18B20_IO_OUT();  //���
		DS18B20_DQ_Low;			//����
		DS18B20_DQ_High;  //�ͷ����ߣ�������
		DS18B20_IO_IN();
		
  	if(GPIO_ReadInputDataBit(GPIO_DS18B20,IO_DS18B20)==1)
		{
			TempData|=0x80;  //�����ݴӵ�λ��ʼ
		}
		delay_us(41);
	}
	
	return TempData;
}

/*������DS18B20 д��һ���ֽڵ�����*/
void DS18B20_Write_Byte(u8 dat)
{
	u8 i=0;
	
	DS18B20_IO_OUT();  
	
	for(i=0;i<8;i++)
	{
		DS18B20_DQ_Low;			//����
		delay_us(11);
		
		if((dat&0x01)==1)
		{
			DS18B20_DQ_High;  
		}
		else
		{
			DS18B20_DQ_Low;  
		}
		
		delay_us(53);
		DS18B20_DQ_High;  
		
		dat>>=1;  //׼����һλ���ݵķ���
	}
}

/*����DS18B20 ��λ*/
void DS18B20_Reset(void)
{
	DS18B20_IO_OUT();  
	DS18B20_DQ_Low;  
	delay_us(480);
	DS18B20_DQ_High;  
	delay_us(480);
}

/*��ȡָ�� DS18B20 ���¶�*/
double DS18B20_Get_wd(u8 id)
{
	u8 TL=0,TH=0;
	u16 temp;
	double wd=0;
	
	switch(id)
	{
		case 1:
			IO_DS18B20 = GPIO_Pin_8;
			break;
	}

	DS18B20_Reset();
	DS18B20_Write_Byte(0xcc);  //����ROM����
	DS18B20_Write_Byte(0x44);  //�¶�ת������
	
	delay_ms(50);
	DS18B20_Reset();
	DS18B20_Write_Byte(0xcc);  //����ROM����
	DS18B20_Write_Byte(0xbe);  //���¶�����
	
	TL=DS18B20_Read_Byte(); //LSB
	TH=DS18B20_Read_Byte(); //MSB
	
	temp=TH;
	temp=(temp<<8)+TL;
	
	if(temp==0xffff)			/*��Ϊһ��������û����Ӧ�Ĵ����ʶ*/
		return -100;
	
	if((temp&0xf800)==0xf800) //���¶��ж�ǰ5λ �Ƿ�Ϊ1
	{
		temp=~temp;
		temp=temp+1;
		wd=temp*(-0.0625);
	}
	else
	{
		wd=temp*(0.0625);
	}
	return wd;
}


