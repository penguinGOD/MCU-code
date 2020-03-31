#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"

 int main(void)
 {		
 	u16 led0pwmval=4800;
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
 	LED_Init();			     //LED�˿ڳ�ʼ��
 	TIM3_PWM_Init(4999,287);	 //����Ƶ��PWMƵ��=72000000/��arr+1��(psc+1)=50HZ
   	while(1)
	{
 		delay_ms(100);	 
    led0pwmval--;
    if(led0pwmval<4600) led0pwmval=4600;								 
		TIM_SetCompare2(TIM3,led0pwmval);  //   led0pwmval/arr=1-ռ�ձ�
	}	 
 }

