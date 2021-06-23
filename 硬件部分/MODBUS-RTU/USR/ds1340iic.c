#include "pbdata.h"

void DS1340_I2C_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	
	GPIO_InitStructure.GPIO_Pin=DS1340_I2C_SCL|DS1340_I2C_SDA;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(DS1340_GPIO_I2C,&GPIO_InitStructure);

	DS1340_I2C_SCL_H;
	DS1340_I2C_SDA_H;
}

void DS1340_I2C_SDA_OUT(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;	
	
	GPIO_InitStructure.GPIO_Pin=DS1340_I2C_SDA;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(DS1340_GPIO_I2C,&GPIO_InitStructure);
}

void DS1340_I2C_SDA_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	
	GPIO_InitStructure.GPIO_Pin=DS1340_I2C_SDA;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(DS1340_GPIO_I2C,&GPIO_InitStructure);
}

//������ʼ�ź�
void DS1340_I2C_Start(void)
{
  DS1340_I2C_SDA_OUT();
	
	DS1340_I2C_SDA_H;
	DS1340_I2C_SCL_H;
	delay_us(3);
	DS1340_I2C_SDA_L;
	delay_us(3);
	DS1340_I2C_SCL_L;
}

//����ֹͣ�ź�
void DS1340_I2C_Stop(void)
{
   DS1340_I2C_SDA_OUT();

   DS1340_I2C_SCL_L;
   DS1340_I2C_SDA_L;
   DS1340_I2C_SCL_H;
   delay_us(3);
   DS1340_I2C_SDA_H;
   delay_us(3);
}

//��������Ӧ���ź�ACK
void DS1340_I2C_Ack(void)
{
   DS1340_I2C_SCL_L;
   DS1340_I2C_SDA_OUT();
   DS1340_I2C_SDA_L;
   delay_us(3);
   DS1340_I2C_SCL_H;
   delay_us(3);
   DS1340_I2C_SCL_L;
}

//����������Ӧ���ź�NACK
void DS1340_I2C_NAck(void)
{
   DS1340_I2C_SCL_L;
   DS1340_I2C_SDA_OUT();
   DS1340_I2C_SDA_H;
   delay_us(3);
   DS1340_I2C_SCL_H;
   delay_us(3);
   DS1340_I2C_SCL_L;
}
//�ȴ��ӻ�Ӧ���ź�
//����ֵ��1 ����Ӧ��ʧ��
//		  0 ����Ӧ��ɹ�
u8 DS1340_I2C_Wait_Ack(void)
{
	u8 tempTime=0;

	DS1340_I2C_SDA_IN();

	DS1340_I2C_SDA_H;
	delay_us(3);
	DS1340_I2C_SCL_H;
	delay_us(3);

	while(GPIO_ReadInputDataBit(DS1340_GPIO_I2C,DS1340_I2C_SDA))
	{
		tempTime++;
		if(tempTime>250)
		{
			DS1340_I2C_Stop();
			return 1;
		}	 
	}

	DS1340_I2C_SCL_L;
	return 0;
}
//I2C ����һ���ֽ�
void DS1340_I2C_Send_Byte(u8 txd)
{
	u8 i=0;

	DS1340_I2C_SDA_OUT();
	DS1340_I2C_SCL_L;//����ʱ�ӿ�ʼ���ݴ���

	for(i=0;i<8;i++)
	{
		if((txd&0x80)>0) //0x80  1000 0000
			DS1340_I2C_SDA_H;
		else
			DS1340_I2C_SDA_L;

		txd<<=1;
		DS1340_I2C_SCL_H;
		delay_us(3); //��������
		DS1340_I2C_SCL_L;
		delay_us(3);
	}
}

//I2C ��ȡһ���ֽ�

u8 DS1340_I2C_Read_Byte(u8 ack)
{
   u8 i=0,receive=0;

   DS1340_I2C_SDA_IN();
   for(i=0;i<8;i++)
   {
   	DS1340_I2C_SCL_L;
		delay_us(3);
		DS1340_I2C_SCL_H;
		receive<<=1;
		if(GPIO_ReadInputDataBit(DS1340_GPIO_I2C,DS1340_I2C_SDA))
		   receive++;
		delay_us(3);	
   }

   	if(ack==0)
	   	DS1340_I2C_NAck();
	else
		DS1340_I2C_Ack();

	return receive;
}























