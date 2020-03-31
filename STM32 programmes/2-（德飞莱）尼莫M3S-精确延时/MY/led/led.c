/*-------------------------------------------------------------------------------
�ļ����ƣ�led.c
�ļ�����������Ӳ����������LED�˿ڣ��򿪶�Ӧ�ļĴ���        
��    ע����
---------------------------------------------------------------------------------*/
#include "led.h"
/*-------------------------------------------------------------------------------
�������ƣ�LED_Init
������������ʼ��LED��ض˿ڣ��򿪶˿�ʱ�ӣ����ö˿����  
�����������
���ز�������
��    ע����
---------------------------------------------------------------------------------*/
void LED_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//��PB��ʱ��
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);//��PE��ʱ��
	
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOC, ENABLE);
	

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;//PB5,PE5��������
	
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�˿��ٶ�
	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�˿�ģʽ����Ϊ�������ģʽ
	
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ����Ӧ�Ķ˿�
  GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOC, &GPIO_InitStructure );
}
/*----------------------�·��� ������̳��www.doflye.net--------------------------*/
