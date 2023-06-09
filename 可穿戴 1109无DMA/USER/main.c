/******************** (C) COPYRIGHT 2018 *****************************************
 * �ļ���  ��main.c
 * ����    ��  
 * Ӳ������:              
 * �汾    �� 
 * �޸����ڣ� 
 * ����    ��Wu
 * �޸���־��
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
	static float ADC1_value=1, ADC2_value;
	static float tempr;
	short cx,cy,cz,Acc_x_cali=0,Acc_y_cali,Acc_z_cali,Gyr_x_cali=0,Gyr_y_cali=0,Gyr_z_cali=0;
	float aacx=0, aacy=0, aacz=0, x ,y, z;
	u8 str[20], send_buf[100];
	u8 t=0;
	delay_init(72);
	LED_Init();
	LED_debug();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(9600);
	Adc_Init();
	
	MPU_Init();	
	delay_ms(100);
	MPU_ACC_Cali(100,&Acc_x_cali,&Acc_y_cali,&Acc_z_cali);
	MPU_Gyr_Cali(100,&Gyr_x_cali,&Gyr_y_cali,&Gyr_z_cali);
//	//У׼

	
	NRF24L01_Init(); 
	while(NRF24L01_Check())
	{
		LED1( LED_ON );
	}
	LED1( LED_OFF );
	NRF24L01_TX_Mode();
	
	uart2_init(9600);
	
	printf("Test success!\r\n");
  while(1)
  {
		Get_Adc(&ADC1_value, &ADC2_value);

//		sprintf((char*)str, "C0 %7fv\r\n", ADC1_value);
//		printf(str);
//		
//		sprintf((char*)str, "C1 %7fv\r\n", ADC2_value);
//		printf(str);
		

		
		tempr = MPU_Get_Temperature()/100.0;
		MPU_Get_Accelerometer(&cx,&cy,&cz);
		aacx = (cx-Acc_x_cali)*9.8*2/32768.0, aacy=(cy-Acc_y_cali)*9.8*2/32768.0, aacz = (cz-Acc_z_cali)*9.8*2/32768.0;
//		sprintf((char*)str, "%.5f %.5f %.5f\r\n",(float)aacx, (float)aacy, (float)aacz);	
//		printf(str);
		
		MPU_Get_Gyroscope(&cx,&cy,&cz);
		x=((double)cx-Gyr_x_cali)*2000/32768, y=(cy-Gyr_y_cali)*2000/32768, z=(cz-Gyr_z_cali)*2000/32768;
//		sprintf((char*)str, "%.5f %.5f %.5f\r\n", (float)x, (float)y, (float)z);//2000
//		printf(str);
		
//		sprintf((char*)str, "C1 %7fv  %7f\r\n", (double)Gyr_x_cali,(double)cx);
//		printf(str);
		
		sprintf((char*)send_buf, "C0:%fv  C1:%fv\r\n Gyro:%.3f %.3f %.3f\r\n Acc:%.5f %.5f %.5f\r\n", ADC1_value, ADC2_value, (float)x, (float)y, (float)z, (float)aacx, (float)aacy, (float)aacz);
		
		usrt2_send(send_buf);
		printf(send_buf);
		
//		str[19]=0;
//		if (NRF24L01_TxPacket(str) != TX_OK)
//		{
//				t=!t;
//				LED1(t);
//		}
		
//		delay_ms(50);
		t=!t;
		LED1(t);
			
	}
}
/******************* (C) COPYRIGHT 2018 END OF FILE *****************************/

