#ifndef MENU_H
#define MENU_H

#include "pbdata.h"

#define MEN_DIS  0
#define MEN_SET  1

#define MEN_ID	 2
#define MEN_BAUD 3
#define MEN_PARY 4
#define MEN_BACKLIGHT  5
#define MEN_MESSGEMODE 6
#define MEN_SLEEPTIME	 7
#define MEN_SHT1MODE	 8
#define MEN_SHT2MODE   9
#define MEN_18B20MODE  10
#define MEN_WARNING		 11
#define MEN_CAL				 12
#define MEN_TIME			 13

typedef struct
{
	unsigned char Now_Men;
	unsigned char MenSetNum;
}men_;
extern men_ MEN_T;

void MEN_KEY(unsigned char keyval);

void KEY_MEN_DIS(unsigned char keyval);
void KEY_MEN_SET(unsigned char keyval);

#endif
