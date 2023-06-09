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
#include "system.h"

/************************************
整合版程序，三合一
只需修改system.h中的变量
改好了再下载即可
************************************/


extern u16 ADC_ConvertedValue[data_len];
extern u16 Time_count;
#if !THIS_F__KING_VARIABLE_DECIDES_EVERYTHING
	u16 data[9][8];
	const u8 G_Point[8]={1,7,13,29,31,37,43,59};
/**************************************
需要数据的8个位点，	修改即可使用	
****************************/	
#else
	 u16 data[data_len];
#endif

int main()
{	
//	u16 ADC_max=0,adcnew=0;
//  u8 select_num=0,scan_code, press=0,i=0;
//	u16 time=0;
//	u32 temp=0;
//	uart_init(9600);
	
	u8 str[20],G_count=0,Matrix_count=1,send_buf[SEND_BUF_SIZE],count=0,t=0,j,k;
	uart3_init(9600);
	printf("114514\r\n");
	delay_init(72);
	LED_Init();
//	KEY_Init();
//	Select_Init();
	LED_debug();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	Adc_Init();
//	MYDMA_Config(DMA1_Channel4,(u32)&USART1->DR,(u32)send_buf,SEND_BUF_SIZE);
//	MYDMA_Config(DMA1_Channel7,(u32)&USART2->DR,(u32)send_buf,SEND_BUF_SIZE);
MYDMA_Config(DMA1_Channel2,(u32)&USART3->DR,(u32)send_buf,SEND_BUF_SIZE);
//	TIM3_Int_Init(999,71);
	
//	MPU_Init();	
//	delay_ms(100);
//	MPU_ACC_Cali(100,&Acc_x_cali,&Acc_y_cali,&Acc_z_cali);
//	MPU_Gyr_Cali(100,&Gyr_x_cali,&Gyr_y_cali,&Gyr_z_cali);
//	//校准

//	uart2_init(9600);
	
//  Scan_Init();
//	scan_code=Scan_Deputy();
//  sprintf((char*)str, "%d \r\n", Scan_Deputy());
//	printf(str);
	printf("Test success!\r\n");
	
	send_buf[0]=SEND_BUF_SIZE; //帧长度
	
#if THIS_F__KING_VARIABLE_DECIDES_EVERYTHING==0
	send_buf[1]=0xFA;
#elif THIS_F__KING_VARIABLE_DECIDES_EVERYTHING==1
	send_buf[1]=0xFB;
#elif THIS_F__KING_VARIABLE_DECIDES_EVERYTHING==2
	send_buf[1]=0xFC;
#endif
  while(1)
  {		
//		TIM_Cmd(TIM3, ENABLE);
		send_buf[2]=count++;
		
		/*
		ADC1 ADC1 ...  ADC1
		ADC2 ...  ...  ADC2
		 .  .           .
		 .    .         .
		 .      .       .
		ADC9 ... ...  ADC9
		*/
		
		#if !THIS_F__KING_VARIABLE_DECIDES_EVERYTHING
		
			for(k=0;k<9;k++)   
			{
				for(j=0;j<8;j++)
				{
					if(G_Point[G_count]== Matrix_count)
					{
						data[k][j] = ADC_ConvertedValue[G_count];
						G_count++;
					}	
					Matrix_count++;
				}
			}
	
//     固定位置单列					
//			for(k=0;k<9;k++)   
//			{
//				data[k][0] = ADC_ConvertedValue[k];
//				delay_us(100);
//			}
		
			for(k=0;k<9;k++)
			{
				for(j=0;j<8;j++)  
					{
						send_buf[3+2*j+16*k] = (u8)((u32)data[k][j]>>4);
						send_buf[3+2*j+16*k+1] = (u8)((u32)data[k][j] & 0x0f)<<4;
						data[k][j] = 0;
						G_count = 0;
						Matrix_count = 1;
					}
			}
		#else
			for(j=0;j<data_len;j++)   
			{
				data[j] = ADC_ConvertedValue[j];
				delay_us(100);
			}

			for(j=0;j<data_len;j++)
			{
				send_buf[3+2*j] = (u8)((u32)data[j]>>4);
				send_buf[3+2*j+1] = (u8)((u32)data[j] & 0x0f)<<4;
				data[j] = 0;
			}
		#endif	

//		//guangdian
//		for(k=0;k<4;k++)
//		{
////			sprintf((char*)str, "%d \r\n", ADC_ConvertedValue[k+10]);
////			printf(str);
//			temp=ADC_ConvertedValue[k+10];
//			send_buf[147+k*2] = (u8)((u32)temp>>4);
//			send_buf[147+k*2+1] = (u8)((u32)temp & 0x0f)<<4;
//		}
		
		//正式版发送代码
		USART_DMACmd(USART3,USART_DMAReq_Tx,ENABLE);
		MYDMA_Enable(DMA1_Channel2);
		while(1)
		{
			if(DMA_GetFlagStatus(DMA1_FLAG_TC2)!=RESET)	//判断通道7传输完成
			{
				DMA_ClearFlag(DMA1_FLAG_TC2);//清除通道7传输完成标志
				break; 
			}
		}

//		TIM_Cmd(TIM3, DISABLE);
//			sprintf((char*)str, "%d  \r\n", Time_count);
//			printf(str);
//		Time_count=0;

		delay_ms(200);    //调试时取消注释
		t=!t;
		LED1(t);
			
	}
}
/******************* (C) COPYRIGHT 2018 END OF FILE *****************************/

