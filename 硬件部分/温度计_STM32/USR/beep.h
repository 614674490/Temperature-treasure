#ifndef BEEP_H
#define BEEP_H

#include "pbdata.h"

#define SpeekTime 100
#define SpeekFre  300

#define BEEP_GPIO GPIOC
#define BEEP_PORT GPIO_Pin_13

#define SET_BEEP(n)  ((n) ? (BEEP_GPIO->BSRR = BEEP_PORT):(BEEP_GPIO->BRR = BEEP_PORT))

void BEEP_GPIO_Configuration(void);
void BEEP_Speek(int time,int fre);

#endif
