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
#include "timer.h"
#include "oled.h"

/*******************************
1.A0 1 2 3 TIM2 1kHz PWM
2.usart3 B10 out   B11 In

*******************************/
void Get_Servo_Data(const u8 *buff,u16 *data);
void filter(u16 *data);
void Joycon(u16 *ADC, u16 *data);
u16 servo_data[4]={75,75,75,75},new_servo_data[4]={75,90,80,75};
u8 buff[25],USART_Flag=0,Servo_Flag=1;
extern u16 count,Sleep_Time_count;
extern u16 ADC_ConvertedValue[channelnum];
int main()
{	
	u8 t=0,str[20],i=0,move_count=0;
	u16 data=0;
	u32 timetime;
	uart3_init(115200);
	printf("114514\r\n");
	delay_init(72);
	Adc_Init();
	OLED_Init();
	OLED_Clear();
//	OLED_ShowString(0,0,"Success",12);	
	LED_Init();
	LED_debug();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	TIM2_PWM_Init(1000,1440-1);
	TIM3_Int_Init(1000,71);
	printf("Test success!\r\n");
//	Servo_Set(servo_data);
	delay_ms(20);
  while(1)
  {	
	/*************************
			电机控制PWM波输出调试
		*************************/
//		servo_data[i]+=1;
//		if(servo_data[i]>=125)
//		{
//			servo_data[i]=25;
//		}
//		Servo_Set(servo_data);
//		sprintf((char*)str, "%d, %d, %d, %d\r\n", servo_data[0], servo_data[1], servo_data[2], servo_data[3]);
//		printf(str);

		Joycon(ADC_ConvertedValue,new_servo_data);

		
		
		if(USART_Flag)
		{
			Get_Servo_Data(buff,new_servo_data);
			USART_Flag=0;
			Servo_Flag=1;
			Sleep_Time_count=0;
		}
//		if(Servo_Flag && count%3==0)
		if(Servo_Flag)
		{
			Servo_Flag=0;
			for(i=0;i<4;i++)
			{
				if(servo_data[i]<new_servo_data[i])
				{
					servo_data[i]++;
					Servo_Flag=1;
				}
				else if(servo_data[i]>new_servo_data[i])
				{
					servo_data[i]--;
					Servo_Flag=1;
				}
				else
				{
					Servo_Flag|=Servo_Flag;
				}
			}
			Sleep_Time_count=0;
			Servo_Set(servo_data);
//			sprintf((char*)str, "%d,%d,%d,%d\r\n", servo_data[0], servo_data[1], servo_data[2], servo_data[3]);
//			printf(str);
		}	
		
		if(!Servo_Flag)
		{
			if(++move_count>7)
			{
				move_count=0;

			}
			switch(move_count)
			{
				case 1:
				{
					new_servo_data[0]=73;
					new_servo_data[1]=90;
					new_servo_data[2]=80;
					new_servo_data[3]=30;
					break;
				}
				case 2:
				{
					new_servo_data[0]=45;
					new_servo_data[1]=109;
					new_servo_data[2]=80;
					new_servo_data[3]=30;
					break;
				}
				case 3:
				{
					new_servo_data[0]=45;
					new_servo_data[1]=109;
					new_servo_data[2]=75;
					new_servo_data[3]=75;
					break;
				}
				case 4:
				{
					new_servo_data[0]=45;
					new_servo_data[1]=90;
					new_servo_data[2]=80;
					new_servo_data[3]=75;
					break;
				}
				case 5:
				{
					new_servo_data[0]=45;
					new_servo_data[1]=113;
					new_servo_data[2]=78;
					new_servo_data[3]=30;
					break;
				}
				case 6:
				{
					new_servo_data[0]=73;
					new_servo_data[1]=90;
					new_servo_data[2]=80;
					new_servo_data[3]=30;
					break;
				}
			}
			Servo_Flag=1;
		}
		
		if(move_count==7)
		{
			delay_ms(1800);
			delay_ms(1800);
			delay_ms(1800);
			delay_ms(1800);
			delay_ms(1800);
			delay_ms(1800);

			
		}
		
		
		
		sprintf((char*)str, "%3d,%3d,%3d,%3d ", new_servo_data[0], new_servo_data[1], new_servo_data[2], new_servo_data[3]);
		OLED_ShowString(0,0,str,16);
		sprintf((char*)str, "%3d,%3d,%3d,%3d", servo_data[0], servo_data[1], servo_data[2], servo_data[3]);
		OLED_ShowString(0,2,str,16);
		sprintf((char*)str, "%d,%d,%d", Servo_Flag,USART_Flag,move_count);
		OLED_ShowString(0,4,str,16);		
		delay_ms(20);    //调试时取消注释
		t=!t;
		LED1(t);
			
	}
}
/******************* (C) COPYRIGHT 2018 END OF FILE *****************************/

void Get_Servo_Data(const u8 *buff,u16 *data)
{
	u8 count,str[20],i;
//	printf(buff);
	for(i=0;i<4;i++)
	{
		data[i]=0;
	}

		for(count=0;count<4;count++)
		{
			while(*buff >= '0' && *buff <= '9')
			{
				data[count]=data[count]*10 + *buff - '0';
				buff++;
			}
			buff++;
		}
	


//			sprintf((char*)str, "%d, %d, %d, %d\r\n", data[0], data[1], data[3], data[2]);
//			printf(str);
//		printf("Test success!\r\n");

}


void filter(u16 *data)
{
	u8 i;
	for(i=0;i<4;i++)
	{
		if(data[i]<25)
		{
			data[i]=25;
		}
		else if(data[i]>125)
		{
			data[i]=125;
		}
	}
}

void Joycon(u16 *ADC, u16 *data)
{
	u8 str[20];
	if(ADC[0]<1000&&count%10==0)
	{
		data[0]++;
		Servo_Flag=1;
	}
	else if(ADC[0]>3000&&count%10==0)
	{
		data[0]--;
		Servo_Flag=1;
	}
	
	if(ADC[1]<1000&&count%5==0)
	{
		data[1]++;
		Servo_Flag=1;
	}
	else if(ADC[1]>3000&&count%5==0)
	{
		data[1]--;
		Servo_Flag=1;
	}
	
	if(ADC[2]<1000&&count%5==0)
	{
		data[3]--;
		Servo_Flag=1;
	}
	else if(ADC[2]>3000&&count%5==0)
	{
		data[3]++;
		Servo_Flag=1;
	}
	
	if(ADC[3]<1000&&count%5==0)
	{
		data[2]++;
		Servo_Flag=1;
	}
	else if(ADC[3]>3000&&count%5==0)
	{
		data[2]--;
		Servo_Flag=1;
	}
//	sprintf((char*)str, "flag %d\r\n", flag);
//	printf(str);
	filter(data);
//	sprintf((char*)str, "flag %d", flag);
//	printf(str);
}
