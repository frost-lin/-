/******************** (C) COPYRIGHT 2018 *****************************************
 * 文件名  ：delay.h
 * 描述    ：延时函数头文件
 * 硬件配置:              
 * 版本    ： 
 * 修改日期： 
 * 作者    ：Wu
 * 修改日志：
*********************************************************************************/
#ifndef __DELAY_H
#define __DELAY_H 

#include "stm32f10x.h"
#include "sys.h"

void delay_init(u8 SYSCLK);
void delay_ms(u16 nms);
void delay_us(u32 nus);
void delay_s(u8 ns);

#endif /* __DELAY_H */

/******************* (C) COPYRIGHT 2018 END OF FILE *****************************/



