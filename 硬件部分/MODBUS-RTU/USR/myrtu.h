#ifndef MYRTU_H
#define MYRTU_H

#include "pbdata.h"

#define REG_INPUT_START 	0002
#define REG_INPUT_NREGS 	5			 /*八个模拟量输入*/
#define REG_HOLDING_START 0002
#define REG_HOLDING_NREGS 132		 /*132个配置寄存器*/
#define REG_COILS_START   0002
#define REG_COILS_SIZE    8      /*八个数字量输入输出*/
#define REG_DISC_START    0002
#define REG_DISC_SIZE     8			 /*八个数字量输入*/


/* ----------------------- Static variables ---------------------------------*/
extern USHORT   usRegInputStart;
extern USHORT   usRegInputBuf[REG_INPUT_NREGS];
extern USHORT   usRegHoldingStart;
extern USHORT   usRegHoldingBuf[REG_HOLDING_NREGS];
extern UCHAR 		ucRegCoilsBuf[REG_COILS_SIZE / 8];
extern UCHAR 		ucRegDiscBuf[REG_DISC_SIZE / 8];

eMBErrorCode eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs );
eMBErrorCode eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode );
eMBErrorCode eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils, eMBRegisterMode eMode );
eMBErrorCode eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete );

#endif
