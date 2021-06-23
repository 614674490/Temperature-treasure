#ifndef STOREDATA_H
#define STOREDATA_H

#include "pbdata.h"

#define OnePackageLen  20
#define EEPROMLenBit	 8000000
#define DataPackageNum ( (EEPROMLenBit-20)/OnePackageLen)

#define DataStartAddr	 (0x0+OnePackageLen)
#define DataEndAddr		 (EEPROMLenBit-OnePackageLen)

extern unsigned char SendDataBuf[4000];

typedef union
{
	unsigned char buf[OnePackageLen];
	struct 
	{
		unsigned short storeflag1;	/*两个起始标志*/
		unsigned short storeflag2;	
		unsigned int   datanum;			/*总数据条数*/
		unsigned int   nowaddr;			/*当前数据地址*/
		unsigned int	 lastaddr;		/*上一次数据存放地址*/
	}usr_;
}storeparam_;
extern storeparam_ STOREPARAM_U;

typedef union
{
	unsigned char buf[OnePackageLen];
	struct
	{
		unsigned char isServer;
		
		unsigned char month;
		unsigned char date;
		unsigned char hours;
		unsigned char min;
		unsigned char sec;
		
		unsigned short year;
		unsigned short t1;
		unsigned short h1;
		unsigned short t2;
		unsigned short h2;
		unsigned short t3;
	}usr_;
}storedata_;
extern storedata_ STOREDATA_U;

void StoreSysParamInit(storeparam_ *sp);
void StoreData(time_ tt,storeparam_ *sp,storedata_ *sd);
void SendDataToServer(void);
void InitStore(storeparam_ *sp);
unsigned short GetData(storeparam_ *sp,unsigned char *buf,unsigned int startNum,unsigned int num);

#endif
