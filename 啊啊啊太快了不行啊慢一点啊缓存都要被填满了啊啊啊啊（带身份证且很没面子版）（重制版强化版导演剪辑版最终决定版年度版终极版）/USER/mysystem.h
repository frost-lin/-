#ifndef __MYSYSTEM_H
#define __MYSYSTEM_H

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
	#define data_len 10
#elif THIS_F__KING_VARIABLE_DECIDES_EVERYTHING==1
	#define data_len 4
#elif THIS_F__KING_VARIABLE_DECIDES_EVERYTHING==2
	#define data_len 5
#endif

#ifndef SEND_BUF_SIZE
#define SEND_BUF_SIZE 3+data_len*2
#endif

#ifndef channelnum
#define channelnum data_len
#endif

#endif
