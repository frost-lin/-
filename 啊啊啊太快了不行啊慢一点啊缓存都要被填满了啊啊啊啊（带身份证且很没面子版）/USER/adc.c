 #include "adc.h"
 #include "delay.h"
 #include "system.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK 精英STM32开发板
//ADC 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/7
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
	

u16 ADC_ConvertedValue[channelnum]={0};		   
//初始化ADC
//这里我们仅以规则通道为例															   
void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1	, ENABLE );	  //使能ADC1通道时钟
	
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
 
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

#if THIS_F__KING_VARIABLE_DECIDES_EVERYTHING==0
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOB, &GPIO_InitStructure);
#elif  THIS_F__KING_VARIABLE_DECIDES_EVERYTHING==1	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOA, &GPIO_InitStructure);
#elif  THIS_F__KING_VARIABLE_DECIDES_EVERYTHING==2	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;  
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOA, &GPIO_InitStructure);
#endif

	ADC_DeInit(ADC1);  //复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;	//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = channelnum;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

  
	ADC_Cmd(ADC1, ENABLE);	//使能指定的ADC1
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
	
	ADC_ResetCalibration(ADC1);	//使能复位校准  
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束
	
	ADC_StartCalibration(ADC1);	 //开启AD校准
 
	while(ADC_GetCalibrationStatus(ADC1));	 //等待校准结束
 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能

}				  
////获得ADC值
//void Get_Adc(float *adc1, float *adc2)   
//{
//  	                                                                              //设置指定ADC的规则组通道，一个序列，采样时间
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_55Cycles5);//ADC1,ADC通道,采样时间为239.5周期	  			  


//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能	

//	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束

//	*adc1 = ADC_GetConversionValue(ADC1)*3.3/4096;	//返回最近一次ADC1规则组的转换结果
//	
//	
//	ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 1, ADC_SampleTime_55Cycles5);//ADC1,ADC通道,采样时间为239.5周期	  			  

//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能	

//	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束

//	*adc2 = ADC_GetConversionValue(ADC1)*3.3/4096;	//返回最近一次ADC1规则组的转换结果
//	
//	delay_ms(1);
//	
//}
	 
