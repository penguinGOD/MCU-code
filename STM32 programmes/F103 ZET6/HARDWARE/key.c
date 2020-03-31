#include "key.h"
#include "delay.h"
void key_init()
{
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);//使能PORTA,PORTE时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4|GPIO_Pin_3;//KEY0-KEY1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE4,3

	//初始化 WK_UP-->GPIOA.0	  下拉输入
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0设置成输入，默认下拉	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.0
}

unsigned int key_scan()
{
	if(KEY0==0||KEY1==0|KEY_UP==1)
	{
		delay_ms(10);
		if(KEY0==0)
		{
			while(KEY0!=0);
			return 0;
		}
		else if(KEY1==0)
		{	
			while(KEY1!=0);
			return 1;
		}
		else if(KEY_UP==1)
		{	
			while(KEY_UP!=1);
			return 2;
		}
	}
	return 3;	//none key pressed
}
