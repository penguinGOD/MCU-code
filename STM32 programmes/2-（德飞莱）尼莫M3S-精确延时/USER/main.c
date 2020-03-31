/*-------------------------------------------------------------------------------
文件名称：main.c
文件描述：控制LED2，LED3闪烁，使用SysTick定时器做精确延时
硬件平台：尼莫M3S开发板
编写整理：shifang
固件库  ：V3.5
技术论坛：www.doflye.net
备    注：通过简单修改可以移植到其他开发板，部分资料来源于网络。
---------------------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "led.h"
#include "delay.h"

int main(void)
{

LED_Init(); //初始化LED
SysTick_Init();//初始化延时时钟

LED1_OFF;;
LED2_ON;

LED3_OFF;
Delay_ms(1000);//延时1S
while(1)
 {
  Delay_ms(1000);//延时1000ms
	LED1_REV;
	LED2_REV;//LED2取反
	LED3_REV;//LED3取反
 } 
}
/*----------------------德飞莱 技术论坛：www.doflye.net--------------------------*/
