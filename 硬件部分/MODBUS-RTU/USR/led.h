#ifndef LED_H
#define LED_H

#include "pbdata.h"

#define LED_GPIO GPIOC
#define LED1_PORT GPIO_Pin_1
#define LED2_PORT GPIO_Pin_2

#define SET_LED1(n)  ((n) ? (LED_GPIO->BSRR = LED1_PORT):(LED_GPIO->BRR = LED1_PORT))
#define SET_LED2(n)  ((n) ? (LED_GPIO->BSRR = LED2_PORT):(LED_GPIO->BRR = LED2_PORT))

void LED_GPIO_Configuration(void);

#endif
