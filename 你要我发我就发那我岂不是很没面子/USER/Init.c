///******************** (C) COPYRIGHT 2014 *****************************************
// * 文件名  ：Init.c
// * 描述    ：         
// * 库版本  ：ST3.0.0
// * 作者    ： 
//**********************************************************************************/
//#include "Init.h"
//
//
//
///*
// * 函数名：Init
// * 描述  ：主函数
// * 输入  : 无
// * 输出  ：无
// */
//void Init(void)
//{
////  	/* 配置系统时钟为72M */      
////  SystemInit();	
////
////  /* 关掉Jtag swd */
////  GPIO_Init_SWJ_Disable();
////
////	/* LED 端口初始化 */
////	LED_GPIO_Config();
////
////	/* TIM3 PWM波输出初始化，并使能TIM3 PWM输出 */
////	TIM3_PWM_Init();
////
////	/* TIM1 定时配置 */
////	TIM1_NVIC_Configuration();
////  TIM1_Configuration();
////
////  /* USART1 config */
////	USART1_Config();
////  printf("\r\n -------USART1 已经就绪！------\r\n");
////
////	/* enable adc1 and config adc1 to dma mode */
////	ADC1_Init(); 
////
////  key_port_init();
//////  LCD_Init();
////  debug_init();
////
////  /* Start ADC1 Software Conversion */ 
////  ADC_SoftwareStartConvCmd(ADC1, ENABLE); //启动AD1转换  
////  /* Enable DMA channel1 */
////  DMA_Cmd(DMA1_Channel1, ENABLE);         //启动DMA通道  
////  /* TIM1 开始计时 */
////	START_TIME;                             //启动TIM1 1ms中断
//}
//
//
//
//
///*
// * 函数名：GPIO_Init_SWJ_Disable
// * 描述  ：关掉Jtag swd，以便可以正常使用PB口
// * 输入  : 无
// * 输出  ：无
// */
//void GPIO_Init_SWJ_Disable(void)
//{
//
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);  
//  GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);  
//  /* 改变指定管脚的映射 GPIO_Remap_SWJ_Disable SWJ 完全禁用（JTAG+SW-DP 都禁用）*/
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
