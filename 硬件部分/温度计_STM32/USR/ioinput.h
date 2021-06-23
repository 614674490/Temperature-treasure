#ifndef IOINPUT_H
#define IOINPUT_H

#include "pbdata.h"

typedef union
{
	unsigned char iobuf;
	struct
	{
		unsigned char BIT0:1;
		unsigned char BIT1:1;
		unsigned char BIT2:1;
		unsigned char BIT3:1;
		unsigned char BIT4:1;
		unsigned char BIT5:1;
		unsigned char BIT6:1;
		unsigned char BIT7:1;
	}usr_;
}io_;
extern io_ ADIN_T;

#define IO_GPIO GPIOB
#define ADIN1	  GPIO_Pin_0
#define ADIN2	  GPIO_Pin_1

#define READ_ADIN1	 GPIO_ReadInputDataBit(IO_GPIO,ADIN1)
#define READ_ADIN2	 GPIO_ReadInputDataBit(IO_GPIO,ADIN2)

void IO_GPIO_Configuration(void);
void ADIN_GET_IO(void);

#endif
