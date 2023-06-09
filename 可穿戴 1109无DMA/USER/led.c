/******************** (C) COPYRIGHT 2018 *****************************************
 * �ļ���  ��led.c
 * ����    ����ͨ��IO�ڽ��г�ʼ��
 * Ӳ�����ã�    
 * �汾    �� 
 * �޸����ڣ� 
 * ����    ��Wu
 * �޸���־��
*********************************************************************************/
#include "led.h"

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

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				        //PE 1 �˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		    //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_SetBits(GPIOB,GPIO_Pin_5);						            	//PE 1 �����

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

/******************* (C) COPYRIGHT 2018 END OF FILE *****************************/


