/******************** (C) COPYRIGHT 2018 *****************************************
 * 文件名  ：led.c
 * 描述    ：对通用IO口进行初始化
 * 硬件配置：    
 * 版本    ： 
 * 修改日期： 
 * 作者    ：Wu
 * 修改日志：
*********************************************************************************/
#include "IO.h"
#include <stdio.h>
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

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				        //PE 1 端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		    //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  GPIO_SetBits(GPIOC,GPIO_Pin_13);						            	//PE 1 输出高

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

void Servo_Set(u16 *data)
{
	TIM_SetCompare1(TIM2,data[0]);
	TIM_SetCompare2(TIM2,data[1]);
	TIM_SetCompare3(TIM2,data[2]);
	if(data[3]<30)
		data[3]=30;
	if(data[3]>100)
		data[3]=100;
	TIM_SetCompare4(TIM2,data[3]);
}



/******************* (C) COPYRIGHT 2018 END OF FILE *****************************/


