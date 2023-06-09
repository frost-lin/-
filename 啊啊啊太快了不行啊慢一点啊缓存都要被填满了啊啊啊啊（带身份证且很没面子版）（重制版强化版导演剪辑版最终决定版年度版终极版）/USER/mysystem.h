#ifndef __MYSYSTEM_H
#define __MYSYSTEM_H

#include "stdio.h"	
#include "sys.h" 

#define THIS_F__KING_VARIABLE_DECIDES_EVERYTHING 0 
/**********************************************************
THIS_F__KING_VARIABLE_DECIDES_EVERYTHING
这该死的变量决定了整个程序的功能，可以取3个值
0:足底压力检测模式
1：单独光电模式
2：脊柱侧弯模式
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
