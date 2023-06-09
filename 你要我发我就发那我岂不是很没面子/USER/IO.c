/******************** (C) COPYRIGHT 2018 *****************************************
 * �ļ���  ��IO.c
 * ����    ����ͨ��IO�ڽ��г�ʼ��
 * Ӳ�����ã�    
 * �汾    �� 
 * �޸����ڣ� 
 * ����    ��Wu
 * �޸���־��
*********************************************************************************/
#include "IO.h"
#include <stdio.h>
u8 led_debug_flag = 0;


/*
 * ��������LED_Init
 * ����  ������LED�õ���I/O��  PE 1   
 * ����  ����
 * ���  ����
 */
void LED_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;				        //PE 1 �˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		    //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_SetBits(GPIOB,GPIO_Pin_12);						            	//PE 1 �����

}

void KEY_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);//ʹ��PORTA,PORTEʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;//KEY0-KEY1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOE4,3
}

void Select_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;				        //PE 1 �˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		    //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void Select1(u8 pos)
{
	sel0=(u8)(1 & pos);
	sel1=(1<<1 & pos)>>1;
	sel2=(1<<2 & pos)>>2;	
}

void Select2(u8 pos)
{
	sel3=(u8)(1 & pos);
	sel4=(1<<1 & pos)>>1;
	sel5=(1<<2 & pos)>>2;	
}

/*
 * ��������LED_debug()
 * ����  ��LED���Գ���
 * ����  : ��
 * ���  ����
 */
void LED_debug(void)
{
	LED1( LED_ON );
	delay_ms(50);
	LED1( LED_OFF );
	delay_ms(50);
}

void Scan_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;				       
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		   
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;				       
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

u8 Scan_Deputy(void)
{
	u8 i,Scan_Code=0,str[10];
	for(i=0;i<8;i++)
	{
		Select1(i);
		delay_ms(1);
		Scan_Code = Scan_Code | ((u8)GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11) << i);
		sprintf((char*)str, "%d", GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11));
	  printf(str);
	}
	printf("\r\n");
	return Scan_Code;
}


/******************* (C) COPYRIGHT 2018 END OF FILE *****************************/


