/******************** (C) COPYRIGHT 2018 *****************************************
 * 文件名  ：delay.c
 * 描述    ：使用SysTick的普通计数模式对延时进行管理
 * 硬件配置:              
 * 版本    ： 
 * 修改日期： 
 * 作者    ：Wu
 * 修改日志：
*********************************************************************************/
#include "delay.h"

	 
static u8  fac_us=0;//us延时倍乘数
static u16 fac_ms=0;//ms延时倍乘数


/*
 *函数名 ：delay_init(u8 SYSCLK)
 *描述   ：延迟函数初始化
           SYSTICK的时钟固定为HCLK时钟的1/8
           SYSCLK:系统时钟
 *输入   ：无
 *输出   ：无
 */
void delay_init(u8 SYSCLK)
{
//	SysTick->CTRL&=0xfffffffb;//bit2清空,选择外部时钟  HCLK/8
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//选择外部时钟  HCLK/8
	fac_us=SYSCLK/8;		    
	fac_ms=(u16)fac_us*1000;
}


/*
 * 函数名：delay_ms(u16 nms)
 * 描述  ：延时nms 
 *         注意nms的范围
 *         SysTick->LOAD为24位寄存器,所以,最大延时为:
 *         nms<=0xffffff*8*1000/SYSCLK
 *         SYSCLK单位为Hz,nms单位为ms
 *         对72M条件下,nms<=1864 
 * 输入  ：nms 延时毫秒数   
 * 输出  ：无 
 */								    
void delay_ms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;           //清空计数器
	SysTick->CTRL=0x01 ;          //开始倒数  
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//等待时间到达   
	SysTick->CTRL=0x00;       //关闭计数器
	SysTick->VAL =0X00;       //清空计数器	  	    
}

/*
 * 函数名：delay_us(u32 nus)
 * 描述  ：延时nus  
 *         nus为要延时的us数.		    								   
 * 输入  ：nus 延时微秒数   
 * 输出  ： 
 */   		    								   
void delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; //时间加载	  		 
	SysTick->VAL=0x00;        //清空计数器
	SysTick->CTRL=0x01 ;      //开始倒数 	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//等待时间到达   
	SysTick->CTRL=0x00;       //关闭计数器
	SysTick->VAL =0X00;       //清空计数器	 
}


/*
 * 函数名：delay_s(u8 ns)
 * 描述  ：延时ns  
 *         ns为要延时的s数.		    								   
 * 输入  ：ns 延时秒数   
 * 输出  ： 
 */   		    								   
void delay_s(u8 ns)
{
    u8 i;
    for(i=0;i<ns;i++)
        delay_ms(1000);
}


/******************* (C) COPYRIGHT 2018 END OF FILE *****************************/



