/******************** (C) COPYRIGHT 2018 *****************************************
 * �ļ���  ��delay.c
 * ����    ��ʹ��SysTick����ͨ����ģʽ����ʱ���й���
 * Ӳ������:              
 * �汾    �� 
 * �޸����ڣ� 
 * ����    ��Wu
 * �޸���־��
*********************************************************************************/
#include "delay.h"

	 
static u8  fac_us=0;//us��ʱ������
static u16 fac_ms=0;//ms��ʱ������


/*
 *������ ��delay_init(u8 SYSCLK)
 *����   ���ӳٺ�����ʼ��
           SYSTICK��ʱ�ӹ̶�ΪHCLKʱ�ӵ�1/8
           SYSCLK:ϵͳʱ��
 *����   ����
 *���   ����
 */
void delay_init(u8 SYSCLK)
{
//	SysTick->CTRL&=0xfffffffb;//bit2���,ѡ���ⲿʱ��  HCLK/8
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//ѡ���ⲿʱ��  HCLK/8
	fac_us=SYSCLK/8;		    
	fac_ms=(u16)fac_us*1000;
}


/*
 * ��������delay_ms(u16 nms)
 * ����  ����ʱnms 
 *         ע��nms�ķ�Χ
 *         SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:
 *         nms<=0xffffff*8*1000/SYSCLK
 *         SYSCLK��λΪHz,nms��λΪms
 *         ��72M������,nms<=1864 
 * ����  ��nms ��ʱ������   
 * ���  ���� 
 */								    
void delay_ms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;//ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL =0x00;           //��ռ�����
	SysTick->CTRL=0x01 ;          //��ʼ����  
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
	SysTick->CTRL=0x00;       //�رռ�����
	SysTick->VAL =0X00;       //��ռ�����	  	    
}

/*
 * ��������delay_us(u32 nus)
 * ����  ����ʱnus  
 *         nusΪҪ��ʱ��us��.		    								   
 * ����  ��nus ��ʱ΢����   
 * ���  �� 
 */   		    								   
void delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; //ʱ�����	  		 
	SysTick->VAL=0x00;        //��ռ�����
	SysTick->CTRL=0x01 ;      //��ʼ���� 	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
	SysTick->CTRL=0x00;       //�رռ�����
	SysTick->VAL =0X00;       //��ռ�����	 
}


/*
 * ��������delay_s(u8 ns)
 * ����  ����ʱns  
 *         nsΪҪ��ʱ��s��.		    								   
 * ����  ��ns ��ʱ����   
 * ���  �� 
 */   		    								   
void delay_s(u8 ns)
{
    u8 i;
    for(i=0;i<ns;i++)
        delay_ms(1000);
}


/******************* (C) COPYRIGHT 2018 END OF FILE *****************************/



