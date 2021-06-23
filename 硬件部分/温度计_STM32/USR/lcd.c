#include "pbdata.h"

disbuf_ DISBUF_U;

unsigned char numbuf[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x0};/*���� 0~9 10�����֣�A~F ,һ���հ�ʲô������ʾ*/


void BACK_GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;	
	
	GPIO_InitStructure.GPIO_Pin=BACK0_PORT;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(BACK0_GPIO,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=BACK1_PORT;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(BACK1_GPIO,&GPIO_InitStructure);
	
	BACKLIGHT_SET(Sys_Para_T.BackLightMode,0,0);
}

void BACKLIGHT_SET(unsigned char mode,unsigned char r,unsigned char b)
{
	switch(mode)
	{
		case 0:
			SET_BLUE(0);
			SET_RED(0);
			break;
		case 1:
			{
				switch(r)
				{
					case 0:
						SET_RED(0);
						break;
					case 1:
						SET_RED(1);
						break;
					default:
						break;
				}
				
				switch(b)
				{
					case 0:
						SET_BLUE(0);
						break;
					case 1:
						SET_BLUE(1);
						break;
					default:
						break;
				}
			}
			break;
		case 2:
			SET_BLUE(1);
			SET_RED(0);
			break;
		default:
			break;
	}
}

void LCD_WriteCMD(unsigned char cmdbyte,unsigned char cmdset)
{
	I2C_Start();
	
	I2C_Send_Byte(0x7c);
	I2C_Wait_Ack();
	
	I2C_Send_Byte(cmdbyte);
	I2C_Wait_Ack();
	I2C_Send_Byte(cmdset);
	I2C_Wait_Ack();
	
	I2C_Stop();
}

void LCD_ReadRegPage(unsigned char cmdbyte,unsigned char regaddr,unsigned char *buf,int len)
{
	int i=0;
	
	I2C_Start();
	
	I2C_Send_Byte(0x7c);
	I2C_Wait_Ack();
	
	I2C_Send_Byte(cmdbyte);
	I2C_Wait_Ack();
	I2C_Send_Byte(regaddr);
	I2C_Wait_Ack();
	
	I2C_Stop();
	I2C_Start();
	
	I2C_Send_Byte(0x7d);
	I2C_Wait_Ack();
	
	for(i=0;i<len-1;i++)
	{
		buf[i] = I2C_Read_Byte(1);
	}
	
	buf[len-1] = I2C_Read_Byte(0);
	
	I2C_Stop();
}

void LCD_WriteRegPage(unsigned char cmdbyte,unsigned char regaddr,unsigned char *buf,int len)
{
	int i=0;
	
	I2C_Start();
	
	I2C_Send_Byte(0x7c);
	I2C_Wait_Ack();
	
	I2C_Send_Byte(cmdbyte);
	I2C_Wait_Ack();
	I2C_Send_Byte(regaddr);
	I2C_Wait_Ack();
	
	for(i=0;i<len;i++)
	{
		I2C_Send_Byte(buf[i]);
		I2C_Wait_Ack();
	}
	
	I2C_Stop();
}

void LCD_Init(void)
{
	unsigned char buf[0x33];
	
	LCD_WriteCMD(0x82,0x02);			/*����ģʽ 1/8 duty   1/3 bias*/
	LCD_WriteCMD(0x86,0x00);			/*֡Ƶ��   80Hz*/
	LCD_WriteCMD(0x8a,0x30);			/*�ڲ���ѹ����*/
	LCD_WriteCMD(0x88,0x00);			/*��˸Ƶ�� �ر�*/
	LCD_WriteCMD(0x84,0x03);			/*ϵͳģʽ �ڲ������򿪣�LCD��ʾ����*/
	
	memset(buf,0x0,0x33);
	LCD_WriteRegPage(0x80,0x0,buf,0x33);
	
	memset(&DISBUF_U,0x0,sizeof(DISBUF_U));	/*�����ʾ������������ʾ*/
	LCD_WriteRegPage(0x80,0x0,DISBUF_U.buf,sizeof(DISBUF_U.buf));	
}

void LCD_CLOSE(void)
{
	LCD_WriteCMD(0x84,0x00);
}

void Update_Display(disbuf_ dis_u)				/*ϵͳ��ʱˢ��ȫ����������ʹ����ֻ�ı��ڴ����ݣ�*/
{
	LCD_WriteRegPage(0x80,0x0,dis_u.buf,sizeof(dis_u.buf));
}

/*************************************************����Ϊ��ʾĳЩ�ض��ַ��ĺ���,ֻ�Ǹı���ʾ�����ֵ******************************/
void DIS_Suona(unsigned char key,unsigned char val)		/*��������С���ȣ�1�������*/
{
	switch(key)
	{
		case 1:
			DISBUF_U.usr_.gether_p1_p2_p3_p4_t1_t2_t3_t4_.p1=val;
			break;
		case 2:
			DISBUF_U.usr_.gether_p1_p2_p3_p4_t1_t2_t3_t4_.t1=val;
			break;
		default:
			break;
	}
}

void DIS_Minus(unsigned char key,unsigned char val)		/*�����������ţ�1�������*/
{
	switch(key)
	{
		case 1:
			DISBUF_U.usr_.gether_p1_p2_p3_p4_t1_t2_t3_t4_.p4=val;
			break;
		case 2:
			DISBUF_U.usr_.gether_p1_p2_p3_p4_t1_t2_t3_t4_.t4=val;
			break;
		default:
			break;
	}
}

void DIS_TOPDOWN(unsigned char key,unsigned char val)		/*����� ���� ���¼�ͷ , 1�������*/
{
	if(val > 3) val = 0;
	
	switch(key)
	{
		case 1:
			DISBUF_U.usr_.gether_p1_p2_p3_p4_t1_t2_t3_t4_.p2=(val>>0)&0x01;
			DISBUF_U.usr_.gether_p1_p2_p3_p4_t1_t2_t3_t4_.p3=(val>>1)&0x01;
			break;
		case 2:
			DISBUF_U.usr_.gether_p1_p2_p3_p4_t1_t2_t3_t4_.t2=(val>>0)&0x01;
			DISBUF_U.usr_.gether_p1_p2_p3_p4_t1_t2_t3_t4_.t3=(val>>1)&0x01;
			break;
		default:
			break;
	}
}

void DIS_DC(unsigned char val)													/*��ʾ���϶ȷ��ţ�0-����ʾ��1-�㣬2-C��3-��,һ���������÷��ţ����ǵ�һ�е�*/
{
	if(val > 3) val = 0;
	
#ifdef LCD_A
	DISBUF_U.usr_.gether_5b2_10b2_p11_p12_.p11_1=(val>>0)&0x01;
	DISBUF_U.usr_.gether_13_17_.sm13_1=(val>>1)&0x01;
#else
	DISBUF_U.usr_.gether_5b2_10b2_p11_p12_.p11_1=(val>>0)&0x01;
	DISBUF_U.usr_.gether_p11_p13_p14_p15_p16_p17_p18_t14_.p11_2=(val>>1)&0x01;
#endif
}

void DIS_KW(unsigned char val)													/*��ʾǧ�߷��ţ�0-����ʾ��1-k��2-w��3-kw*/
{
	if(val > 3) val = 0;
	
	DISBUF_U.usr_.gether_p11_p13_p14_p15_p16_p17_p18_t14_.p17=(val>>0)&0x01;
	DISBUF_U.usr_.gether_p11_p13_p14_p15_p16_p17_p18_t14_.p13=(val>>1)&0x01;
}

void DIS_MV(unsigned char val)													/*0-����ʾ��1-m��2-v��3-mv*/
{
	if(val > 3) val = 0;
	
	DISBUF_U.usr_.gether_p11_p13_p14_p15_p16_p17_p18_t14_.p18=(val>>0)&0x01;
	DISBUF_U.usr_.gether_p11_p13_p14_p15_p16_p17_p18_t14_.p14=(val>>1)&0x01;
}

void DIS_ugm3(unsigned char val)													/*0-����ʾ��1-ug/m3*/
{
	if(val > 1) val = 0;
	
	DISBUF_U.usr_.gether_p11_p13_p14_p15_p16_p17_p18_t14_.p15=(val>>0)&0x01;
}

void DIS_PPM(unsigned char val)													/*0-����ʾ��1-ppm*/
{
	if(val > 1) val = 0;
	
	DISBUF_U.usr_.gether_p11_p13_p14_p15_p16_p17_p18_t14_.p16=(val>>0)&0x01;
}

void DIS_FD(unsigned char val)													/*0-����ʾ��1-�H*/
{
	if(val > 1) val = 0;
	
	DISBUF_U.usr_.gether_5b2_10b2_p11_p12_.p12=(val>>0)&0x01;
}

void DIS_PC(unsigned char val)													/*0-����ʾ��1-%*/
{
	if(val > 1) val = 0;
	
	DISBUF_U.usr_.gether_2b2_7b2_t11_t12_.t11=(val>>0)&0x01;
}

void DIS_KLX(unsigned char val)													/*0-����ʾ��1-k��2-lx��3-klx*/
{
	if(val > 3) val = 0;
	
#ifdef LCD_A
	DISBUF_U.usr_.gether_p11_p13_p14_p15_p16_p17_p18_t14_.t14=(val>>0)&0x01;
	DISBUF_U.usr_.gether_p11_p13_p14_p15_p16_p17_p18_t14_.p11_2=(val>>1)&0x01;
#else
	DISBUF_U.usr_.gether_p11_p13_p14_p15_p16_p17_p18_t14_.t14=(val>>0)&0x01;
	DISBUF_U.usr_.gether_1_6_T13_T15_.t13=(val>>1)&0x01;
#endif
}

void DIS_KPa(unsigned char val)													/*0-����ʾ��1-k��2-pa��3-kpa*/
{
	if(val > 3) val = 0;
	
	
#ifdef LCD_A
	DISBUF_U.usr_.gether_1_6_T13_T15_.t15=(val>>0)&0x01;
	DISBUF_U.usr_.gether_1_6_T13_T15_.t13=(val>>1)&0x01;
#else
	DISBUF_U.usr_.gether_1_6_T13_T15_.t15=(val>>0)&0x01;
	DISBUF_U.usr_.gether_m11_m20_m21_m22_m23_m24_m26_t16_.t16=(val>>1)&0x01;
#endif
}

void DIS_ma(unsigned char val)													/*0-����ʾ��1-m��2-a��3-ma*/
{
	if(val > 3) val = 0;
	
#ifdef LCD_A
	DISBUF_U.usr_.gether_m11_m20_m21_m22_m23_m24_m26_t16_.m11_2=(val>>0)&0x01;
	DISBUF_U.usr_.gether_m11_m20_m21_m22_m23_m24_m26_t16_.t16=(val>>1)&0x01;
#else
	DISBUF_U.usr_.gether_24b1_t17_.t17=(val>>0)&0x01;
	DISBUF_U.usr_.gether_24b2_t18_.t18=(val>>1)&0x01;
#endif

}

void DIS_m_s(unsigned char val)													/*0-����ʾ��1-m/s*/
{
	if(val > 1) val = 0;

#ifdef LCD_A
	DISBUF_U.usr_.gether_m11_m20_m21_m22_m23_m24_m26_t16_.m24=(val>>0)&0x01;
#else
	DISBUF_U.usr_.gether_21b1_t19.t19=(val>>0)&0x01;
#endif
}

void DIS_LOW_DC(unsigned char val)											/*0-����ʾ��1-��,һ���������÷��ţ����ǵڶ��е�*/
{
	if(val > 1) val = 0;
	
	DISBUF_U.usr_.gether_2b2_7b2_t11_t12_.t12=(val>>0)&0x01;
}

void DIS_FIRST_POINT(unsigned char val)									/*0-����ʾ,1-���һ��С����*/
{
	if(val > 1) val = 0;
	
	DISBUF_U.usr_.gether_5b1_10b1_p10_t10_.p10=(val>>0)&0x01;
}

void DIS_SECOND_POINT(unsigned char val)								/*0-����ʾ,1-���һ��С����*/
{
	if(val > 1) val = 0;
	
	DISBUF_U.usr_.gether_5b1_10b1_p10_t10_.t10=(val>>0)&0x01;
}

void DIS_SECOND1_POINT(unsigned char val)								/*��ʾ�ڶ��е�һ��С����*/
{
	if(val > 1) val = 0;
	
	DISBUF_U.usr_.gether_2b1_7b1_p5_t5_.t5=(val>>0)&0x01;
}

void DIS_FIRST_COLON(unsigned char val)									/*0-����ʾ��1-��ʾ��һ��ð��*/
{
	if(val > 1) val = 0;
	
	switch(val)
	{
		case 0:
			DISBUF_U.usr_.gether_p6_p7_p8_p9_t6_t7_t8_t9_.p6 = 0;
			DISBUF_U.usr_.gether_p6_p7_p8_p9_t6_t7_t8_t9_.p8 = 0;
			break;
		case 1:
			DISBUF_U.usr_.gether_p6_p7_p8_p9_t6_t7_t8_t9_.p6 = 1;
			DISBUF_U.usr_.gether_p6_p7_p8_p9_t6_t7_t8_t9_.p8 = 1;
			break;
		default:
			DISBUF_U.usr_.gether_p6_p7_p8_p9_t6_t7_t8_t9_.p6 = 0;
			DISBUF_U.usr_.gether_p6_p7_p8_p9_t6_t7_t8_t9_.p8 = 0;
			break;
	}
}

void DIS_SENCOND_COLON(unsigned char val)									/*0-����ʾ��1-��ʾ�ڶ���ð��*/
{
	if(val > 1) val = 0;
	
	switch(val)
	{
		case 0:
			DISBUF_U.usr_.gether_p6_p7_p8_p9_t6_t7_t8_t9_.t6 = 0;
			DISBUF_U.usr_.gether_p6_p7_p8_p9_t6_t7_t8_t9_.t8 = 0;
			break;
		case 1:
			DISBUF_U.usr_.gether_p6_p7_p8_p9_t6_t7_t8_t9_.t6 = 1;
			DISBUF_U.usr_.gether_p6_p7_p8_p9_t6_t7_t8_t9_.t8 = 1;
			break;
		default:
			DISBUF_U.usr_.gether_p6_p7_p8_p9_t6_t7_t8_t9_.t6 = 0;
			DISBUF_U.usr_.gether_p6_p7_p8_p9_t6_t7_t8_t9_.t8 = 0;
			break;
	}
}

void DIS_NUM_1(unsigned char val)											  /*��һ����ͷ�ϵ� С����*/
{
	if(val > 15) val = 16;
	
	DISBUF_U.usr_.gether_1_6_T13_T15_.sm1_1 = (numbuf[val]>>0)&0x01;
	DISBUF_U.usr_.gether_1_6_T13_T15_.sm1_2 = (numbuf[val]>>1)&0x01;
	DISBUF_U.usr_.gether_1_6_T13_T15_.sm1_3 = (numbuf[val]>>2)&0x01;
	DISBUF_U.usr_.gether_1_6_.sm1_4	= (numbuf[val]>>3)&0x01;
	DISBUF_U.usr_.gether_1_6_.sm1_5 = (numbuf[val]>>4)&0x01;
	DISBUF_U.usr_.gether_1_6_.sm1_6 = (numbuf[val]>>5)&0x01;
	DISBUF_U.usr_.gether_1_6_.sm1_7 = (numbuf[val]>>6)&0x01;
}

void DIS_NUM_6(unsigned char val)											  /*�ڶ�����ͷ�ϵ� С����*/
{
	if(val > 15) val = 16;
	
	DISBUF_U.usr_.gether_1_6_T13_T15_.sm6_1 = (numbuf[val]>>0)&0x01;
	DISBUF_U.usr_.gether_1_6_T13_T15_.sm6_2 = (numbuf[val]>>1)&0x01;
	DISBUF_U.usr_.gether_1_6_T13_T15_.sm6_3 = (numbuf[val]>>2)&0x01;
	DISBUF_U.usr_.gether_1_6_.sm6_4	= (numbuf[val]>>3)&0x01;
	DISBUF_U.usr_.gether_1_6_.sm6_5 = (numbuf[val]>>4)&0x01;
	DISBUF_U.usr_.gether_1_6_.sm6_6 = (numbuf[val]>>5)&0x01;
	DISBUF_U.usr_.gether_1_6_.sm6_7 = (numbuf[val]>>6)&0x01;
}

void DIS_NUM_2b1(unsigned char val)											/*��һ�е�һ��������*/
{
	if(val > 15) val = 16;
	
	DISBUF_U.usr_.gether_2b1_7b1_p5_t5_.sm2_1 = (numbuf[val]>>0)&0x01;
	DISBUF_U.usr_.gether_2b1_7b1_p5_t5_.sm2_2 = (numbuf[val]>>1)&0x01;
	DISBUF_U.usr_.gether_2b1_7b1_p5_t5_.sm2_3 = (numbuf[val]>>2)&0x01;
	DISBUF_U.usr_.gether_2b1_7b1_.sm2_4 = (numbuf[val]>>3)&0x01;
	DISBUF_U.usr_.gether_2b1_7b1_.sm2_5 = (numbuf[val]>>4)&0x01;
	DISBUF_U.usr_.gether_2b1_7b1_.sm2_6 = (numbuf[val]>>5)&0x01;
	DISBUF_U.usr_.gether_2b1_7b1_.sm2_7 = (numbuf[val]>>6)&0x01;
}

void DIS_NUM_2b2(unsigned char val)											/*��һ�еڶ���������*/
{
	if(val > 15) val = 16;
	
	DISBUF_U.usr_.gether_2b2_7b2_t11_t12_.sm2_1 = (numbuf[val]>>0)&0x01;
	DISBUF_U.usr_.gether_2b2_7b2_t11_t12_.sm2_2 = (numbuf[val]>>1)&0x01;
	DISBUF_U.usr_.gether_2b2_7b2_t11_t12_.sm2_3 = (numbuf[val]>>2)&0x01;
	DISBUF_U.usr_.gether_2b2_7b2_.sm2_4 = (numbuf[val]>>3)&0x01;
	DISBUF_U.usr_.gether_2b2_7b2_.sm2_5 = (numbuf[val]>>4)&0x01;
	DISBUF_U.usr_.gether_2b2_7b2_.sm2_6 = (numbuf[val]>>5)&0x01;
	DISBUF_U.usr_.gether_2b2_7b2_.sm2_7 = (numbuf[val]>>6)&0x01;
}

void DIS_NUM_5b1(unsigned char val)											/*��һ�е�����������*/
{
	if(val > 15) val = 16;
	
	DISBUF_U.usr_.gether_5b1_10b1_p10_t10_.sm5_1 = (numbuf[val]>>0)&0x01;
	DISBUF_U.usr_.gether_5b1_10b1_p10_t10_.sm5_2 = (numbuf[val]>>1)&0x01;
	DISBUF_U.usr_.gether_5b1_10b1_p10_t10_.sm5_3 = (numbuf[val]>>2)&0x01;
	DISBUF_U.usr_.gether_5b1_10b1_.sm5_4 = (numbuf[val]>>3)&0x01;
	DISBUF_U.usr_.gether_5b1_10b1_.sm5_5 = (numbuf[val]>>4)&0x01;
	DISBUF_U.usr_.gether_5b1_10b1_.sm5_6 = (numbuf[val]>>5)&0x01;
	DISBUF_U.usr_.gether_5b1_10b1_.sm5_7 = (numbuf[val]>>6)&0x01;
}

void DIS_NUM_5b2(unsigned char val)											/*��һ�е��ĸ�������*/
{
	if(val > 15) val = 16;
	
	DISBUF_U.usr_.gether_5b2_10b2_p11_p12_.sm5_1 = (numbuf[val]>>0)&0x01;
	DISBUF_U.usr_.gether_5b2_10b2_p11_p12_.sm5_2 = (numbuf[val]>>1)&0x01;
	DISBUF_U.usr_.gether_5b2_10b2_p11_p12_.sm5_3 = (numbuf[val]>>2)&0x01;
	DISBUF_U.usr_.gether_5b2_10b2_.sm5_4 = (numbuf[val]>>3)&0x01;
	DISBUF_U.usr_.gether_5b2_10b2_.sm5_5 = (numbuf[val]>>4)&0x01;
	DISBUF_U.usr_.gether_5b2_10b2_.sm5_6 = (numbuf[val]>>5)&0x01;
	DISBUF_U.usr_.gether_5b2_10b2_.sm5_7 = (numbuf[val]>>6)&0x01;
}

void DIS_NUM_7b1(unsigned char val)											/*�ڶ��е�һ��������*/
{
	if(val > 15) val = 16;
	
	DISBUF_U.usr_.gether_2b1_7b1_p5_t5_.sm7_1 = (numbuf[val]>>0)&0x01;
	DISBUF_U.usr_.gether_2b1_7b1_p5_t5_.sm7_2 = (numbuf[val]>>1)&0x01;
	DISBUF_U.usr_.gether_2b1_7b1_p5_t5_.sm7_3 = (numbuf[val]>>2)&0x01;
	DISBUF_U.usr_.gether_2b1_7b1_.sm7_4 = (numbuf[val]>>3)&0x01;
	DISBUF_U.usr_.gether_2b1_7b1_.sm7_5 = (numbuf[val]>>4)&0x01;
	DISBUF_U.usr_.gether_2b1_7b1_.sm7_6 = (numbuf[val]>>5)&0x01;
	DISBUF_U.usr_.gether_2b1_7b1_.sm7_7 = (numbuf[val]>>6)&0x01;
}

void DIS_NUM_7b2(unsigned char val)											/*�ڶ��еڶ���������*/
{
	if(val > 15) val = 16;
	
	DISBUF_U.usr_.gether_2b2_7b2_t11_t12_.sm7_1 = (numbuf[val]>>0)&0x01;
	DISBUF_U.usr_.gether_2b2_7b2_t11_t12_.sm7_2 = (numbuf[val]>>1)&0x01;
	DISBUF_U.usr_.gether_2b2_7b2_t11_t12_.sm7_3 = (numbuf[val]>>2)&0x01;
	DISBUF_U.usr_.gether_2b2_7b2_.sm7_4 = (numbuf[val]>>3)&0x01;
	DISBUF_U.usr_.gether_2b2_7b2_.sm7_5 = (numbuf[val]>>4)&0x01;
	DISBUF_U.usr_.gether_2b2_7b2_.sm7_6 = (numbuf[val]>>5)&0x01;
	DISBUF_U.usr_.gether_2b2_7b2_.sm7_7 = (numbuf[val]>>6)&0x01;
}

void DIS_NUM_10b1(unsigned char val)											/*�ڶ��е�����������*/
{
	if(val > 15) val = 16;
	
	DISBUF_U.usr_.gether_5b1_10b1_p10_t10_.sm10_1 = (numbuf[val]>>0)&0x01;
	DISBUF_U.usr_.gether_5b1_10b1_p10_t10_.sm10_2 = (numbuf[val]>>1)&0x01;
	DISBUF_U.usr_.gether_5b1_10b1_p10_t10_.sm10_3 = (numbuf[val]>>2)&0x01;
	DISBUF_U.usr_.gether_5b1_10b1_.sm10_4 = (numbuf[val]>>3)&0x01;
	DISBUF_U.usr_.gether_5b1_10b1_.sm10_5 = (numbuf[val]>>4)&0x01;
	DISBUF_U.usr_.gether_5b1_10b1_.sm10_6 = (numbuf[val]>>5)&0x01;
	DISBUF_U.usr_.gether_5b1_10b1_.sm10_7 = (numbuf[val]>>6)&0x01;
}

void DIS_NUM_10b2(unsigned char val)											/*�ڶ��е��ĸ�������*/
{
	if(val > 15) val = 16;
	
	DISBUF_U.usr_.gether_5b2_10b2_p11_p12_.sm10_1 = (numbuf[val]>>0)&0x01;
	DISBUF_U.usr_.gether_5b2_10b2_p11_p12_.sm10_2 = (numbuf[val]>>1)&0x01;
	DISBUF_U.usr_.gether_5b2_10b2_p11_p12_.sm10_3 = (numbuf[val]>>2)&0x01;
	DISBUF_U.usr_.gether_5b2_10b2_.sm10_4 = (numbuf[val]>>3)&0x01;
	DISBUF_U.usr_.gether_5b2_10b2_.sm10_5 = (numbuf[val]>>4)&0x01;
	DISBUF_U.usr_.gether_5b2_10b2_.sm10_6 = (numbuf[val]>>5)&0x01;
	DISBUF_U.usr_.gether_5b2_10b2_.sm10_7 = (numbuf[val]>>6)&0x01;
}

void DIS_NUM_21b1(unsigned char val)										/*��ʾ ���½�4�������еĵ�һ��*/
{
	if(val > 15) val = 16;
	
#ifdef LCD_A
	DISBUF_U.usr_.gether_21b1_t19.sm21_1 = (numbuf[val]>>0)&0x01;
	DISBUF_U.usr_.gether_21b1_t19.sm21_6 = (numbuf[val]>>1)&0x01;
	DISBUF_U.usr_.gether_21b1_t19.sm21_5 = (numbuf[val]>>2)&0x01;
	DISBUF_U.usr_.gether_21b1_t19.sm21_4 = (numbuf[val]>>3)&0x01;
	DISBUF_U.usr_.gether_21b1_t19.sm21_3 = (numbuf[val]>>4)&0x01;
	DISBUF_U.usr_.gether_21b1_t19.sm21_2 = (numbuf[val]>>5)&0x01;
	DISBUF_U.usr_.gether_21b1_t19.sm21_7 = (numbuf[val]>>6)&0x01;
#else
	DISBUF_U.usr_.gether_21b1_t19.sm21_1 = (numbuf[val]>>0)&0x01;
	DISBUF_U.usr_.gether_21b1_t19.sm21_2 = (numbuf[val]>>1)&0x01;
	DISBUF_U.usr_.gether_21b1_t19.sm21_3 = (numbuf[val]>>2)&0x01;
	DISBUF_U.usr_.gether_21b1_t19.sm21_4 = (numbuf[val]>>3)&0x01;
	DISBUF_U.usr_.gether_21b1_t19.sm21_5 = (numbuf[val]>>4)&0x01;
	DISBUF_U.usr_.gether_21b1_t19.sm21_6 = (numbuf[val]>>5)&0x01;
	DISBUF_U.usr_.gether_21b1_t19.sm21_7 = (numbuf[val]>>6)&0x01;
#endif
}

void DIS_NUM_21b2(unsigned char val)											/*��ʾ ���½�4�������еĵڶ���*/
{
	if(val > 15) val = 16;

#ifdef LCD_A
	DISBUF_U.usr_.gether_21b2_n4_.sm21_1 = (numbuf[val]>>0)&0x01;
	DISBUF_U.usr_.gether_21b2_n4_.sm21_6 = (numbuf[val]>>1)&0x01;
	DISBUF_U.usr_.gether_21b2_n4_.sm21_5 = (numbuf[val]>>2)&0x01;
	DISBUF_U.usr_.gether_21b2_n4_.sm21_4 = (numbuf[val]>>3)&0x01;
	DISBUF_U.usr_.gether_21b2_n4_.sm21_3 = (numbuf[val]>>4)&0x01;
	DISBUF_U.usr_.gether_21b2_n4_.sm21_2 = (numbuf[val]>>5)&0x01;
	DISBUF_U.usr_.gether_21b2_n4_.sm21_7 = (numbuf[val]>>6)&0x01;
#else
	DISBUF_U.usr_.gether_21b2_n4_.sm21_1 = (numbuf[val]>>0)&0x01;
	DISBUF_U.usr_.gether_21b2_n4_.sm21_2 = (numbuf[val]>>1)&0x01;
	DISBUF_U.usr_.gether_21b2_n4_.sm21_3 = (numbuf[val]>>2)&0x01;
	DISBUF_U.usr_.gether_21b2_n4_.sm21_4 = (numbuf[val]>>3)&0x01;
	DISBUF_U.usr_.gether_21b2_n4_.sm21_5 = (numbuf[val]>>4)&0x01;
	DISBUF_U.usr_.gether_21b2_n4_.sm21_6 = (numbuf[val]>>5)&0x01;
	DISBUF_U.usr_.gether_21b2_n4_.sm21_7 = (numbuf[val]>>6)&0x01;
#endif
}

void DIS_NUM_24b1(unsigned char val)										/*��ʾ ���½�4�������еĵ�����*/
{
	if(val > 15) val = 16;

#ifdef LCD_A
	DISBUF_U.usr_.gether_24b1_t17_.sm24_1 = (numbuf[val]>>0)&0x01;
	DISBUF_U.usr_.gether_24b1_t17_.sm24_6 = (numbuf[val]>>1)&0x01;
	DISBUF_U.usr_.gether_24b1_t17_.sm24_5 = (numbuf[val]>>2)&0x01;
	DISBUF_U.usr_.gether_24b1_t17_.sm24_4 = (numbuf[val]>>3)&0x01;
	DISBUF_U.usr_.gether_24b1_t17_.sm24_3 = (numbuf[val]>>4)&0x01;
	DISBUF_U.usr_.gether_24b1_t17_.sm24_2 = (numbuf[val]>>5)&0x01;
	DISBUF_U.usr_.gether_24b1_t17_.sm24_7 = (numbuf[val]>>6)&0x01;
#else
	DISBUF_U.usr_.gether_24b1_t17_.sm24_1 = (numbuf[val]>>0)&0x01;
	DISBUF_U.usr_.gether_24b1_t17_.sm24_2 = (numbuf[val]>>1)&0x01;
	DISBUF_U.usr_.gether_24b1_t17_.sm24_3 = (numbuf[val]>>2)&0x01;
	DISBUF_U.usr_.gether_24b1_t17_.sm24_4 = (numbuf[val]>>3)&0x01;
	DISBUF_U.usr_.gether_24b1_t17_.sm24_5 = (numbuf[val]>>4)&0x01;
	DISBUF_U.usr_.gether_24b1_t17_.sm24_6 = (numbuf[val]>>5)&0x01;
	DISBUF_U.usr_.gether_24b1_t17_.sm24_7 = (numbuf[val]>>6)&0x01;
#endif
}

void DIS_NUM_24b2(unsigned char val)										/*��ʾ ���½�4�������еĵ��ĸ�*/
{
	if(val > 15) val = 16;

#ifdef LCD_A
	DISBUF_U.usr_.gether_24b2_t18_.sm24_1 = (numbuf[val]>>0)&0x01;
	DISBUF_U.usr_.gether_24b2_t18_.sm24_6 = (numbuf[val]>>1)&0x01;
	DISBUF_U.usr_.gether_24b2_t18_.sm24_5 = (numbuf[val]>>2)&0x01;
	DISBUF_U.usr_.gether_24b2_t18_.sm24_4 = (numbuf[val]>>3)&0x01;
	DISBUF_U.usr_.gether_24b2_t18_.sm24_3 = (numbuf[val]>>4)&0x01;
	DISBUF_U.usr_.gether_24b2_t18_.sm24_2 = (numbuf[val]>>5)&0x01;
	DISBUF_U.usr_.gether_24b2_t18_.sm24_7 = (numbuf[val]>>6)&0x01;
#else
	DISBUF_U.usr_.gether_24b2_t18_.sm24_1 = (numbuf[val]>>0)&0x01;
	DISBUF_U.usr_.gether_24b2_t18_.sm24_2 = (numbuf[val]>>1)&0x01;
	DISBUF_U.usr_.gether_24b2_t18_.sm24_3 = (numbuf[val]>>2)&0x01;
	DISBUF_U.usr_.gether_24b2_t18_.sm24_4 = (numbuf[val]>>3)&0x01;
	DISBUF_U.usr_.gether_24b2_t18_.sm24_5 = (numbuf[val]>>4)&0x01;
	DISBUF_U.usr_.gether_24b2_t18_.sm24_6 = (numbuf[val]>>5)&0x01;
	DISBUF_U.usr_.gether_24b2_t18_.sm24_7 = (numbuf[val]>>6)&0x01;
#endif
}

void DIS_NUM_11(unsigned char val)											/*��ʾNO. �ĵ�һ������*/
{
	if(val > 15) val = 16;

#ifdef LCD_A
	DISBUF_U.usr_.gether_12_16_m15_m18_.sm12_6= (numbuf[val]>>0)&0x01; //1
	DISBUF_U.usr_.gether_12_16_m15_m18_.sm12_7= (numbuf[val]>>1)&0x01; //2
	DISBUF_U.usr_.gether_12_16_m15_m18_.sm12_5= (numbuf[val]>>2)&0x01; //3
	DISBUF_U.usr_.gether_11_15_.sm15_1= (numbuf[val]>>3)&0x01; //4
	DISBUF_U.usr_.gether_11_15_.sm11_4= (numbuf[val]>>4)&0x01; //5
	DISBUF_U.usr_.gether_11_15_.sm11_2= (numbuf[val]>>5)&0x01; //6
	DISBUF_U.usr_.gether_11_15_.sm11_3= (numbuf[val]>>6)&0x01; //7
#else
	DISBUF_U.usr_.gether_11_15_.sm11_1 = (numbuf[val]>>0)&0x01;
	DISBUF_U.usr_.gether_11_15_.sm11_2 = (numbuf[val]>>1)&0x01;
	DISBUF_U.usr_.gether_11_15_.sm11_3 = (numbuf[val]>>2)&0x01;
	DISBUF_U.usr_.gether_11_15_.sm11_4 = (numbuf[val]>>3)&0x01;
	DISBUF_U.usr_.gether_11_15_m16_m17_.sm11_5 = (numbuf[val]>>4)&0x01;
	DISBUF_U.usr_.gether_11_15_m16_m17_.sm11_6 = (numbuf[val]>>5)&0x01;
	DISBUF_U.usr_.gether_11_15_m16_m17_.sm11_7 = (numbuf[val]>>6)&0x01;
#endif
}

void DIS_NUM_12(unsigned char val)											/*��ʾNO. �ĵڶ�������*/
{
	if(val > 15) val = 16;

#ifdef LCD_A
	DISBUF_U.usr_.gether_13_17_n1_msh_.sm13_6 = (numbuf[val]>>0)&0x01;	//1
	DISBUF_U.usr_.gether_13_17_n1_msh_.sm13_7 = (numbuf[val]>>1)&0x01;	//2
	DISBUF_U.usr_.gether_13_17_n1_msh_.sm13_5 = (numbuf[val]>>2)&0x01;	//3
	DISBUF_U.usr_.gether_12_16_.sm16_1 = (numbuf[val]>>3)&0x01;		//4
	DISBUF_U.usr_.gether_12_16_.sm12_4 = (numbuf[val]>>4)&0x01;		//5
	DISBUF_U.usr_.gether_12_16_.sm12_2 = (numbuf[val]>>5)&0x01;		//6
	DISBUF_U.usr_.gether_12_16_.sm12_3 = (numbuf[val]>>6)&0x01;		//7
#else
	DISBUF_U.usr_.gether_12_16_.sm12_1 = (numbuf[val]>>0)&0x01;
	DISBUF_U.usr_.gether_12_16_.sm12_2 = (numbuf[val]>>1)&0x01;
	DISBUF_U.usr_.gether_12_16_.sm12_3 = (numbuf[val]>>2)&0x01;
	DISBUF_U.usr_.gether_12_16_.sm12_4 = (numbuf[val]>>3)&0x01;
	DISBUF_U.usr_.gether_12_16_m15_m18_.sm12_5 = (numbuf[val]>>4)&0x01;
	DISBUF_U.usr_.gether_12_16_m15_m18_.sm12_6 = (numbuf[val]>>5)&0x01;
	DISBUF_U.usr_.gether_12_16_m15_m18_.sm12_7 = (numbuf[val]>>6)&0x01;
#endif
}

void DIS_NUM_13(unsigned char val)										/*��ʾ msh ���ĵ�һ������*/
{
	if(val > 15) val = 16;
	
#ifdef LCD_A
	DISBUF_U.usr_.gether_14_18_n2_msh_.msh_m = (numbuf[val]>>0)&0x01; //1
	DISBUF_U.usr_.gether_14_18_n2_msh_.sm14_6 = (numbuf[val]>>1)&0x01; //2
	DISBUF_U.usr_.gether_14_18_n2_msh_.sm14_7 = (numbuf[val]>>2)&0x01; //3

	DISBUF_U.usr_.gether_13_17_.sm17_1 = (numbuf[val]>>3)&0x01; //5
	DISBUF_U.usr_.gether_13_17_.sm13_4 = (numbuf[val]>>4)&0x01; //5
	DISBUF_U.usr_.gether_13_17_.sm13_2 = (numbuf[val]>>5)&0x01; //6
	DISBUF_U.usr_.gether_13_17_.sm13_3 = (numbuf[val]>>6)&0x01; //7
#else
	DISBUF_U.usr_.gether_13_17_.sm13_1 = (numbuf[val]>>0)&0x01;
	DISBUF_U.usr_.gether_13_17_.sm13_2 = (numbuf[val]>>1)&0x01;
	DISBUF_U.usr_.gether_13_17_.sm13_3 = (numbuf[val]>>2)&0x01;
	DISBUF_U.usr_.gether_13_17_.sm13_4 = (numbuf[val]>>3)&0x01;
	DISBUF_U.usr_.gether_13_17_n1_msh_.sm13_5 = (numbuf[val]>>4)&0x01;
	DISBUF_U.usr_.gether_13_17_n1_msh_.sm13_6 = (numbuf[val]>>5)&0x01;
	DISBUF_U.usr_.gether_13_17_n1_msh_.sm13_7 = (numbuf[val]>>6)&0x01;
#endif
}

void DIS_NUM_14(unsigned char val)											/*��ʾ msh ���ĵڶ�������*/
{
	if(val > 15) val = 16;
	
#ifdef LCD_A
	DISBUF_U.usr_.gether_19_n3_.n3 = (numbuf[val]>>0)&0x01; //1
	DISBUF_U.usr_.gether_19_n3_.sm19_1 = (numbuf[val]>>1)&0x01; //2
	DISBUF_U.usr_.gether_19_n3_.sm19_6 = (numbuf[val]>>2)&0x01; //3

	DISBUF_U.usr_.gether_14_18_.sm14_4 = (numbuf[val]>>3)&0x01; //4
	DISBUF_U.usr_.gether_14_18_.sm14_3 = (numbuf[val]>>4)&0x01; //5
	DISBUF_U.usr_.gether_14_18_.sm14_1 = (numbuf[val]>>5)&0x01; //6
	DISBUF_U.usr_.gether_14_18_.sm14_2 = (numbuf[val]>>6)&0x01; //7
#else
	DISBUF_U.usr_.gether_14_18_.sm14_1 = (numbuf[val]>>0)&0x01;
	DISBUF_U.usr_.gether_14_18_.sm14_2 = (numbuf[val]>>1)&0x01;
	DISBUF_U.usr_.gether_14_18_.sm14_3 = (numbuf[val]>>2)&0x01;
	DISBUF_U.usr_.gether_14_18_.sm14_4 = (numbuf[val]>>3)&0x01;
	DISBUF_U.usr_.gether_14_18_n2_msh_.sm14_5 = (numbuf[val]>>4)&0x01;
	DISBUF_U.usr_.gether_14_18_n2_msh_.sm14_6 = (numbuf[val]>>5)&0x01;
	DISBUF_U.usr_.gether_14_18_n2_msh_.sm14_7 = (numbuf[val]>>6)&0x01;
#endif
}

void DIS_NUM_15(unsigned char val)										/*��ʾID �ĵ�һ������*/
{
	if(val > 15) val = 16;
	
#ifdef LCD_A
	DISBUF_U.usr_.gether_11_15_.sm15_2 = (numbuf[val]>>0)&0x01;	//1
	DISBUF_U.usr_.gether_11_15_.sm15_3 = (numbuf[val]>>1)&0x01;	//2
	DISBUF_U.usr_.gether_11_15_.sm15_4 = (numbuf[val]>>2)&0x01;	//3

	DISBUF_U.usr_.gether_11_15_m16_m17_.m17 = (numbuf[val]>>3)&0x01;	//4
	DISBUF_U.usr_.gether_11_15_m16_m17_.sm15_5 = (numbuf[val]>>4)&0x01;	//5
	DISBUF_U.usr_.gether_11_15_m16_m17_.sm15_6 = (numbuf[val]>>5)&0x01;	//6
	DISBUF_U.usr_.gether_11_15_m16_m17_.sm15_7 = (numbuf[val]>>6)&0x01;	//7
#else
	DISBUF_U.usr_.gether_11_15_.sm15_1 = (numbuf[val]>>0)&0x01;
	DISBUF_U.usr_.gether_11_15_.sm15_2 = (numbuf[val]>>1)&0x01;
	DISBUF_U.usr_.gether_11_15_.sm15_3 = (numbuf[val]>>2)&0x01;
	DISBUF_U.usr_.gether_11_15_.sm15_4 = (numbuf[val]>>3)&0x01;
	DISBUF_U.usr_.gether_11_15_m16_m17_.sm15_5 = (numbuf[val]>>4)&0x01;
	DISBUF_U.usr_.gether_11_15_m16_m17_.sm15_6 = (numbuf[val]>>5)&0x01;
	DISBUF_U.usr_.gether_11_15_m16_m17_.sm15_7 = (numbuf[val]>>6)&0x01;
#endif
}

void DIS_NUM_16(unsigned char val)										/*��ʾID �ĵڶ�������*/
{
	if(val > 15) val = 16;
	
#ifdef LCD_A
	DISBUF_U.usr_.gether_12_16_.sm16_2 = (numbuf[val]>>0)&0x01;	//1
	DISBUF_U.usr_.gether_12_16_.sm16_3 = (numbuf[val]>>1)&0x01;	//2
	DISBUF_U.usr_.gether_12_16_.sm16_4 = (numbuf[val]>>2)&0x01;	//3

	DISBUF_U.usr_.gether_12_16_m15_m18_.m18 = (numbuf[val]>>3)&0x01;	//4
	DISBUF_U.usr_.gether_12_16_m15_m18_.sm16_5 = (numbuf[val]>>4)&0x01;	//5
	DISBUF_U.usr_.gether_12_16_m15_m18_.sm16_6 = (numbuf[val]>>5)&0x01;	//6
	DISBUF_U.usr_.gether_12_16_m15_m18_.sm16_7 = (numbuf[val]>>6)&0x01;	//7
#else
	DISBUF_U.usr_.gether_12_16_.sm16_1 = (numbuf[val]>>0)&0x01;
	DISBUF_U.usr_.gether_12_16_.sm16_2 = (numbuf[val]>>1)&0x01;
	DISBUF_U.usr_.gether_12_16_.sm16_3 = (numbuf[val]>>2)&0x01;
	DISBUF_U.usr_.gether_12_16_.sm16_4 = (numbuf[val]>>3)&0x01;
	DISBUF_U.usr_.gether_12_16_m15_m18_.sm16_5 = (numbuf[val]>>4)&0x01;
	DISBUF_U.usr_.gether_12_16_m15_m18_.sm16_6 = (numbuf[val]>>5)&0x01;
	DISBUF_U.usr_.gether_12_16_m15_m18_.sm16_7 = (numbuf[val]>>6)&0x01;
#endif
}

void DIS_NUM_17(unsigned char val)										/*��ʾID �ĵ���������*/
{
	if(val > 15) val = 16;
	
#ifdef LCD_A
	DISBUF_U.usr_.gether_13_17_.sm17_2 = (numbuf[val]>>0)&0x01;	//1
	DISBUF_U.usr_.gether_13_17_.sm17_3 = (numbuf[val]>>1)&0x01;	//2
	DISBUF_U.usr_.gether_13_17_.sm17_4 = (numbuf[val]>>2)&0x01;	//3

	DISBUF_U.usr_.gether_13_17_n1_msh_.n1_1 = (numbuf[val]>>3)&0x01;	//4
	DISBUF_U.usr_.gether_13_17_n1_msh_.sm17_5 = (numbuf[val]>>4)&0x01;	//5
	DISBUF_U.usr_.gether_13_17_n1_msh_.sm17_6 = (numbuf[val]>>5)&0x01;	//6
	DISBUF_U.usr_.gether_13_17_n1_msh_.sm17_7 = (numbuf[val]>>6)&0x01;	//7
#else
	DISBUF_U.usr_.gether_13_17_.sm17_1 = (numbuf[val]>>0)&0x01;
	DISBUF_U.usr_.gether_13_17_.sm17_2 = (numbuf[val]>>1)&0x01;
	DISBUF_U.usr_.gether_13_17_.sm17_3 = (numbuf[val]>>2)&0x01;
	DISBUF_U.usr_.gether_13_17_.sm17_4 = (numbuf[val]>>3)&0x01;
	DISBUF_U.usr_.gether_13_17_n1_msh_.sm17_5 = (numbuf[val]>>4)&0x01;
	DISBUF_U.usr_.gether_13_17_n1_msh_.sm17_6 = (numbuf[val]>>5)&0x01;
	DISBUF_U.usr_.gether_13_17_n1_msh_.sm17_7 = (numbuf[val]>>6)&0x01;
#endif
}

void DIS_NUM_18(unsigned char val)									/*��ʾ�·ݵ� �ڶ�������*/
{
	if(val > 15) val = 16;
	
#ifdef LCD_A
	DISBUF_U.usr_.gether_14_18_.sm18_1 = (numbuf[val]>>0)&0x01;
	DISBUF_U.usr_.gether_14_18_.sm18_2 = (numbuf[val]>>1)&0x01;
	DISBUF_U.usr_.gether_14_18_.sm18_3 = (numbuf[val]>>2)&0x01;
	DISBUF_U.usr_.gether_14_18_n2_msh_.n2 = (numbuf[val]>>3)&0x01;
	DISBUF_U.usr_.gether_14_18_n2_msh_.sm18_5 = (numbuf[val]>>4)&0x01;
	DISBUF_U.usr_.gether_14_18_n2_msh_.sm18_6 = (numbuf[val]>>5)&0x01;
	DISBUF_U.usr_.gether_14_18_n2_msh_.sm18_7 = (numbuf[val]>>6)&0x01;
#else
	DISBUF_U.usr_.gether_14_18_.sm18_1 = (numbuf[val]>>0)&0x01;
	DISBUF_U.usr_.gether_14_18_.sm18_2 = (numbuf[val]>>1)&0x01;
	DISBUF_U.usr_.gether_14_18_.sm18_3 = (numbuf[val]>>2)&0x01;
	DISBUF_U.usr_.gether_14_18_.sm18_4 = (numbuf[val]>>3)&0x01;
	DISBUF_U.usr_.gether_14_18_n2_msh_.sm18_5 = (numbuf[val]>>4)&0x01;
	DISBUF_U.usr_.gether_14_18_n2_msh_.sm18_6 = (numbuf[val]>>5)&0x01;
	DISBUF_U.usr_.gether_14_18_n2_msh_.sm18_7 = (numbuf[val]>>6)&0x01;
#endif
}

void DIS_NUM_19(unsigned char val)									/*��ʾ�� �ĵ�һ������*/
{
	if(val > 15) val = 16;
	
#ifdef LCD_A
	switch(val)
	{
		case 1:
			DISBUF_U.usr_.gether_19_n3_.sm19_3 = 1; //2
			DISBUF_U.usr_.gether_19_n3_.sm19_4 = 1; //3
			DISBUF_U.usr_.gether_19_n3_.sm19_5 = 0; //ʣ�µ�4�Σ���������������ģ����ܹ���ʾ3
			break;
		case 2:
			DISBUF_U.usr_.gether_19_n3_.sm19_3 = 1; //2
			DISBUF_U.usr_.gether_19_n3_.sm19_4 = 0; //3
			DISBUF_U.usr_.gether_19_n3_.sm19_5 = 1; //ʣ�µ�4�Σ���������������ģ����ܹ���ʾ3
			break;
		case 3:
			DISBUF_U.usr_.gether_19_n3_.sm19_3 = 1; //2
			DISBUF_U.usr_.gether_19_n3_.sm19_4 = 1; //3
			DISBUF_U.usr_.gether_19_n3_.sm19_5 = 1; //ʣ�µ�4�Σ���������������ģ����ܹ���ʾ3
			break;
		default:
			DISBUF_U.usr_.gether_19_n3_.sm19_3 = 0; //2
			DISBUF_U.usr_.gether_19_n3_.sm19_4 = 0; //3
			DISBUF_U.usr_.gether_19_n3_.sm19_5 = 0; //ʣ�µ�4�Σ���������������ģ����ܹ���ʾ3
			break;
	}
#else
	DISBUF_U.usr_.gether_19_n3_.sm19_1 = (numbuf[val]>>0)&0x01;
	DISBUF_U.usr_.gether_19_n3_.sm19_2 = (numbuf[val]>>1)&0x01;
	DISBUF_U.usr_.gether_19_n3_.sm19_3 = (numbuf[val]>>2)&0x01;
	DISBUF_U.usr_.gether_19_n3_.sm19_4 = (numbuf[val]>>3)&0x01;
	DISBUF_U.usr_.gether_19_n3_.sm19_5 = (numbuf[val]>>4)&0x01;
	DISBUF_U.usr_.gether_19_n3_.sm19_6 = (numbuf[val]>>5)&0x01;
	DISBUF_U.usr_.gether_19_n3_.sm19_7 = (numbuf[val]>>6)&0x01;
#endif
}
	
void DIS_NUM_20(unsigned char val)										/*��ʾ�� �ĵڶ�������*/
{
	if(val > 15) val = 16;
	
#ifdef LCD_A
	DISBUF_U.usr_.gether_20_msh_.sm20_1 = (numbuf[val]>>0)&0x01;	//1
	DISBUF_U.usr_.gether_20_msh_.sm20_6 = (numbuf[val]>>1)&0x01;	//2
	DISBUF_U.usr_.gether_20_msh_.sm20_5 = (numbuf[val]>>2)&0x01;	//3
	DISBUF_U.usr_.gether_20_msh_.sm20_4 = (numbuf[val]>>3)&0x01;	//4
	DISBUF_U.usr_.gether_20_msh_.sm20_3 = (numbuf[val]>>4)&0x01;	//5
	DISBUF_U.usr_.gether_20_msh_.sm20_2 = (numbuf[val]>>5)&0x01;	//6
	DISBUF_U.usr_.gether_20_msh_.sm20_7 = (numbuf[val]>>6)&0x01;	//7
#else
	DISBUF_U.usr_.gether_20_msh_.sm20_1 = (numbuf[val]>>0)&0x01;
	DISBUF_U.usr_.gether_20_msh_.sm20_2 = (numbuf[val]>>1)&0x01;
	DISBUF_U.usr_.gether_20_msh_.sm20_3 = (numbuf[val]>>2)&0x01;
	DISBUF_U.usr_.gether_20_msh_.sm20_4 = (numbuf[val]>>3)&0x01;
	DISBUF_U.usr_.gether_20_msh_.sm20_5 = (numbuf[val]>>4)&0x01;
	DISBUF_U.usr_.gether_20_msh_.sm20_6 = (numbuf[val]>>5)&0x01;
	DISBUF_U.usr_.gether_20_msh_.sm20_7 = (numbuf[val]>>6)&0x01;
#endif
}

void DIS_NUM_N1_N2(unsigned char val)			/*��������ϣ�ֻ����ʾ 0����1,��ʾ�·ݵ� ��һ������*/
{
	
#ifdef LCD_A
	switch(val)
	{
		case 1:
			DISBUF_U.usr_.gether_14_18_n2_msh_.sm14_5 = 1;
			break;
		default:
			DISBUF_U.usr_.gether_14_18_n2_msh_.sm14_5 = 0;
			break;
	}
#else
	switch(val)
	{
		case 0:
			DISBUF_U.usr_.gether_13_17_n1_msh_.n1_1 = 1;
			DISBUF_U.usr_.gether_14_18_n2_msh_.n2 = 1;
			break;
		case 1:
			DISBUF_U.usr_.gether_13_17_n1_msh_.n1_1 = 0;
			DISBUF_U.usr_.gether_14_18_n2_msh_.n2 = 1;
			break;
		default:
			DISBUF_U.usr_.gether_13_17_n1_msh_.n1_1 = 0;
			DISBUF_U.usr_.gether_14_18_n2_msh_.n2 = 0;
			break;
	}
#endif
}

void DIS_N3(unsigned char val)            /*��ʾʱ�ӵı�ʶ ������ĺ���*/
{
	if(val > 1) val = 0;
	
#ifdef LCD_A
	DISBUF_U.usr_.gether_21b1_t19.t19= val;
	DISBUF_U.usr_.gether_21b2_n4_.n4= val;
#else
	DISBUF_U.usr_.gether_19_n3_.n3 = val;
#endif
}

void DIS_N4(unsigned char val)            /*��ʾʱ�ӵ����ʶ*/
{
	if(val > 1) val = 0;
	
#ifdef LCD_A
	DISBUF_U.usr_.gether_19_n3_.sm19_2= val;
#else
	DISBUF_U.usr_.gether_21b2_n4_.n4 = val;
#endif
}

void DIS_No(unsigned char val)						/*��ʾNo ͼ��*/
{
	if(val > 1) val = 0;
	
	DISBUF_U.usr_.gether_11_15_m16_m17_.m16 = val;
}

void DIS_ID(unsigned char val)						/*��ʾID ͼ��*/
{
	if(val > 1) val = 0;
	
#ifdef LCD_A
	DISBUF_U.usr_.gether_11_15_m16_m17_.sm11_5 = val;
#else
	DISBUF_U.usr_.gether_11_15_m16_m17_.m17 = val;
#endif
}

void DIS_Usb(unsigned char val)						/*��ʾusb ͼ��*/
{
	if(val > 1) val = 0;
	
#ifdef LCD_A
	DISBUF_U.usr_.gether_11_15_m16_m17_.sm11_6 = val;
#else
	DISBUF_U.usr_.gether_12_16_m15_m18_.m15 = val;
#endif
}

void DIS_BlueTooth(unsigned char val)						/*��ʾ���� ͼ��*/
{
	if(val > 1) val = 0;
	
#ifdef LCD_A
	DISBUF_U.usr_.gether_11_15_m16_m17_.sm11_7 = val;
#else
	DISBUF_U.usr_.gether_12_16_m15_m18_.m18 = val;
#endif
}

void DIS_Printer(unsigned char val)						/*��ʾ��ӡ�� ͼ��*/
{
	if(val > 1) val = 0;
	
#ifdef LCD_A
	DISBUF_U.usr_.gether_m11_m20_m21_m22_m23_m24_m26_t16_.m20 = val;
#else
	DISBUF_U.usr_.gether_m8_m11_m12_m13_m14_m19_m25_m27_.m14 = val;
#endif
}

void DIS_Gps(unsigned char val)						/*��ʾ��λͼ�� ͼ��*/
{
	if(val > 1) val = 0;
	
#ifdef LCD_A
	DISBUF_U.usr_.gether_m11_m20_m21_m22_m23_m24_m26_t16_.m26 = val;
#else
	DISBUF_U.usr_.gether_m8_m11_m12_m13_m14_m19_m25_m27_.m19 = val;
#endif
}

void DIS_Set(unsigned char val)						/*��ʾ���� ͼ��*/
{
	if(val > 1) val = 0;

#ifdef LCD_A
	DISBUF_U.usr_.gether_m11_m20_m21_m22_m23_m24_m26_t16_.m21 = val;
#else
	DISBUF_U.usr_.gether_m8_m11_m12_m13_m14_m19_m25_m27_.m13 = val;
#endif
}

void DIS_UpLoad(unsigned char val)						/*��ʾ�ϴ� ͼ��*/
{
	if(val > 1) val = 0;
	
#ifdef LCD_A
	DISBUF_U.usr_.gether_m11_m20_m21_m22_m23_m24_m26_t16_.m22 = val;
#else
	DISBUF_U.usr_.gether_m8_m11_m12_m13_m14_m19_m25_m27_.m12 = val;
#endif
}

void DIS_Lock(unsigned char val)						/*��ʾ�� ͼ��  0-no  1-����  2-δ����*/
{
	if(val > 2) val = 0;
	
#ifdef LCD_A
	switch(val)
	{
		case 1:
			DISBUF_U.usr_.gether_m8_m11_m12_m13_m14_m19_m25_m27_.m14 = 1;
			DISBUF_U.usr_.gether_m11_m20_m21_m22_m23_m24_m26_t16_.m23 = 1;
			DISBUF_U.usr_.gether_m8_m11_m12_m13_m14_m19_m25_m27_.m13 = 0;
			break;
		case 2:
			DISBUF_U.usr_.gether_m8_m11_m12_m13_m14_m19_m25_m27_.m14 = 1;
			DISBUF_U.usr_.gether_m11_m20_m21_m22_m23_m24_m26_t16_.m23 = 0;
			DISBUF_U.usr_.gether_m8_m11_m12_m13_m14_m19_m25_m27_.m13 = 1;
			break;
		default:
			DISBUF_U.usr_.gether_m8_m11_m12_m13_m14_m19_m25_m27_.m14 = 0;
			DISBUF_U.usr_.gether_m11_m20_m21_m22_m23_m24_m26_t16_.m23 = 0;
			DISBUF_U.usr_.gether_m8_m11_m12_m13_m14_m19_m25_m27_.m13 = 0;
			break;
	}
#else
	switch(val)
	{
		case 1:
			DISBUF_U.usr_.gether_m11_m20_m21_m22_m23_m24_m26_t16_.m26 = 1;
			DISBUF_U.usr_.gether_m8_m11_m12_m13_m14_m19_m25_m27_.m27 = 1;
			DISBUF_U.usr_.gether_m8_m11_m12_m13_m14_m19_m25_m27_.m25 = 0;
			break;
		case 2:
			DISBUF_U.usr_.gether_m11_m20_m21_m22_m23_m24_m26_t16_.m26 = 1;
			DISBUF_U.usr_.gether_m8_m11_m12_m13_m14_m19_m25_m27_.m27 = 0;
			DISBUF_U.usr_.gether_m8_m11_m12_m13_m14_m19_m25_m27_.m25 = 1;
			break;
		default:
			DISBUF_U.usr_.gether_m11_m20_m21_m22_m23_m24_m26_t16_.m26 = 0;
			DISBUF_U.usr_.gether_m8_m11_m12_m13_m14_m19_m25_m27_.m27 = 0;
			DISBUF_U.usr_.gether_m8_m11_m12_m13_m14_m19_m25_m27_.m25 = 0;
			break;
	}
#endif
}

void DIS_Wifi(unsigned char val)   				/*WiFi ��Ϊ5���ź�ǿ�ȣ�0-����ʾ*/
{
	unsigned char buf[6]={0x0,0x01,0x03,0x7,0xf,0x1f};
	
	if(val > 5) val = 0;
	
#ifdef LCD_A
	DISBUF_U.usr_.gether_m8_m11_m12_m13_m14_m19_m25_m27_.m8_2 = (buf[val]>>0)&0x01;
	DISBUF_U.usr_.gether_m8_m11_m12_m13_m14_m19_m25_m27_.m11_1 = (buf[val]>>1)&0x01;
	DISBUF_U.usr_.gether_m8_m11_m12_m13_m14_m19_m25_m27_.m27 = (buf[val]>>2)&0x01;
	DISBUF_U.usr_.gether_m8_m11_m12_m13_m14_m19_m25_m27_.m25 = (buf[val]>>3)&0x01;
	DISBUF_U.usr_.gether_m8_m11_m12_m13_m14_m19_m25_m27_.m12 = (buf[val]>>4)&0x01;
#else
	DISBUF_U.usr_.gether_m11_m20_m21_m22_m23_m24_m26_t16_.m20 = (buf[val]>>0)&0x01;
	DISBUF_U.usr_.gether_m11_m20_m21_m22_m23_m24_m26_t16_.m21 = (buf[val]>>1)&0x01;
	DISBUF_U.usr_.gether_m11_m20_m21_m22_m23_m24_m26_t16_.m22 = (buf[val]>>2)&0x01;
	DISBUF_U.usr_.gether_m11_m20_m21_m22_m23_m24_m26_t16_.m23 = (buf[val]>>3)&0x01;
	DISBUF_U.usr_.gether_m11_m20_m21_m22_m23_m24_m26_t16_.m24 = (buf[val]>>4)&0x01;
#endif
}

void DIS_Battery(unsigned char val)				/*���ͼ���Ϊ 5��������0-����ʾ,�յ�ؿ������һ��*/
{
	unsigned char buf[6]={0x0,0x01,0x03,0x7,0xf,0x1f};
	
	if(val > 5) val = 0;
	
#ifdef LCD_A
	DISBUF_U.usr_.gether_m1_m6_m7_m8_.m6_4 = (buf[val]>>0)&0x01;
	DISBUF_U.usr_.gether_m1_m6_m7_m8_.m6_5 = (buf[val]>>1)&0x01;
	DISBUF_U.usr_.gether_13_17_n1_msh_.msh_s = (buf[val]>>2)&0x01;
	DISBUF_U.usr_.gether_12_16_.sm12_1 = (buf[val]>>3)&0x01;
	DISBUF_U.usr_.gether_12_16_m15_m18_.m15 = (buf[val]>>4)&0x01;
#else
	DISBUF_U.usr_.gether_m1_m6_m7_m8_.m7 = (buf[val]>>0)&0x01;
	DISBUF_U.usr_.gether_m11_m20_m21_m22_m23_m24_m26_t16_.m11_2 = (buf[val]>>1)&0x01;
	DISBUF_U.usr_.gether_m8_m11_m12_m13_m14_m19_m25_m27_.m11_1 = (buf[val]>>2)&0x01;
	DISBUF_U.usr_.gether_m8_m11_m12_m13_m14_m19_m25_m27_.m8_2 = (buf[val]>>3)&0x01;
	DISBUF_U.usr_.gether_m1_m6_m7_m8_.m8_1 = (buf[val]>>4)&0x01;
#endif
}

void DIS_GPRS(unsigned char val)   				/*GPRS ��Ϊ6���ź�ǿ�ȣ�0-����ʾ*/
{
	unsigned char buf[7]={0x0,0x01,0x03,0x7,0xf,0x1f,0x3f};
	
	if(val > 6) val = 0;
	
#ifdef LCD_A
	DISBUF_U.usr_.gether_m1_m6_m7_m8_.m8_1 = (buf[val]>>0)&0x01;
	DISBUF_U.usr_.gether_m1_m6_m7_m8_.m7 	 = (buf[val]>>1)&0x01;
	DISBUF_U.usr_.gether_m1_m6_m7_m8_.m1	 = (buf[val]>>2)&0x01;
	DISBUF_U.usr_.gether_m1_m6_m7_m8_.m6_1 = (buf[val]>>3)&0x01;
	DISBUF_U.usr_.gether_m1_m6_m7_m8_.m6_2 = (buf[val]>>4)&0x01;
	DISBUF_U.usr_.gether_m1_m6_m7_m8_.m6_3 = (buf[val]>>5)&0x01;
#else
	DISBUF_U.usr_.gether_m1_m6_m7_m8_.m1 =   (buf[val]>>0)&0x01;
	DISBUF_U.usr_.gether_m1_m6_m7_m8_.m6_1 = (buf[val]>>1)&0x01;
	DISBUF_U.usr_.gether_m1_m6_m7_m8_.m6_2 = (buf[val]>>2)&0x01;
	DISBUF_U.usr_.gether_m1_m6_m7_m8_.m6_3 = (buf[val]>>3)&0x01;
	DISBUF_U.usr_.gether_m1_m6_m7_m8_.m6_4 = (buf[val]>>4)&0x01;
	DISBUF_U.usr_.gether_m1_m6_m7_m8_.m6_5 = (buf[val]>>5)&0x01;
#endif
}

void DIS_HMS(unsigned char val)							/*��ʾ ʱ���� ��λ��0-����ʾ �� 1-h  , 2-m , 3-s */
{
	unsigned char buf[4]={0x0,0x01,0x02,0x04};
	
	if(val > 3) val = 0;
	
#ifdef LCD_A
	DISBUF_U.usr_.gether_19_n3_.sm19_7 = (buf[val]>>0)&0x01;
	DISBUF_U.usr_.gether_20_msh_.msh_h = (buf[val]>>1)&0x01;
	DISBUF_U.usr_.gether_19_n3_.sm19_2 = (buf[val]>>2)&0x01;
#else
	DISBUF_U.usr_.gether_20_msh_.msh_h = (buf[val]>>0)&0x01;
	DISBUF_U.usr_.gether_14_18_n2_msh_.msh_m = (buf[val]>>1)&0x01;
	DISBUF_U.usr_.gether_13_17_n1_msh_.msh_s = (buf[val]>>2)&0x01;
#endif
}

void DIS_MonthAndDate(unsigned char val)  /*��ʾ �º��� ֮��ĺ��,ʱ�ͷ�֮���ð��*/
{
		if(val > 1) val = 0;
	
#ifdef LCD_A
	DISBUF_U.usr_.gether_14_18_.sm18_4 = val;	// -
	DISBUF_U.usr_.gether_24b1_t17_.t17 = val;	// :
#endif
}




