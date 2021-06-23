#include "pbdata.h"

io_ ADIN_T;

void IO_GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin= ADIN1 | ADIN2;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(IO_GPIO, &GPIO_InitStructure);
}

void ADIN_GET_IO(void)
{
	ADIN_T.usr_.BIT0 = READ_ADIN1;
	ADIN_T.usr_.BIT1 = READ_ADIN2;
	
	ucRegDiscBuf[0] = ADIN_T.iobuf;
}



