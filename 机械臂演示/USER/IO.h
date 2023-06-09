/******************** (C) COPYRIGHT 2018 *****************************************
 * 文件名  ：led.h
 * 描述    ：led函数头文件
 * 硬件配置：      
 * 版本    ： 
 * 修改日期： 
 * 作者    ：Wu
 * 修改日志：
*********************************************************************************/
#ifndef __IO_H
#define	__IO_H

#include "stm32f10x.h"
#include "delay.h"

extern u8 led_debug_flag;

/* the macro definition to trigger the led on or off 
 * 1 - off
 - 0 - on
 */
#define LED_ON  0
#define LED_OFF 1

#define KEY0 PEin(4)   	//PE4

#define LED1(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_13);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_13)
					
#define LED_DEBUG()		led_debug_flag=~led_debug_flag;LED1(led_debug_flag)


					

void LED_Init(void);
void LED_debug(void);
void Servo_Set(u16 *data);

#endif /* __LED_H */

/******************* (C) COPYRIGHT 2018 END OF FILE *****************************/

					
					
