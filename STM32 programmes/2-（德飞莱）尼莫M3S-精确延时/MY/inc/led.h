#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

#define LED1_OFF GPIO_SetBits(GPIOC,GPIO_Pin_13)
#define LED1_ON GPIO_ResetBits(GPIOC,GPIO_Pin_13)
#define LED1_REV GPIO_WriteBit(GPIOC, GPIO_Pin_13,(BitAction)(1-(GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13))))

#define LED2_OFF GPIO_SetBits(GPIOE,GPIO_Pin_5)
#define LED2_ON GPIO_ResetBits(GPIOE,GPIO_Pin_5)
#define LED2_REV GPIO_WriteBit(GPIOE, GPIO_Pin_5,(BitAction)(1-(GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_5))))

#define LED3_OFF GPIO_SetBits(GPIOB,GPIO_Pin_5)
#define LED3_ON GPIO_ResetBits(GPIOB,GPIO_Pin_5)
#define LED3_REV GPIO_WriteBit(GPIOB, GPIO_Pin_5,(BitAction)(1-(GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_5))))

void LED_Init(void);

#endif
/*----------------------�·��� ������̳��www.doflye.net--------------------------*/
