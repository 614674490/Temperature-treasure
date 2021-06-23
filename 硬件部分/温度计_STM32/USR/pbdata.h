#ifndef _pbdata_H
#define _pbdata_H

#include "stm32f10x.h"
#include "misc.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_flash.h"
#include "stm32f10x_iwdg.h"
#include "stm32f10x_pwr.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"

#include "usart.h"
#include "time.h"
#include "mb.h"
#include "mbport.h"
#include "mbutils.h"
#include "myrtu.h"
#include "sht10_75.h"
#include "ds18b20.h"
#include "dealdata.h"
#include "watchdog.h"
#include "beep.h"
#include "lcd.h"
#include "lcdiic.h"
#include "ds1340iic.h"
#include "ds1340.h"
#include "disdata.h"
#include "led.h"
#include "ad.h"
#include "key.h"
#include "tp4054.h"
#include "menu.h"
#include "ioinput.h"
#include "wifi.h"
#include "storedata.h"
#include "spi.h"
#include "w25q64.h"


//定义变量

extern unsigned char dt[50];

#define Para_ADDR 0X08010000 

/*单片机唯一ID*/
typedef struct STMID
{
	unsigned char CpuID[12];
	unsigned char myid[3];
	u16 crc;
}STMID;
extern STMID STMID_T;

//定义函数

void RCC_HSE_Configuration(void);
void Reset_STM(void);
void delay(u32 nCount);
void delay_us(u32 nus);
void delay_ms(u16 nms);
u16 mycrc(unsigned char *ptr,int len);
void Get_SerialNum(void);
void STM_FLASH_Write(uint32_t addr,unsigned char* p,u16 n);
void STM_FLASH_Read(uint32_t addr,unsigned char* p,u16 n);
void Sys_Standby(void);

#endif
