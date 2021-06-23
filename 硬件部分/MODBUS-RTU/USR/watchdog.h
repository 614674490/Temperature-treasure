#ifndef WATCHDOG_H
#define WATCHDOG_H

#include "pbdata.h"

void IWDG_Init(int prer,int rlr);
void IWDG_Feed(void);

#endif
