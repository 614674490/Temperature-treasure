#include "pbdata.h"

void IWDG_Init(int prer,int rlr)
{
	IWDG->KR=0X5555;      //����Ĵ�������        
	IWDG->PR=prer;         // д���ʼ����Ƶֵ
	IWDG->RLR=rlr;            // д���Զ�װ��ֵ
	IWDG->KR=0XAAAA;     //�����Ĵ�������
	IWDG->KR=0XCCCC;       //�������Ź�
}

void IWDG_Feed(void)
{
	IWDG->KR = 0xaaaa;
}



