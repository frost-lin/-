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
#include "dma.h"

 extern u16 ADC_ConvertedValue[channelnum];

int main()
{	
	u16 ADC_max=0,adcnew=0;
	static float tempr;
	short cx,cy,cz,Acc_x_cali=0,Acc_y_cali,Acc_z_cali,Gyr_x_cali=0,Gyr_y_cali=0,Gyr_z_cali=0;
	float aacx=0, aacy=0, aacz=0, x ,y, z;
	u8 str[20], send_buf[SEND_BUF_SIZE], select_num=0,press=0;
	u8 t=0,i=0;
	u16 time=0;
	delay_init(72);
	LED_Init();
	KEY_Init();
	Select_Init();
	LED_debug();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(115200);
	Adc_Init();
	MYDMA_Config(DMA1_Channel4,(u32)&USART1->DR,(u32)send_buf,SEND_BUF_SIZE);
	MYDMA_Config(DMA1_Channel7,(u32)&USART2->DR,(u32)send_buf,SEND_BUF_SIZE);
	
	MPU_Init();	
	delay_ms(100);
	MPU_ACC_Cali(100,&Acc_x_cali,&Acc_y_cali,&Acc_z_cali);
	MPU_Gyr_Cali(100,&Gyr_x_cali,&Gyr_y_cali,&Gyr_z_cali);
//	//校准

	
//	NRF24L01_Init(); 
//	while(NRF24L01_Check())
//	{
//		LED1( LED_ON );
//	}
//	LED1( LED_OFF );
//	NRF24L01_TX_Mode();
	
	uart2_init(9600);
	
	printf("Test success!\r\n");
  while(1)
  {		
		if(KEY0==0)
		{
			press = 1;
		}
		else if(KEY0==1 && press == 1)
		{
			select_num++;
			if(select_num >= 8)
				select_num=0;
			press = 0;
		}
		Slect(select_num);
		adcnew = ADC_ConvertedValue[0];
		if(adcnew > ADC_max)
		{
			ADC_max = adcnew;
		}
		if(++i>=10)
		{
			sprintf((char*)str, "%d \r\n", ADC_max);
			printf(str);
			ADC_max=0;
			i=0;
		}
			
//		USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);
//		MYDMA_Enable(DMA1_Channel4);
//		
//		while(1)
//		{
//			if(DMA_GetFlagStatus(DMA1_FLAG_TC4)!=RESET)	//判断通道4传输完成
//			{
//				DMA_ClearFlag(DMA1_FLAG_TC4);//清除通道4传输完成标志
//				break; 
//			}
//		}
				
//		sprintf((char*)str, "C1 %f\r\n", (float)ADC_ConvertedValue[1]/4095*3.3);
//		printf(str);
		
//		USART_DMACmd(USART2,USART_DMAReq_Tx,ENABLE);
//		MYDMA_Enable(DMA1_Channel7);
//		while(1)
//		{
//			if(DMA_GetFlagStatus(DMA1_FLAG_TC7)!=RESET)	//判断通道7传输完成
//			{
//				DMA_ClearFlag(DMA1_FLAG_TC7);//清除通道7传输完成标志
//				break; 
//			}
//		}
		
		//tempr = MPU_Get_Temperature()/100.0;
		
//		
//		MPU_Get_Accelerometer(&cx,&cy,&cz);
//		aacx = (cx-Acc_x_cali)*9.8*2/32768.0, aacy=(cy-Acc_y_cali)*9.8*2/32768.0, aacz = (cz-Acc_z_cali)*9.8*2/32768.0;
//		sprintf((char*)str, "%.5f %.5f %.5f\r\n",(float)aacx, (float)aacy, (float)aacz);	
//		printf(str);
//		
//		MPU_Get_Gyroscope(&cx,&cy,&cz);
//		x=((double)cx-Gyr_x_cali)*2000/32768, y=(cy-Gyr_y_cali)*2000/32768, z=(cz-Gyr_z_cali)*2000/32768;
//		sprintf((char*)str, "%.5f %.5f %.5f\r\n", (float)x, (float)y, (float)z);//2000
//		printf(str);
		
//		sprintf((char*)str, "C1 %7fv  %7f\r\n", (double)Gyr_x_cali,(double)cx);
//		printf(str);
		
//		sprintf((char*)send_buf, "C0:%fv  C1:%fv Gyro:%.3f %.3f %.3f Acc:%.5f %.5f %.5f\r\n", \
//			(float)ADC_ConvertedValue[0]/4095*3.3, (float)ADC_ConvertedValue[1]/4095*3.3, \
//			(float)x, (float)y, (float)z, (float)aacx, (float)aacy, (float)aacz);
//			
		
//		usrt2_send(send_buf);
//		printf(send_buf);
		
//		str[19]=0;
//		if (NRF24L01_TxPacket(str) != TX_OK)
//		{
//				t=!t;
//				LED1(t);
//		}
		
		delay_ms(20);
		t=!t;
		LED1(t);
			
	}
}
/******************* (C) COPYRIGHT 2018 END OF FILE *****************************/

