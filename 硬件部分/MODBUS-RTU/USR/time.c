#include "pbdata.h"

timer_t Timer2_T;
timer_t Timer3_T;
timer_t Timer4_T;

/*RTU 的工程模板中，TIME2 用作 数据结束的检测*/
void TIME2_Init(u16 prd,u16 psc)
{
	NVIC_InitTypeDef    NVIC_InitStruct;
	TIM_TimeBaseInitTypeDef     TIM_TimeBaseInitStruct;	 	
	
	TIM_TimeBaseInitStruct.TIM_Period=prd;
	TIM_TimeBaseInitStruct.TIM_Prescaler=psc; 
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	NVIC_InitStruct.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStruct);

//	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
//	TIM_Cmd(TIM2, ENABLE);
}

void TIME3_Init(u16 prd,u16 psc)
{
	NVIC_InitTypeDef    NVIC_InitStruct;
	TIM_TimeBaseInitTypeDef     TIM_TimeBaseInitStruct;	 

	TIM_TimeBaseInitStruct.TIM_Period=prd;
	TIM_TimeBaseInitStruct.TIM_Prescaler=psc; 
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	NVIC_InitStruct.NVIC_IRQChannel=TIM3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStruct);

	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM3, ENABLE);
}

void TIME4_Init(u16 prd,u16 psc)
{
	NVIC_InitTypeDef    NVIC_InitStruct;
	TIM_TimeBaseInitTypeDef     TIM_TimeBaseInitStruct;	 

	TIM_TimeBaseInitStruct.TIM_Period=prd;
	TIM_TimeBaseInitStruct.TIM_Prescaler=psc; 
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStruct);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	NVIC_InitStruct.NVIC_IRQChannel=TIM4_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=3;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStruct);

	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM4, ENABLE);
}

void DataDeal_Process(void)
{
	if(Timer4_T.ITCounts >= 500)
	{			
		Timer4_T.ITCounts = 0;
		
		Timer4_T.onesecond++;
		USART_T.RX_RENUM=0;
				
		if(MEN_T.Now_Men == MEN_DIS)
		{
			SystemDeep();
			
			Read_Time(&TIME_T);
			DIS_Time(TIME_T);
			Update_Display(DISBUF_U);
			
			AD_INDATA_T.AD_IN_V = ReadADCAverageValue(0)*3;
			DIS_Voltage(AD_INDATA_T.AD_IN_V);
			
			TempHumiData_GetAndDeal(TIME_T.sec);
			
			TH_To_ModbusReg(usRegInputBuf,SHT75_T,Ds18_T);
			
			StoreData(TIME_T,&STOREPARAM_U,&STOREDATA_U);
			
			CheckWifiLinkStatus();
			
			DataStoreSta();
			
			Update_Display(DISBUF_U);
			
		}
	}
}


