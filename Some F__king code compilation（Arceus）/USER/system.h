#ifndef __SYSTEM_H
#define __SYSTEM_H
#include "stdio.h"	
#include "sys.h" 

#define THIS_F__KING_VARIABLE_DECIDES_EVERYTHING 0
/**********************************************************
THIS_F__KING_VARIABLE_DECIDES_EVERYTHING
������ı�����������������Ĺ��ܣ�����ȡ3��ֵ
0:���ѹ�����ģʽ
1���������ģʽ
2����������ģʽ
***********************************************************/

#if THIS_F__KING_VARIABLE_DECIDES_EVERYTHING==0
	#define data_len 8*9
	#define channelnum 9
#elif THIS_F__KING_VARIABLE_DECIDES_EVERYTHING==1
	#define data_len 4
#elif THIS_F__KING_VARIABLE_DECIDES_EVERYTHING==2
	#define data_len 5
#endif
#define SEND_BUF_SIZE 3+data_len*2

#ifndef channelnum
#define channelnum data_len
#endif

#endif

