/******************** (C) COPYRIGHT 2018 *****************************************
 * �ļ���  ��led.c
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

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				        //PE 1 �˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		    //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
  GPIO_SetBits(GPIOC,GPIO_Pin_13);						            	//PE 1 �����

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


