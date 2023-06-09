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
					GPIO_SetBits(GPIOB,GPIO_Pin_12);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_12)
					
#define LED_DEBUG()		led_debug_flag=~led_debug_flag;LED1(led_debug_flag)

#define sel0 PAout(8)
#define sel1 PAout(9)					
#define sel2 PAout(10)	
#define sel3 PBout(3)
#define sel4 PBout(4)					
#define sel5 PBout(5)	
					

void LED_Init(void);
void LED_debug(void);
void KEY_Init(void);
void Select_Init(void);
void Select1(u8 pos);
void Select2(u8 pos);
void Scan_Init(void);
u8 Scan_Deputy(void);
void test_A(void);
#endif /* __LED_H */

/******************* (C) COPYRIGHT 2018 END OF FILE *****************************/

					
					
