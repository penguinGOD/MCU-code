#include "key.h"
#include "delay.h"
void key_init()
{
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);//ʹ��PORTA,PORTEʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4|GPIO_Pin_3;//KEY0-KEY1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOE4,3

	//��ʼ�� WK_UP-->GPIOA.0	  ��������
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0���ó����룬Ĭ������	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.0
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
