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

void KEY_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);//使能PORTA,PORTE时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;//KEY0-KEY1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE4,3
}

void Select_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;				        //PE 1 端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		    //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void Slect(u8 pos)
{
	sel0=1 & pos;
	sel1=(1<<1 & pos)>>1;
	sel2=(1<<2 & pos)>>2;	
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


