/******************** (C) COPYRIGHT 2017 *****************************************
 * 文件名  ：sys.h
 * 描述    ：IO口的映射以及IO口操作的显示替换 
 * 硬件配置:              
 * 版本    ： 
 * 修改日期： 
 * 作者    ：Wu
 * 修改日志：2016.10.10 将swgPtn函数加入 by LiuYuan
*********************************************************************************/
#ifndef __SYS_H
#define __SYS_H	
#include "stm32f10x.h"

//##############################################################################
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 

//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 


//##############################################################################
//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入


//##############################################################################
//整个项目都要用到的预定义
typedef unsigned char  	BOOLEAN; 				 /*  布尔变量                    */
typedef unsigned char  	INT8U;           /*  无符号8位整型变量           */
typedef signed   char  	INT8S;           /*  有符号8位整型变量           */
typedef unsigned short 	INT16U;          /*  无符号16位整型变量          */
typedef signed   short 	INT16S;          /*  有符号16位整型变量          */
typedef unsigned long  	INT32U;          /*  无符号32位整型变量          */
typedef volatile unsigned int  INT32UV;  /*  编译器不要优化的无符号32位整型变量*/ //原来用long?	
typedef signed   long  	INT32S;          /*  有符号32位整型变量          */
typedef float          	FP32;            /*  单精度浮点数（32位长度）    */
typedef double         	FP64;            /*  双精度浮点数（64位长度）    */

//##############################################################################
typedef unsigned char  	uchar;           /*  无符号8位整型变量           */
typedef unsigned int  	uint;            /*  无符号16位整型变量          */


//##############################################################################
#define BIT0                (0x01)
#define BIT1                (0x02)
#define BIT2                (0x04)
#define BIT3                (0x08)
#define BIT4                (0x0010)
#define BIT5                (0x0020)
#define BIT6                (0x0040)
#define BIT7                (0x0080)


//##############################################################################
//其它一些常用宏
#define false   0
#define true    !false


void NVIC_Configuration(void);


//------------------------------------------------------------------------------
//提供swgPrt()打印功能
//------------------------------------------------------------------------------
void swgPtn(char *str);
#define swgPrt(format, args...)	{sprintf(str,format, ##args);swgPtn(str);}


u8 HBT(u16 a);
u8 LBT(u16 b);
unsigned int alex_crc16(unsigned char *buf, unsigned int len);


#endif /* __SYS_H */

/******************* (C) COPYRIGHT 2015 END OF FILE *****************************/

