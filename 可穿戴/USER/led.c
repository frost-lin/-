/******************** (C) COPYRIGHT 2018 *****************************************
 * 文件名  ：led.c
 * 描述    ：对通用IO口进行初始化
 * 硬件配置：    
 * 版本    ： 
 * 修改日期： 
 * 作者    ：Wu
 * 修改日志：
*********************************************************************************/
#include "led.h"

u8 led_debug_flag = 0;


/*
 * 函数名：LED_Init
 * 描述  ：配置LED用到的I/O口  PE 1   
 * 输入  ：无
 * 输出  ：无
 */
void LED_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				        //PE 1 端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		    //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_SetBits(GPIOB,GPIO_Pin_5);						            	//PE 1 输出高

}



/*
 * 函数名：LED_debug()
 * 描述  ：LED调试程序
 * 输入  : 无
 * 输出  ：无
 */
void LED_debug(void)
{
		LED1( LED_ON );
		delay_ms(50);
		LED1( LED_OFF );
		delay_ms(50);
}

/******************* (C) COPYRIGHT 2018 END OF FILE *****************************/


