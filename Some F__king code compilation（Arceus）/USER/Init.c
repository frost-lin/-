///******************** (C) COPYRIGHT 2014 *****************************************
// * �ļ���  ��Init.c
// * ����    ��         
// * ��汾  ��ST3.0.0
// * ����    �� 
//**********************************************************************************/
//#include "Init.h"
//
//
//
///*
// * ��������Init
// * ����  ��������
// * ����  : ��
// * ���  ����
// */
//void Init(void)
//{
////  	/* ����ϵͳʱ��Ϊ72M */      
////  SystemInit();	
////
////  /* �ص�Jtag swd */
////  GPIO_Init_SWJ_Disable();
////
////	/* LED �˿ڳ�ʼ�� */
////	LED_GPIO_Config();
////
////	/* TIM3 PWM�������ʼ������ʹ��TIM3 PWM��� */
////	TIM3_PWM_Init();
////
////	/* TIM1 ��ʱ���� */
////	TIM1_NVIC_Configuration();
////  TIM1_Configuration();
////
////  /* USART1 config */
////	USART1_Config();
////  printf("\r\n -------USART1 �Ѿ�������------\r\n");
////
////	/* enable adc1 and config adc1 to dma mode */
////	ADC1_Init(); 
////
////  key_port_init();
//////  LCD_Init();
////  debug_init();
////
////  /* Start ADC1 Software Conversion */ 
////  ADC_SoftwareStartConvCmd(ADC1, ENABLE); //����AD1ת��  
////  /* Enable DMA channel1 */
////  DMA_Cmd(DMA1_Channel1, ENABLE);         //����DMAͨ��  
////  /* TIM1 ��ʼ��ʱ */
////	START_TIME;                             //����TIM1 1ms�ж�
//}
//
//
//
//
///*
// * ��������GPIO_Init_SWJ_Disable
// * ����  ���ص�Jtag swd���Ա��������ʹ��PB��
// * ����  : ��
// * ���  ����
// */
//void GPIO_Init_SWJ_Disable(void)
//{
//
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);  
//  GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);  
//  /* �ı�ָ���ܽŵ�ӳ�� GPIO_Remap_SWJ_Disable SWJ ��ȫ���ã�JTAG+SW-DP �����ã�*/
//
//}
//
//
//
//
//
///******************* (C) COPYRIGHT 2011 END OF FILE *****************************/
//
//
//
//                                                                                                       
