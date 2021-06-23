#include "pbdata.h"

unsigned char dt[50];

STMID STMID_T;

void RCC_HSE_Configuration(void) //HSE��ΪPLLʱ�ӣ�PLL��ΪSYSCLK 
{ 
   RCC_DeInit(); /*������RCC�Ĵ�������Ϊȱʡֵ */ 
   RCC_HSEConfig(RCC_HSE_ON); 	 /*�����ⲿ���پ���HSE�� HSE�����(ON)*/ 

   if(RCC_WaitForHSEStartUp() == SUCCESS) {  /*�ȴ�HSE����,  SUCCESS��HSE�����ȶ��Ҿ���*/  

   RCC_HCLKConfig(RCC_SYSCLK_Div1);/*����AHBʱ��(HCLK)RCC_SYSCLK_Div1����AHBʱ�� = ϵͳʱ*/  
   RCC_PCLK2Config(RCC_HCLK_Div1); /*���ø���AHBʱ��(PCLK2)RCC_HCLK_Div1����APB2ʱ�� = HCLK*/     
   RCC_PCLK1Config(RCC_HCLK_Div2); /*���õ���AHBʱ��(PCLK1)RCC_HCLK_Div2����APB1ʱ�� = HCLK / 2*/      

   RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);/*����PLLʱ��Դ����Ƶϵ��*/    
   RCC_PLLCmd(ENABLE); 	 /*ʹ��PLL */ 
   while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) ; /*���ָ����RCC��־λ(PLL׼���ñ�־)�������*/ 
    
   RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);  /*����ϵͳʱ�ӣ�SYSCLK�� */  
   while(RCC_GetSYSCLKSource() != 0x08);     /*0x08��PLL��Ϊϵͳʱ�� */	    
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
 //��ȡCPUΨһID
	unsigned i;
	//static u32 Lock_Code;
	for(i=0;i<12;i++)
	{
		CpuID[i]=*(vu32*)(0x1ffff7e8+i);
	}

}
/*��ȡ��Ƭ��ΨһID,�����ID�ṹ���У��������*/
void Get_SerialNum(void)
{
	Get_Cpu_Id(STMID_T.CpuID); 
	STMID_T.crc= mycrc(STMID_T.CpuID,12);
	STMID_T.myid[0]=STMID_T.crc>>8;
	STMID_T.myid[1]=STMID_T.crc;
	STMID_T.myid[2]=STMID_T.CpuID[0];
}

/****************************************************************************
* ��    �ƣ�STM_FLASH_Init(uint32_t StartAddress)
* ��    �ܣ�STM32�ڲ�FLASH ��ҳ����
* ��ڲ�������ַ  
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/ 
void STM_FLASH_Init(uint32_t StartAddress)
{
	//����
	FLASH_Unlock();
	//�����־λ
	FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|
									FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);	
	//Ҫ����ҳ����ʼ��ַ
	FLASH_ErasePage(StartAddress);
	//����
	FLASH_Lock();
}

/****************************************************************************
* ��    �ƣ�STM_FLASH_Write(uint32_t StartAddress,unsigned char* Data,u16 len)
* ��    �ܣ�STM32�ڲ�FLASH д����
* ��ڲ�������ַ  ��������ʵ��ַ  ����
* ���ڲ�������
* ˵    �����ر�ע��洢��ʱ��Ҫ 4K����
* ���÷������� 
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
	n=n/4;//������дflash          
		
	FLASH_Unlock();//FLASH����
	FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);//���־λ
	FLASH_ErasePage(addr);                 /*д�����ݣ�������ҳ*/
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
* ��    �ƣ�STM_FLASH_Read(uint32_t StartAddress,unsigned char* Data,u16 len)
* ��    �ܣ�STM32�ڲ�FLASH ������
* ��ڲ�������ַ  ��������ʵ��ַ  ����
* ���ڲ�������
* ˵    ����
* ���÷������� 
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
* ��    �ƣ�delay_us(u32 nus)
* ��    �ܣ�΢����ʱ����
* ��ڲ�����u32  nus
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/ 
void delay_us(u32 nus)
{
	 u32 temp;
	
	 SysTick->LOAD = nus;
	 SysTick->VAL=0X00;//��ռ�����
	 SysTick->CTRL=0X01;//ʹ�ܣ����������޶����������ⲿʱ��Դ
	 do
	 {
	  temp=SysTick->CTRL;//��ȡ��ǰ������ֵ
	 }while((temp&0x01)&&(!(temp&(1<<16))));//�ȴ�ʱ�䵽��
	 
	 SysTick->CTRL=0x00; //�رռ�����
	 SysTick->VAL =0X00; //��ռ�����
}

/****************************************************************************
* ��    �ƣ�delay_ms(u16 nms)
* ��    �ܣ�������ʱ����
* ��ڲ�����u16 nms
* ���ڲ�������
* ˵    ����
* ���÷������� 
****************************************************************************/ 
void delay_ms(u16 nms)
{
	 u32 temp;
	 SysTick->LOAD = 1000*nms;
	 SysTick->VAL=0X00;//��ռ�����
	 SysTick->CTRL=0X01;//ʹ�ܣ����������޶����������ⲿʱ��Դ
	 do
	 {
	  temp=SysTick->CTRL;//��ȡ��ǰ������ֵ
	 }while((temp&0x01)&&(!(temp&(1<<16))));//�ȴ�ʱ�䵽��
	 SysTick->CTRL=0x00; //�رռ�����
	 SysTick->VAL =0X00; //��ռ�����
}

void Sys_Standby(void)
{
	//ѡ�����ģʽ
	NVIC_SystemLPConfig(NVIC_LP_SLEEPDEEP,ENABLE);
	//ʹ��PWR����ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
	//ʹ�ܻ��ѹܽ�
	PWR_WakeUpPinCmd(ENABLE);
	//�������ģʽ
	PWR_EnterSTANDBYMode();
}





