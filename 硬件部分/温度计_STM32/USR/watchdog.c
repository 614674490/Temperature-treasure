#include "pbdata.h"

void IWDG_Init(int prer,int rlr)
{
	IWDG->KR=0X5555;      //解除寄存器保护        
	IWDG->PR=prer;         // 写入初始化分频值
	IWDG->RLR=rlr;            // 写入自动装载值
	IWDG->KR=0XAAAA;     //开启寄存器保护
	IWDG->KR=0XCCCC;       //启动看门狗
}

void IWDG_Feed(void)
{
	IWDG->KR = 0xaaaa;
}



