/**
  ******************************************************************************
  * @file GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version  V3.0.0
  * @date  04/06/2009
  * @brief  Main Interrupt Service Routines.
  *         This file provides template for all exceptions handler and 
  *         peripherals interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"	 
#include "stm32f10x_exti.h"
#include "stm32f10x_rcc.h"
#include "misc.h"
#include "pbdata.h"

void NMI_Handler(void)
{
	Reset_STM();
}

void USART1_IRQHandler(void)
{
	unsigned char temp;
	
   if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
   {
			temp = USART_ReceiveData(USART1);

			USART_Rx(temp,0x55,0xaa,0xee);
		 
//		USART_SendData(USART1,USART_ReceiveData(USART1));
//		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
   }
}

void USART2_IRQHandler(void)
{
	if(ModBusUsart == USART2)
	{
		if(USART_GetITStatus(ModBusUsart,USART_IT_RXNE)!=RESET)
   {
				prvvUARTRxISR();
        USART_ClearITPendingBit(ModBusUsart,USART_IT_RXNE);			 
   }
	 
	 if(USART_GetITStatus(ModBusUsart,USART_IT_TXE) == SET)
   {
        prvvUARTTxReadyISR();
				USART_ClearITPendingBit(ModBusUsart, USART_IT_TXE);
   }
	}else
	{
		if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)
   {
		USART_ClearITPendingBit(ModBusUsart,USART_IT_RXNE);
   }
	}
	 
}

void UART4_IRQHandler(void)
{
	unsigned char temp;
	
	if(USART_GetITStatus(UART4,USART_IT_RXNE)!=RESET)
	{
		temp = USART_ReceiveData(UART4);
		
		USART_Rx(temp,0x55,0xaa,0xee);

		if(WIFI_T.RecLen < MaxRecLen)
		{
			WIFI_T.RecBuf[WIFI_T.RecLen++] = temp;
		}else
		{
			WIFI_T.RecLen = 0;
		}
	}
}

/*用于 Modbus-RTU 的时钟*/
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update)!= RESET)
	{
		prvvTIMERExpiredISR();
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);		
	}
}

void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3, TIM_IT_Update)!= RESET)
	{
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
		
	}
}

void TIM4_IRQHandler(void)                                
{
	if(TIM_GetITStatus(TIM4, TIM_IT_Update)!= RESET)
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);   

		Timer4_T.ITCounts++;		
		
		Key_T.key = key_get();	
		
		if(Key_T.key != NO_KEY)  //按下
		{
				if(Key_T.IsKeyDown == 0)  
				{
					Key_T.KeyDownCnt++;
					Key_T.KeyValue = Key_T.key;	
				}
		}else
		{                                
				if(Key_T.KeyDownCnt <= 50)
						Key_T.KeyDownCnt = 0;				
//				if(Key_T.IsKeyDown == 1)	/*程序中 按键处理不及时，标志会被清空，本程序中，SHT温湿度，延时过高，所以去掉标志清空*/
//						Key_T.IsKeyDown = 0;											
		}
		
		if(Key_T.KeyDownCnt > 50)
		{
				Key_T.IsKeyDown = 1;	
				Key_T.KeyDownCnt = 0;
		}
	} 
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval : None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
		Reset_STM();
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval : None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
		Reset_STM();
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval : None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
		Reset_STM();
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval : None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
		Reset_STM();
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval : None
  */
void SVC_Handler(void)
{
	Reset_STM();
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval : None
  */
void DebugMon_Handler(void)
{
	Reset_STM();
}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval : None
  */
void PendSV_Handler(void)
{
	Reset_STM();
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval : None
  */
void SysTick_Handler(void)
{
}


/****************************************************************************
* 名    称：void EXTI9_5_IRQHandler(void)
* 功    能：EXTI9-5中断处理程序
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/
void EXTI9_5_IRQHandler(void)
{
}

/****************************************************************************
* 名    称：void EXTI1_IRQHandler(void)
* 功    能：EXTI2中断处理程序
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/
void EXTI1_IRQHandler(void)
{
    
}

/****************************************************************************
* 名    称：void EXTI2_IRQHandler(void)
* 功    能：EXTI2中断处理程序
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/
void EXTI2_IRQHandler(void)
{
    
}

/****************************************************************************
* 名    称：void EXTI3_IRQHandler(void)
* 功    能：EXTI3中断处理程序
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/
void EXTI3_IRQHandler(void)
{
   
}
