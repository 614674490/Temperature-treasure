#include "pbdata.h"

GPIO_TypeDef* SHT75_PORT=GPIOC;
uint16_t SHT75_SCK=GPIO_Pin_6;         /*数据接口SCK 引脚定义*/
uint16_t SHT75_SDA=GPIO_Pin_7;         /*数据接口SDA 引脚定义*/

SHT75 SHT75_T;

//以下为底层子函数

/*内部用延时函数*/
void  Delay (uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}

void SHT75_Init(void) 
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = SHT75_SDA|SHT75_SCK;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//最高输出速度为50MHz
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出
	GPIO_Init(SHT75_PORT, &GPIO_InitStructure);
}

void SHT75_10_SDA_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = SHT75_SDA;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//最高输出速度为50MHz
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出
	GPIO_Init(SHT75_PORT, &GPIO_InitStructure);
}

void SHT75_10_SDA_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = SHT75_SDA;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//推挽输出
	GPIO_Init(SHT75_PORT, &GPIO_InitStructure);
}


/*******************************************************************************************
* 函数名：   SHT15_Write_Byte
* 功能描述： 写入一个字节，并检查从设备应答：“有应答”返回0；“无应答”返回1
* 入口参数： 要写入的字节，uchar型
* 出口参数： 成功（0）/失败（1）标志
* 备注：     
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
* 函数名：   SHT15_Read_Byte
* 功能描述： 读出一个字节，并根据输入参数决定是否发送应答位，1－发送“有应答”
* 入口参数： 应答位标志，1－读出1个字节后发送“有应答”
* 出口参数： 成功（0）/失败（1）标志
* 备注：     
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
* 函数名：   SHT15_Trans_Start
* 功能描述： 启动总线传输
* 入口参数： 无
* 出口参数： 无
* 备注：     
* 时序：
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
* 函数名：   SHT15_Measure
* 功能描述： 测量1次（可选择温度/湿度）
* 入口参数： 测量结果缓冲区首址，校验和缓冲区首址，测量模式（温度/湿度）
* 出口参数： 成功（0）/失败（1）标志
* 备注：     
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
			error+=1;               //超时出错
			break;
		}
	}

	SHT75_10_SDA_OUT();

	*(p_value)   = SHT75_Read_Byte(ACK);    //读第1个字节(MSB)
	*(p_value+1) = SHT75_Read_Byte(ACK);    //读第2个字节(LSB)
	*p_checksum  = SHT75_Read_Byte(noACK);  //读取校验和

	return error;
}

//温度转换函数，返回结果为5字节，如：-12.3
float SHT75_convert_temp(unsigned char *pdata)
{
	float t;
	int d1 = -4000;
	t = d1 + ((pdata[0]<<8) + pdata[1]);	//结果扩大100倍
	t/=100;
	
	return t;

}

//湿度转换函数，返回结果为2位字节，如：34
float SHT75_convert_humi(unsigned char *pdata)
{
	int c1 = -400;
	int c2 = 4;
	float f  = c1 + c2*((pdata[0]<<8) + pdata[1]);//结果扩大100倍
	f/=100;
	
	if(f>100)         /*限幅*/
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





















