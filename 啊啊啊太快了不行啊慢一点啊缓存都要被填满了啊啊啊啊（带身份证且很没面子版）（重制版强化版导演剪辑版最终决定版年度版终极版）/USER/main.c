#include "led.h"
#include "delay.h"
#include "sys.h"
#include "FreeRTOS.h"
#include "task.h"
#include "adc.h"
#include "usart.h"
#include "dma.h"
#include "mysystem.h"
#include "semphr.h"
/************************************************
 ALIENTEK Mini STM32F103������ FreeRTOSʵ��2-1
 FreeRTOS��ֲʵ��-�⺯���汾
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/

#define Send_Delay_Time 500

#define START_TASK_PRIO		1
#define START_STK_SIZE 		128  
TaskHandle_t StartTask_Handler;
void start_task(void *pvParameters);

#define LED0_TASK_PRIO		2
#define LED0_STK_SIZE 		50  
TaskHandle_t LED0Task_Handler;
void led0_task(void *pvParameters);

#define ID_TASK_PRIO 7
#define ID_STK_SIZE 50
TaskHandle_t GetID_Handler;
void Get_ID(void *pvParameters);

#define ADC_TASK_PRIO 4
#define ADC_TASK_STK_SIZE 100
TaskHandle_t ADC_Task_Handler;
void ADC_Task(void *pvParameters);

#define DMA_TASK_PRIO 5
#define DMA_TASK_STK_SIZE 50
TaskHandle_t DMA_Task_Handler;
void DMA_Send_Task(void *pvParameters);

SemaphoreHandle_t Data_Ready;
SemaphoreHandle_t Send_Ready;

extern u16 ADC_ConvertedValue[data_len];
extern u8 USART_RX_STA;  
u8 send_buf[SEND_BUF_SIZE];
u16 data[data_len];

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//����ϵͳ�ж����ȼ�����4	 	 
	delay_init();	    				//��ʱ������ʼ��	  
	uart3_init(115200);					//��ʼ������
	LED_Init();		  					//��ʼ��LED
	Adc_Init();
	MYDMA_Config(DMA1_Channel2,(u32)&USART3->DR,(u32)send_buf,SEND_BUF_SIZE);
//	printf("Init Success!");
	 
	//������ʼ����
    xTaskCreate((TaskFunction_t )start_task,            //������
                (const char*    )"start_task",          //��������
                (uint16_t       )START_STK_SIZE,        //�����ջ��С
                (void*          )NULL,                  //���ݸ��������Ĳ���
                (UBaseType_t    )START_TASK_PRIO,       //�������ȼ�
                (TaskHandle_t*  )&StartTask_Handler);   //������              
    vTaskStartScheduler();          //�����������
}

//��ʼ����������
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //�����ٽ���
		Data_Ready = xSemaphoreCreateBinary();
		Send_Ready = xSemaphoreCreateBinary();
		xSemaphoreGive(Send_Ready);
    //����LED0����
    xTaskCreate((TaskFunction_t )led0_task,     	
                (const char*    )"led0_task",   	
                (uint16_t       )LED0_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )LED0_TASK_PRIO,	
                (TaskHandle_t*  )&LED0Task_Handler);  
								
		xTaskCreate((TaskFunction_t )Get_ID,     	
                (const char*    )"Get_ID",   	
                (uint16_t       )ID_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )ID_TASK_PRIO,	
                (TaskHandle_t*  )&GetID_Handler);	
		xTaskCreate((TaskFunction_t )ADC_Task,     	
                (const char*    )"ADC_Task",   	
                (uint16_t       )ADC_TASK_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )ADC_TASK_PRIO,	
                (TaskHandle_t*  )&ADC_Task_Handler);		
		xTaskCreate((TaskFunction_t )DMA_Send_Task,     	
                (const char*    )"DMA_Task",   	
                (uint16_t       )DMA_TASK_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )DMA_TASK_PRIO,	
                (TaskHandle_t*  )&DMA_Task_Handler);
    vTaskDelete(StartTask_Handler); //ɾ����ʼ����
		vTaskSuspend(ADC_Task_Handler);
		vTaskSuspend(DMA_Task_Handler);
		
    taskEXIT_CRITICAL();            //�˳��ٽ���
}

//LED0������ 
void led0_task(void *pvParameters)
{
    while(1)
    {
        LED0=~LED0;
        vTaskDelay(500);
    }
}   

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


void Get_ID(void *pvParameters)
{
	u8 i;
	readStm32UniqueID();
	while(1)
	{
		if(USART_RX_STA)
		{
			for(i=0;i<sizeof(Id);i++)
			{
				printf("%02x",Id[i]);			
			}
			printf("\r\n");
			vTaskResume(ADC_Task_Handler);
			vTaskResume(DMA_Task_Handler);
		}
		else
		{
			vTaskSuspend(ADC_Task_Handler);
			vTaskSuspend(DMA_Task_Handler);
		}
		
		vTaskSuspend(GetID_Handler);
	}
}

void ADC_Task(void *pvParameters)
{
	u8 j;
	static u8 count =0;

	send_buf[0]=SEND_BUF_SIZE; //֡����
#if THIS_F__KING_VARIABLE_DECIDES_EVERYTHING==0
	send_buf[1]=0x1A;
//	send_buf[1]=0x2A;
#elif THIS_F__KING_VARIABLE_DECIDES_EVERYTHING==1
	send_buf[1]=0xFB;
#elif THIS_F__KING_VARIABLE_DECIDES_EVERYTHING==2
	send_buf[1]=0xFC;
#endif
	xSemaphoreGive(Send_Ready);
	while(1)
	{ 
		if(xSemaphoreTake(Send_Ready,portMAX_DELAY) == pdTRUE)
		{
			for(j=0;j<data_len;j++)   
				{
					data[j] = ADC_ConvertedValue[j];
					delay_us(10);
				}

				for(j=0;j<data_len;j++)
				{
					send_buf[3+2*j] = (u8)((u32)data[j]>>4);
					send_buf[3+2*j+1] = (u8)((u32)data[j] & 0x0f)<<4;
					data[j] = 0;
				}
			send_buf[2]=count++;
			xSemaphoreGive(Data_Ready);
		}
	}
}

void DMA_Send_Task(void *pvParameters)
{
		TickType_t time=0;
	static u32 times=0;
	while(1)
	{
		if(xSemaphoreTake(Data_Ready,portMAX_DELAY) == pdTRUE)
		{
			taskENTER_CRITICAL();
			USART_DMACmd(USART3,USART_DMAReq_Tx,ENABLE);
			MYDMA_Enable(DMA1_Channel2);
			
			while(1)
			{
				if(DMA_GetFlagStatus(DMA1_FLAG_TC2)!=RESET)	//�ж�ͨ��2�������
				{
					DMA_ClearFlag(DMA1_FLAG_TC2);//���ͨ��2������ɱ�־
					break; 
				}
			}
			taskEXIT_CRITICAL(); 
			xSemaphoreGive(Send_Ready);
		}
		printf("\r\n\r\n %d \r\n\r\n",times++);
//		vTaskDelayUntil(&time,Send_Delay_Time);
	}
}
