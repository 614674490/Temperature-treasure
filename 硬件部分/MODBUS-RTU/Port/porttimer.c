/*
 * FreeModbus Libary: BARE Port
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id: porttimer.c,v 1.1 2006/08/22 21:35:13 wolti Exp $
 */

/* ----------------------- Platform includes --------------------------------*/
#include "pbdata.h"
#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"

/* ----------------------- static functions ---------------------------------*/


/* ----------------------- Start implementation -----------------------------*/
BOOL
xMBPortTimersInit( USHORT usTim1Timerout50us )
{
		TIME2_Init(usTim1Timerout50us,399);
		TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE);
		TIM_Cmd(TIM2, DISABLE);
    return TRUE;
}

void
vMBPortTimersEnable(  )
{
    /* Enable the timer with the timeout passed to xMBPortTimersInit( ) */
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
    TIM_SetCounter(TIM2,0x0000);
    TIM_Cmd(TIM2,ENABLE);
}

void
vMBPortTimersDisable(  )
{
    /* Disable any pending timers. */
		TIM_Cmd(TIM2, DISABLE);
    TIM_SetCounter(TIM2,0x0000); 
    TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE);
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}

/* Create an ISR which is called whenever the timer has expired. This function
 * must then call pxMBPortCBTimerExpired( ) to notify the protocol stack that
 * the timer has expired.
 */
void prvvTIMERExpiredISR( void )
{
    ( void )pxMBPortCBTimerExpired(  );
}

