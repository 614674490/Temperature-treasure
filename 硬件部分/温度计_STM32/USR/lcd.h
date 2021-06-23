#ifndef LCD_H
#define LCD_H

#include "pbdata.h"

#define BACK0_GPIO GPIOC
#define BACK0_PORT GPIO_Pin_0

#define SET_BLUE(n)  ((n) ? (BACK0_GPIO->BSRR = BACK0_PORT):(BACK0_GPIO->BRR = BACK0_PORT))

#define BACK1_GPIO GPIOB
#define BACK1_PORT GPIO_Pin_9

#define SET_RED(n)  ((n) ? (BACK1_GPIO->BSRR = BACK1_PORT):(BACK1_GPIO->BRR = BACK1_PORT))

//#define LCD_A 

typedef union
{
	unsigned char buf[30];
	struct
	{
		struct	//0
		{
			unsigned char sm1_1:1;
			unsigned char sm1_2:1;
			unsigned char sm1_3:1;
			unsigned char t13  :1;
			unsigned char sm6_1:1;
			unsigned char sm6_2:1;
			unsigned char sm6_3:1;
			unsigned char t15  :1;
		}gether_1_6_T13_T15_;
		
		struct	//1
		{
			unsigned char sm1_6:1;
			unsigned char sm1_7:1;
			unsigned char sm1_5:1;
			unsigned char sm1_4:1;
			unsigned char sm6_6:1;
			unsigned char sm6_7:1;
			unsigned char sm6_5:1;
			unsigned char sm6_4:1;
		}gether_1_6_;
		
		struct	//2
		{
			unsigned char m8_1:1;
			unsigned char m7  :1;
			unsigned char m1  :1;
			unsigned char m6_1:1;
			unsigned char m6_2:1;
			unsigned char m6_3:1;
			unsigned char m6_4:1;
			unsigned char m6_5:1;
		}gether_m1_m6_m7_m8_;
		
		struct	//3
		{
			unsigned char m8_2:1;
			unsigned char m11_1:1;
			unsigned char m27  :1;
			unsigned char m25  :1;
			unsigned char m12  :1;
			unsigned char m13  :1;
			unsigned char m14  :1;
			unsigned char m19  :1;
		}gether_m8_m11_m12_m13_m14_m19_m25_m27_;
		
		struct	//4
		{
			unsigned char t16  :1;
			unsigned char m11_2:1;
			unsigned char m26  :1;
			unsigned char m20  :1;
			unsigned char m21  :1;
			unsigned char m22  :1;
			unsigned char m23  :1;
			unsigned char m24  :1;
		}gether_m11_m20_m21_m22_m23_m24_m26_t16_;
		
		struct	//5
		{
			unsigned char m17   :1;
			unsigned char sm15_5:1;
			unsigned char sm15_7:1;
			unsigned char sm15_6:1;
			unsigned char sm11_5:1;
			unsigned char sm11_7:1;
			unsigned char sm11_6:1;
			unsigned char m16   :1;
		}gether_11_15_m16_m17_;
		
		struct	//6
		{
			unsigned char sm15_4:1;
			unsigned char sm15_3:1;
			unsigned char sm15_2:1;
			unsigned char sm15_1:1;
			unsigned char sm11_4:1;
			unsigned char sm11_3:1;
			unsigned char sm11_2:1;
			unsigned char sm11_1:1;
		}gether_11_15_;
		
		struct	//7
		{
			unsigned char m18   :1;
			unsigned char sm16_5:1;
			unsigned char sm16_7:1;
			unsigned char sm16_6:1;
			unsigned char sm12_5:1;
			unsigned char sm12_7:1;
			unsigned char sm12_6:1;
			unsigned char m15   :1;
		}gether_12_16_m15_m18_;
		
		struct	//8
		{
			unsigned char sm16_4:1;
			unsigned char sm16_3:1;
			unsigned char sm16_2:1;
			unsigned char sm16_1:1;
			unsigned char sm12_4:1;
			unsigned char sm12_3:1;
			unsigned char sm12_2:1;
			unsigned char sm12_1:1;
		}gether_12_16_;
		
		struct	//9
		{
			unsigned char n1_1  :1;
			unsigned char sm17_5:1;
			unsigned char sm17_7:1;
			unsigned char sm17_6:1;
			unsigned char sm13_5:1;
			unsigned char sm13_7:1;
			unsigned char sm13_6:1;
			unsigned char msh_s :1;
		}gether_13_17_n1_msh_;
		
		struct	//10
		{
			unsigned char sm17_4:1;
			unsigned char sm17_3:1;
			unsigned char sm17_2:1;
			unsigned char sm17_1:1;
			unsigned char sm13_4:1;
			unsigned char sm13_3:1;
			unsigned char sm13_2:1;
			unsigned char sm13_1:1;
		}gether_13_17_;
		
		struct	//11
		{
			unsigned char n2   :1;
			unsigned char sm18_5:1;
			unsigned char sm18_7:1;
			unsigned char sm18_6:1;
			unsigned char sm14_5:1;
			unsigned char sm14_7:1;
			unsigned char sm14_6:1;
			unsigned char msh_m :1;
		}gether_14_18_n2_msh_;
		
		struct	//12
		{
			unsigned char sm18_4:1;
			unsigned char sm18_3:1;
			unsigned char sm18_2:1;
			unsigned char sm18_1:1;
			unsigned char sm14_4:1;
			unsigned char sm14_3:1;
			unsigned char sm14_2:1;
			unsigned char sm14_1:1;
		}gether_14_18_;
		
		struct	//13
		{
			unsigned char sm19_4:1;
			unsigned char sm19_3:1;
			unsigned char sm19_5:1;
			unsigned char sm19_7:1;
			unsigned char sm19_2:1;
			unsigned char sm19_6:1;
			unsigned char sm19_1:1;
			unsigned char n3    :1;
		}gether_19_n3_;
		
		struct	//14
		{
			unsigned char sm20_4:1;
			unsigned char sm20_3:1;
			unsigned char sm20_5:1;
			unsigned char sm20_7:1;
			unsigned char sm20_2:1;
			unsigned char sm20_6:1;
			unsigned char sm20_1:1;
			unsigned char msh_h :1;
		}gether_20_msh_;
		
		struct	//15
		{
			unsigned char sm21_4:1;
			unsigned char sm21_3:1;
			unsigned char sm21_5:1;
			unsigned char sm21_7:1;
			unsigned char sm21_2:1;
			unsigned char sm21_6:1;
			unsigned char sm21_1:1;
			unsigned char t19   :1;
		}gether_21b1_t19;
		
		struct	//16
		{
			unsigned char sm21_4:1;
			unsigned char sm21_3:1;
			unsigned char sm21_5:1;
			unsigned char sm21_7:1;
			unsigned char sm21_2:1;
			unsigned char sm21_6:1;
			unsigned char sm21_1:1;
			unsigned char n4    :1;
		}gether_21b2_n4_;
		
		struct	//17
		{
			unsigned char sm24_4:1;
			unsigned char sm24_3:1;
			unsigned char sm24_5:1;
			unsigned char sm24_7:1;
			unsigned char sm24_2:1;
			unsigned char sm24_6:1;
			unsigned char sm24_1:1;
			unsigned char t17    :1;
		}gether_24b1_t17_;
		
		struct	//18
		{
			unsigned char sm24_4:1;
			unsigned char sm24_3:1;
			unsigned char sm24_5:1;
			unsigned char sm24_7:1;
			unsigned char sm24_2:1;
			unsigned char sm24_6:1;
			unsigned char sm24_1:1;
			unsigned char t18    :1;
		}gether_24b2_t18_;
		
		struct	//19
		{
			unsigned char p1:1;
			unsigned char p2:1;
			unsigned char p3:1;
			unsigned char p4:1;
			unsigned char t1:1;
			unsigned char t2:1;
			unsigned char t3:1;
			unsigned char t4:1;
		}gether_p1_p2_p3_p4_t1_t2_t3_t4_;
			
		struct	//20
		{
			unsigned char sm2_6:1;
			unsigned char sm2_7:1;
			unsigned char sm2_5:1;
			unsigned char sm2_4:1;
			unsigned char sm7_6:1;
			unsigned char sm7_7:1;
			unsigned char sm7_5:1;
			unsigned char sm7_4:1;
		}gether_2b1_7b1_;
		
		struct	//21
		{
			unsigned char sm2_1:1;
			unsigned char sm2_2:1;
			unsigned char sm2_3:1;
			unsigned char p5   :1;
			unsigned char sm7_1:1;
			unsigned char sm7_2:1;
			unsigned char sm7_3:1;
			unsigned char t5   :1;
		}gether_2b1_7b1_p5_t5_;
		
		struct	//22
		{
			unsigned char sm2_6:1;
			unsigned char sm2_7:1;
			unsigned char sm2_5:1;
			unsigned char sm2_4:1;
			unsigned char sm7_6:1;
			unsigned char sm7_7:1;
			unsigned char sm7_5:1;
			unsigned char sm7_4:1;
		}gether_2b2_7b2_;
		
		struct	//23
		{
			unsigned char sm2_1:1;
			unsigned char sm2_2:1;
			unsigned char sm2_3:1;
			unsigned char t11  :1;
			unsigned char sm7_1:1;
			unsigned char sm7_2:1;
			unsigned char sm7_3:1;
			unsigned char t12  :1;
		}gether_2b2_7b2_t11_t12_;
		
		struct	//24
		{
			unsigned char p6:1;
			unsigned char p7:1;
			unsigned char p8:1;
			unsigned char p9:1;
			unsigned char t6:1;
			unsigned char t7:1;
			unsigned char t8:1;
			unsigned char t9:1;
		}gether_p6_p7_p8_p9_t6_t7_t8_t9_;
		
		struct	//25
		{
			unsigned char sm5_6 :1;
			unsigned char sm5_7 :1;
			unsigned char sm5_5 :1;
			unsigned char sm5_4 :1;
			unsigned char sm10_6:1;
			unsigned char sm10_7:1;
			unsigned char sm10_5:1;
			unsigned char sm10_4:1;
		}gether_5b1_10b1_;
		
		struct	//26
		{
			unsigned char sm5_1 :1;
			unsigned char sm5_2 :1;
			unsigned char sm5_3 :1;
			unsigned char p10   :1;
			unsigned char sm10_1:1;
			unsigned char sm10_2:1;
			unsigned char sm10_3:1;
			unsigned char t10   :1;
		}gether_5b1_10b1_p10_t10_;
		
		struct	//27
		{
			unsigned char sm5_6 :1;
			unsigned char sm5_7 :1;
			unsigned char sm5_5 :1;
			unsigned char sm5_4 :1;
			unsigned char sm10_6:1;
			unsigned char sm10_7:1;
			unsigned char sm10_5:1;
			unsigned char sm10_4:1;
		}gether_5b2_10b2_;
		
		struct	//28
		{
			unsigned char sm5_1 :1;
			unsigned char sm5_2 :1;
			unsigned char sm5_3 :1;
			unsigned char p11_1 :1;
			unsigned char sm10_1:1;
			unsigned char sm10_2:1;
			unsigned char sm10_3:1;
			unsigned char p12   :1;
		}gether_5b2_10b2_p11_p12_;
		
		struct	//29
		{
			unsigned char p17  :1;
			unsigned char p13  :1;
			unsigned char p14  :1;
			unsigned char p18  :1;
			unsigned char p15  :1;
			unsigned char p16  :1;
			unsigned char t14  :1;
			unsigned char p11_2:1;
		}gether_p11_p13_p14_p15_p16_p17_p18_t14_;
		
	}usr_;
}disbuf_;
extern disbuf_ DISBUF_U;

void BACK_GPIO_Configuration(void);
void LCD_Init(void);
void LCD_CLOSE(void);
void BACKLIGHT_SET(unsigned char mode,unsigned char r,unsigned char b);
void Update_Display(disbuf_ dis_u);

void DIS_Suona(unsigned char key,unsigned char val);
void DIS_Minus(unsigned char key,unsigned char val);
void DIS_TOPDOWN(unsigned char key,unsigned char val);
void DIS_DC(unsigned char val);
void DIS_KW(unsigned char val);
void DIS_MV(unsigned char val);
void DIS_ugm3(unsigned char val);
void DIS_PPM(unsigned char val);
void DIS_FD(unsigned char val);
void DIS_PC(unsigned char val);
void DIS_KLX(unsigned char val);
void DIS_KPa(unsigned char val);
void DIS_ma(unsigned char val);
void DIS_m_s(unsigned char val);
void DIS_LOW_DC(unsigned char val);
void DIS_FIRST_POINT(unsigned char val);
void DIS_SECOND_POINT(unsigned char val);
void DIS_FIRST_COLON(unsigned char val)	;
void DIS_SENCOND_COLON(unsigned char val);
void DIS_SECOND1_POINT(unsigned char val);
void DIS_NUM_1(unsigned char val);
void DIS_NUM_6(unsigned char val);
void DIS_NUM_2b1(unsigned char val);
void DIS_NUM_2b2(unsigned char val);
void DIS_NUM_5b1(unsigned char val);
void DIS_NUM_5b2(unsigned char val);
void DIS_NUM_7b1(unsigned char val);
void DIS_NUM_7b2(unsigned char val);
void DIS_NUM_10b1(unsigned char val);
void DIS_NUM_10b2(unsigned char val);
void DIS_NUM_21b1(unsigned char val);
void DIS_NUM_21b2(unsigned char val);
void DIS_NUM_24b1(unsigned char val);
void DIS_NUM_24b2(unsigned char val);
void DIS_NUM_11(unsigned char val);
void DIS_NUM_12(unsigned char val);
void DIS_NUM_13(unsigned char val);
void DIS_NUM_14(unsigned char val);
void DIS_NUM_15(unsigned char val);
void DIS_NUM_16(unsigned char val);
void DIS_NUM_17(unsigned char val);
void DIS_NUM_18(unsigned char val);
void DIS_NUM_19(unsigned char val);
void DIS_NUM_20(unsigned char val);
void DIS_NUM_N1_N2(unsigned char val);
void DIS_N3(unsigned char val);
void DIS_N4(unsigned char val);
void DIS_No(unsigned char val);
void DIS_ID(unsigned char val);
void DIS_Usb(unsigned char val);
void DIS_BlueTooth(unsigned char val);
void DIS_Printer(unsigned char val);
void DIS_Gps(unsigned char val);
void DIS_Set(unsigned char val);
void DIS_UpLoad(unsigned char val);
void DIS_Lock(unsigned char val);
void DIS_Wifi(unsigned char val);
void DIS_Battery(unsigned char val);
void DIS_GPRS(unsigned char val);
void DIS_HMS(unsigned char val);
void DIS_MonthAndDate(unsigned char val);

#endif













