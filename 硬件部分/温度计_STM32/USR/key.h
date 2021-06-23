#ifndef KEY_H
#define KEY_H

#include "pbdata.h"

/*按键相关 定义*/
typedef struct
{
  unsigned int  KeyDownCnt;   
	unsigned char key;	
	unsigned char KeyValue;
	unsigned char IsKeyDown;
}key_t;
extern key_t Key_T;

#define Short 1
#define Long  2

#define NOProce         0
#define YESProce        1

#define NO_KEY					0x1F
#define S1_DOWN					0x17
#define S2_DOWN					0x1B
#define S3_DOWN					0x1D
#define S4_DOWN					0x1E
#define S5_DOWN					0x0F

#define S1S3_DOWN				0x15
#define S1S2_DOWN				0x13
#define S2S3_DOWN				0x19

#define KEYS5_GPIO GPIOC
#define KEYS5_PORT GPIO_Pin_3

#define READ_S5	 GPIO_ReadInputDataBit(KEYS5_GPIO,KEYS5_PORT)

#define KEY_GPIO GPIOA
#define KEY_S1	 GPIO_Pin_0
#define KEY_S2	 GPIO_Pin_1
#define KEY_S3	 GPIO_Pin_4
#define KEY_S4	 GPIO_Pin_5

#define READ_S1	 GPIO_ReadInputDataBit(KEY_GPIO,KEY_S1)
#define READ_S2	 GPIO_ReadInputDataBit(KEY_GPIO,KEY_S2)
#define READ_S3	 GPIO_ReadInputDataBit(KEY_GPIO,KEY_S3)
#define READ_S4	 GPIO_ReadInputDataBit(KEY_GPIO,KEY_S4)

void KEY_Init(void);
unsigned char key_get(void);
void Key_Action(void);

#endif
