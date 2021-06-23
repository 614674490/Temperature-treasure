#ifndef USART_H
#define USART_H
#include "pbdata.h"


#define ModBusUsart USART2

#define MAX485_TR_GPIO GPIOA
#define MAX485_TR_PORT GPIO_Pin_6

#define MAX485_RX_MODE GPIO_ResetBits(MAX485_TR_GPIO,MAX485_TR_PORT)
#define MAX485_TX_MODE GPIO_SetBits(MAX485_TR_GPIO,MAX485_TR_PORT)

void AllUSART_Init(uint32_t rate1,uint32_t rate2,uint32_t rate3,uint16_t parity1,uint16_t parity2,uint16_t parity3);

void USART_PutChar(USART_TypeDef* USARTx , uint8_t Data);
void USART_PutStr(USART_TypeDef* USARTx , char *str);
void UARTX_Sendbytes(USART_TypeDef* USARTx ,unsigned char* s,u16 n);
void USARTX_485Sendbytes(USART_TypeDef* USARTx ,unsigned char* s,u16 n);

void USART_Rx(unsigned char Data,unsigned char HEAD,unsigned char START,unsigned char END);
unsigned char USART_Tx(USART_TypeDef* USARTx ,unsigned char BUF[],int LENTH,unsigned char HEAD,unsigned char START,unsigned char END);

unsigned char SumCheck(unsigned char *c,unsigned char n);

void USART_Recieve_Process(void);

#define USART_BUF_LENTH 128
typedef struct USART
{
	unsigned char RX_LENTH;
	unsigned int 	RX_RENUM;
	unsigned char RX_BUF[USART_BUF_LENTH];
	unsigned char RX_OK;
}USART;
extern USART USART_T;




#endif
