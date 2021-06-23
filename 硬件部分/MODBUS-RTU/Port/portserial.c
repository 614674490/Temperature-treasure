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
 * File: $Id: portserial.c,v 1.1 2006/08/22 21:35:13 wolti Exp $
 */

#include "pbdata.h"
#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"

/* ----------------------- static functions ---------------------------------*/


/* ----------------------- Start implementation -----------------------------*/
void
vMBPortSerialEnable( BOOL xRxEnable, BOOL xTxEnable )
{
    /* If xRXEnable enable serial receive interrupts. If xTxENable enable
     * transmitter empty interrupts.
     */
	ENTER_CRITICAL_SECTION();//关中断
	if(TRUE==xRxEnable)
	{
				MAX485_RX_MODE;			/*开启接收模式，485专用的*/
        USART_ITConfig(ModBusUsart,USART_IT_RXNE, ENABLE);
  }else
	{
        USART_ITConfig(ModBusUsart,USART_IT_RXNE, DISABLE); 
  }

  if(TRUE==xTxEnable)
  {
				MAX485_TX_MODE;			/*开启发送模式，485专用的*/
        USART_ITConfig(ModBusUsart,USART_IT_TXE, ENABLE);
  }else
	{
       USART_ITConfig(ModBusUsart,USART_IT_TXE, DISABLE);
  }
	EXIT_CRITICAL_SECTION();
}

BOOL
xMBPortSerialInit( UCHAR ucPORT, ULONG ulBaudRate, UCHAR ucDataBits, eMBParity eParity )
{
	uint16_t my_parity_set;
	
	switch(eParity)
	{
		case MB_PAR_NONE:
			my_parity_set = USART_Parity_No;
			break;
		case MB_PAR_ODD:
			my_parity_set = USART_Parity_Odd;
			break;
		case MB_PAR_EVEN:
			my_parity_set = USART_Parity_Even;
			break;
		default:
			my_parity_set = USART_Parity_No;
			break;
	}
		AllUSART_Init(9600,ulBaudRate,115200,0,my_parity_set,0);		/*三个波特率，三个奇偶校验*/
    return TRUE;
}

BOOL
xMBPortSerialPutByte( CHAR ucByte )
{
    /* Put a byte in the UARTs transmit buffer. This function is called
     * by the protocol stack if pxMBFrameCBTransmitterEmpty( ) has been
     * called. */
	USART_SendData(ModBusUsart,ucByte);
	while(USART_GetFlagStatus(ModBusUsart,USART_FLAG_TC)==RESET){};    /*此处必须 查询 USART_FLAG_TC 位，等待缓冲区数据发送完，否则 最后一位发送不出去*/

  return TRUE;
}

BOOL
xMBPortSerialGetByte( CHAR * pucByte )
{
    /* Return the byte in the UARTs receive buffer. This function is called
     * by the protocol stack after pxMBFrameCBByteReceived( ) has been called.
     */
		*pucByte = USART_ReceiveData(ModBusUsart);
    return TRUE;
}

/* Create an interrupt handler for the transmit buffer empty interrupt
 * (or an equivalent) for your target processor. This function should then
 * call pxMBFrameCBTransmitterEmpty( ) which tells the protocol stack that
 * a new character can be sent. The protocol stack will then call 
 * xMBPortSerialPutByte( ) to send the character.
 */
void prvvUARTTxReadyISR(void)
{
    pxMBFrameCBTransmitterEmpty();
}

/* Create an interrupt handler for the receive interrupt for your target
 * processor. This function should then call pxMBFrameCBByteReceived( ). The
 * protocol stack will then call xMBPortSerialGetByte( ) to retrieve the
 * character.
 */
void prvvUARTRxISR(void)
{
    pxMBFrameCBByteReceived();
}
