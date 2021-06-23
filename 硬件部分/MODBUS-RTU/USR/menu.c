#include "pbdata.h"

men_ MEN_T={0,0};
short SetTemp=0;  /*设置某一个参数时的中间变量*/
unsigned char Now_Nober=0; /*用于记录当前在哪个界面的编号，保存参数时使用*/

/**********************************************************************************各个界面初始化及显示部分***************************************/
void DIS_0_MAC(void)				/*显示设备MAC地址(硬件地址)*/
{
	DIS_FIRST_POINT(0);
	DIS_SECOND_POINT(0);
	DIS_SECOND1_POINT(0);
	DIS_DC(0);
	DIS_PC(0);
	DIS_LOW_DC(0);
	
	DIS_NUM_2b1(0xa);
	DIS_NUM_2b2(0xc);
	DIS_FIRST_COLON(1);
	
	DIS_NUM_5b1((STMID_T.myid[0]&0xf0)>>4);
	DIS_NUM_5b2((STMID_T.myid[0]&0x0f));
	DIS_NUM_7b1((STMID_T.myid[1]&0xf0)>>4);
	DIS_NUM_7b2((STMID_T.myid[1]&0x0f));
	DIS_NUM_10b1((STMID_T.myid[2]&0xf0)>>4);
	DIS_NUM_10b2((STMID_T.myid[2]&0x0f));
}

void DIS_1_ModBusAddr(unsigned char issure,unsigned short id)
{
	unsigned char i=0;
	
	DIS_FIRST_POINT(0);
	DIS_SECOND_POINT(0);
	DIS_SECOND1_POINT(0);
	DIS_DC(0);
	DIS_PC(0);
	DIS_LOW_DC(0);
	
	DIS_NUM_2b1(0x1);
	DIS_NUM_2b2(0xd);
	DIS_FIRST_COLON(1);
	
	DIS_NUM_5b1(17);
	DIS_NUM_5b2(17);
	DIS_NUM_7b1(17);
	
	if(issure == 0)
	{
		DIS_NUM_7b2(id/100);
		DIS_NUM_10b1(id%100/10);
		DIS_NUM_10b2(id%100%10);
	}else
	{
		for(i=0;i<5;i++)
		{
			DIS_NUM_7b2(17);
			DIS_NUM_10b1(17);
			DIS_NUM_10b2(17);
			Update_Display(DISBUF_U);
			delay_ms(50);
			DIS_NUM_7b2(id/100);
			DIS_NUM_10b1(id%100/10);
			DIS_NUM_10b2(id%100%10);
			Update_Display(DISBUF_U);
			delay_ms(20);
			
		}
	}
}

void DIS_2_ModBusBaud(unsigned char issure,unsigned short baud)
{
	unsigned char i=0;
	
	DIS_FIRST_POINT(0);
	DIS_SECOND_POINT(0);
	DIS_SECOND1_POINT(0);
	DIS_DC(0);
	DIS_PC(0);
	DIS_LOW_DC(0);
	
	DIS_NUM_2b1(0xb);
	DIS_NUM_2b2(0xd);
	DIS_FIRST_COLON(1);
	
	DIS_NUM_5b1(17);
	DIS_NUM_5b2(17);
	DIS_NUM_7b1(17);
	DIS_NUM_7b2(17);
	DIS_NUM_10b1(17);
	
	if(issure == 0)
	{
		DIS_NUM_10b2(baud);
	}else
	{
		for(i=0;i<5;i++)
		{
			DIS_NUM_10b2(17);
			Update_Display(DISBUF_U);
			delay_ms(50);
			DIS_NUM_10b2(baud);
			Update_Display(DISBUF_U);
			delay_ms(20);
			
		}
	}
}

void DIS_3_ModBusParity(unsigned char issure,unsigned short par)
{
	unsigned char i=0;
	
	DIS_FIRST_POINT(0);
	DIS_SECOND_POINT(0);
	DIS_SECOND1_POINT(0);
	DIS_DC(0);
	DIS_PC(0);
	DIS_LOW_DC(0);
	
	DIS_NUM_2b1(0xe);
	DIS_NUM_2b2(0xd);
	DIS_FIRST_COLON(1);
	
	DIS_NUM_5b1(17);
	DIS_NUM_5b2(17);
	DIS_NUM_7b1(17);
	DIS_NUM_7b2(17);
	DIS_NUM_10b1(17);
	
	if(issure == 0)
	{
		DIS_NUM_10b2(par);
	}else
	{
		for(i=0;i<5;i++)
		{
			DIS_NUM_10b2(17);
			Update_Display(DISBUF_U);
			delay_ms(50);
			DIS_NUM_10b2(par);
			Update_Display(DISBUF_U);
			delay_ms(20);
			
		}
	}
}

void DIS_4_BackLight(unsigned char issure,unsigned short mode)
{
	unsigned char i=0;
	
	DIS_FIRST_POINT(0);
	DIS_SECOND_POINT(0);
	DIS_SECOND1_POINT(0);
	DIS_DC(0);
	DIS_PC(0);
	DIS_LOW_DC(0);
	
	DIS_NUM_2b1(0xb);
	DIS_NUM_2b2(0xb);
	DIS_FIRST_COLON(1);
	
	DIS_NUM_5b1(17);
	DIS_NUM_5b2(17);
	DIS_NUM_7b1(17);
	DIS_NUM_7b2(17);
	DIS_NUM_10b1(17);
	
	if(issure == 0)
	{
		DIS_NUM_10b2(mode);
	}else
	{
		for(i=0;i<5;i++)
		{
			DIS_NUM_10b2(17);
			Update_Display(DISBUF_U);
			delay_ms(50);
			DIS_NUM_10b2(mode);
			Update_Display(DISBUF_U);
			delay_ms(20);
			
		}
	}
}

void DIS_5_MessageMode(unsigned char issure,unsigned short mode)
{
	unsigned char i=0;
	
	DIS_FIRST_POINT(0);
	DIS_SECOND_POINT(0);
	DIS_SECOND1_POINT(0);
	DIS_DC(0);
	DIS_PC(0);
	DIS_LOW_DC(0);
	
	DIS_NUM_2b1(0xe);
	DIS_NUM_2b2(0xa);
	DIS_FIRST_COLON(1);
	
	DIS_NUM_5b1(17);
	DIS_NUM_5b2(17);
	DIS_NUM_7b1(17);
	DIS_NUM_7b2(17);
	DIS_NUM_10b1(17);
	
	if(issure == 0)
	{
		DIS_NUM_10b2(mode);
	}else
	{
		for(i=0;i<5;i++)
		{
			DIS_NUM_10b2(17);
			Update_Display(DISBUF_U);
			delay_ms(50);
			DIS_NUM_10b2(mode);
			Update_Display(DISBUF_U);
			delay_ms(20);
			
		}
	}
}

void DIS_6_SleepTime(unsigned char issure,unsigned short time)
{
	unsigned char i=0;
	
	DIS_FIRST_POINT(0);
	DIS_SECOND_POINT(0);
	DIS_SECOND1_POINT(0);
	DIS_DC(0);
	DIS_PC(0);
	DIS_LOW_DC(0);
	
	DIS_NUM_2b1(0x5);
	DIS_NUM_2b2(0xe);
	DIS_FIRST_COLON(1);
	
	DIS_NUM_5b1(17);
	DIS_NUM_5b2(17);
	DIS_NUM_7b1(17);
	DIS_NUM_7b2(17);
	
	if(issure == 0)
	{
		DIS_NUM_10b1(time%10000%1000%100/10);
		DIS_NUM_10b2(time%10000%1000%100%10);
	}else
	{
		for(i=0;i<5;i++)
		{
			DIS_NUM_10b1(17);
			DIS_NUM_10b2(17);
			Update_Display(DISBUF_U);
			delay_ms(50);
			DIS_NUM_10b1(time%10000%1000%100/10);
			DIS_NUM_10b2(time%10000%1000%100%10);
			Update_Display(DISBUF_U);
			delay_ms(20);
			
		}
	}
}

void DIS_6_TH1Mode(unsigned char issure,unsigned short mode)
{
	unsigned char i=0;
	
	DIS_FIRST_POINT(0);
	DIS_SECOND_POINT(0);
	DIS_SECOND1_POINT(0);
	DIS_DC(0);
	DIS_PC(0);
	DIS_LOW_DC(0);
	
	DIS_NUM_2b1(0xf);
	DIS_NUM_2b2(0x1);
	DIS_FIRST_COLON(1);
	
	DIS_NUM_5b1(17);
	DIS_NUM_5b2(17);
	DIS_NUM_7b1(17);
	DIS_NUM_7b2(17);
	DIS_NUM_10b1(17);
	
	if(issure == 0)
	{
		DIS_NUM_10b2(mode);
	}else
	{
		for(i=0;i<5;i++)
		{
			DIS_NUM_10b2(17);
			Update_Display(DISBUF_U);
			delay_ms(50);
			DIS_NUM_10b2(mode);
			Update_Display(DISBUF_U);
			delay_ms(20);
			
		}
	}
}

void DIS_7_TH2Mode(unsigned char issure,unsigned short mode)
{
	unsigned char i=0;
	
	DIS_FIRST_POINT(0);
	DIS_SECOND_POINT(0);
	DIS_SECOND1_POINT(0);
	DIS_DC(0);
	DIS_PC(0);
	DIS_LOW_DC(0);
	
	DIS_NUM_2b1(0xf);
	DIS_NUM_2b2(0x2);
	DIS_FIRST_COLON(1);
	
	DIS_NUM_5b1(17);
	DIS_NUM_5b2(17);
	DIS_NUM_7b1(17);
	DIS_NUM_7b2(17);
	DIS_NUM_10b1(17);
	
	if(issure == 0)
	{
		DIS_NUM_10b2(mode);
	}else
	{
		for(i=0;i<5;i++)
		{
			DIS_NUM_10b2(17);
			Update_Display(DISBUF_U);
			delay_ms(50);
			DIS_NUM_10b2(mode);
			Update_Display(DISBUF_U);
			delay_ms(20);
			
		}
	}
}

void DIS_8_T3Mode(unsigned char issure,unsigned short mode)
{
	unsigned char i=0;
	
	DIS_FIRST_POINT(0);
	DIS_SECOND_POINT(0);
	DIS_SECOND1_POINT(0);
	DIS_DC(0);
	DIS_PC(0);
	DIS_LOW_DC(0);
	
	DIS_NUM_2b1(0xf);
	DIS_NUM_2b2(0x3);
	DIS_FIRST_COLON(1);
	
	DIS_NUM_5b1(17);
	DIS_NUM_5b2(17);
	DIS_NUM_7b1(17);
	DIS_NUM_7b2(17);
	DIS_NUM_10b1(17);

	if(issure == 0)
	{
		DIS_NUM_10b2(mode);
	}else
	{
		for(i=0;i<5;i++)
		{
			DIS_NUM_10b2(17);
			Update_Display(DISBUF_U);
			delay_ms(50);
			DIS_NUM_10b2(mode);
			Update_Display(DISBUF_U);
			delay_ms(20);
			
		}
	}
}

void DIS_10_19_Waring(unsigned char issure,unsigned char disnum,short val) /*界面会显示小数点，但是实际上，在缓存区内是 扩大10倍的数据*/
{	
	unsigned char i=0;
	
	if(disnum <10 || disnum>19) return;
	
	DIS_FIRST_POINT(0);
	DIS_SECOND_POINT(1);
	DIS_SECOND1_POINT(0);
	DIS_DC(0);
	DIS_PC(0);
	DIS_LOW_DC(0);
	
	if(val<0)
		DIS_Minus(2,1);
	else
		DIS_Minus(2,0);
	
	switch(disnum)
	{
		case 10:
		case 11:
		case 14:
		case 15:
		case 18:
		case 19:
			DIS_LOW_DC(1);
			break;
		case 12:
		case 13:
		case 16:
		case 17:
			DIS_PC(1);
			break;
	}
	
	DIS_NUM_2b1(0xa);
	DIS_NUM_2b2(disnum-10);
	DIS_FIRST_COLON(1);
	
	DIS_NUM_5b1(17);
	DIS_NUM_5b2(17);
	
	if(issure == 0)
	{
		DIS_NUM_7b1(abs(val)/1000);
		DIS_NUM_7b2(abs(val)%1000/100);
		DIS_NUM_10b1(abs(val)%1000%100/10);
		DIS_NUM_10b2(abs(val)%1000%100%10);
	}else
	{
		for(i=0;i<5;i++)
		{
			DIS_NUM_7b1(17);
			DIS_NUM_7b2(17);
			DIS_NUM_10b1(17);
			DIS_NUM_10b2(17);
			Update_Display(DISBUF_U);
			delay_ms(50);
			DIS_NUM_7b1(abs(val)/1000);
			DIS_NUM_7b2(abs(val)%1000/100);
			DIS_NUM_10b1(abs(val)%1000%100/10);
			DIS_NUM_10b2(abs(val)%1000%100%10);
			Update_Display(DISBUF_U);
			delay_ms(20);
			
		}
	}
}

void DIS_20_29_Cal(unsigned char issure,unsigned char disnum,short val) /*界面会显示小数点，但是实际上，在缓存区内是 扩大1000倍的数据*/
{	
	unsigned char i=0;
	
	if(disnum <20 || disnum>29) return;
	
	DIS_FIRST_POINT(0);
	DIS_SECOND_POINT(0);
	DIS_SECOND1_POINT(1);
	DIS_DC(0);
	DIS_PC(0);
	DIS_LOW_DC(0);
	
	if(val<0)
		DIS_Minus(2,1);
	else
		DIS_Minus(2,0);
	
	DIS_NUM_2b1(0xc);
	DIS_NUM_2b2(disnum-20);
	DIS_FIRST_COLON(1);
	
	DIS_NUM_5b1(17);
	
	
	if(issure == 0)
	{
		DIS_NUM_5b2(abs(val)/10000);
	DIS_NUM_7b1(abs(val)%10000/1000);
	DIS_NUM_7b2(abs(val)%10000%1000/100);
	DIS_NUM_10b1(abs(val)%10000%1000%100/10);
	DIS_NUM_10b2(abs(val)%10000%1000%100%10);
	}else
	{
		for(i=0;i<5;i++)
		{
			DIS_NUM_5b2(17);
			DIS_NUM_7b1(17);
			DIS_NUM_7b2(17);
			DIS_NUM_10b1(17);
			DIS_NUM_10b2(17);
			Update_Display(DISBUF_U);
			delay_ms(50);
			DIS_NUM_5b2(abs(val)/10000);
			DIS_NUM_7b1(abs(val)%10000/1000);
			DIS_NUM_7b2(abs(val)%10000%1000/100);
			DIS_NUM_10b1(abs(val)%10000%1000%100/10);
			DIS_NUM_10b2(abs(val)%10000%1000%100%10);
			Update_Display(DISBUF_U);
			delay_ms(20);
			
		}
	}
}

void DIS_30_35_Time(unsigned char disnum,time_ *t)
{
	unsigned char i=0;
	
	if(disnum <30 || disnum>35) return;
	
	DIS_FIRST_POINT(0);
	DIS_SECOND_POINT(0);
	DIS_SECOND1_POINT(0);
	DIS_DC(0);
	DIS_PC(0);
	DIS_LOW_DC(0);
	
	DIS_NUM_2b1(17);
	DIS_NUM_2b2(17);
	DIS_FIRST_COLON(0);
	DIS_NUM_5b1(17);
	DIS_NUM_5b2(17);
	DIS_NUM_7b1(2);
	DIS_NUM_7b2(0);
	
	switch(disnum)
	{
		case 30:
			for(i=0;i<5;i++)
			{
				DIS_NUM_10b1(17);
				DIS_NUM_10b2(17);
				Update_Display(DISBUF_U);
				delay_ms(50);
				DIS_NUM_10b1((t->year-2000)/10);
				DIS_NUM_10b2((t->year-2000)%10);
				Update_Display(DISBUF_U);
				delay_ms(20);
				
			}
			break;
		case 31:
			for(i=0;i<5;i++)
			{
				DIS_NUM_N1_N2(17);
				DIS_NUM_18(17);
				Update_Display(DISBUF_U);
				delay_ms(50);
				DIS_NUM_N1_N2((t->month)/10);
				DIS_NUM_18((t->month)%10);
				Update_Display(DISBUF_U);
				delay_ms(20);
				
			}
			break;
		case 32:
			for(i=0;i<5;i++)
			{
				DIS_NUM_19(17);
				DIS_NUM_20(17);
				Update_Display(DISBUF_U);
				delay_ms(50);
				DIS_NUM_19((t->date)/10);
				DIS_NUM_20((t->date)%10);
				Update_Display(DISBUF_U);
				delay_ms(20);
				
			}
			break;
		case 33:
			for(i=0;i<5;i++)
			{
				DIS_NUM_21b1(17);
				DIS_NUM_21b2(17);
				Update_Display(DISBUF_U);
				delay_ms(50);
				DIS_NUM_21b1((t->hours)/10);
				DIS_NUM_21b2((t->hours)%10);
				Update_Display(DISBUF_U);
				delay_ms(20);
				
			}
			break;
		case 34:
			for(i=0;i<5;i++)
			{
				DIS_NUM_24b1(17);
				DIS_NUM_24b2(17);
				Update_Display(DISBUF_U);
				delay_ms(50);
				DIS_NUM_24b1((t->min)/10);
				DIS_NUM_24b2((t->min)%10);
				Update_Display(DISBUF_U);
				delay_ms(20);
				
			}
			break;
		case 35:
			for(i=0;i<5;i++)
			{
				DIS_NUM_13(17);
				DIS_NUM_14(17);
				Update_Display(DISBUF_U);
				delay_ms(50);
				DIS_NUM_13((t->sec)/10);
				DIS_NUM_14((t->sec)%10);
				Update_Display(DISBUF_U);
				delay_ms(20);
				
			}
			break;
	}
}

/*********************************************************************************************以上为子设置界面*/


void DIS_MEN_DIS(void)	/*清除不需要显示的图标,准备显示传感器数据*/
{
	DIS_Set(0);
	DIS_MenNum(100);
	DIS_FIRST_COLON(0);
	DIS_FIRST_POINT(0);
	DIS_SECOND_POINT(0);
	DIS_SECOND1_POINT(0);
	DIS_DC(0);
	DIS_PC(0);
	DIS_LOW_DC(0);
	DIS_Minus(1,0);
	DIS_Minus(2,0);
	
	MEN_T.MenSetNum=0;
	MEN_T.Now_Men = MEN_DIS;
}

void DIS_MEN_SET(unsigned char issure,unsigned char mennum)	/*由此一级入口 显示个分级 设置界面*/
{
	DIS_Set(1);
	DIS_SensorChl(3,17);
	DIS_Suona(1,0);
	DIS_Suona(2,0);
	DIS_TOPDOWN(1,0);
	DIS_TOPDOWN(2,0);
	BACKLIGHT_SET(Sys_Para_T.BackLightMode,0,0);
	DIS_MenNum(mennum);
	
	switch(mennum)
	{
		case 0:
			DIS_0_MAC();
			break;
		case 1:
			DIS_1_ModBusAddr(issure,usRegHoldingBuf[mennum-1]);
			break;
		case 2:
			DIS_2_ModBusBaud(issure,usRegHoldingBuf[mennum-1]);
			break;
		case 3:
			DIS_3_ModBusParity(issure,usRegHoldingBuf[mennum-1]);
			break;
		case 4:
			DIS_4_BackLight(issure,usRegHoldingBuf[mennum-1]);
			break;
		case 5: 
			DIS_5_MessageMode(issure,usRegHoldingBuf[mennum-1]);
			break;
		case 6:
			DIS_6_SleepTime(issure,usRegHoldingBuf[mennum-1]);
			break;
		case 7:
			DIS_6_TH1Mode(issure,usRegHoldingBuf[mennum-1]);
			break;
		case 8:
			DIS_7_TH2Mode(issure,usRegHoldingBuf[mennum-1]);
			break;
		case 9:
			DIS_8_T3Mode(issure,usRegHoldingBuf[mennum-1]);
			break;
		default:
			if( mennum>=10 && mennum <=19)
				DIS_10_19_Waring(issure,mennum,(short)usRegHoldingBuf[mennum-1]);
			if( mennum>=20 && mennum <=29)
				DIS_20_29_Cal(issure,mennum,(short)usRegHoldingBuf[mennum-20+100]);
			if( mennum>=30 && mennum <=35)
				DIS_30_35_Time(mennum,&TIMESET_T);
			break;
	}
	
	Now_Nober = mennum;
	
	if(issure == 0)								/*点击确定，才切换界面*/
	{
		MEN_T.Now_Men = MEN_SET;
		DIS_TOPDOWN(2,0);
	}else
	{
		DIS_TOPDOWN(2,3);						/*显示左下侧的 上下箭头，标识一下现在在调整数据界面*/
		
		if(mennum<10)
		{
			if(mennum!=0)
			{
				MEN_T.Now_Men =	mennum+1;
				SetTemp = usRegHoldingBuf[mennum-1];
			}
		}else if(mennum<20)
		{
			MEN_T.Now_Men = MEN_WARNING;
			SetTemp = usRegHoldingBuf[mennum-1];
		}else if(mennum<30)
		{
			MEN_T.Now_Men = MEN_CAL;
			SetTemp = usRegHoldingBuf[mennum-20+100];
		}else if(mennum<36)
		{
			MEN_T.Now_Men = MEN_TIME;
		}
	}
}

/*当前界面编号用来区分调整那个参数，addorcut 1-加  0-减，tt 需要调整的时间结构体*/
void DIS_TIME_SET(unsigned char mennum,unsigned char addorcut,time_ *tt)
{
	switch(mennum)
	{
		case 30:		/*年*/
			{
				switch(addorcut)
				{
					case 0:
						if( (tt->year-2000)>0)
							tt->year--;
						break;
					case 1:
						if( (tt->year-2000)<99)
						tt->year++;
						break;
				}
				DIS_NUM_10b1((tt->year-2000)/10);
				DIS_NUM_10b2((tt->year-2000)%10);
			}
			break;
		case 31:		/*月*/
			{
				switch(addorcut)
				{
					case 0:
						if( tt->month >1)
						tt->month--;
						break;
					case 1:
						if( tt->month <12)
						tt->month++;
						break;
				}
			}
			break;
		case 32:		/*日*/
			{
				switch(addorcut)
				{
					case 0:
						if( tt->date >1)
						tt->date--;
						break;
					case 1:
						if(tt->month == 2)
						{
							if((tt->year%4==0&&tt->year%100!=0)||(tt->year%400==0))	/*闰年*/
							{
								if( tt->date <29)
									tt->date++;
							}else
							{
								if( tt->date <28)
									tt->date++;
							}
						}else if(tt->month==4 || tt->month==6 || tt->month==9 || tt->month==11)
						{
							if( tt->date <30)
								tt->date++;
						}else
						{
							if( tt->date <31)
								tt->date++;
						}
						break;
				}
			}
			break;
		case 33:		/*时*/
			{
				switch(addorcut)
				{
					case 0:
						if( tt->hours >0)
						tt->hours--;
						break;
					case 1:
						if( tt->hours <23)
						tt->hours++;
						break;
				}
			}
			break;
		case 34:		/*分*/
			{
				switch(addorcut)
				{
					case 0:
						if( tt->min >0)
						tt->min--;
						break;
					case 1:
						if( tt->min <59)
						tt->min++;
						break;
				}
			}
			break;
		case 35:		/*秒*/
			{
				switch(addorcut)
				{
					case 0:
						if( tt->sec >0)
						tt->sec--;
						break;
					case 1:
						if( tt->sec <59)
						tt->sec++;
						break;
				}
			}
			break;
	}
}



/**********************************************************************************按键与界面处理函数********************************************/

/**********************************************MEN_DIS key deal function,level-1*/
void KEY_MEN_DIS(unsigned char keyval)
{
	switch(keyval)
	{
		case S1_DOWN:
			DIS_MEN_SET(0,MEN_T.MenSetNum);
			memcpy(&TIMESET_T,&TIME_T,sizeof(TIME_T));
			break;
		case S2_DOWN:
			break;
		case S3_DOWN:
			break;
		case S4_DOWN:
			keysystemIntoDeepCount++;
			if(keysystemIntoDeepCount > 30)
			{
				keysystemIntoDeepCount=0;
				delay_ms(1000);
				BEEP_Speek(SpeekTime,SpeekFre);
				delay_ms(1000);
				BEEP_Speek(SpeekTime,SpeekFre);
				delay_ms(1000);
					
				LCD_CLOSE();
				WIFI_AT("AT+GSLP=1","OK",100,0);
				WIFI_PowerSet(1);
				RCC_APB2PeriphResetCmd(0X01FC,DISABLE); //复位所有IO口
				Sys_Standby();
			}
			break;
		case S5_DOWN:
			if(Sys_Para_T.MessageMode != 1) return;
			wifi_set++;
			if(wifi_set > 30)
			{
				wifi_set=0;
				BEEP_Speek(SpeekTime,SpeekFre);
				WIFI_AT("AT+CWSTARTSMART","smartconfig connected wifi",1000*60,1);
				WIFI_AT("AT+CWSTOPSMART","OK",100,0);
			}
			break;
		default:
			break;
	}
}

/**********************************************MEN_SET key deal function,level-1*/
void KEY_MEN_SET(unsigned char keyval)
{
	switch(keyval)
	{
		case S1_DOWN:
			DIS_MEN_DIS();
			Timer4_T.ITCounts=500; /*让数据显示马上刷新一次*/
			break;
		case S2_DOWN:
			if(MEN_T.MenSetNum>0)
				MEN_T.MenSetNum--;
			DIS_MEN_SET(0,MEN_T.MenSetNum);
			break;
		case S3_DOWN:
			if(MEN_T.MenSetNum<35)
				MEN_T.MenSetNum++;
			DIS_MEN_SET(0,MEN_T.MenSetNum);
			break;
		case S4_DOWN:
			DIS_MEN_SET(1,MEN_T.MenSetNum);
			break;
		case S5_DOWN:
			Reset_STM();
			break;
		default:
			break;
	}
}

void KEY_MEN_ID(unsigned char keyval)
{
	switch(keyval)
	{
		case S1_DOWN:
			DIS_MEN_SET(0,Now_Nober);
			break;
		case S2_DOWN:
			if(SetTemp>1)
				SetTemp--;
			DIS_1_ModBusAddr(0,SetTemp);
			break;
		case S3_DOWN:
			if(SetTemp<254)
				SetTemp++;
			DIS_1_ModBusAddr(0,SetTemp);
			break;
		case S1S2_DOWN:				/*快速减*/
			if(SetTemp>10)
				SetTemp-=10;
			DIS_1_ModBusAddr(0,SetTemp);
			break;
		case S1S3_DOWN:				/*快速加*/
			if(SetTemp<244)
				SetTemp+=10;
			DIS_1_ModBusAddr(0,SetTemp);
			break;
		case S4_DOWN:
			usRegHoldingBuf[Now_Nober-1] = SetTemp;
			Usr_SetPara();
			DIS_MEN_SET(0,Now_Nober);
			break;
		default:
			break;
	}
}

void KEY_MEN_BAUD(unsigned char keyval)
{
	switch(keyval)
	{
		case S1_DOWN:
			DIS_MEN_SET(0,Now_Nober);
			break;
		case S2_DOWN:
			if(SetTemp>0)
				SetTemp--;
			DIS_2_ModBusBaud(0,SetTemp);
			break;
		case S3_DOWN:
			if(SetTemp<7)
				SetTemp++;
			DIS_2_ModBusBaud(0,SetTemp);
			break;
		case S4_DOWN:
			usRegHoldingBuf[Now_Nober-1] = SetTemp;
			Usr_SetPara();
			DIS_MEN_SET(0,Now_Nober);
			break;
		default:
			break;
	}
}

void KEY_MEN_PARY(unsigned char keyval)
{
	switch(keyval)
	{
		case S1_DOWN:
			DIS_MEN_SET(0,Now_Nober);
			break;
		case S2_DOWN:
			if(SetTemp>0)
				SetTemp--;
			DIS_3_ModBusParity(0,SetTemp);
			break;
		case S3_DOWN:
			if(SetTemp<2)
				SetTemp++;
			DIS_3_ModBusParity(0,SetTemp);
			break;
		case S4_DOWN:
			usRegHoldingBuf[Now_Nober-1] = SetTemp;
			Usr_SetPara();
			DIS_MEN_SET(0,Now_Nober);
			break;
		default:
			break;
	}
}

void KEY_MEN_BACKLIGHT(unsigned char keyval)
{
	switch(keyval)
	{
		case S1_DOWN:
			DIS_MEN_SET(0,Now_Nober);
			break;
		case S2_DOWN:
			if(SetTemp>0)
				SetTemp--;
			DIS_4_BackLight(0,SetTemp);
			break;
		case S3_DOWN:
			if(SetTemp<2)
				SetTemp++;
			DIS_4_BackLight(0,SetTemp);
			break;
		case S4_DOWN:
			usRegHoldingBuf[Now_Nober-1] = SetTemp;
			Usr_SetPara();
			DIS_MEN_SET(0,Now_Nober);
			break;
		default:
			break;
	}
}

void KEY_MEN_MESSGEMODE(unsigned char keyval)
{
	switch(keyval)
	{
		case S1_DOWN:
			DIS_MEN_SET(0,Now_Nober);
			break;
		case S2_DOWN:
			if(SetTemp>0)
				SetTemp--;
			DIS_5_MessageMode(0,SetTemp);
			break;
		case S3_DOWN:
			if(SetTemp<2)
				SetTemp++;
			DIS_5_MessageMode(0,SetTemp);
			break;
		case S4_DOWN:
			usRegHoldingBuf[Now_Nober-1] = SetTemp;
			Usr_SetPara();
			DIS_MEN_SET(0,Now_Nober);
			Reset_STM();
			break;
		default:
			break;
	}
}

void KEY_MEN_SLEEPTIME(unsigned char keyval)
{
	switch(keyval)
	{
		case S1_DOWN:
			DIS_MEN_SET(0,Now_Nober);
			break;
		case S2_DOWN:
			if(SetTemp>0)
				SetTemp--;
			DIS_6_SleepTime(0,SetTemp);
			break;
		case S3_DOWN:
			if(SetTemp<60)
				SetTemp++;
			DIS_6_SleepTime(0,SetTemp);
			break;
		case S4_DOWN:
			usRegHoldingBuf[Now_Nober-1] = SetTemp;
			Usr_SetPara();
			DIS_MEN_SET(0,Now_Nober);
			break;
		default:
			break;
	}
}

void KEY_MEN_SHT1MODE(unsigned char keyval)
{
	switch(keyval)
	{
		case S1_DOWN:
			DIS_MEN_SET(0,Now_Nober);
			break;
		case S2_DOWN:
			if(SetTemp>0)
				SetTemp--;
			DIS_6_TH1Mode(0,SetTemp);
			break;
		case S3_DOWN:
			if(SetTemp<1)
				SetTemp++;
			DIS_6_TH1Mode(0,SetTemp);
			break;
		case S4_DOWN:
			usRegHoldingBuf[Now_Nober-1] = SetTemp;
			Usr_SetPara();
			DIS_MEN_SET(0,Now_Nober);
			break;
		default:
			break;
	}
}

void KEY_MEN_SHT2MODE(unsigned char keyval)
{
	switch(keyval)
	{
		case S1_DOWN:
			DIS_MEN_SET(0,Now_Nober);
			break;
		case S2_DOWN:
			if(SetTemp>0)
				SetTemp--;
			DIS_7_TH2Mode(0,SetTemp);
			break;
		case S3_DOWN:
			if(SetTemp<1)
				SetTemp++;
			DIS_7_TH2Mode(0,SetTemp);
			break;
		case S4_DOWN:
			usRegHoldingBuf[Now_Nober-1] = SetTemp;
			Usr_SetPara();
			DIS_MEN_SET(0,Now_Nober);
			break;
		default:
			break;
	}
}

void KEY_MEN_18B20MODE(unsigned char keyval)
{
	switch(keyval)
	{
		case S1_DOWN:
			DIS_MEN_SET(0,Now_Nober);
			break;
		case S2_DOWN:
			if(SetTemp>0)
				SetTemp--;
			DIS_8_T3Mode(0,SetTemp);
			break;
		case S3_DOWN:
			if(SetTemp<1)
				SetTemp++;
			DIS_8_T3Mode(0,SetTemp);
			break;
		case S4_DOWN:
			usRegHoldingBuf[Now_Nober-1] = SetTemp;
			Usr_SetPara();
			DIS_MEN_SET(0,Now_Nober);
			break;
		default:
			break;
	}
}

void KEY_MEN_WARNING(unsigned char keyval)
{
	switch(keyval)
	{
		case S1_DOWN:
			DIS_MEN_SET(0,Now_Nober);
			break;
		case S2_DOWN:
			if(SetTemp>-500)
				SetTemp--;
			DIS_10_19_Waring(0,Now_Nober,SetTemp);
			break;
		case S3_DOWN:
			if(SetTemp<1500)
				SetTemp++;
			DIS_10_19_Waring(0,Now_Nober,SetTemp);
			break;
		case S1S2_DOWN:				/*快速减*/
			if(SetTemp>-400)
				SetTemp-=100;
			DIS_10_19_Waring(0,Now_Nober,SetTemp);
			break;
		case S1S3_DOWN:				/*快速加*/
			if(SetTemp<1400)
				SetTemp+=100;
			DIS_10_19_Waring(0,Now_Nober,SetTemp);
			break;
		case S4_DOWN:
			usRegHoldingBuf[Now_Nober-1] = SetTemp;
			Usr_SetPara();
			DIS_MEN_SET(0,Now_Nober);
			break;
		default:
			break;
	}
}

void KEY_MEN_CAL(unsigned char keyval)
{
	switch(keyval)
	{
		case S1_DOWN:
			DIS_MEN_SET(0,Now_Nober);
			break;
		case S2_DOWN:
			if(SetTemp>-32767)
				SetTemp--;
			DIS_20_29_Cal(0,Now_Nober,SetTemp);
			break;
		case S3_DOWN:
			if(SetTemp<32767)
				SetTemp++;
			DIS_20_29_Cal(0,Now_Nober,SetTemp);
			break;
		case S1S2_DOWN:				/*快速减*/
			if(SetTemp>-32667)
				SetTemp-=100;
			DIS_20_29_Cal(0,Now_Nober,SetTemp);
			break;
		case S1S3_DOWN:				/*快速加*/
			if(SetTemp<32667)
				SetTemp+=100;
			DIS_20_29_Cal(0,Now_Nober,SetTemp);
			break;
		case S4_DOWN:
			usRegHoldingBuf[Now_Nober-20+100] = SetTemp;
			Usr_SetPara();
			DIS_MEN_SET(0,Now_Nober);
			break;
		default:
			break;
	}
}

void KEY_MEN_TIME(unsigned char keyval)
{
	switch(keyval)
	{
		case S1_DOWN:
			DIS_MEN_SET(0,Now_Nober);
			break;
		case S2_DOWN:
			DIS_TIME_SET(Now_Nober,0,&TIMESET_T);
			DIS_Time(TIMESET_T);
			break;
		case S3_DOWN:
			DIS_TIME_SET(Now_Nober,1,&TIMESET_T);
			DIS_Time(TIMESET_T);
			break;
		case S4_DOWN:
			DIS_MEN_SET(0,Now_Nober);
			Set_Time(TIMESET_T.year-2000,TIMESET_T.month,TIMESET_T.date,TIMESET_T.hours,TIMESET_T.min,TIMESET_T.sec,0);
			break;
		default:
			break;
	}
}

void MEN_KEY(unsigned char keyval)		/*按键界面处理 接口函数*/
{
		switch(MEN_T.Now_Men)				/*判断当前界面*/
		{
			case MEN_DIS:
				KEY_MEN_DIS(Key_T.KeyValue);
				break;
			case MEN_SET:
				KEY_MEN_SET(Key_T.KeyValue);
				break;
			case MEN_ID:
				KEY_MEN_ID(Key_T.KeyValue);
				break;
			case MEN_BAUD:
				KEY_MEN_BAUD(Key_T.KeyValue);
				break;
			case MEN_PARY:
				KEY_MEN_PARY(Key_T.KeyValue);
				break;
			case MEN_BACKLIGHT:
				KEY_MEN_BACKLIGHT(Key_T.KeyValue);
				break;
			case MEN_MESSGEMODE:
				KEY_MEN_MESSGEMODE(Key_T.KeyValue);
				break;
			case MEN_SLEEPTIME:
				KEY_MEN_SLEEPTIME(Key_T.KeyValue);
				break;
			case MEN_SHT1MODE:
				KEY_MEN_SHT1MODE(Key_T.KeyValue);
				break;
			case MEN_SHT2MODE:
				KEY_MEN_SHT2MODE(Key_T.KeyValue);
				break;
			case MEN_18B20MODE:
				KEY_MEN_18B20MODE(Key_T.KeyValue);
				break;
			case MEN_WARNING:
				KEY_MEN_WARNING(Key_T.KeyValue);
				break;
			case MEN_CAL:
				KEY_MEN_CAL(Key_T.KeyValue);
				break;
			case MEN_TIME:
				KEY_MEN_TIME(Key_T.KeyValue);
				break;

		}
}






