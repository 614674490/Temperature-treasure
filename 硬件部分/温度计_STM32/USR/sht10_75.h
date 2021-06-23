#ifndef SHT10_75_H
#define SHT10_75_H

#include "pbdata.h"

extern uint16_t SHT75_SCK;
extern uint16_t SHT75_SDA;
extern GPIO_TypeDef* SHT75_PORT;

#define NOP()   __asm__ __volatile__ ("nop" ::);


#define SHT75_SCK_H		GPIO_SetBits(SHT75_PORT,SHT75_SCK)
#define SHT75_SCK_L		GPIO_ResetBits(SHT75_PORT,SHT75_SCK);
#define SHT75_SDA_H		GPIO_SetBits(SHT75_PORT,SHT75_SDA)
#define SHT75_SDA_L		GPIO_ResetBits(SHT75_PORT,SHT75_SDA);

#define SHT75_SDA_IN	GPIO_ReadInputDataBit(SHT75_PORT,SHT75_SDA)

#define SHT75_CMD_TE	0x03	//ÎÂ¶È²âÁ¿ÃüÁî
#define SHT75_CMD_RH	0x05	//Êª¶È²âÁ¿ÃüÁî
#define SHT75_CMD_RD	0x07	//¶Á×´Ì¬¼Ä´æÆ÷
#define SHT75_CMD_WR	0x06	//Ð´×´Ì¬¼Ä´æÆ÷
#define SHT75_CMD_RST	0x1E	//¸´Î»

#define noACK 0 //¡°ÎÞÓ¦´ð¡±ÐÅºÅ
#define ACK   1 //¡°ÓÐÓ¦´ð¡±ÐÅºÅ
#define TEMP	0
#define HUMI	1

typedef struct SHT75
{
	float humi_1;
	float humi_2;
	float temp_1;
	float temp_2;
	
	unsigned char humi_1_buf[2];
	unsigned char temp_1_buf[2];
	unsigned char humi_2_buf[2];
	unsigned char temp_2_buf[2];
	unsigned char check[2];
	
}SHT75;

extern SHT75 SHT75_T;

void SHT75_GetData(unsigned char id);

#endif
