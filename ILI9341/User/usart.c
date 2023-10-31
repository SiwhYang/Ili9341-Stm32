#include "usart.h"
#include "stm32f30x_usart.h"
#include "list.h"
#include "lcd.h"


u8 opcode = 0x00;
u8 data = 0x00;
u16 combined_color = 0x0000;
u8 gamma_setting = 0xFF; // 0x00 cause error 
extern u8 Gamma_setting[15];

extern double CCM[9];
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
		data = (inputcommand  )& 0xF;
		
		switch (opcode)	
		{
			case 0x01 :
				combined_color = ((combined_color & ~0x000F)) | data;			
				break;
			case 0x02 :
				combined_color = ((combined_color & ~0x00F0)) | data <<4 ;
				break;
			case 0x03 :
				combined_color = ((combined_color & ~0x0F00)) | data <<8;
				break;
			case 0x04:
				combined_color = ((combined_color & ~0xF000)) | data <<12;
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
				//Push_back(Gamma_mapping(combined_color));
			break;
			case 0x08:
				LCD_showPattern(first);
				FreeList(first);
				break;
			case 0x09:
				for (int i = 0; i < 30 ; i ++)
				{
					USART_SendData(USART3,*(Gamma_setting + i));
					Delay_ms(1);
				}
				break;	
			case 0x0A :
				gamma_setting = ((gamma_setting & ~0x0F)) | data;
				break;
			case 0x0B :
				gamma_setting = ((gamma_setting & ~0xF0)) | data <<4 ;
				break;
			case 0x0C :
				LCD_setGamma(first_8, Gamma_setting);
				FreeList_8(first_8);
				break;
			case 0x0D :
				Push_back_8(gamma_setting);
				break;
			case 0x0E :
				Push_back(CCM_Mapping(combined_color,CCM));
				break;	
			case 0x0F :
				NVIC_SystemReset();
				break;	
			}
		USART_SendData(USART3,inputcommand);
	}
}


