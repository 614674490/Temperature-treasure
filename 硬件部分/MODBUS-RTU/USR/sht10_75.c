#include "pbdata.h"

GPIO_TypeDef* SHT75_PORT=GPIOC;
uint16_t SHT75_SCK=GPIO_Pin_6;         /*���ݽӿ�SCK ���Ŷ���*/
uint16_t SHT75_SDA=GPIO_Pin_7;         /*���ݽӿ�SDA ���Ŷ���*/

SHT75 SHT75_T;

//����Ϊ�ײ��Ӻ���

/*�ڲ�����ʱ����*/
void  Delay (uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}

void SHT75_Init(void) 
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = SHT75_SDA|SHT75_SCK;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�������ٶ�Ϊ50MHz
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������
	GPIO_Init(SHT75_PORT, &GPIO_InitStructure);
}

void SHT75_10_SDA_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = SHT75_SDA;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�������ٶ�Ϊ50MHz
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������
	GPIO_Init(SHT75_PORT, &GPIO_InitStructure);
}

void SHT75_10_SDA_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = SHT75_SDA;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//�������
	GPIO_Init(SHT75_PORT, &GPIO_InitStructure);
}


/*******************************************************************************************
* ��������   SHT15_Write_Byte
* ���������� д��һ���ֽڣ��������豸Ӧ�𣺡���Ӧ�𡱷���0������Ӧ�𡱷���1
* ��ڲ����� Ҫд����ֽڣ�uchar��
* ���ڲ����� �ɹ���0��/ʧ�ܣ�1����־
* ��ע��     
*******************************************************************************************/
unsigned char SHT75_Write_Byte(unsigned char value)
{ 
	unsigned char i,error=0;

	SHT75_10_SDA_OUT();

	for (i=0x80;i>0;i/=2)
	{ 
		if (i & value)
			SHT75_SDA_H;
		else
			SHT75_SDA_L;   
		
		SHT75_SCK_H;
		Delay(1);
		SHT75_SCK_L;
	}

	SHT75_SCK_H;

	SHT75_10_SDA_IN();

	error=SHT75_SDA_IN;

	SHT75_10_SDA_OUT();

	SHT75_SCK_L;
	
	return error;
}

/*******************************************************************************************
* ��������   SHT15_Read_Byte
* ���������� ����һ���ֽڣ�������������������Ƿ���Ӧ��λ��1�����͡���Ӧ��
* ��ڲ����� Ӧ��λ��־��1������1���ֽں��͡���Ӧ��
* ���ڲ����� �ɹ���0��/ʧ�ܣ�1����־
* ��ע��     
*******************************************************************************************/
unsigned char SHT75_Read_Byte(unsigned char ack)
{ 
	unsigned char i,val=0;

	SHT75_10_SDA_IN();

	SHT75_SDA_H;

	for (i=0x80;i>0;i/=2)
	{
		SHT75_SCK_H;
		
		if (SHT75_SDA_IN)
			val=(val | i);
		
		SHT75_SCK_L;  					 
	}

	SHT75_10_SDA_OUT();

	if(ack==1)
	{
		SHT75_SDA_L;
	}else
	{
		SHT75_SDA_H;
	}
		

	SHT75_SCK_H;
	Delay(1);
	SHT75_SCK_L;
	Delay(1);;							    
	SHT75_SDA_H;
	
	return val;
}

/*******************************************************************************************
* ��������   SHT15_Trans_Start
* ���������� �������ߴ���
* ��ڲ����� ��
* ���ڲ����� ��
* ��ע��     
* ʱ��
      _____         ________
DATA:      |_______|
          ___     ___
SCK : ___|   |___|   |______
*******************************************************************************************/
void SHT75_Trans_Start(void)
{  
	SHT75_SDA_H;
	SHT75_SCK_L;
	Delay(1);
	SHT75_SCK_H;
	Delay(1);
	SHT75_SDA_L;
	Delay(1);
	SHT75_SCK_L;
	Delay(1);
	SHT75_SCK_H;
	Delay(1);
	SHT75_SDA_H;
	Delay(1);
	SHT75_SCK_L;	   
}

/*******************************************************************************************
* ��������   SHT15_Measure
* ���������� ����1�Σ���ѡ���¶�/ʪ�ȣ�
* ��ڲ����� ���������������ַ��У��ͻ�������ַ������ģʽ���¶�/ʪ�ȣ�
* ���ڲ����� �ɹ���0��/ʧ�ܣ�1����־
* ��ע��     
*******************************************************************************************/
unsigned char SHT75_Measure(unsigned char *p_value, unsigned char *p_checksum, unsigned char mode,u8 id)
{ 
	unsigned char error=0,overtime=0;

	switch(id)
	{
		case 1:
			SHT75_PORT=GPIOC;
			SHT75_SCK=GPIO_Pin_6;
			SHT75_SDA=GPIO_Pin_7;
			break;
		case 2:
			SHT75_PORT=GPIOA;
			SHT75_SCK=GPIO_Pin_11;
			SHT75_SDA=GPIO_Pin_12;
			break;
		default:
			break;
	}

	SHT75_Init();

	SHT75_Trans_Start();
	switch(mode)
	{
		case TEMP : 
			error+=SHT75_Write_Byte(SHT75_CMD_TE); 
			break;
		case HUMI : 
			error+=SHT75_Write_Byte(SHT75_CMD_RH);
			break;
		default   : 
			break;	 
	}

	SHT75_10_SDA_IN();

	while(SHT75_SDA_IN)
	{
		delay_ms(2);
		overtime++;
		if(overtime>130)
		{
			overtime=0;
			error+=1;               //��ʱ����
			break;
		}
	}

	SHT75_10_SDA_OUT();

	*(p_value)   = SHT75_Read_Byte(ACK);    //����1���ֽ�(MSB)
	*(p_value+1) = SHT75_Read_Byte(ACK);    //����2���ֽ�(LSB)
	*p_checksum  = SHT75_Read_Byte(noACK);  //��ȡУ���

	return error;
}

//�¶�ת�����������ؽ��Ϊ5�ֽڣ��磺-12.3
float SHT75_convert_temp(unsigned char *pdata)
{
	float t;
	int d1 = -4000;
	t = d1 + ((pdata[0]<<8) + pdata[1]);	//�������100��
	t/=100;
	
	return t;

}

//ʪ��ת�����������ؽ��Ϊ2λ�ֽڣ��磺34
float SHT75_convert_humi(unsigned char *pdata)
{
	int c1 = -400;
	int c2 = 4;
	float f  = c1 + c2*((pdata[0]<<8) + pdata[1]);//�������100��
	f/=100;
	
	if(f>100)         /*�޷�*/
		f=100;
	
	return f;
}

void SHT75_GetData(unsigned char id)
{
	switch(id)
	{
		case 1:
			SHT75_Measure(SHT75_T.temp_1_buf,SHT75_T.check,TEMP,id);
			SHT75_T.temp_1 = SHT75_convert_temp(SHT75_T.temp_1_buf);
			SHT75_Measure(SHT75_T.humi_1_buf,SHT75_T.check,HUMI,id);
			SHT75_T.humi_1 = SHT75_convert_humi(SHT75_T.humi_1_buf);
			break;
		case 2:
			SHT75_Measure(SHT75_T.temp_2_buf,SHT75_T.check,TEMP,id);
			SHT75_T.temp_2 = SHT75_convert_temp(SHT75_T.temp_2_buf);
			SHT75_Measure(SHT75_T.humi_2_buf,SHT75_T.check,HUMI,id);
			SHT75_T.humi_2 = SHT75_convert_humi(SHT75_T.humi_2_buf);
			break;
	}
	

}





















