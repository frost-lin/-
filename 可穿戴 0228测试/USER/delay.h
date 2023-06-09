/******************** (C) COPYRIGHT 2018 *****************************************
 * �ļ���  ��delay.h
 * ����    ����ʱ����ͷ�ļ�
 * Ӳ������:              
 * �汾    �� 
 * �޸����ڣ� 
 * ����    ��Wu
 * �޸���־��
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



