#include "pbdata.h"

ds1340TimeReg_ TIMEREG_U;
time_ TIME_T;
time_ TIMESET_T;

void DS1340_WriteReg(unsigned char addr,unsigned char *buf,int len)
{
	int i=0;
	
	DS1340_I2C_Start();
	
	DS1340_I2C_Send_Byte(0xd0);
	DS1340_I2C_Wait_Ack();
	
	DS1340_I2C_Send_Byte(addr);
	DS1340_I2C_Wait_Ack();
	
	for(i=0;i<len;i++)
	{
		DS1340_I2C_Send_Byte(buf[i]);
		DS1340_I2C_Wait_Ack();
	}
	
	DS1340_I2C_Stop();
}

void DS1340_ReadReg(unsigned char addr,unsigned char *buf,int len)
{
	int i=0;
	
	DS1340_I2C_Start();
	
	DS1340_I2C_Send_Byte(0xd0);
	DS1340_I2C_Wait_Ack();
	
	DS1340_I2C_Send_Byte(addr);
	DS1340_I2C_Wait_Ack();
	
	DS1340_I2C_Stop();
	
	DS1340_I2C_Start();
	
	DS1340_I2C_Send_Byte(0xd1);
	DS1340_I2C_Wait_Ack();
	
	for(i=0;i<len-1;i++)
	{
		buf[i] = DS1340_I2C_Read_Byte(1);
	}
	buf[len-1] = DS1340_I2C_Read_Byte(0);
	
	DS1340_I2C_Stop();
}

void SetCalReg(unsigned char ft,unsigned char s,unsigned char cal)
{
	TIMEREG_U.bit_.ft = ft;
	TIMEREG_U.bit_.s  = s;
	TIMEREG_U.bit_.cal= cal;
	
	DS1340_WriteReg(0x07,&TIMEREG_U.buf[7],1);
}

void SetTCReg(unsigned char tcs,unsigned char ds,unsigned char rout)
{
	TIMEREG_U.bit_.tcs = tcs;
	TIMEREG_U.bit_.ds  = ds;
	TIMEREG_U.bit_.rout= rout;
	
	DS1340_WriteReg(0x08,&TIMEREG_U.buf[8],1);
}

void Set_Time(unsigned char year,unsigned char month,unsigned char date,unsigned char hours,unsigned char min,unsigned char sec,unsigned char week)
{
	TIMEREG_U.bit_.sec = sec%10;
	TIMEREG_U.bit_.tensec = sec/10;
	TIMEREG_U.bit_.eosc = 0;
	
	TIMEREG_U.bit_.min = min%10;
	TIMEREG_U.bit_.tenmin = min/10;
	
	TIMEREG_U.bit_.hours = hours%10;
	TIMEREG_U.bit_.tenhours = hours/10;
	TIMEREG_U.bit_.cb=0;
	TIMEREG_U.bit_.ceb = 0;
	
	TIMEREG_U.bit_.day = week;
	
	TIMEREG_U.bit_.date = date%10;
	TIMEREG_U.bit_.tendate = date/10;
	
	TIMEREG_U.bit_.month = month%10;
	TIMEREG_U.bit_.tenmonth = month/10;
	
	TIMEREG_U.bit_.year = year%10;
	TIMEREG_U.bit_.tenyear = year/10;
	
	DS1340_WriteReg(0x0,TIMEREG_U.buf,8);
	
}

void Read_Time(time_ *tt)
{
	DS1340_ReadReg(0x0,TIMEREG_U.buf,8);
	
	tt->year 	= TIMEREG_U.bit_.tenyear*10+TIMEREG_U.bit_.year+2000;
	tt->month = TIMEREG_U.bit_.tenmonth*10+TIMEREG_U.bit_.month;
	tt->date 	= TIMEREG_U.bit_.tendate*10+TIMEREG_U.bit_.date;
	tt->hours = TIMEREG_U.bit_.tenhours*10+TIMEREG_U.bit_.hours;
	tt->min 	= TIMEREG_U.bit_.tenmin*10+TIMEREG_U.bit_.min;
	tt->sec		= TIMEREG_U.bit_.tensec*10+TIMEREG_U.bit_.sec;
	tt->week  = TIMEREG_U.bit_.day;
}

void DS1340_Init(void)
{
	SetTCReg(0x0a,0x01,0x02);
	Read_Time(&TIME_T);
}








