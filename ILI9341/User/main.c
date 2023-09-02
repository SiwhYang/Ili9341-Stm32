#include "main.h"
#include "led.h"
#include "delay.h"
#include "usart.h"
#include "lcd.h"


int main(void)	
{
	
	LCD_Init();
	Usart_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
	LCD_BackLight_Enable;
	
	while (1)
		{
		
		}
	return 0;
}


