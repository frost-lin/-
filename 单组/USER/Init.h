#ifndef __INIT_H
#define	__INIT_H


#include "stm32f10x.h"
#include "led.h"
#include "TIMER.h"
#include "usart.h"
#include "debug.h"


void Init(void);
void GPIO_Init_SWJ_Disable(void);

#endif /* __INIT_H */

