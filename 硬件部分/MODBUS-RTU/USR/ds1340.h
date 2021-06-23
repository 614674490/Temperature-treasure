#ifndef DS1340_H
#define DS1340_H

#include "pbdata.h"

typedef struct
{
	int year;
	unsigned char month;
	unsigned char date;
	unsigned char hours;
	unsigned char min;
	unsigned char sec;
	unsigned char week;
}time_;
extern time_ TIME_T;
extern time_ TIMESET_T;

typedef union
{
	unsigned char buf[10];
	struct
	{
		unsigned char sec:4;
		unsigned char tensec:3;
		unsigned char eosc:1;
		
		unsigned char min:4;
		unsigned char tenmin:3;
		unsigned char x01h:1;
		
		unsigned char hours:4;
		unsigned char tenhours:2;
		unsigned char cb:1;
		unsigned char ceb:1;
		
		unsigned char day:3;
		unsigned char x03h:5;
		
		unsigned char date:4;
		unsigned char tendate:2;
		unsigned char x04h:2;
		
		unsigned char month:4;
		unsigned char tenmonth:1;
		unsigned char x05h:3;
		
		unsigned char year:4;
		unsigned char tenyear:4;
		
		unsigned char cal:5;
		unsigned char s:1;
		unsigned char ft:1;
		unsigned char out:1;
		
		unsigned char rout:2;
		unsigned char ds:2;
		unsigned char tcs:4;
		
		unsigned char x09h:7;
		unsigned char osf:1;
	}bit_;
	
}ds1340TimeReg_;

extern ds1340TimeReg_ TIMEREG_U;

void Set_Time(unsigned char year,unsigned char month,unsigned char date,unsigned char hours,unsigned char min,unsigned char sec,unsigned char week);
void Read_Time(time_ *tt);
void DS1340_Init(void);
void SetTCReg(unsigned char tcs,unsigned char ds,unsigned char rout);
#endif
