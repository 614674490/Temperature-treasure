#ifndef DS1340IIC_H
#define DS1340IIC_H

#include "pbdata.h"

//如果移植程序时只要改一下三个地方就行了
#define DS1340_I2C_SCL GPIO_Pin_6
#define DS1340_I2C_SDA GPIO_Pin_7
#define DS1340_GPIO_I2C GPIOB

#define DS1340_I2C_SCL_H GPIO_SetBits(DS1340_GPIO_I2C,DS1340_I2C_SCL)
#define DS1340_I2C_SCL_L GPIO_ResetBits(DS1340_GPIO_I2C,DS1340_I2C_SCL)

#define DS1340_I2C_SDA_H GPIO_SetBits(DS1340_GPIO_I2C,DS1340_I2C_SDA)
#define DS1340_I2C_SDA_L GPIO_ResetBits(DS1340_GPIO_I2C,DS1340_I2C_SDA)

void DS1340_I2C_Init(void);
void DS1340_I2C_SDA_OUT(void);
void DS1340_I2C_SDA_IN(void);
void DS1340_I2C_Start(void);
void DS1340_I2C_Stop(void);
void DS1340_I2C_Ack(void);
void DS1340_I2C_NAck(void);
u8   DS1340_I2C_Wait_Ack(void);
void DS1340_I2C_Send_Byte(u8 txd);
u8   DS1340_I2C_Read_Byte(u8 ack);




#endif
