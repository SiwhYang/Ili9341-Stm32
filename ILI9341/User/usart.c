#include "usart.h"
#include "stm32f30x_usart.h"
#include "list.h"
#include "lcd.h"


u8 opcode = 0x00;
u8 tempcolor = 0x00;
u16 combined_color = 0x0000;
u8 gamma_setting = 0x00;
extern u8 PositiveGamma_setting[15];

/*
extern u8 PositiveGamma_value_VP63 ;
extern u8 PositiveGamma_value_VP62 ;
extern u8 PositiveGamma_value_VP61 ;
extern u8 PositiveGamma_value_VP59 ;
extern u8 PositiveGamma_value_VP57 ;
extern u8 PositiveGamma_value_VP50 ;
extern u8 PositiveGamma_value_VP43 ;
extern u8 PositiveGamma_value_VP29_36 ;
extern u8 PositiveGamma_value_VP20 ;
extern u8 PositiveGamma_value_VP13 ;
extern u8 PositiveGamma_value_VP6 ;
extern u8 PositiveGamma_value_VP4 ;
extern u8 PositiveGamma_value_VP2 ;
extern u8 PositiveGamma_value_VP1 ;
extern u8 PositiveGamma_value_VP0 ;
*/

/*
4 bits opcode 0 - 16 ->>  0x00 - 0x0F 

0 : initial state

1 : first u4 color
2 : second u4 color
3 : third u4 color 
4 : fourth u4 color
5 : start showing pure color

6 : start writting list
7 : pushback
8 : showing pattern from list

9 : start adjust Gamma
10:



*/
extern Node* current, * first, * previous;
extern Node_8* current_8, * first_8, * previous_8;

void Usart_Init(void)	
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	
	RCC_AHBPeriphClockCmd (RCC_AHBPeriph_GPIOC, ENABLE); //enable usart time clock of gpio
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE); // enable usart time clock which locate in APB2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP ;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource10, GPIO_AF_7);
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource11,GPIO_AF_7);
	
	USART_InitStruct.USART_BaudRate = 115200;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //key
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx ;   // key, this has to be set read and recieve, if set only read, it fail at send and receive exp
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1; // key
	USART_InitStruct.USART_WordLength = USART_WordLength_8b; //key
	USART_Init(USART3,&USART_InitStruct);
	USART_Cmd(USART3,ENABLE); // turn on
	
	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE); // second parmeter is set to read for we use read mode of usart1 
	// this meand we turn on read interupt on usart1
	NVIC_InitStruct.NVIC_IRQChannel = USART3_IRQn; //on top header stm32f0x.h with ORQN suffix, means which channel
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;// means enable or not
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;// set PreemptionPriority we have 0-3 because we have group 2, this is arbitrary for now because we have no other  interrupt  
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
	
}



void USART3_printf(Node* first)
{
	Node* node = first;
	while (node != NULL) 
	{
		node = node->nextnode;
		USART_SendData(USART3,(node->data));
	}
}

void USART3_IRQHandler (void)
{
	u8 inputcommand;
	if (USART_GetITStatus(USART3,USART_IT_RXNE))
	{		
		inputcommand = USART_ReceiveData(USART3);
		opcode = (inputcommand >> 4 ) & 0xF; 
		tempcolor = (inputcommand  )& 0xF;
		
		switch (opcode)	
		{
			case 0x01 :
					combined_color = ((combined_color & ~0x000F)) | tempcolor;			
				break;
			case 0x02 :
					combined_color = ((combined_color & ~0x00F0)) | tempcolor <<4 ;
				break;
			case 0x03 :
					combined_color = ((combined_color & ~0x0F00)) | tempcolor <<8;
			break;
			case 0x04:
					combined_color = ((combined_color & ~0xF000)) | tempcolor <<12;
				break;
			case 0x05:
				LCD_Clear(combined_color);
				break;
			case 0x06:
				LCD_SetCursor(0x00, 0x0000);    
				LCD_Write_Command(LCD_WriteGramCmd); 
				break;
			case 0x07:
			  Push_back(combined_color);
				break;
			case 0x08:
				LCD_showPattern(first);
				FreeList(first);
				break;
			case 0x09:
				for (int i = 0; i < 15 ; i ++)
				{
					USART_SendData(USART3,*(PositiveGamma_setting + i));
					Delay_ms(1);
				}
					break;	
				case 0x0A :
					gamma_setting = ((gamma_setting & ~0x0F)) | tempcolor;
					break;
				case 0x0B :
					gamma_setting = ((gamma_setting & ~0xF0)) | tempcolor <<4 ;
					break;
				case 0x0C :
					LCD_setPositiveGamma(first_8, PositiveGamma_setting);
					FreeList_8(first_8);
				break;
				case 0x0D :
					Push_back_8(gamma_setting);
					break;
				case 0x0E :
					LCD_Write_Command(0xE0);    //Set Gamma 
					LCD_Write_Data(0x00); 
					LCD_Write_Data(0x28); 
					LCD_Write_Data(0x20); 
					LCD_Write_Data(0x0D); 
					LCD_Write_Data(0x11); 
					LCD_Write_Data(0x00); 
					LCD_Write_Data(0x50); 
					LCD_Write_Data(0XA8); 
					LCD_Write_Data(0x46); 
					LCD_Write_Data(0x0F); 
					LCD_Write_Data(0x10); 
					LCD_Write_Data(0x00); 
					LCD_Write_Data(0x00); 
					LCD_Write_Data(0x0C); 
					LCD_Write_Data(0x00); 
/*				
					LCD_Write_Command(0XE1);    //Set Gamma 
					LCD_Write_Data(0x00);
					LCD_Write_Data(0x1B); 
					LCD_Write_Data(0x1E); 
					LCD_Write_Data(0x00); 
					LCD_Write_Data(0x13); 
					LCD_Write_Data(0x00); 
					LCD_Write_Data(0x20); 
					LCD_Write_Data(0x47); 
					LCD_Write_Data(0x39); 
					LCD_Write_Data(0x03); 
					LCD_Write_Data(0x00); 
					LCD_Write_Data(0x0C); 
					LCD_Write_Data(0x30); 
					LCD_Write_Data(0x30); 
					LCD_Write_Data(0x0F); 
					*/
					break;	
				case 0x0F :
					LCD_Write_Command(0xE0);
					LCD_Write_Data(0xFF); 
					LCD_Write_Data(0xF); 
					LCD_Write_Data(0xFF); 
					LCD_Write_Data(0xFF); 
					LCD_Write_Data(0xFF); 
					LCD_Write_Data(0xFF); 
					LCD_Write_Data(0xFF); 
					LCD_Write_Data(0xFF); 
					LCD_Write_Data(0xFF); 
					LCD_Write_Data(0xFF); 
					LCD_Write_Data(0xFF); 
					LCD_Write_Data(0xFF); 
					LCD_Write_Data(0xFF); 
					LCD_Write_Data(0xFF); 
					LCD_Write_Data(0xFF); 
/*				
					LCD_Write_Command(0xE1);
					LCD_Write_Data(0xFF); 
					LCD_Write_Data(0xFF); 
					LCD_Write_Data(0xFF); 
					LCD_Write_Data(0xFF); 
					LCD_Write_Data(0xFF); 
					LCD_Write_Data(0xFF); 
					LCD_Write_Data(0xFF); 
					LCD_Write_Data(0xFF); 
					LCD_Write_Data(0xFF); 
					LCD_Write_Data(0xFF); 
					LCD_Write_Data(0xFF); 
					LCD_Write_Data(0xFF); 
					LCD_Write_Data(0xFF); 
					LCD_Write_Data(0xFF); 
					LCD_Write_Data(0xFF); 	
					*/
					break;	
		}
		USART_SendData(USART3,inputcommand);
		}
}


