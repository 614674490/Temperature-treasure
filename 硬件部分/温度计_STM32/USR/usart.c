#include "pbdata.h"

USART USART_T;

void USART_GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;	
	
	//usart1 
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;//TX
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//RX
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;//T/R0
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
		
	//usart2 
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2;//TX
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_3;//RX
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	//usart3 :MAX3485-ESA
		
	GPIO_InitStructure.GPIO_Pin=MAX485_TR_PORT;//T/R0
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(MAX485_TR_GPIO,&GPIO_InitStructure);
	
	MAX485_RX_MODE;                         //初始化485接收
	
	//usart4
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//TX
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOC,&GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;//RX
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
}

//usart priority
void USART_NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure; 

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 
	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
//	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 
	
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
}

//usart1 set
//后面三个参数为 校验方式，Modbus rtu 中  数据为8位，停止位1位，可以改变的只有 波特率和校验方式
// 0-无校验
// 1-奇校验
// 2-偶校验
void USART_Configuration(uint32_t rate1,uint32_t rate2,uint32_t rate3,uint16_t parity1,uint16_t parity2,uint16_t parity3)
{
  USART_InitTypeDef  USART_InitStructure;
	
	USART_InitStructure.USART_BaudRate=rate1;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_Parity=parity1;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;

	//usart1 init
	USART_Init(USART1,&USART_InitStructure);
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART1,ENABLE);
	USART_ClearFlag(USART1,USART_FLAG_TC);
	
	
	USART_InitStructure.USART_BaudRate=rate2;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_Parity=parity2;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	//usart2 init
	USART_Init(USART2,&USART_InitStructure);
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART2,ENABLE);
	USART_ClearFlag(USART2,USART_FLAG_TC);
 
 
	USART_InitStructure.USART_BaudRate=rate3;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_Parity=parity3;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	//usart4 init
	USART_Init(UART4,&USART_InitStructure);
	USART_ITConfig(UART4,USART_IT_RXNE,ENABLE);
	USART_Cmd(UART4,ENABLE);
	USART_ClearFlag(UART4,USART_FLAG_TC);
}

void AllUSART_Init(uint32_t rate1,uint32_t rate2,uint32_t rate3,uint16_t parity1,uint16_t parity2,uint16_t parity3)
{
	USART_GPIO_Configuration();
	USART_Configuration(rate1,rate2,rate3,parity1,parity2,parity3);
	USART_NVIC_Configuration();
}


/*usartx send char*/
void USART_PutChar(USART_TypeDef* USARTx , uint8_t Data)
{
	USART_SendData(USARTx,Data);
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TC) == RESET);
}

/*usartx send string*/
void USART_PutStr(USART_TypeDef* USARTx , char *str)
{
	while(*str != NULL)
	{
		USART_PutChar(USARTx,*str);
		str++;
	}
}

/*sum check*/
unsigned char SumCheck(unsigned char *c,unsigned char n)
{
	unsigned char    sub_c=c[0];
	unsigned char    i;

	for(i=1;i<n;i++)
	{
		sub_c+=c[i];
	}
	return (sub_c);
}

/*recieve usart data*/
void USART_Rx(unsigned char Data,unsigned char HEAD,unsigned char START,unsigned char END)
{
	unsigned char h,t;
	if (USART_T.RX_RENUM<USART_BUF_LENTH)
	{
		h=USART_T.RX_RENUM;
		t=Data;
		USART_T.RX_BUF[h]=t;
		USART_T.RX_RENUM=h+1;

		t=0;

		if ((h==0)&&(USART_T.RX_BUF[0]!=HEAD)) t=1;
		if ((h==1)&&(USART_T.RX_BUF[1]!=START)) t=1;
		if (t==1) 
		{
			USART_T.RX_RENUM=0;				
		}
		
		if((h > 2)&&(USART_T.RX_RENUM>=USART_T.RX_BUF[2])&&(USART_T.RX_BUF[h-1]==END))
		{
				USART_T.RX_RENUM=0;
				USART_T.RX_OK=1;
//			if(SumCheck(USART_T.RX_BUF,USART_T.RX_BUF[2]-1) == USART_T.RX_BUF[h])
//			{
//				USART_T.RX_RENUM=0;
//				USART_T.RX_OK=1;
//			}

		}
		
	}
	else
	{
			USART_T.RX_RENUM=0;			
	}
}

/*send buf*/
unsigned char USART_Tx(USART_TypeDef* USARTx ,unsigned char BUF[],int LENTH,unsigned char HEAD,unsigned char START,unsigned char END)
{
	unsigned int i;
	unsigned char Check=0;
	
	USART_PutChar(USARTx,HEAD);
	Check+=HEAD;
	USART_PutChar(USARTx,START);
	Check+=START;
	USART_PutChar(USARTx,LENTH+5);
	Check+=(LENTH+5);
	
	for(i=0;i<LENTH;i++)
	{
		USART_PutChar(USARTx,BUF[i]);
		Check+=BUF[i];
	}
	
	USART_PutChar(USARTx,END);
	Check+=END;
	
	USART_PutChar(USARTx,Check);
	
	return 1;
}

void UARTX_Sendbytes(USART_TypeDef* USARTx ,unsigned char* s,u16 n)
{
	while(n--)//检测字符串结束符
	{
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC)==RESET); 
		USART_SendData(USARTx ,*s++);//发送当前字符
	}
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TC)==RESET); 
}

void USARTX_485Sendbytes(USART_TypeDef* USARTx ,unsigned char* s,u16 n)
{
	MAX485_TX_MODE;
	delay_us(500);
	UARTX_Sendbytes(USARTx ,s,n);
	delay_us(500);
	MAX485_RX_MODE;
}

/*只用在上传数据时*/
void USART_TX_FLASHDATA(USART_TypeDef* USARTx ,unsigned char BUF[],int LENTH,unsigned char HEAD,unsigned char START,unsigned char END,unsigned char CMD)
{
	unsigned int i;
	unsigned char Check=0;
	
	USART_PutChar(USARTx,HEAD);
	Check+=HEAD;
	USART_PutChar(USARTx,START);
	Check+=START;
	USART_PutChar(USARTx,LENTH+10);
	Check+=(LENTH+10);
	USART_PutChar(USARTx,(LENTH+10)>>8);
	Check+= ((LENTH+10)>>8);
	USART_PutChar(USARTx,CMD);
	Check+=CMD;
	
	for(i=0;i<3;i++)
	{
		USART_PutChar(USARTx,STMID_T.myid[i]);
		Check+=STMID_T.myid[i];
	}
	
	for(i=0;i<LENTH;i++)
	{
		USART_PutChar(USARTx,BUF[i]);
		Check+=BUF[i];
	}
	
	USART_PutChar(USARTx,END);
	Check+=END;
	
	USART_PutChar(USARTx,Check);
	
}

void USART_Recieve_Process(void)
{
	unsigned char buf[20];
	unsigned short SendLen=0;
	unsigned int readStartAddr=0,readDataNum=0;
		
	if(USART_T.RX_OK==1)                                               					/*串口2收到数据,115200*/
	{		
		USART_T.RX_OK=0;
		switch(USART_T.RX_BUF[3])
		{
			case 0x11:                                                    				 /*读取设备ID*/
					buf[0] = 0x11;
					buf[1] = STMID_T.myid[0];
					buf[2] = STMID_T.myid[1];
					buf[3] = STMID_T.myid[2];
			
					USART_Tx(USART1,buf,4,0x55,0xaa,0xee);           									 /*发送本机ID*/
					break;
			case 0x33:                                                   					 /*读取本地数据*/
					if((USART_T.RX_BUF[4]==STMID_T.myid[0])&&(USART_T.RX_BUF[5]==STMID_T.myid[1])&(USART_T.RX_BUF[6]==STMID_T.myid[2]))
					{
						if( (DataPackageNum - STOREPARAM_U.usr_.datanum) < 2 )		/*数据已存满，不可继续存储*/
						{
							
						}else
						{
							STOREDATA_U.usr_.isServer = 1;
							SPI_Flash_Write(STOREDATA_U.buf,STOREPARAM_U.usr_.lastaddr,sizeof(STOREDATA_U.buf));
						}
					}
					break;
			case 0x31:   					/*对时*/
					if((USART_T.RX_BUF[4]==STMID_T.myid[0])&&(USART_T.RX_BUF[5]==STMID_T.myid[1])&(USART_T.RX_BUF[6]==STMID_T.myid[2]))
					{
						/*设置              年                月              日                 时                   分               秒*/
						Set_Time( (USART_T.RX_BUF[7]<<8|USART_T.RX_BUF[8])-2000 ,USART_T.RX_BUF[9],USART_T.RX_BUF[10],USART_T.RX_BUF[11],USART_T.RX_BUF[12],USART_T.RX_BUF[13],7);
						Read_Time(&TIME_T);                                             /*获取当前时间并存放到时间结构体中*/
					}
					break;
			case 0x71:                                                  /*初始化存储器*/
						if((USART_T.RX_BUF[4]==STMID_T.myid[0])&&(USART_T.RX_BUF[5]==STMID_T.myid[1])&(USART_T.RX_BUF[6]==STMID_T.myid[2]))
						{
							InitStore(&STOREPARAM_U);
							
							buf[0] = 0x71;                                        /*回复上位机设置成功消息*/
							buf[1] = STMID_T.myid[0];
							buf[2] = STMID_T.myid[1];
							buf[3] = STMID_T.myid[2];
							USART_Tx(USART1,buf,4,0x55,0xaa,0xee);
						}
						break;
			 case 0x12:						/*获取数据总条数*/
					 if((USART_T.RX_BUF[4]==STMID_T.myid[0])&&(USART_T.RX_BUF[5]==STMID_T.myid[1])&(USART_T.RX_BUF[6]==STMID_T.myid[2]))
						{
							buf[0] = 0x12;
							buf[1] = STMID_T.myid[0];
							buf[2] = STMID_T.myid[1];
							buf[3] = STMID_T.myid[2];
							buf[4] = STOREPARAM_U.usr_.datanum>>24;
							buf[5] = STOREPARAM_U.usr_.datanum>>16;
							buf[6] = STOREPARAM_U.usr_.datanum>>8;
							buf[7] = STOREPARAM_U.usr_.datanum>>0;
				
							USART_Tx(USART1,buf,8,0x55,0xaa,0xee);                                        /*获取当前时间并存放到时间结构体中*/
						}
						         									
						break;
			 case 0x13:						/*获取指定区间的数据*/
						if((USART_T.RX_BUF[4]==STMID_T.myid[0])&&(USART_T.RX_BUF[5]==STMID_T.myid[1])&(USART_T.RX_BUF[6]==STMID_T.myid[2]))
						{
							readStartAddr = USART_T.RX_BUF[7]<<24 | USART_T.RX_BUF[8]<<16 | USART_T.RX_BUF[9]<<8 | USART_T.RX_BUF[10];   
							readDataNum   = USART_T.RX_BUF[11]<<24 | USART_T.RX_BUF[12]<<16 | USART_T.RX_BUF[13]<<8 | USART_T.RX_BUF[14];
				 
							SendLen = GetData(&STOREPARAM_U,SendDataBuf,readStartAddr,readDataNum);
							if( SendLen != 0)
							{
								USART_TX_FLASHDATA(USART1,SendDataBuf,SendLen,0x55,0xbb,0xee,0x13);
							}
						}
						break;
		}
	}
}





