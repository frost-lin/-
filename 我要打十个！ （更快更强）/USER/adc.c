 #include "adc.h"
 #include "delay.h"
 #include "system.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK ��ӢSTM32������
//ADC ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/7
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
	

u16 ADC_ConvertedValue[channelnum]={0};		   
//��ʼ��ADC
//�������ǽ��Թ���ͨ��Ϊ��															   
void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1	, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;			           
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&ADC_ConvertedValue;	            
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;					            
	DMA_InitStructure.DMA_BufferSize = channelnum;						 //
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;	 
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;				 //
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;      //
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;		//
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;					//
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	
  DMA_Cmd( DMA1_Channel1, ENABLE );
 
	//DMA_ITConfig(DMA1_Channel1,DMA_IT_TC, ENABLE);
 
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

#if THIS_F__KING_VARIABLE_DECIDES_EVERYTHING==0
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOB, &GPIO_InitStructure);
#elif  THIS_F__KING_VARIABLE_DECIDES_EVERYTHING==1	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);
#elif  THIS_F__KING_VARIABLE_DECIDES_EVERYTHING==2	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif

	ADC_DeInit(ADC1);  //��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = channelnum;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

  
	ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC1
#if THIS_F__KING_VARIABLE_DECIDES_EVERYTHING==0
	ADC_RegularChannelConfig( ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5 );
	ADC_RegularChannelConfig( ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5 );
	ADC_RegularChannelConfig( ADC1, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5 );
	ADC_RegularChannelConfig( ADC1, ADC_Channel_3, 4, ADC_SampleTime_55Cycles5 );
	ADC_RegularChannelConfig( ADC1, ADC_Channel_4, 5, ADC_SampleTime_55Cycles5 );
	ADC_RegularChannelConfig( ADC1, ADC_Channel_5, 6, ADC_SampleTime_55Cycles5 );
	ADC_RegularChannelConfig( ADC1, ADC_Channel_6, 7, ADC_SampleTime_55Cycles5 );
	ADC_RegularChannelConfig( ADC1, ADC_Channel_7, 8, ADC_SampleTime_55Cycles5 );
	ADC_RegularChannelConfig( ADC1, ADC_Channel_8, 9, ADC_SampleTime_55Cycles5 );
	ADC_RegularChannelConfig( ADC1, ADC_Channel_9, 10, ADC_SampleTime_55Cycles5 );
#elif  THIS_F__KING_VARIABLE_DECIDES_EVERYTHING==1	
	ADC_RegularChannelConfig( ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5 );
	ADC_RegularChannelConfig( ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5 );
	ADC_RegularChannelConfig( ADC1, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5 );
	ADC_RegularChannelConfig( ADC1, ADC_Channel_3, 4, ADC_SampleTime_55Cycles5 );
#elif  THIS_F__KING_VARIABLE_DECIDES_EVERYTHING==2	
	ADC_RegularChannelConfig( ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5 );
	ADC_RegularChannelConfig( ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5 );
	ADC_RegularChannelConfig( ADC1, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5 );
	ADC_RegularChannelConfig( ADC1, ADC_Channel_3, 4, ADC_SampleTime_55Cycles5 );
	ADC_RegularChannelConfig( ADC1, ADC_Channel_4, 5, ADC_SampleTime_55Cycles5 );
#endif

	ADC_DMACmd( ADC1, ENABLE );
	
	ADC_Cmd( ADC1, ENABLE );
	
	ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼  
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����
	
	ADC_StartCalibration(ADC1);	 //����ADУ׼
 
	while(ADC_GetCalibrationStatus(ADC1));	 //�ȴ�У׼����
 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������

}				  
////���ADCֵ
//void Get_Adc(float *adc1, float *adc2)   
//{
//  	                                                                              //����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_55Cycles5);//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	  			  


//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������	

//	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������

//	*adc1 = ADC_GetConversionValue(ADC1)*3.3/4096;	//�������һ��ADC1�������ת�����
//	
//	
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 1, ADC_SampleTime_55Cycles5);//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	  			  

//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������	

//	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������

//	*adc2 = ADC_GetConversionValue(ADC1)*3.3/4096;	//�������һ��ADC1�������ת�����
//	
//	delay_ms(1);
//	
//}
	 
