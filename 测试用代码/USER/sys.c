/******************** (C) COPYRIGHT 2018 *****************************************
 * 文件名  ：sys.c
 * 描述    ：系统NVIC中断分组设置
 * 硬件配置:              
 * 版本    ： 
 * 修改日期： 
 * 作者    ：Wu
 * 修改日志：
*********************************************************************************/
#include "sys.h"

//------------------------------------------------------------------------------
/*
 * 函数名：swgPtb5 
 * 描述  ：提供swgPrt()打印功能
 * 输入  :  
 * 输出  ： 
 */
void swgPtb5(char c) 					
{
	#if 0
	UART5->DR = c;
	while(!(UART5->SR & BIT7));		
	#else
	USART1->DR = c;
	while(!(USART1->SR & BIT7));
	#endif
}


/*
 * 函数名：swgPtn 
 * 描述  ：提供swgPrt()打印功能
 * 输入  :  
 * 输出  ： 
 */
void swgPtn(char *str)
{
	char *p = str;
	
	while(*p)
	{
		if(*p=='\n')
			swgPtb5('\r');
		swgPtb5(*p);
		p++;
	}
}


/*
 * 函数名：HBT(u16 a)
 * 描述  ：取数据的高8位值
 * 输入  ：16位的数据
 * 输出  ：该数据的高8位值	
 */
u8 HBT(u16 a)	 //取出高八位函数
{
	  a&=0xFF00;
	  a>>=8;
	  return a;
}



/*
 * 函数名：LBT(u16 b)
 * 描述  ：取数据的低8位值
 * 输入  ：16位的数据
 * 输出  ：该数据的低8位值	
 */
u8 LBT(u16 b)	//取出低八位函数
{
	  b&=0x00FF;
	  return b;
}


/*
 * 函数名：alex_crc16(unsigned char *buf, unsigned int len)
 * 描述  ：16位检验方法
 * 输入  ：*buf 字符串  len 字符串长度
 * 输出  ：校验和	
 */
unsigned int alex_crc16(unsigned char *buf, unsigned int len) 
{
    int i,j;
    unsigned int c, crc = 0xFFFF;
    for (i = 0; i < len; i++){
   	c = *(buf+i) & 0x00FF;
   	crc^=c;
        for(j=0;j<8;j++){
             if (crc & 0x0001)
                 {crc>>=1;crc^=0xA001;}
             else crc>>=1;
        }
    }

    return(crc);	
}

	 
void NVIC_Configuration(void)
{

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 	//设置NVIC中断分组2:2位抢占优先级（0-3），2位响应优先级（0-3）
																										// 数字越小，中断优先级越高
}




/******************* (C) COPYRIGHT 2018 END OF FILE *****************************/
