#include "pbdata.h"

unsigned char loopdis=0;
int systemIntoDeepCount=0;
int keysystemIntoDeepCount=0;

Sys_Para_M Sys_Para_T;
ModBus_Mes MB_Mes = No_Mes;	/*��ʼ��������Ϣ*/

void RegPara_Init(void)			/*��ϵͳflash ��ȡ���ù��Ĳ�������ͬ���� Modbus�Ĵ���*/
{
	unsigned char buf[268];  /*4+264  ,4�ֽڵĲ�����־��264�ֽڵļĴ�������*/
	int i=0;
	
	STM_FLASH_Read(Para_ADDR,buf,268);
	if(buf[0]==0x55 && buf[1]==0xaa && buf[2]==0x55 && buf[3]==0xaa )   /*�ж�ϵͳ�����Ƿ����ù�*/
	{
		memcpy(usRegHoldingBuf,buf+4,264);																/*���Ĵ������ݻ�ԭ��������*/
	}else
	{
		usRegHoldingBuf[0] = Default_DeviceAddr;													/*���ڲ������*/
		usRegHoldingBuf[1] = Default_Baud;						
		usRegHoldingBuf[2] = Default_Parity;
		
		usRegHoldingBuf[3] = Default_BackLightMode;		
		usRegHoldingBuf[4] = Default_MessageMode;
		usRegHoldingBuf[5] = Default_SleepMin;
		
		usRegHoldingBuf[6] = Default_TH_1_Mode;
		usRegHoldingBuf[7] = Default_TH_2_Mode;
		usRegHoldingBuf[8] = Default_T_3_Mode;
		
		for(i=0;i<10;i++)
			usRegHoldingBuf[i+9] = Default_Warning;
		
		for(i=0;i<10;i+=2)
			usRegHoldingBuf[i+100] = Default_Chl_A;													/*ϵ��A ���*/
		
		for(i=0;i<10;i+=2)
			usRegHoldingBuf[i+101] = Default_Chl_B;													/*ϵ��B ���*/
	}
}

unsigned short GetBaudNum(int baud)								/*Ϊ�˾��� ���ڲ�ʹ�õĺ���*/
{
	switch(baud)
	{
		case 1200:
			return 0;
		case 2400:
			return 1;
		case 4800:
			return 2;
		case 9600:
			return 3;
		case 19200:
			return 4;
		case 38400:
			return 5;
		case 57600:
			return 6;
		case 115200:
			return 7;
		default:
			return 3;
	}
}

unsigned short GetParityNum(eMBParity parity)		/*Ϊ�˾��� ���ڲ�ʹ�õĺ���*/
{
	switch(parity)
	{
		case MB_PAR_NONE:
			return 0;
		case MB_PAR_ODD:
			return 1;
		case MB_PAR_EVEN:
			return 2;
		default:
			return 0;
	}
}

void SysPara_Init(unsigned short *regbuf,Sys_Para_M *sys_t)						/*�жϽ�Modbus�Ĵ����е������Ƿ�Ϸ� �� ת��Ϊ ϵͳ��ʹ�õĽṹ��*/
{	
	int i=0;
	
	if(regbuf[0]>0 && regbuf[0]<255)
		sys_t->Addr = regbuf[0];				/*��ֵ��ַ,��ַ��ΧΪ 1~254*/
	else
		regbuf[0] = sys_t->Addr;				/*�����ַ�Ƿ�������ǰ��ַ��ֵ���Ĵ���*/

	
	switch(regbuf[1])									/*��ֵ������*/
	{
		case BAUD1200:
			sys_t->Baud = 1200;
			break;
		case BAUD2400:
			sys_t->Baud = 2400;
			break;
		case BAUD4800:
			sys_t->Baud = 4800;
			break;
		case BAUD9600:
			sys_t->Baud = 9600;
			break;
		case BAUD19200:
			sys_t->Baud = 19200;
			break;
		case BAUD38400:
			sys_t->Baud = 38400;
			break;
		case BAUD57600:
			sys_t->Baud = 57600;
			break;
		case BAUD115200:
			sys_t->Baud = 115200;
			break;
		default:
			regbuf[1] = GetBaudNum(sys_t->Baud);	/*��������ʷǷ�������ǰ�����ʵı�ʶ��ֵ�� �Ĵ���*/
			break;
	}
	
	switch(regbuf[2])							/*��ֵ��żУ��λ*/
	{
		case PAR_NONE:
			sys_t->Parity = MB_PAR_NONE;
			break;
		case PAR_ODD:
			sys_t->Parity = MB_PAR_ODD;
			break;
		case PAR_EVEN:
			sys_t->Parity = MB_PAR_EVEN;
			break;
		default:
			regbuf[2] = GetParityNum(sys_t->Parity);	/*�����żУ��Ƿ����򽫵�ǰ����żУ���ʶ��ֵ���Ĵ���*/
			break;
	}
	
	switch(regbuf[3])															/*����ģʽ����*/
	{
		case BL_CLOSE:
			sys_t->BackLightMode = BL_CLOSE;
			break;
		case BL_AUTO:
			sys_t->BackLightMode = BL_AUTO;
			break;
		case BL_OPEN:
			sys_t->BackLightMode = BL_OPEN;
			break;
		default:
			regbuf[3] = sys_t->BackLightMode;
			break;
	}
	
	switch(regbuf[4])
	{
		case ME_NO:
			sys_t->MessageMode = ME_NO;
			break;
		case ME_WIFI:
			sys_t->MessageMode = ME_WIFI;
			break;
		case ME_GPRS:
			sys_t->MessageMode = ME_GPRS;
			break;
		default:
			regbuf[4] = sys_t->MessageMode;
			break;
	}
	
	sys_t->SleepMin = regbuf[5];
	
	switch(regbuf[6])
	{
		case SENSOR_NOTUSE:
			sys_t->TH_1_Mode = SENSOR_NOTUSE;
			break;
		case SENSOR_USE:
			sys_t->TH_1_Mode = SENSOR_USE;
			break;
		default:
			regbuf[6] = sys_t->TH_1_Mode;
			break;
	}
		
	switch(regbuf[7])
	{
		case SENSOR_NOTUSE:
			sys_t->TH_2_Mode = SENSOR_NOTUSE;
			break;
		case SENSOR_USE:
			sys_t->TH_2_Mode = SENSOR_USE;
			break;
		default:
			regbuf[7] = sys_t->TH_2_Mode;
			break;
	}
		
	switch(regbuf[8])
	{
		case SENSOR_NOTUSE:
			sys_t->T_3_Mode = SENSOR_NOTUSE;
			break;
		case SENSOR_USE:
			sys_t->T_3_Mode = SENSOR_USE;
			break;
		default:
			regbuf[8] = sys_t->T_3_Mode;
			break;
	}
	
	for(i=0;i<4;i++)
		sys_t->TH_1_Warning[i] = (float)(short)regbuf[9+i]/10.0;
	
	for(i=0;i<4;i++)
		sys_t->TH_2_Warning[i] = (float)(short)regbuf[13+i]/10.0;
	
	for(i=0;i<2;i++)
		sys_t->T_3_Warning[i] = (float)(short)regbuf[17+i]/10.0;
	
	
	for(i=0;i<4;i++)
		sys_t->TH_1_Cal[i] = (float)(short)regbuf[100+i]/1000.0;
	
	for(i=0;i<4;i++)
		sys_t->TH_2_Cal[i] = (float)(short)regbuf[104+i]/1000.0;
	
	for(i=0;i<2;i++)
		sys_t->T_3_Cal[i] = (float)(short)regbuf[108+i]/1000.0;
}

void StartUp_Init(void)						/*���������Ķ�ȡ,�ⲿ����*/
{
	RegPara_Init();
	SysPara_Init(usRegHoldingBuf,&Sys_Para_T);			
}

void Usr_SetPara(void)						/*�û����ò���*/
{
	unsigned char buf[268]={0x55,0xaa,0x55,0xaa};  /*4+264  ,4�ֽڵĲ�����־��264�ֽڵļĴ�������*/
	
	SysPara_Init(usRegHoldingBuf,&Sys_Para_T);		 /*�������ݵ� ���� �� ����ṹ��ĸ�ֵ*/
	memcpy(buf+4,usRegHoldingBuf,264);						 /*���Ĵ������ݻ�ԭ��������*/
	STM_FLASH_Write(Para_ADDR,buf,268);
}

void ModBus_Message_Deal(ModBus_Mes *mes_)       /*Modbus��Ϣ����*/
{
	switch(*mes_)
	{
		case No_Mes:
			ADIN_GET_IO();
			DataDeal_Process();
			break;
		case Set_SysPara:
			Usr_SetPara();
			Reset_STM();
			break;
		default:
			break;
	}
	
	*mes_ = No_Mes;              	 /*�����Ϣ��־*/
}


float Avrage(float *buf,float len)
{
	int i=0;
	float sum=0;
	
	for(i=0;i<len;i++)
		sum +=buf[i];
	
	return sum/len;
}

void TempHumiData_GetAndDeal(unsigned char sec)
{
	if( sec%5 ==0 )
	{
		loopdis++;
		DIS_Suona(1,0);
		DIS_Suona(2,0);
		DIS_TOPDOWN(1,0);
		DIS_TOPDOWN(2,0);
		BACKLIGHT_SET(Sys_Para_T.BackLightMode,0,0);
	}
		
	switch(loopdis)
	{
		case 0:
			if(Sys_Para_T.TH_1_Mode==0)
			{
				loopdis++;
			}else
			{
				SHT75_GetData(1);
				DIS_SensorChl(3,1);
				
				if( SHT75_T.temp_1<-50 || SHT75_T.temp_1>150)
				{
					DIS_NODATA(3);
					DIS_FIRST_POINT(0);
					DIS_SECOND_POINT(0);
				}else
				{
					SHT75_T.temp_1 = SHT75_T.temp_1*Sys_Para_T.TH_1_Cal[0] + Sys_Para_T.TH_1_Cal[1];
					SHT75_T.humi_1 = SHT75_T.humi_1*Sys_Para_T.TH_1_Cal[2] + Sys_Para_T.TH_1_Cal[3];
					DIS_TempHumi(SHT75_T.temp_1,SHT75_T.humi_1);
					TempHumiData_Warning(1,SHT75_T.temp_1,SHT75_T.humi_1);
				}
				break;
			}
		case 1:
			if(Sys_Para_T.TH_2_Mode==0)
			{
				loopdis++;
			}else
			{
				SHT75_GetData(2);
				DIS_SensorChl(3,2);
				
				if( SHT75_T.temp_2<-50 || SHT75_T.temp_2>150)
				{
					DIS_NODATA(3);
					DIS_FIRST_POINT(0);
					DIS_SECOND_POINT(0);
				}else
				{
					SHT75_T.temp_2 = SHT75_T.temp_2*Sys_Para_T.TH_2_Cal[0] + Sys_Para_T.TH_2_Cal[1];
					SHT75_T.humi_2 = SHT75_T.humi_2*Sys_Para_T.TH_2_Cal[2] + Sys_Para_T.TH_2_Cal[3];
					
					DIS_TempHumi(SHT75_T.temp_2,SHT75_T.humi_2);
					TempHumiData_Warning(2,SHT75_T.temp_2,SHT75_T.humi_2);
				}
				break;
			}
		case 2:
			if(Sys_Para_T.T_3_Mode==0)
			{
				loopdis++;
			}else
			{
				Ds18_T.Temp_1 = DS18B20_Get_wd(1);
				DIS_SensorChl(1,3);
				
				if( Ds18_T.Temp_1<-50 || Ds18_T.Temp_1>150)
				{
					DIS_NODATA(3);
					DIS_FIRST_POINT(0);
					DIS_SECOND_POINT(0);
				}else
				{
					Ds18_T.Temp_1 = Ds18_T.Temp_1*Sys_Para_T.T_3_Cal[0] + Sys_Para_T.T_3_Cal[1];
					
					DIS_TempHumi(Ds18_T.Temp_1,SHT75_T.humi_2);		/*������ ��ʪ�ȵ���ʾ����*/
					TempHumiData_Warning(3,Ds18_T.Temp_1,0);
				}
				
				DIS_NUM_7b1(17);
				DIS_NUM_7b2(17);
				DIS_NUM_10b1(17);
				DIS_SECOND_POINT(0);
				DIS_NUM_10b2(17);
				DIS_PC(0);
				break;
			}
		default:
			loopdis=0;
			break;
	}
}


void TempHumiData_Warning(unsigned char chl,float temp,float humi)
{
	switch(chl)
	{
		case 1:
			
			if( temp > Sys_Para_T.TH_1_Warning[0] && Sys_Para_T.TH_1_Warning[0]!=0 )  /*1·�¶ȴ�������ֵ������ֵ��Ϊ0(Ϊ0ʱ�����ñ���)*/
			{
				BEEP_Speek(SpeekTime,SpeekFre);
				DIS_Suona(1,1);
				DIS_TOPDOWN(1,1);
				BACKLIGHT_SET(Sys_Para_T.BackLightMode,1,2);
			}
			
			if( temp < Sys_Para_T.TH_1_Warning[1] && Sys_Para_T.TH_1_Warning[1]!=0 )  /*1·�¶�С������ֵ������ֵ��Ϊ0(Ϊ0ʱ�����ñ���)*/
			{
				BEEP_Speek(SpeekTime,SpeekFre);
				DIS_Suona(1,1);
				DIS_TOPDOWN(1,2);
				BACKLIGHT_SET(Sys_Para_T.BackLightMode,2,1);
			}
			
			if( humi > Sys_Para_T.TH_1_Warning[2] && Sys_Para_T.TH_1_Warning[2]!=0 )  /*1·ʪ�ȴ�������ֵ������ֵ��Ϊ0(Ϊ0ʱ�����ñ���)*/
			{
				BEEP_Speek(SpeekTime,SpeekFre);
				DIS_Suona(2,1);
				DIS_TOPDOWN(2,1);
				BACKLIGHT_SET(Sys_Para_T.BackLightMode,1,2);
			}
			
			if( humi < Sys_Para_T.TH_1_Warning[3] && Sys_Para_T.TH_1_Warning[3]!=0 )  /*1·ʪ�ȴ�������ֵ������ֵ��Ϊ0(Ϊ0ʱ�����ñ���)*/
			{
				BEEP_Speek(SpeekTime,SpeekFre);
				DIS_Suona(2,1);
				DIS_TOPDOWN(2,2);
				BACKLIGHT_SET(Sys_Para_T.BackLightMode,2,1);
			}
			break;
			
		case 2:
			
			if( temp > Sys_Para_T.TH_2_Warning[0] && Sys_Para_T.TH_2_Warning[0]!=0 )  /*2·�¶ȴ�������ֵ������ֵ��Ϊ0(Ϊ0ʱ�����ñ���)*/
			{
				BEEP_Speek(SpeekTime,SpeekFre);
				DIS_Suona(1,1);
				DIS_TOPDOWN(1,1);
				BACKLIGHT_SET(Sys_Para_T.BackLightMode,1,2);
			}
			
			if( temp < Sys_Para_T.TH_2_Warning[1] && Sys_Para_T.TH_2_Warning[1]!=0 )  /*2·�¶�С������ֵ������ֵ��Ϊ0(Ϊ0ʱ�����ñ���)*/
			{
				BEEP_Speek(SpeekTime,SpeekFre);
				DIS_Suona(1,1);
				DIS_TOPDOWN(1,2);
				BACKLIGHT_SET(Sys_Para_T.BackLightMode,2,1);
			}
			
			if( humi > Sys_Para_T.TH_2_Warning[2] && Sys_Para_T.TH_2_Warning[2]!=0 )  /*2·ʪ�ȴ�������ֵ������ֵ��Ϊ0(Ϊ0ʱ�����ñ���)*/
			{
				BEEP_Speek(SpeekTime,SpeekFre);
				DIS_Suona(2,1);
				DIS_TOPDOWN(2,1);
				BACKLIGHT_SET(Sys_Para_T.BackLightMode,1,2);
			}
			
			if( humi < Sys_Para_T.TH_2_Warning[3] && Sys_Para_T.TH_2_Warning[3]!=0 )  /*2·ʪ�ȴ�������ֵ������ֵ��Ϊ0(Ϊ0ʱ�����ñ���)*/
			{
				BEEP_Speek(SpeekTime,SpeekFre);
				DIS_Suona(2,1);
				DIS_TOPDOWN(2,2);
				BACKLIGHT_SET(Sys_Para_T.BackLightMode,2,1);
			}
			break;
			
		case 3:
			
			if( temp > Sys_Para_T.T_3_Warning[0] && Sys_Para_T.T_3_Warning[0]!=0 )  /*2·�¶ȴ�������ֵ������ֵ��Ϊ0(Ϊ0ʱ�����ñ���)*/
			{
				BEEP_Speek(SpeekTime,SpeekFre);
				DIS_Suona(1,1);
				DIS_TOPDOWN(1,1);
				BACKLIGHT_SET(Sys_Para_T.BackLightMode,1,2);
			}
			
			if( temp < Sys_Para_T.T_3_Warning[1] && Sys_Para_T.T_3_Warning[1]!=0 )  /*2·�¶�С������ֵ������ֵ��Ϊ0(Ϊ0ʱ�����ñ���)*/
			{
				BEEP_Speek(SpeekTime,SpeekFre);
				DIS_Suona(1,1);
				DIS_TOPDOWN(1,2);
				BACKLIGHT_SET(Sys_Para_T.BackLightMode,2,1);
			}
			break;
			
		default:
			break;
	}
}

void TH_To_ModbusReg(unsigned short *buf,SHT75 sht,DS18B20 ds)
{
	buf[0] = (short)(sht.temp_1*10);
	buf[1] = (short)(sht.humi_1*10);
	buf[2] = (short)(sht.temp_2*10);
	buf[3] = (short)(sht.humi_2*10);
	buf[4] = (short)(ds.Temp_1*10);
}

void SystemDeep(void)		/*�˺������� ÿ��ִ��һ��*/
{
	if(Sys_Para_T.SleepMin != 0)
	{
		systemIntoDeepCount++;
		if(systemIntoDeepCount > (Sys_Para_T.SleepMin*60) )
		{
			/*�˴���ӽ���͹��ĵĺ���*/
			systemIntoDeepCount=0;
			delay_ms(1000);
			delay_ms(1000);
			delay_ms(1000);
				
			LCD_CLOSE();
			WIFI_AT("AT+GSLP=1","OK",100,0);
			RCC_APB2PeriphResetCmd(0X01FC,DISABLE); //��λ����IO��
			Sys_Standby();
		}
	}
}











