/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/main.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */  

/* Includes ------------------------------------------------------------------*/
#include "led.h"
#include "delay.h"
#include "sys.h"

#include "lcd.h"
#include "stm32f10x.h"
#include "usart2.h"			 	 
#include "string.h"	 
#include "key.h"
#include "adc.h"
#include "dma.h"


#define data_len 4
#define SEND_BUF_SIZE    11  	
/************************
可能需要该的文件：usart.c和adc.c，主要改gpio端口位置
printf可以直接输出到usb串口
蓝牙串口直接用DMA，开启取消那段注释，需要发送的存到send_buf里就行，注意数据长度


*****************/




 extern u16 ADC_ConvertedValue[channelnum];
 extern u16 Time_count;
 u16 data[8]={0,0,0,0,0,0,0,0 };

int main()
{	
	u16 ADC_max=0,adcnew=0;
	static float tempr;
	u8 str[20];
	//u32 SEND_BUF_SIZE=16;
	u8 send_buf[SEND_BUF_SIZE],count=0;
	u8 t=0,i=0,j;
	u32 temp=0;
	u16 time=0;
	delay_init(72);
	KEY_Init();


	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(115200); //usb连接电脑的串口
	Adc_Init();
	MYDMA_Config(DMA1_Channel4,(u32)&USART1->DR,(u32)send_buf,SEND_BUF_SIZE);
//	MYDMA_Config(DMA1_Channel7,(u32)&USART2->DR,(u32)send_buf,SEND_BUF_SIZE);

	
	uart2_init(9600); //这个是蓝牙串口
	
	//printf("Test success!\r\n");
  while(1)
  {		

		send_buf[0]=3+2*data_len; //帧长度
		send_buf[1]=0xFA;
		send_buf[2]=count++;

		for(j=0;j<4;j++)  
		{
			data[j] = ADC_ConvertedValue[j];  //A0 5 6 7四个IO口
			delay_us(100);
		}
		
		for(j=0;j<4;j++)
			{
				send_buf[3+2*j] = (u8)((u32)data[j]>>4);
				send_buf[3+2*j+1] = (u8)((u32)data[j] & 0x0f)<<4;
				data[j] = 0;
			}
/*
下面这一段是DMA的，USART1就是usb串口，USART2是蓝牙串口
*/
		USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);
		MYDMA_Enable(DMA1_Channel4);
		while(1)
		{
				if(DMA_GetFlagStatus(DMA1_FLAG_TC4)!=RESET)	//判断通道4传输完成
				{
					DMA_ClearFlag(DMA1_FLAG_TC4);//清除通道4传输完成标志
					break; 
				}
		}



//		TIM_Cmd(TIM3, ENABLE); //算时间用的，可以先关了


		
//			USART_DMACmd(USART2,USART_DMAReq_Tx,ENABLE);
//			MYDMA_Enable(DMA1_Channel7);
//			
//				if(DMA_GetFlagStatus(DMA1_FLAG_TC7)!=RESET)	//判断通道7传输完成
//				{
//					DMA_ClearFlag(DMA1_FLAG_TC7);//清除通道7传输完成标志
//					break; 
//				}
		

//		TIM_Cmd(TIM3, DISABLE);
//			sprintf((char*)str, "%d  \r\n", Time_count);
//			printf(str);
//		Time_count=0;

//			printf(send_buf);
		

		
//		sprintf((char*)send_buf, "%.3f\r\n", ((float)ADC_ConvertedValue[0]/4095*3.3));
//		printf(send_buf);
		delay_ms(500);
		t=!t;
		
			
	}
}
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
