/******************** (C) COPYRIGHT 2018 *****************************************
 * �ļ���  ��sys.c
 * ����    ��ϵͳNVIC�жϷ�������
 * Ӳ������:              
 * �汾    �� 
 * �޸����ڣ� 
 * ����    ��Wu
 * �޸���־��
*********************************************************************************/
#include "sys.h"

//------------------------------------------------------------------------------
/*
 * ��������swgPtb5 
 * ����  ���ṩswgPrt()��ӡ����
 * ����  :  
 * ���  �� 
 */
void swgPtb5(char c) 					
{
	#if 0
	UART5->DR = c;
	while(!(UART5->SR & BIT7));		
	#else
	USART1->DR = c;
	while(!(USART1->SR & BIT7));
	#endif
}


/*
 * ��������swgPtn 
 * ����  ���ṩswgPrt()��ӡ����
 * ����  :  
 * ���  �� 
 */
void swgPtn(char *str)
{
	char *p = str;
	
	while(*p)
	{
		if(*p=='\n')
			swgPtb5('\r');
		swgPtb5(*p);
		p++;
	}
}


/*
 * ��������HBT(u16 a)
 * ����  ��ȡ���ݵĸ�8λֵ
 * ����  ��16λ������
 * ���  �������ݵĸ�8λֵ	
 */
u8 HBT(u16 a)	 //ȡ���߰�λ����
{
	  a&=0xFF00;
	  a>>=8;
	  return a;
}



/*
 * ��������LBT(u16 b)
 * ����  ��ȡ���ݵĵ�8λֵ
 * ����  ��16λ������
 * ���  �������ݵĵ�8λֵ	
 */
u8 LBT(u16 b)	//ȡ���Ͱ�λ����
{
	  b&=0x00FF;
	  return b;
}


/*
 * ��������alex_crc16(unsigned char *buf, unsigned int len)
 * ����  ��16λ���鷽��
 * ����  ��*buf �ַ���  len �ַ�������
 * ���  ��У���	
 */
unsigned int alex_crc16(unsigned char *buf, unsigned int len) 
{
    int i,j;
    unsigned int c, crc = 0xFFFF;
    for (i = 0; i < len; i++){
   	c = *(buf+i) & 0x00FF;
   	crc^=c;
        for(j=0;j<8;j++){
             if (crc & 0x0001)
                 {crc>>=1;crc^=0xA001;}
             else crc>>=1;
        }
    }

    return(crc);	
}

	 
void NVIC_Configuration(void)
{

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 	//����NVIC�жϷ���2:2λ��ռ���ȼ���0-3����2λ��Ӧ���ȼ���0-3��
																										// ����ԽС���ж����ȼ�Խ��
}




/******************* (C) COPYRIGHT 2018 END OF FILE *****************************/
