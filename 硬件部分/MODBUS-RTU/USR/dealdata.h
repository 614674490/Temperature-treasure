#ifndef DEALDATA_H
#define DEALDATA_H

#include "pbdata.h"

#define BAUD1200   0
#define BAUD2400   1
#define BAUD4800   2
#define BAUD9600   3
#define BAUD19200  4
#define BAUD38400  5
#define BAUD57600  6
#define BAUD115200 7

#define PAR_NONE   0               
#define PAR_ODD    1           
#define PAR_EVEN   2   

#define BL_CLOSE   0	/*����*/
#define BL_AUTO    1
#define BL_OPEN    2

#define ME_NO			 0	/*ͨѶ��ʽ*/
#define ME_WIFI		 1
#define ME_GPRS		 2

#define SENSOR_NOTUSE 0
#define SENSOR_USE    1


/*����ΪϵͳĬ�ϲ���*/
#define Default_DeviceAddr 1         		/*Ĭ�ϵ�ַΪ1*/
#define Default_Baud			 BAUD9600  		/*Ĭ�ϲ�����Ϊ9600*/
#define Default_Parity		 PAR_NONE  		/*Ĭ����У��*/
#define Default_Chl_A			 1000  				/*Ĭ��Aϵ��Ϊ10000��ϵ���ڴ��䡢�洢ʱ��������1000����*/
#define Default_Chl_B      0						/*Ĭ��Bϵ��Ϊ0*/
#define Default_Warning    0						/*Ĭ�ϱ���ֵΪ0 �������ñ�������*/
#define Default_BackLightMode 0					/*Ĭ�ϱ���ر�*/
#define Default_MessageMode   1					/*Ĭ�ϲ�ͨѶ*/
#define Default_SleepMin			0					/*Ĭ�ϲ�����*/
#define Default_TH_1_Mode     1					/*Ĭ�������ڲ���ʪ�ȴ�����*/
#define Default_TH_2_Mode			0					/*Ĭ���ⲿ��ʪ�ȴ�����������*/
#define Default_T_3_Mode			0 				/*Ĭ���ⲿ�¶ȴ�����������*/

/*����Ϊϵͳ������ʹ�õĲ���*/
typedef struct
{
	unsigned short Addr;									/*�豸��ַ����Χ 1~254*/
	int						 Baud;									/*���ڲ�����*/
	eMBParity 		 Parity;								/*��żУ�飬ʹ��Modbus��� ö����*/
	unsigned short BackLightMode;					/*����ģʽ*/
	unsigned short MessageMode;						/*ͨѶģʽ*/
	unsigned short SleepMin;							/*��ʱ���ߣ�0Ϊ������*/
	unsigned short TH_1_Mode;							/*�ڲ���ʪ�ȴ������Ƿ�����*/
	unsigned short TH_2_Mode;							/*�ⲿ��ʪ�ȴ������Ƿ�����*/
	unsigned short T_3_Mode;							/*�ⲿ�¶ȴ������Ƿ�����*/
	float TH_1_Warning[4];								/*�ڲ���ʪ�ȴ����� ����ֵ��T�����ޣ�H�����ޣ����ĸ�*/
	float TH_2_Warning[4];								/*�ⲿ��ʪ�ȴ����� ����ֵ��T�����ޣ�H�����ޣ����ĸ�*/
	float T_3_Warning[2];									/*�ⲿ�¶ȴ����� ����ֵ��T�����ޣ�������*/
	float TH_1_Cal[4];										/*�ڲ���ʪ�ȴ����� У׼ֵ��T-A B��H-A B�����ĸ�*/
	float TH_2_Cal[4];										/*�ⲿ��ʪ�ȴ����� У׼ֵ��T-A B��H-A B�����ĸ�*/
	float T_3_Cal[2];											/*�ⲿ�¶ȴ����� У׼ֵ��T-A B��������*/
}Sys_Para_M;
extern Sys_Para_M Sys_Para_T;

extern unsigned char loopdis;
extern int systemIntoDeepCount;					/*�豸����͹��ļ��������������߹���1S �ۼ�һ��*/
extern int keysystemIntoDeepCount;			/*ͨ����������͹��ģ�����*/

/*����Ϊϵͳ��Ϣ������ʹ��ö����,���üĴ���ʱ��������Ϣ������ȡ���Զ����¼Ĵ���*/
typedef enum
{
	No_Mes,
	Set_SysPara
}ModBus_Mes;
extern ModBus_Mes MB_Mes;

void StartUp_Init(void);
void Usr_SetPara(void);
void ModBus_Message_Deal(ModBus_Mes *mes_);
void TempHumiData_GetAndDeal(unsigned char sec);
void TempHumiData_Warning(unsigned char chl,float temp,float humi);
void TH_To_ModbusReg(unsigned short *buf,SHT75 sht,DS18B20 ds);
void SystemDeep(void);

#endif
