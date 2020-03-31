#ifndef COM_PROP_H
#define COM_PROP_H
#include "comLib.h"

/*******************************************************************************
//帧属性 //限制大小64位
*******************************************************************************/
 #define  FEED_DOG     1
 #define  HANDLE_ROCK  2
 #define  HANDLE_KEY   3
 #define  KEYBOARD     4

 #define MOTOR_PARA_SEND      5
 #define AIM_STATE_SEND       6

 #define SPEED_PID_SEND       7
 #define POS_PID_SEND         8
 #define CURRENT_PID_SEND     9

 #define EXT_IO_SEND          17
 #define SENSOR_SEND          18
 #define EXT_PARA_SEND        19

 #define SAMPLE_VALUE_STORAGE 20 

/*******************************************************************************
															  指令函数
*******************************************************************************/
void TestSend();

/*******************************************************************************
															  执行函数
*******************************************************************************/


#endif // COM_PROP_H
