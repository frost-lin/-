/******************** (C) COPYRIGHT 2018 *****************************************
 * 文件名  ：main.c
 * 描述    ：  
 * 硬件配置:              
 * 版本    ： 
 * 修改日期： 
 * 作者    ：Wu
 * 修改日志：
*********************************************************************************/
#include "stm32f10x.h"
#include <stdio.h>
#include "delay.h"
#include "led.h"
#include "sys.h"
#include "usart.h"
#include "adc.h"
#include "24l01.h"
#include "mpu6050.h"


int main()
{	
	static float ADC_value=1;
	static float tempr;
	short aacx, aacy, aacz;
	u8 str[20];
//	u8 tmp_buf[20];
	u8 t=0,i;
	delay_init(72);
	LED_Init();
	LED_debug();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(115200);
	Adc_Init();
	
	MPU_Init();	
	
	NRF24L01_Init(); 
	while(NRF24L01_Check())
	{
		LED1( LED_ON );
	}
	LED1( LED_OFF );
	NRF24L01_TX_Mode();
	
	uart4_init(9600);
	
	printf("Test success!\r\n");
  while(1)
  {
		ADC_value = (Get_Adc(ADC_Channel_10)*3.3/4095);
		sprintf((char*)str, " %7f v\r\n", ADC_value);
		printf(str);
		for(i=0;i<19;i++)
	{
		USART_SendData(UART4, i);//向串口1发送数据
		while(USART_GetFlagStatus(UART4,USART_FLAG_TC)!=SET);//等待发送结束
	}
		
		tempr = MPU_Get_Temperature()/100.0;
		MPU_Get_Gyroscope(&aacx,&aacy,&aacz);
		sprintf((char*)str, " %f %f %f %f\r\n", tempr, (float)aacx, (float)aacy, (float)aacz);
		printf(str);
		
		
		MPU_Get_Accelerometer(&aacx,&aacy,&aacz);
		sprintf((char*)str, " %f %f %f %f\r\n", tempr, (float)aacx, (float)aacy, (float)aacz);
		printf(str);
		
		str[19]=0;
		if (NRF24L01_TxPacket(str) != TX_OK)
		{
				t=!t;
				LED1(t);
		}
		
		delay_ms(100);
		t=!t;
		LED1(t);
			
	}
}
/******************* (C) COPYRIGHT 2018 END OF FILE *****************************/

