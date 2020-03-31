# include "stm32f10x.h"
//# include "srting.h"
# include "stdio.h"
# include "exti.h"
# include "key.h"
#include "timer.h"
#include "lcd.h"
#include "usart.h"

//#define length (69.32+28.70)/2			//��λ mm
#define LED_ON  GPIO_ResetBits(GPIOC,GPIO_Pin_13);
#define LED_OFF GPIO_SetBits(GPIOC,GPIO_Pin_13);
//ѭ����ʽ��ʱ
void Delay_nms(u16 time)
{
	u16 i=0;
	while(time--)
	{
		i=12000;
		while(i--);
	}
}

//����1 GPIO��ʼ��
void GPIO_USARTX_Config(USART_TypeDef *USARTx)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	if(USARTx==USART1)
	{
		//TX
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&GPIO_InitStructure);
		
		//RX
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOC,&GPIO_InitStructure);
	}
}

	int Time_us=0;
	int Time_ms=0;
//	int Key=1;
	float Time_output=0.0;
int main(void)
{
//	int times,t;
//	int len=0;//�ַ�������
//	volatile float speed=0.0;
//float length=5.0;
	
	LEDInit();
//	delay_init();	   //��ʱ������ʼ��	  
//	uart_init(115200);
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 		//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
//	OpticalKey_1_Init();
//	OpticalKey_2_Init();
	TIM3_Int_Init(5-1,72-1);				//5us��ʱһ��
	EXTIX_Init();
	
	while(1)
	{
		//PC13 LED shift
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		Delay_nms(50);
		GPIO_SetBits(GPIOC,GPIO_Pin_13);
		Delay_nms(50);
		
//		if(USART_RX_STA&0x8000)
//		{					   
//			len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
//			printf("\r\n�����͵���ϢΪ:\r\n\r\n");
//			for(t=0;t<len;t++)
//			{
//				USART_SendData(USART1, USART_RX_BUF[t]);//�򴮿�1��������
//				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
//			}
//			printf("\r\n\r\n");//���뻻��
//			USART_RX_STA=0;
//		}
//		else
//		{
//			times++;
//			if(times%5000==0)
//			{
//				printf("\r\nSTM32 F103C8T6 USART Lab\r\n");
//				//printf("copy\r\n\r\n");
//			}
//			if(times%200==0)
//				printf("����������,�Իس�������\n");
//			if(times%30==0)
//				LED_ON;
//			if(times%60==0)
//			LED_OFF;
//			Delay_nms(10);
		}
		
		
//		Key=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1);
//		if(Key==0)
//		GPIO_ResetBits(GPIOC,GPIO_Pin_13);
//		if(Key==1)
//		GPIO_SetBits(GPIOC,GPIO_Pin_13);
		
		//speed=(length)/(Time_output);
}
