#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK��ӢSTM32������
//ADC ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/7
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 

#define ADC1_DR_Address ((u32)0x4001244C)
#define channelnum 9

void Adc_Init(void);
void Get_Adc(float *adc1, float *adc2);  
void Dac1_Init(void); 
void Dac1_Set_Vol(u16 vol);
void Dac2_Init(void);
#endif 
