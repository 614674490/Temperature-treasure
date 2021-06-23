#include "pbdata.h"

uint16_t IO_DS18B20;
DS18B20 Ds18_T;

/*DS18B20 引脚配置输入*/
void DS18B20_IO_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin=IO_DS18B20;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIO_DS18B20,&GPIO_InitStructure);
}

/*DS18B20 引脚配置输出*/
void DS18B20_IO_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin=IO_DS18B20;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIO_DS18B20,&GPIO_InitStructure);
}

/*从指定的 DS18B20 读取一个字节的数据*/
u8 DS18B20_Read_Byte()
{
	u8 i=0,TempData=0;
	
	for(i=0;i<8;i++)
	{
    TempData>>=1;
		
		DS18B20_IO_OUT();  //输出
		DS18B20_DQ_Low;			//拉低
		DS18B20_DQ_High;  //释放总线，即拉高
		DS18B20_IO_IN();
		
  	if(GPIO_ReadInputDataBit(GPIO_DS18B20,IO_DS18B20)==1)
		{
			TempData|=0x80;  //读数据从低位开始
		}
		delay_us(41);
	}
	
	return TempData;
}

/*向所有DS18B20 写入一个字节的数据*/
void DS18B20_Write_Byte(u8 dat)
{
	u8 i=0;
	
	DS18B20_IO_OUT();  
	
	for(i=0;i<8;i++)
	{
		DS18B20_DQ_Low;			//拉低
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
		
		dat>>=1;  //准备下一位数据的发送
	}
}

/*所有DS18B20 复位*/
void DS18B20_Reset(void)
{
	DS18B20_IO_OUT();  
	DS18B20_DQ_Low;  
	delay_us(480);
	DS18B20_DQ_High;  
	delay_us(480);
}

/*获取指定 DS18B20 的温度*/
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
	DS18B20_Write_Byte(0xcc);  //跳过ROM命令
	DS18B20_Write_Byte(0x44);  //温度转换命令
	
	delay_ms(50);
	DS18B20_Reset();
	DS18B20_Write_Byte(0xcc);  //跳过ROM命令
	DS18B20_Write_Byte(0xbe);  //读温度命令
	
	TL=DS18B20_Read_Byte(); //LSB
	TH=DS18B20_Read_Byte(); //MSB
	
	temp=TH;
	temp=(temp<<8)+TL;
	
	if(temp==0xffff)			/*作为一个传感器没有响应的错误标识*/
		return -100;
	
	if((temp&0xf800)==0xf800) //负温度判断前5位 是否都为1
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


