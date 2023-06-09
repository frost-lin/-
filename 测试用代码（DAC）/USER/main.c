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
#include "IO.h"
#include "sys.h"
#include "usart.h"
#include "adc.h"
#include "mpu6050.h"
#include "dma.h"
#include "timer.h"

#define data_len 8*9

 extern u16 ADC_ConvertedValue[channelnum];
 extern u16 Time_count;
 u16 data[9][8];

int main()
{	
//	static float tempr;
//	short cx,cy,cz,Acc_x_cali=0,Acc_y_cali,Acc_z_cali,Gyr_x_cali=0,Gyr_y_cali=0,Gyr_z_cali=0;
//	float aacx=0, aacy=0, aacz=0, x ,y, z;
	u8 str[20],t;
//	u8 send_buf[SEND_BUF_SIZE];
	u16 vol=2022;
	BOOLEAN up=1;
//	uart_init(9600);
	uart3_init(9600);
	printf("114514\r\n");
	delay_init(72);
	LED_Init();
//	KEY_Init();
//	Select_Init();
	LED_debug();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	Adc_Init();
//	Dac1_Init();
//	Dac2_Init();
	test_A();
//	MYDMA_Config(DMA1_Channel4,(u32)&USART1->DR,(u32)send_buf,SEND_BUF_SIZE);
//	MYDMA_Config(DMA1_Channel7,(u32)&USART2->DR,(u32)send_buf,SEND_BUF_SIZE);
//MYDMA_Config(DMA1_Channel2,(u32)&USART3->DR,(u32)send_buf,SEND_BUF_SIZE);
	TIM3_Int_Init(999,71);
	
//	MPU_Init();	
//	delay_ms(100);
//	MPU_ACC_Cali(100,&Acc_x_cali,&Acc_y_cali,&Acc_z_cali);
//	MPU_Gyr_Cali(100,&Gyr_x_cali,&Gyr_y_cali,&Gyr_z_cali);
//	//校准

//	uart2_init(9600);
	
	printf("Test success!\r\n");
TIM_Cmd(TIM3, ENABLE);
  while(1)
  {		
//		TIM_Cmd(TIM3, ENABLE);
//		send_buf[0]=3+2*data_len + 2*4; //帧长度
//		send_buf[1]=0xFA;
//		send_buf[2]=count++;
		
////		Select2(0);
//		delay_ms(5);
//		adcnew=ADC_ConvertedValue[0];
//		Select2(1);
//		delay_ms(5);
//		Dac1_Set_Vol(vol);
//		if(vol<3300&&up)
//		{
//			vol++;
//		}
//		if(vol>0&&!up)
//		{
//			vol--;
//		}
//		if(vol==3300|vol==0)
//		{
//			up=!up;
//		}
//DAC_SetChannel1Data(DAC_Align_12b_R, 200);
//DAC_SetChannel2Data(DAC_Align_12b_R, 200);
//delay_ms(500); 
//DAC_SetChannel1Data(DAC_Align_12b_R, 2000);
//DAC_SetChannel2Data(DAC_Align_12b_R, 2000);
//delay_ms(500); 
//DAC_SetChannel1Data(DAC_Align_12b_R, 4000);
//DAC_SetChannel2Data(DAC_Align_12b_R, 4000);
//delay_ms(500); 
// GPIO_SetBits(GPIOA,GPIO_Pin_4);	
// GPIO_SetBits(GPIOA,GPIO_Pin_5);	
//delay_ms(500);

// GPIO_ResetBits(GPIOA,GPIO_Pin_4);	
// GPIO_ResetBits(GPIOA,GPIO_Pin_5);	
//delay_ms(500);

		sprintf((char*)str, "%d,%d\r\n", ADC_ConvertedValue[0],ADC_ConvertedValue[1]);
		printf(str);
//		
//		sprintf((char*)str, "%d\r\n", ADC_ConvertedValue[0]);
//		printf(str);
		/*
		ADC1 ADC1 ...  ADC1
		ADC2 ...  ...  ADC2
		 .  .           .
		 .    .         .
		 .      .       .
		ADC9 ... ...  ADC9
		*/

//			for(j=0;j<8;j++)   //无滤波
//			{
//				Select2(j);
//				delay_us(200);
//				for(k=0;k<9;k++)   //正式版改为9
//				{
//					temp = ADC_ConvertedValue[k];
//					delay_us(100);
//					if(temp>data[k][j])
//					{
//						data[k][j] = temp;
//					}	
//				}				
//			}

		
//		for(k=0;k<9;k++)
//		{
//			for(j=0;j<8;j++)
//				{
//					send_buf[3+2*j+16*k] = (u8)((u32)data[k][j]>>4);
//					send_buf[3+2*j+16*k+1] = (u8)((u32)data[k][j] & 0x0f)<<4;
//					data[k][j] = 0;
//				}
//		}

		//guangdian
//		for(k=0;k<4;k++)
//		{
////			sprintf((char*)str, "%d \r\n", ADC_ConvertedValue[k+10]);
////			printf(str);
//			temp=ADC_ConvertedValue[k+10];
//			send_buf[147+k*2] = (u8)((u32)temp>>4);
//			send_buf[147+k*2+1] = (u8)((u32)temp & 0x0f)<<4;
//		}
		

		//正式版发送代码
//		USART_DMACmd(USART3,USART_DMAReq_Tx,ENABLE);
//		MYDMA_Enable(DMA1_Channel2);
//		while(1)
//		{
//			if(DMA_GetFlagStatus(DMA1_FLAG_TC2)!=RESET)	//判断通道7传输完成
//			{
//				DMA_ClearFlag(DMA1_FLAG_TC2);//清除通道7传输完成标志
//				break; 
//			}
//		}


//		TIM_Cmd(TIM3, DISABLE);
//			sprintf((char*)str, "%d  \r\n", Time_count);
//			printf(str);
//		Time_count=0;


		delay_ms(25);    //调试时取消注释
		t=!t;
		LED1(t);
			
	}
}
/******************* (C) COPYRIGHT 2018 END OF FILE *****************************/

