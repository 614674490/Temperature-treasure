#include "pbdata.h"

void SPI_Configuration(void)
{
	SPI_InitTypeDef 		SPI_InitStructure;
	GPIO_InitTypeDef   	GPIO_InitStructure;

	//SPI2 :                          SCK       MISO      MOSI
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	SPI_InitStructure.SPI_Direction=SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Mode=SPI_Mode_Master;					/*主机模式*/
	SPI_InitStructure.SPI_DataSize=SPI_DataSize_8b;			/*8位数据位*/
	SPI_InitStructure.SPI_CPOL=SPI_CPOL_High;						/*空闲时，始终总线为高电平*/
	SPI_InitStructure.SPI_CPHA=SPI_CPHA_2Edge;					/*数据采样发生在第二个跳变沿*/
	SPI_InitStructure.SPI_NSS=SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_4;	  /*时钟256分频  32M / 256 = 125K*/
	SPI_InitStructure.SPI_FirstBit=SPI_FirstBit_MSB;										/*高位在前*/
	SPI_InitStructure.SPI_CRCPolynomial = 7;														/*校验等级*/

	SPI_Init(SPI2,&SPI_InitStructure);

	SPI_Cmd(SPI2,ENABLE); //enable SPI
}

u8 SPI_SendByte(u8 byte)
{
	while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE)==RESET);
	SPI_I2S_SendData(SPI2,byte);

	while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_RXNE)==RESET);
	return SPI_I2S_ReceiveData(SPI2);
}



