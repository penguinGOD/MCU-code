#include "stm32f10x.h"
#include "delay.h"
#include "LED.h"
#include "key.h"

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	LED_Init();
	key_init();
	delay_init();
	while(1)
	{
		switch(key_scan())
		{
			case 0:
				(LED0==0)?(LED0=1):(LED0=0);
			break;
			case 1:
				(LED1==0)?(LED1=1):(LED1=0);
			break;
			case 2:
				LED0=1;LED1=1;
			break;
		}
		delay_ms(5);
	}
}
