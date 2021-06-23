#include "pbdata.h"

unsigned char dt[50];

STMID STMID_T;

void RCC_HSE_Configuration(void) //HSE作为PLL时钟，PLL作为SYSCLK 
{ 
   RCC_DeInit(); /*将外设RCC寄存器重设为缺省值 */ 
   RCC_HSEConfig(RCC_HSE_ON); 	 /*设置外部高速晶振（HSE） HSE晶振打开(ON)*/ 

   if(RCC_WaitForHSEStartUp() == SUCCESS) {  /*等待HSE起振,  SUCCESS：HSE晶振稳定且就绪*/  

   RCC_HCLKConfig(RCC_SYSCLK_Div1);/*设置AHB时钟(HCLK)RCC_SYSCLK_Div1——AHB时钟 = 系统时*/  
   RCC_PCLK2Config(RCC_HCLK_Div1); /*设置高速AHB时钟(PCLK2)RCC_HCLK_Div1——APB2时钟 = HCLK*/     
   RCC_PCLK1Config(RCC_HCLK_Div2); /*设置低速AHB时钟(PCLK1)RCC_HCLK_Div2——APB1时钟 = HCLK / 2*/      

   RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);/*设置PLL时钟源及倍频系数*/    
   RCC_PLLCmd(ENABLE); 	 /*使能PLL */ 
   while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) ; /*检查指定的RCC标志位(PLL准备好标志)设置与否*/ 
    
   RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);  /*设置系统时钟（SYSCLK） */  
   while(RCC_GetSYSCLKSource() != 0x08);     /*0x08：PLL作为系统时钟 */	    
 } 
} 

void Reset_STM(void)
{
	__set_FAULTMASK(1); 
	NVIC_SystemReset();
}

u16 mycrc(unsigned char *ptr,int len)
{
		unsigned char i; 
		unsigned short crc = 0xFFFF;     
	  if(len==0) 
		{
			len = 1;
    } 
		while(len--)
		{
			crc ^= *ptr;		
			for(i=0; i<8; i++)
			{ 
				if(crc&1)
				{ 
					crc >>= 1;
					crc ^= 0xA001;
				}
				else
				{
					crc >>= 1;
				}
			}
		  ptr++;
   } 
	 return(crc);  
}

void Get_Cpu_Id(unsigned char *CpuID)
{
 //获取CPU唯一ID
	unsigned i;
	//static u32 Lock_Code;
	for(i=0;i<12;i++)
	{
		CpuID[i]=*(vu32*)(0x1ffff7e8+i);
	}

}
/*获取单片机唯一ID,并存放ID结构体中，方便调用*/
void Get_SerialNum(void)
{
	Get_Cpu_Id(STMID_T.CpuID); 
	STMID_T.crc= mycrc(STMID_T.CpuID,12);
	STMID_T.myid[0]=STMID_T.crc>>8;
	STMID_T.myid[1]=STMID_T.crc;
	STMID_T.myid[2]=STMID_T.CpuID[0];
}

/****************************************************************************
* 名    称：STM_FLASH_Init(uint32_t StartAddress)
* 功    能：STM32内部FLASH 整页擦除
* 入口参数：地址  
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/ 
void STM_FLASH_Init(uint32_t StartAddress)
{
	//解锁
	FLASH_Unlock();
	//清除标志位
	FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|
									FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);	
	//要擦出页的起始地址
	FLASH_ErasePage(StartAddress);
	//锁定
	FLASH_Lock();
}

/****************************************************************************
* 名    称：STM_FLASH_Write(uint32_t StartAddress,unsigned char* Data,u16 len)
* 功    能：STM32内部FLASH 写数据
* 入口参数：地址  缓冲区其实地址  长度
* 出口参数：无
* 说    明：特别注意存储的时候要 4K对齐
* 调用方法：无 
****************************************************************************/ 
void STM_FLASH_Write(uint32_t addr,unsigned char* p,u16 n)
{
	u32 r1;

	u8 remainder=0;
	
	remainder = n%4;
	switch(remainder)
	{
		case 0:
			break;
		case 1:
			n+=3;
			break;
		case 2:
			n+=2;
			break;
		case 3:
			n+=1;
			break;
	}
	n=n/4;//擦除并写flash          
		
	FLASH_Unlock();//FLASH解锁
	FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);//清标志位
	FLASH_ErasePage(addr);                 /*写入数据，擦出整页*/
	while(n--)
	{
		r1=*(p++);
		r1|=*(p++)<<8;
		r1|=*(p++)<<16;
		r1|=*(p++)<<24;
		FLASH_ProgramWord(addr, r1);
		addr+=4;
	}
}

/****************************************************************************
* 名    称：STM_FLASH_Read(uint32_t StartAddress,unsigned char* Data,u16 len)
* 功    能：STM32内部FLASH 读数据
* 入口参数：地址  缓冲区其实地址  长度
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/ 
void STM_FLASH_Read(uint32_t addr,unsigned char* p,u16 n)
{	
	while(n--)
	{
		*(p++)=*((u8*)addr++);
	}
}

void delay(u32 nCount)
{
	for(;nCount!=0;nCount--);
}

/****************************************************************************
* 名    称：delay_us(u32 nus)
* 功    能：微秒延时函数
* 入口参数：u32  nus
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/ 
void delay_us(u32 nus)
{
	 u32 temp;
	
	 SysTick->LOAD = nus;
	 SysTick->VAL=0X00;//清空计数器
	 SysTick->CTRL=0X01;//使能，减到零是无动作，采用外部时钟源
	 do
	 {
	  temp=SysTick->CTRL;//读取当前倒计数值
	 }while((temp&0x01)&&(!(temp&(1<<16))));//等待时间到达
	 
	 SysTick->CTRL=0x00; //关闭计数器
	 SysTick->VAL =0X00; //清空计数器
}

/****************************************************************************
* 名    称：delay_ms(u16 nms)
* 功    能：毫秒延时函数
* 入口参数：u16 nms
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/ 
void delay_ms(u16 nms)
{
	 u32 temp;
	 SysTick->LOAD = 1000*nms;
	 SysTick->VAL=0X00;//清空计数器
	 SysTick->CTRL=0X01;//使能，减到零是无动作，采用外部时钟源
	 do
	 {
	  temp=SysTick->CTRL;//读取当前倒计数值
	 }while((temp&0x01)&&(!(temp&(1<<16))));//等待时间到达
	 SysTick->CTRL=0x00; //关闭计数器
	 SysTick->VAL =0X00; //清空计数器
}

void Sys_Standby(void)
{
	//选择待机模式
	NVIC_SystemLPConfig(NVIC_LP_SLEEPDEEP,ENABLE);
	//使能PWR外设时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
	//使能唤醒管脚
	PWR_WakeUpPinCmd(ENABLE);
	//进入待机模式
	PWR_EnterSTANDBYMode();
}





