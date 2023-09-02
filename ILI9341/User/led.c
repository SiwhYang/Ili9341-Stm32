#include "led.h"
#include "stm32f30x.h"


void LED_init()
{

GPIO_InitTypeDef GPIO_InitStructure;
RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE,ENABLE);
GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_Init(GPIOE,&GPIO_InitStructure);


GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
GPIO_Init(GPIOE,&GPIO_InitStructure);
	
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
GPIO_Init(GPIOE,&GPIO_InitStructure);
	
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
GPIO_Init(GPIOE,&GPIO_InitStructure);
	
GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
GPIO_Init(GPIOE,&GPIO_InitStructure);

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
GPIO_Init(GPIOE,&GPIO_InitStructure);

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
GPIO_Init(GPIOE,&GPIO_InitStructure);

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
GPIO_Init(GPIOE,&GPIO_InitStructure);
}



void LED_All_TurnOn()
{
	GPIO_SetBits(GPIOE,GPIO_Pin_8);
	GPIO_SetBits(GPIOE,GPIO_Pin_9);
	GPIO_SetBits(GPIOE,GPIO_Pin_10);
	GPIO_SetBits(GPIOE,GPIO_Pin_11);
	GPIO_SetBits(GPIOE,GPIO_Pin_12);
	GPIO_SetBits(GPIOE,GPIO_Pin_13);
	GPIO_SetBits(GPIOE,GPIO_Pin_14);
	GPIO_SetBits(GPIOE,GPIO_Pin_15);
	
}


void LED_All_TurnOff(void)
{
	GPIO_ResetBits(GPIOE,GPIO_Pin_8);
	GPIO_ResetBits(GPIOE,GPIO_Pin_9);
	GPIO_ResetBits(GPIOE,GPIO_Pin_10);
	GPIO_ResetBits(GPIOE,GPIO_Pin_11);
	GPIO_ResetBits(GPIOE,GPIO_Pin_12);
	GPIO_ResetBits(GPIOE,GPIO_Pin_13);
	GPIO_ResetBits(GPIOE,GPIO_Pin_14);
	GPIO_ResetBits(GPIOE,GPIO_Pin_15);
}


void LED_All_Loop(int i)
{
	switch(i)
	{
		case 8:
			GPIO_SetBits(GPIOE,GPIO_Pin_8);
			break;
		case 9:
			GPIO_SetBits(GPIOE,GPIO_Pin_9);
			break;
		case 10:
			GPIO_SetBits(GPIOE,GPIO_Pin_10);
			break;
		case 11:
			GPIO_SetBits(GPIOE,GPIO_Pin_11);
			break;
		case 12:
			GPIO_SetBits(GPIOE,GPIO_Pin_12);
			break;
		case 13:
			GPIO_SetBits(GPIOE,GPIO_Pin_13);
			break;
		case 14:
			GPIO_SetBits(GPIOE,GPIO_Pin_14);
			break;
		case 15:
			GPIO_SetBits(GPIOE,GPIO_Pin_15);
			break;
		case 16:
			GPIO_ResetBits(GPIOE,GPIO_Pin_8);
			break;
		case 17:
			GPIO_ResetBits(GPIOE,GPIO_Pin_9);
			break;
		case 18:
			GPIO_ResetBits(GPIOE,GPIO_Pin_10);		
			break;		
		case 19:
			GPIO_ResetBits(GPIOE,GPIO_Pin_11);
			break;
		case 20:
			GPIO_ResetBits(GPIOE,GPIO_Pin_12);
			break;
		case 21:
			GPIO_ResetBits(GPIOE,GPIO_Pin_13);
			break;
		case 22:
			GPIO_ResetBits(GPIOE,GPIO_Pin_14);
			break;
		case 23:
			GPIO_ResetBits(GPIOE,GPIO_Pin_15);
			break;
	}

}




