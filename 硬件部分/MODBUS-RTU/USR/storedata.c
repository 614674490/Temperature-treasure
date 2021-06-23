#include "pbdata.h"

storeparam_ STOREPARAM_U;
storedata_ STOREDATA_U;
unsigned char SendDataBuf[4000];

void StoreSysParamInit(storeparam_ *sp)
{
	SPI_Flash_Read(sp->buf,0x0,sizeof(sp->buf));
	
	if(sp->usr_.storeflag1 == 0x55aa && sp->usr_.storeflag2 == 0x55aa )	/*不是第一次启动,可以使用*/
	{
		
	}else
	{
		sp->usr_.storeflag1 = 0x55aa;																			/*第一次启动，初始化存储参数*/
		sp->usr_.storeflag2 = 0x55aa;
		sp->usr_.datanum    = 0;
		sp->usr_.nowaddr    = DataStartAddr;
		sp->usr_.lastaddr   = DataStartAddr;
		
		SPI_Flash_Write(sp->buf,0x0,sizeof(sp->buf));
	}
}

void InitStore(storeparam_ *sp)
{
	sp->usr_.storeflag1 = 0x55aa;																			/*第一次启动，初始化存储参数*/
	sp->usr_.storeflag2 = 0x55aa;
	sp->usr_.datanum    = 0;
	sp->usr_.nowaddr    = DataStartAddr;
	sp->usr_.lastaddr   = DataStartAddr;
	
	SPI_Flash_Write(sp->buf,0x0,sizeof(sp->buf));
}

unsigned short GetData(storeparam_ *sp,unsigned char *buf,unsigned int startNum,unsigned int num)		/*一次最多读取200条，条数不够时，已最后一条结束*/
{
	unsigned int readNum=0;
	
	if(num >200)
		readNum = 200;		
	else
		readNum = num;
	
	if(startNum > sp->usr_.datanum )
		return 0;
	if(startNum+num > sp->usr_.datanum)
		return 0;
	
	SPI_Flash_Read(buf,startNum*OnePackageLen,readNum*OnePackageLen);
	
	return (num*OnePackageLen);
}

void StoreData(time_ tt,storeparam_ *sp,storedata_ *sd)
{		
	if(tt.sec == 0)
	{
		sd->usr_.isServer  = 0;
		
		sd->usr_.year  = tt.year;
		sd->usr_.month = tt.month;
		sd->usr_.date  = tt.date;
		sd->usr_.hours = tt.hours;
		sd->usr_.min   = tt.min;
		sd->usr_.sec   = tt.sec;
		
		sd->usr_.t1 = (short)(SHT75_T.temp_1*10);
		sd->usr_.h1 = (short)(SHT75_T.humi_1*10);
		sd->usr_.t2 = (short)(SHT75_T.temp_2*10);
		sd->usr_.h2 = (short)(SHT75_T.humi_2*10);
		sd->usr_.t3 = (short)(Ds18_T.Temp_1*10);
				
		
		if( (DataPackageNum - sp->usr_.datanum) < 2 )		/*数据已存满，不可继续存储*/
		{
			
		}else 																								/*正常存储数据*/
		{
			SPI_Flash_Write(sd->buf,sp->usr_.nowaddr,sizeof(sd->buf));
			
			sp->usr_.datanum++;
			sp->usr_.lastaddr = sp->usr_.nowaddr;					/*记录上一次数据存储的位置，等待服务器回应消息后，改变标志*/
			sp->usr_.nowaddr += OnePackageLen;						/*在存储器 开头，写入当前存储数据的情况*/
			SPI_Flash_Write(sp->buf,0x0,sizeof(sp->buf));
			
			
		}
		
	}
	
	if( (STMID_T.myid[0]/10)==tt.sec )			/*数据是 随机上传的*/	
		SendDataToServer();
	
}

void SendDataToServer(void)
{
	unsigned short elementId[6] = {1,2,281,282,283,32};
	short element_b[6] = {1000,0,1000,0,1000,0};
	unsigned char buf[50],packagenum=1,elementnum=6,onepackagelen=31;
	unsigned short len=46,packageid=1;
	unsigned char eleidbuflen = sizeof(elementId);
	
	if( Sys_Para_T.TH_1_Mode == 0)
	{
		elementId[0] = 284;
		elementId[1] = 285;
		SHT75_T.temp_1 = 0;
		SHT75_T.humi_1 = 0;
		element_b[0] = 0;
	}
	
	if( Sys_Para_T.TH_2_Mode == 0)
	{
		elementId[2] = 286;
		elementId[3] = 287;
		SHT75_T.temp_2 = 0; 
		SHT75_T.humi_2 = 0;
		element_b[2] = 0;
	}
	
	if( Sys_Para_T.T_3_Mode == 0)
	{
		elementId[4] = 288;
		Ds18_T.Temp_1 = 0;
		element_b[4] = 0;
	}
	
	buf[0] = 0x55;
	buf[1] = 0xbb;
	buf[2] = len;
	buf[3] = len>>8;
	buf[4] = 0x33;  /*数据通讯命令*/
	
	buf[5] = STMID_T.myid[0];
	buf[6] = STMID_T.myid[1];
	buf[7] = STMID_T.myid[2];
	
	buf[8] = packageid;
	buf[9] = packageid>>8;

	buf[10] = packagenum;
	buf[11] = elementnum;
	buf[12] = onepackagelen;
	
	memcpy(buf+13,elementId,eleidbuflen);

	memcpy(buf+13+eleidbuflen,STOREDATA_U.buf+1,7);
	
	buf[13+eleidbuflen+5+2+0] = (STOREDATA_U.usr_.t1+element_b[0]);
	buf[13+eleidbuflen+5+2+1] = (STOREDATA_U.usr_.t1+element_b[0])>>8;
	
	buf[13+eleidbuflen+5+2+2] = (STOREDATA_U.usr_.h1/10);
	buf[13+eleidbuflen+5+2+3] = (STOREDATA_U.usr_.h1/10)>>8;
	
	buf[13+eleidbuflen+5+2+4] = (STOREDATA_U.usr_.t2+element_b[2]);
	buf[13+eleidbuflen+5+2+5] = (STOREDATA_U.usr_.t2+element_b[2])>>8;
	
	buf[13+eleidbuflen+5+2+6] = (STOREDATA_U.usr_.h2/10);
	buf[13+eleidbuflen+5+2+7] = (STOREDATA_U.usr_.h2/10)>>8;
	
	buf[13+eleidbuflen+5+2+8] = (STOREDATA_U.usr_.t3+element_b[4]);
	buf[13+eleidbuflen+5+2+9] = (STOREDATA_U.usr_.t3+element_b[4])>>8;
	
	buf[13+eleidbuflen+5+2+10] = (unsigned short)(AD_INDATA_T.AD_IN_V/100);
	buf[13+eleidbuflen+5+2+11] = (unsigned short)(AD_INDATA_T.AD_IN_V/100)>>8;
	
	buf[13+eleidbuflen+5+2+12] = 0xee;
	buf[13+eleidbuflen+5+2+13] = SumCheck(buf,len-1);
	
	switch(Sys_Para_T.MessageMode)
	{
		case 0:				/*不通讯*/
			break;
		case 1:				/*WIFI通讯*/
			WIFI_AT("AT+CIPSTART=\"UDP\",\"123.56.241.118\",8899","OK",100,0);

			if( WIFI_AT("AT+CIPSEND=46",">",100,0) == 1)
				UARTX_Sendbytes(UART4,buf,len);
			break;
		case 2:				/*GPRS通讯*/
			UARTX_Sendbytes(UART4,buf,len);
			break;
	}
}


