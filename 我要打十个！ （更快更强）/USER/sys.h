/******************** (C) COPYRIGHT 2017 *****************************************
 * �ļ���  ��sys.h
 * ����    ��IO�ڵ�ӳ���Լ�IO�ڲ�������ʾ�滻 
 * Ӳ������:              
 * �汾    �� 
 * �޸����ڣ� 
 * ����    ��Wu
 * �޸���־��2016.10.10 ��swgPtn�������� by LiuYuan
*********************************************************************************/
#ifndef __SYS_H
#define __SYS_H	
#include "stm32f10x.h"

//##############################################################################
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 

//IO�ڵ�ַӳ��
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
//IO�ڲ���,ֻ�Ե�һ��IO��!
//ȷ��n��ֵС��16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //��� 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //���� 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //��� 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //���� 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //��� 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //���� 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //��� 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //���� 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //��� 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //����

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //��� 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //����

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //��� 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //����


//##############################################################################
//������Ŀ��Ҫ�õ���Ԥ����
typedef unsigned char  	BOOLEAN; 				 /*  ��������                    */
typedef unsigned char  	INT8U;           /*  �޷���8λ���ͱ���           */
typedef signed   char  	INT8S;           /*  �з���8λ���ͱ���           */
typedef unsigned short 	INT16U;          /*  �޷���16λ���ͱ���          */
typedef signed   short 	INT16S;          /*  �з���16λ���ͱ���          */
typedef unsigned long  	INT32U;          /*  �޷���32λ���ͱ���          */
typedef volatile unsigned int  INT32UV;  /*  ��������Ҫ�Ż����޷���32λ���ͱ���*/ //ԭ����long?	
typedef signed   long  	INT32S;          /*  �з���32λ���ͱ���          */
typedef float          	FP32;            /*  �����ȸ�������32λ���ȣ�    */
typedef double         	FP64;            /*  ˫���ȸ�������64λ���ȣ�    */

//##############################################################################
typedef unsigned char  	uchar;           /*  �޷���8λ���ͱ���           */
typedef unsigned int  	uint;            /*  �޷���16λ���ͱ���          */


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
//����һЩ���ú�
#define false   0
#define true    !false


void NVIC_Configuration(void);


//------------------------------------------------------------------------------
//�ṩswgPrt()��ӡ����
//------------------------------------------------------------------------------
void swgPtn(char *str);
#define swgPrt(format, args...)	{sprintf(str,format, ##args);swgPtn(str);}


u8 HBT(u16 a);
u8 LBT(u16 b);
unsigned int alex_crc16(unsigned char *buf, unsigned int len);


#endif /* __SYS_H */

/******************* (C) COPYRIGHT 2015 END OF FILE *****************************/

