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
#include "timer.h"

#define data_len 8

 extern u16 ADC_ConvertedValue[channelnum];
 extern u16 Time_count;
 u16 data[8]={4095, 287, 344, 461, 511, 6, 7, 8 };

int main()
{	
	u16 ADC_max=0,adcnew=0;
	static float tempr;
	short cx,cy,cz,Acc_x_cali=0,Acc_y_cali,Acc_z_cali,Gyr_x_cali=0,Gyr_y_cali=0,Gyr_z_cali=0;
	float aacx=0, aacy=0, aacz=0, x ,y, z;
	u8 str[20], select_num=0,press=0;
	u8 send_buf[SEND_BUF_SIZE],count=0;
	u8 t=0,i=0,j;
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
	TIM3_Int_Init(1,35);
	
//	MPU_Init();	
//	delay_ms(100);
//	MPU_ACC_Cali(100,&Acc_x_cali,&Acc_y_cali,&Acc_z_cali);
//	MPU_Gyr_Cali(100,&Gyr_x_cali,&Gyr_y_cali,&Gyr_z_cali);
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
//		if(KEY0==0)
//		{
//			press = 1;
//		}
//		else if(KEY0==1 && press == 1)
//		{
//			select_num++;
//			if(select_num >= 8)
//				select_num=0;
//			press = 0;
//		}
//		Slect(select_num);
		
//		adcnew = ADC_ConvertedValue[0];
//		if(adcnew > ADC_max)
//		{
//			ADC_max = adcnew;
//		}
//		if(++i>=15)
//		{
//			sprintf((char*)str, "%d \r\n", ADC_max);
////			printf(str);
//			ADC_max=0;
//			i=0;
//		}
			
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
				
		
		USART_DMACmd(USART2,USART_DMAReq_Tx,ENABLE);
		MYDMA_Enable(DMA1_Channel7);
		while(1)
		{
			if(DMA_GetFlagStatus(DMA1_FLAG_TC7)!=RESET)	//判断通道7传输完成
			{
				DMA_ClearFlag(DMA1_FLAG_TC7);//清除通道7传输完成标志
				break; 
			}
		}
		
//		sprintf((char*)send_buf, "%s %d\r\n", "TS",ADC_ConvertedValue[0]);
		send_buf[0]=3+2*data_len;
		send_buf[1]=0xFA;
		send_buf[2]=count++;
		TIM_Cmd(TIM3, ENABLE);
	  for(j=0;j<8;j++)
		{
//			send_buf[3+2*j] = (u8)((u32)data[j]>>4);
//			send_buf[3+2*j+1] = (u8)((u32)data[j] & 0x0f)<<4;
			send_buf[3+2*j] = (u8)((u32)ADC_ConvertedValue[0]>>4);
			send_buf[3+2*j+1] = (u8)((u32)ADC_ConvertedValue[0] & 0x0f)<<4;
			Slect(select_num);
			select_num++;
			if(select_num >= 8)
				select_num=0;
//			sprintf((char*)str, "%d  ", ADC_ConvertedValue[0]);
//			printf(str);
		}
		TIM_Cmd(TIM3, DISABLE);
//			sprintf((char*)str, "%d  \r\n", Time_count);
//			printf(str);
		Time_count=0;
		if (count >= 0xff)
			count=0;
//		printf(send_buf);
		
		//tempr = MPU_Get_Temperature()/100.0;
		
		
//		MPU_Get_Accelerometer(&cx,&cy,&cz);
//		aacx = (cx-Acc_x_cali)*9.8*2/32768.0, aacy=(cy-Acc_y_cali)*9.8*2/32768.0, aacz = (cz-Acc_z_cali)*9.8*2/32768.0;

//		
//		MPU_Get_Gyroscope(&cx,&cy,&cz);
//		x=((double)cx-Gyr_x_cali)*2000/32768, y=(cy-Gyr_y_cali)*2000/32768, z=(cz-Gyr_z_cali)*2000/32768;

//		
//		sprintf((char*)send_buf, "C0:%fv  C1:%fv Gyro:%.3f %.3f %.3f Acc:%.5f %.5f %.5f\r\n", \
//			(float)ADC_ConvertedValue[0]/4095*3.3, (float)ADC_ConvertedValue[1]/4095*3.3, \
//			(float)x, (float)y, (float)z, (float)aacx, (float)aacy, (float)aacz);
//	
		
		delay_ms(100);
		t=!t;
		LED1(t);
			
	}
}
/******************* (C) COPYRIGHT 2018 END OF FILE *****************************/

