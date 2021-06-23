#ifndef W25Q64_H
#define W25Q64_H

#include "pbdata.h"

#define W25X_ReadStatusReg  0x05
#define W25X_WriteStatusReg 0x01
#define W25X_WriteEnable    0x06
#define W25X_WriteDisable   0x04
#define W25X_ChipErase      0x60
#define W25X_SectorErase    0x20
#define W25X_PowerDown      0xb9
#define W25X_ReleasePowerDown 0xab
#define W25X_ReadData       0x03
#define W25X_PageProgram		0x02


#define W25_HOLDGPIO GPIOA
#define W25_HOLDPort GPIO_Pin_8

#define W25_NSSGPIO GPIOB
#define W25_NSSPort GPIO_Pin_12

#define W25_WPGPIO GPIOC
#define W25_WPPort GPIO_Pin_9

#define W25_SET_HOLD(n)  ((n) ? (W25_HOLDGPIO->BSRR = W25_HOLDPort):(W25_HOLDGPIO->BRR = W25_HOLDPort))
#define W25_SET_NSS(n)  ((n) ? (W25_NSSGPIO->BSRR = W25_NSSPort):(W25_NSSGPIO->BRR = W25_NSSPort))
#define W25_SET_WP(n)  ((n) ? (W25_WPGPIO->BSRR = W25_WPPort):(W25_WPGPIO->BRR = W25_WPPort))

void W25_GPIO_Configuration(void);
void SPI_Flash_Read(u8* pBuffer,u32 ReadAddr,u16 NumByteToRead);
void SPI_Flash_Write(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite);

#endif
