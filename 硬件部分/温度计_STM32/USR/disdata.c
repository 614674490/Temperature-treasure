#include "pbdata.h"

void DIS_TempHumi(float temp,float humi)			/*进来的数据首先扩大1000倍，方便显示计算每一位，实际显示仍然是 原数据*/
{
	unsigned char ge,shi,bai,qian;
	int tempX10=fabs(temp*10),humiX10=fabs(humi*10);
	
	if(temp<0.0)
		DIS_Minus(1,1);
	else
		DIS_Minus(1,0);
	
	qian = tempX10/1000;
	if(qian==0) 
		qian=16;
	
	bai  = tempX10%1000/100;
	shi  = tempX10%1000%100/10;
	ge   = tempX10%1000%100%10;
	
	DIS_NUM_2b1(qian);
	DIS_NUM_2b2(bai);
	DIS_NUM_5b1(shi);
	DIS_FIRST_POINT(1);
	DIS_NUM_5b2(ge);
	DIS_DC(3);
	
	qian = humiX10/1000;
	if(qian==0) 
		qian=16;
	
	bai  = humiX10%1000/100;
	shi  = humiX10%1000%100/10;
	ge   = humiX10%1000%100%10;
	
	DIS_NUM_7b1(qian);
	DIS_NUM_7b2(bai);
	DIS_NUM_10b1(shi);
	DIS_SECOND_POINT(1);
	DIS_NUM_10b2(ge);
	DIS_PC(1);
}

void DIS_Time(time_ tt)
{
	DIS_N3(1);
	DIS_N4(1);
	DIS_MonthAndDate(1);
		
	DIS_NUM_N1_N2(tt.month/10);
	DIS_NUM_18(tt.month%10);
	
	DIS_NUM_19(tt.date/10);
	DIS_NUM_20(tt.date%10);
	
	DIS_NUM_21b1(tt.hours/10);
	DIS_NUM_21b2(tt.hours%10);
	
	DIS_NUM_24b1(tt.min/10);
	DIS_NUM_24b2(tt.min%10);
	
	DIS_NUM_13(tt.sec/10);
	DIS_NUM_14(tt.sec%10);
	
	DIS_HMS(3);
}

void DIS_Voltage(float valmv)
{
	static unsigned char volcharge=2;
	float temp = valmv/1000.0;
	
	if(temp >= VoltageMax) temp = VoltageMax;
	if(temp <= VoltageMin) temp = VoltageMin;
	
	if(READ_TP == 0)
	{
		if(volcharge > 5)
			volcharge=2;
		
		DIS_Battery(volcharge);
			volcharge++;
		
	}else
	{
		if(temp <= VoltageMin)		/*电量太低，进入休眠状态*/
		{
			delay_ms(1000);
			delay_ms(1000);
			delay_ms(1000);
				
			LCD_CLOSE();
			WIFI_AT("AT+GSLP=1","OK",100,0);
			RCC_APB2PeriphResetCmd(0X01FC,DISABLE); //复位所有IO口
			Sys_Standby();
		}else if(temp <= 3.4)
		{
			DIS_Battery(1);
		}else if(temp <= 3.6)
		{
			DIS_Battery(2);
		}else if(temp <= 3.8) 
		{
			DIS_Battery(3);
		}else if(temp <= 4.0)
		{
			DIS_Battery(4);
		}else if(temp <= 4.2)
		{
			DIS_Battery(5);
		}
	}
}

void DIS_RTU_Addr(unsigned char val)
{
	DIS_ID(1);
	
	DIS_NUM_15(val/100);
	DIS_NUM_16(val%100/10);
	DIS_NUM_17(val%100%10);
}

void DIS_SystemInit(void)
{
	Read_Time(&TIME_T);
	DIS_Time(TIME_T);
	
	DIS_NODATA(3);
	
	SHT75_T.temp_1 = 0;
	SHT75_T.humi_1 = 0;
	SHT75_T.temp_2 = 0; 
	SHT75_T.humi_2 = 0;
	Ds18_T.Temp_1 = 0;
	
	if(Sys_Para_T.TH_1_Mode==1)
	{
		SHT75_GetData(1);
		SHT75_T.temp_1 = SHT75_T.temp_1*Sys_Para_T.TH_1_Cal[0] + Sys_Para_T.TH_1_Cal[1];
		SHT75_T.humi_1 = SHT75_T.humi_1*Sys_Para_T.TH_1_Cal[2] + Sys_Para_T.TH_1_Cal[3];
	}
	
	if(Sys_Para_T.TH_2_Mode==1)
	{
		SHT75_GetData(2);
		SHT75_T.temp_2 = SHT75_T.temp_2*Sys_Para_T.TH_2_Cal[0] + Sys_Para_T.TH_2_Cal[1];
		SHT75_T.humi_2 = SHT75_T.humi_2*Sys_Para_T.TH_2_Cal[2] + Sys_Para_T.TH_2_Cal[3];
	}
	
	if(Sys_Para_T.T_3_Mode==1)
	{
		//Ds18_T.Temp_1 = DS18B20_Get_wd(1);
		Ds18_T.Temp_1 = Ds18_T.Temp_1*Sys_Para_T.T_3_Cal[0] + Sys_Para_T.T_3_Cal[1];
	}
	
	AD_INDATA_T.AD_IN_V = ReadADCAverageValue(0)*3;
	DIS_Voltage(AD_INDATA_T.AD_IN_V);
	
	DIS_RTU_Addr(Sys_Para_T.Addr);
}

void DIS_MenNum(unsigned char val)
{
	if(val <=99)
	{
		DIS_No(1);
		DIS_NUM_11(val/10);
		DIS_NUM_12(val%10);
	}else							/*清空显示*/
	{
		DIS_No(0);
		DIS_NUM_11(16);
		DIS_NUM_12(16);
	}
	
}

void DIS_SensorChl(unsigned char num,unsigned char val)
{
	switch(num)
	{
		case 1:
			DIS_NUM_1(val);
			DIS_NUM_6(17);
			break;
		case 2:
			DIS_NUM_1(17);
			DIS_NUM_6(val);
			break;
		case 3:
			DIS_NUM_1(val);
			DIS_NUM_6(val);
			break;
	}
	
}

void DIS_NODATA(unsigned char val)
{
	if(val>3) val=0;
	
	DIS_NUM_2b1(17);
	DIS_NUM_2b2(17);
	DIS_NUM_5b1(17);
	DIS_NUM_5b2(17);
	DIS_NUM_7b1(17);
	DIS_NUM_7b2(17);
	DIS_NUM_10b1(17);
	DIS_NUM_10b2(17);
	
	switch(val)
	{
		case 0:
			DISBUF_U.usr_.gether_2b1_7b1_.sm2_7=0;
			DISBUF_U.usr_.gether_2b2_7b2_.sm2_7=0;
			DISBUF_U.usr_.gether_5b1_10b1_.sm5_7=0;
			DISBUF_U.usr_.gether_5b2_10b2_.sm5_7=0;
		
			DISBUF_U.usr_.gether_2b1_7b1_.sm7_7=0;
			DISBUF_U.usr_.gether_2b2_7b2_.sm7_7=0;
			DISBUF_U.usr_.gether_5b1_10b1_.sm10_7=0;
			DISBUF_U.usr_.gether_5b2_10b2_.sm10_7=0;
			break;
		case 1:
			DISBUF_U.usr_.gether_2b1_7b1_.sm2_7=1;
			DISBUF_U.usr_.gether_2b2_7b2_.sm2_7=1;
			DISBUF_U.usr_.gether_5b1_10b1_.sm5_7=1;
			DISBUF_U.usr_.gether_5b2_10b2_.sm5_7=1;
		
			DISBUF_U.usr_.gether_2b1_7b1_.sm7_7=0;
			DISBUF_U.usr_.gether_2b2_7b2_.sm7_7=0;
			DISBUF_U.usr_.gether_5b1_10b1_.sm10_7=0;
			DISBUF_U.usr_.gether_5b2_10b2_.sm10_7=0;
			break;
		case 2:
			DISBUF_U.usr_.gether_2b1_7b1_.sm2_7=0;
			DISBUF_U.usr_.gether_2b2_7b2_.sm2_7=0;
			DISBUF_U.usr_.gether_5b1_10b1_.sm5_7=0;
			DISBUF_U.usr_.gether_5b2_10b2_.sm5_7=0;
		
			DISBUF_U.usr_.gether_2b1_7b1_.sm7_7=1;
			DISBUF_U.usr_.gether_2b2_7b2_.sm7_7=1;
			DISBUF_U.usr_.gether_5b1_10b1_.sm10_7=1;
			DISBUF_U.usr_.gether_5b2_10b2_.sm10_7=1;
			break;
		case 3:
			DISBUF_U.usr_.gether_2b1_7b1_.sm2_7=1;
			DISBUF_U.usr_.gether_2b2_7b2_.sm2_7=1;
			DISBUF_U.usr_.gether_5b1_10b1_.sm5_7=1;
			DISBUF_U.usr_.gether_5b2_10b2_.sm5_7=1;
		
			DISBUF_U.usr_.gether_2b1_7b1_.sm7_7=1;
			DISBUF_U.usr_.gether_2b2_7b2_.sm7_7=1;
			DISBUF_U.usr_.gether_5b1_10b1_.sm10_7=1;
			DISBUF_U.usr_.gether_5b2_10b2_.sm10_7=1;
			break;
	}
}

void Wifi_SmartSta(void)
{
	static int count=0,disnum=1;
	
	count++;
	if(count > 50)
	{
		count=0;
		DIS_Wifi(disnum);
		Update_Display(DISBUF_U);
		disnum++;
		if(disnum>5)
			disnum=1;
		
	}
}

void DataStoreSta(void)
{
	static unsigned char val=0;
	
	if( (DataPackageNum - STOREPARAM_U.usr_.datanum) < 2 )
	{
		val = 1;
	}else if((DataPackageNum - STOREPARAM_U.usr_.datanum) < 1000)
	{
		val = ~val;
	}else
	{
		val = 0;
	}
	
	DIS_Usb(val&0x01);
}





