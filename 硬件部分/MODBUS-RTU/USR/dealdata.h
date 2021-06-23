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

#define BL_CLOSE   0	/*背光*/
#define BL_AUTO    1
#define BL_OPEN    2

#define ME_NO			 0	/*通讯方式*/
#define ME_WIFI		 1
#define ME_GPRS		 2

#define SENSOR_NOTUSE 0
#define SENSOR_USE    1


/*以下为系统默认参数*/
#define Default_DeviceAddr 1         		/*默认地址为1*/
#define Default_Baud			 BAUD9600  		/*默认波特率为9600*/
#define Default_Parity		 PAR_NONE  		/*默认无校验*/
#define Default_Chl_A			 1000  				/*默认A系数为10000，系数在传输、存储时都是扩大1000倍的*/
#define Default_Chl_B      0						/*默认B系数为0*/
#define Default_Warning    0						/*默认报警值为0 ，不启用报警功能*/
#define Default_BackLightMode 0					/*默认背光关闭*/
#define Default_MessageMode   1					/*默认不通讯*/
#define Default_SleepMin			0					/*默认不休眠*/
#define Default_TH_1_Mode     1					/*默认启动内部温湿度传感器*/
#define Default_TH_2_Mode			0					/*默认外部温湿度传感器不启动*/
#define Default_T_3_Mode			0 				/*默认外部温度传感器不启动*/

/*以下为系统配置所使用的参数*/
typedef struct
{
	unsigned short Addr;									/*设备地址，范围 1~254*/
	int						 Baud;									/*串口波特率*/
	eMBParity 		 Parity;								/*奇偶校验，使用Modbus库的 枚举类*/
	unsigned short BackLightMode;					/*背光模式*/
	unsigned short MessageMode;						/*通讯模式*/
	unsigned short SleepMin;							/*定时休眠，0为不休眠*/
	unsigned short TH_1_Mode;							/*内部温湿度传感器是否启用*/
	unsigned short TH_2_Mode;							/*外部温湿度传感器是否启用*/
	unsigned short T_3_Mode;							/*外部温度传感器是否启用*/
	float TH_1_Warning[4];								/*内部温湿度传感器 报警值，T上下限，H上下限，共四个*/
	float TH_2_Warning[4];								/*外部温湿度传感器 报警值，T上下限，H上下限，共四个*/
	float T_3_Warning[2];									/*外部温度传感器 报警值，T上下限，共两个*/
	float TH_1_Cal[4];										/*内部温湿度传感器 校准值，T-A B，H-A B，共四个*/
	float TH_2_Cal[4];										/*外部温湿度传感器 校准值，T-A B，H-A B，共四个*/
	float T_3_Cal[2];											/*外部温度传感器 校准值，T-A B，共两个*/
}Sys_Para_M;
extern Sys_Para_M Sys_Para_T;

extern unsigned char loopdis;
extern int systemIntoDeepCount;					/*设备进入低功耗计数，若开启休眠功能1S 累加一次*/
extern int keysystemIntoDeepCount;			/*通过按键进入低功耗，计数*/

/*以下为系统消息处理所使用枚举类,设置寄存器时，进行消息处理，读取的自动更新寄存器*/
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
