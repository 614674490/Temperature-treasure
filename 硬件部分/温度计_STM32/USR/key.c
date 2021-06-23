#include "pbdata.h"

key_t Key_T;

void KEY_GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin= KEY_S1 | KEY_S2 | KEY_S3 | KEY_S4;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(KEY_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin= KEYS5_PORT;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(KEYS5_GPIO, &GPIO_InitStructure);
}

void KEY_Init(void)
{
	KEY_GPIO_Configuration();
	TIME4_Init(19,799);			/*定时20ms*/
}

unsigned char key_get(void)
{
	unsigned char key_Sn[5]={0,0,0,0,0};
	
	key_Sn[0] = READ_S1;
	key_Sn[1] = READ_S2;
	key_Sn[2] = READ_S3;
	key_Sn[3] = READ_S4;
	key_Sn[4] = READ_S5;
	
	return key_Sn[0] | key_Sn[1]<<1 | key_Sn[2]<<2 | key_Sn[3]<<3 | key_Sn[4]<<4;
}

/*按键处理函数*/
void Key_Action(void)
{				
	if(Key_T.IsKeyDown == 1)
	{	
		MEN_KEY(Key_T.KeyValue);
		Update_Display(DISBUF_U);
		Key_T.IsKeyDown = 0;
	}
}
















