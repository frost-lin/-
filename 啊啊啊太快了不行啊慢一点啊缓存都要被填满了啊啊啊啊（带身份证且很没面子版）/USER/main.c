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

#define Set_Time 5     //设置每帧发送间隔时间，单位ms，必须大于2

extern u16 ADC_ConvertedValue[data_len];
extern u16 Time_count;
u16 data[data_len];
u8 flag=0;

#define STM32_UNIQUE_ID_SIZE 12
u8 Id[STM32_UNIQUE_ID_SIZE];
u8* readStm32UniqueID(void)
{
	u8 i;
    vu8* addr = (vu8*)(0x1ffff7e8);   //UID???
    for(i = 0; i < STM32_UNIQUE_ID_SIZE;++i)
    {
        u8 id= *addr;
        Id[i] = id;
        ++addr;
    }
    return Id;
}

u8 sb=1;
int main()
{	
//	u16 ADC_max=0,adcnew=0;
//  u8 select_num=0,scan_code, press=0,i=0;
//	u16 time=0;
//	u32 temp=0;
//	uart_init(9600);
	
	u8 str[20],send_buf[SEND_BUF_SIZE],count=0,t=0,j;
	u16 start;
	uart3_init(115200);
//	printf("114514\r\n");
	
	
	
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
	TIM3_Int_Init(999,71);
		TIM_Cmd(TIM3, ENABLE);
//	MPU_Init();	
//	MPU_ACC_Cali(100,&Acc_x_cali,&Acc_y_cali,&Acc_z_cali);
//	MPU_Gyr_Cali(100,&Gyr_x_cali,&Gyr_y_cali,&Gyr_z_cali);
//	//校准

//	uart2_init(9600);
	
//  Scan_Init();
//	scan_code=Scan_Deputy();
//  sprintf((char*)str, "%d \r\n", Scan_Deputy());
//	printf(str);
//	printf("Test success!\r\n");
	
	send_buf[0]=SEND_BUF_SIZE; //帧长度
	
#if THIS_F__KING_VARIABLE_DECIDES_EVERYTHING==0
	send_buf[1]=0x1A;
//	send_buf[1]=0x2A;
#elif THIS_F__KING_VARIABLE_DECIDES_EVERYTHING==1
	send_buf[1]=0xFB;
#elif THIS_F__KING_VARIABLE_DECIDES_EVERYTHING==2
	send_buf[1]=0xFC;
#endif

  while(1)
  {		
//		start=Time_count;
//		TIM_Cmd(TIM3, ENABLE);
		
		
		/*
		ADC1 ADC1 ...  ADC1
		ADC2 ...  ...  ADC2
		 .  .           .
		 .    .         .
		 .      .       .
		ADC9 ... ...  ADC9
		*/
		
		#if !THIS_F__KING_VARIABLE_DECIDES_EVERYTHING
		
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

//			//在之前的147字节后加上4个字节的第9,10个ADC数据
//			send_buf[147] = (u8)((u32)ADC_ConvertedValue[8]>>4);
//			send_buf[148] = (u8)((u32)ADC_ConvertedValue[8] & 0x0f)<<4;			
//			
//			send_buf[149] = (u8)((u32)ADC_ConvertedValue[9]>>4);
//			send_buf[150] = (u8)((u32)ADC_ConvertedValue[9] & 0x0f)<<4;	
			
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
//		sprintf((char*)str, "%d", USART_RX_STA);
//		printf(str);			
		if(USART_RX_STA)
		{
			if(sb)
			{
				sb=0;
				printf(readStm32UniqueID());
				count=0;
				delay_us(10);
			}	
		send_buf[2]=count++;
			
		//正式版发送代码
		USART_DMACmd(USART3,USART_DMAReq_Tx,ENABLE);
		MYDMA_Enable(DMA1_Channel2);
			
//		sprintf((char*)str, "\r\nScan Time: %d\r\n", Time_count);
//		printf(str);
			
		while(1)
		{
			if(DMA_GetFlagStatus(DMA1_FLAG_TC2)!=RESET)	//判断通道7传输完成
			{
				DMA_ClearFlag(DMA1_FLAG_TC2);//清除通道7传输完成标志
				break; 
			}
		}
			
	
		
		}
//sprintf((char*)str, "\r\n\r\nTotal Time: %d  %d\r\n", Time_count,start);
//		printf(str);
		//固定发送频率,-2为不知道哪里出现的时差
		while(1)
		{
			if(Time_count-start>=Set_Time-2)
				break;
			else if(flag)
			{
				flag=0;
				if(Time_count+(65000)-start>=Set_Time-2)
					break;
			}
		}
//		sprintf((char*)str, "\r\n\r\n%d  %d\r\n", Time_count,start);
//		printf(str);
//		delay_ms(200);    //调试时取消注释
		t=!t;
		LED1(t);


		
//		TIM_Cmd(TIM3, DISABLE);
//		sprintf((char*)str, "\r\nTotal Time: %d\r\n", Time_count);
//		printf(str);
//		Time_count=0;		
	}
}
/******************* (C) COPYRIGHT 2018 END OF FILE *****************************/

