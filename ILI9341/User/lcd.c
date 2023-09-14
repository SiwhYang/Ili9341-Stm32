#include "lcd.h"
#include "stm32f30x.h"
#include "stm32f30x_spi.h"
#include "STDLIB.H"


u8 Gamma_setting [30]  = {0x0F,0x28,0x29,0x0D,0x11,0x09,0x54,
													0xA8,0x46,0x0F,0x1A,0x0E,0x14,0x0C,0x00, // positive gamma setting
													0x00,0x1B,0x1E,0x07,0x13,0x07,0x2A,0x47, // negative gamma setting
													0x39,0x03,0x09,0x0C,0x35,0x3D,0x0F };			

void LCD_Init()	
{
	// init SPI
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE,ENABLE);
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
	// init SCK pin
	GPIO_InitStructure.GPIO_Pin = LCD_SCK_Pin ;
	GPIO_Init(LCD_SCK_Port,&GPIO_InitStructure);
	// init MOSI pin
	GPIO_InitStructure.GPIO_Pin = LCD_MOSI_Pin;
	GPIO_Init(LCD_MOSI_Port,&GPIO_InitStructure);
	// init MISO pin
	GPIO_InitStructure.GPIO_Pin = LCD_MISO_Pin;
	GPIO_Init(LCD_MISO_Port,&GPIO_InitStructure);
	
	// init CS
	GPIO_InitStructure.GPIO_Pin = LCD_CS_Pin ;
	GPIO_Init(LCD_CS_Port,&GPIO_InitStructure);
	
	// init BL
	GPIO_InitStructure.GPIO_Pin = LCD_BackLight_Pin ;
	GPIO_Init(LCD_BackLight_Port,&GPIO_InitStructure);
	
	// init Reset
	GPIO_InitStructure.GPIO_Pin = LCD_Reset_Pin ;
	GPIO_Init(LCD_Reset_Port,&GPIO_InitStructure);
	GPIO_SetBits(LCD_Reset_Port,LCD_Reset_Pin);
	
	// init DC
	GPIO_InitStructure.GPIO_Pin = LCD_DC_Pin ;
	GPIO_Init(LCD_DC_Port,&GPIO_InitStructure);
	
	//LCD_Reset_Off;
	Delay_ms(1);
	LCD_Reset_On;
	Delay_ms(10);
	LCD_Reset_Off;
	Delay_ms(120);
	
	LCD_Write_Command(0xCF);  
	LCD_Write_Data(0x00); 
	LCD_Write_Data(0xC9); //C1 
	LCD_Write_Data(0X30); 
	LCD_Write_Command(0xED);  
	LCD_Write_Data(0x64); 
	LCD_Write_Data(0x03); 
	LCD_Write_Data(0X12); 
	LCD_Write_Data(0X81); 
	LCD_Write_Command(0xE8);  
	LCD_Write_Data(0x85); 
	LCD_Write_Data(0x10); 
	LCD_Write_Data(0x7A); 
	LCD_Write_Command(0xCB);  
	LCD_Write_Data(0x39); 
	LCD_Write_Data(0x2C); 
	LCD_Write_Data(0x00); 
	LCD_Write_Data(0x34); 
	LCD_Write_Data(0x03); 
	LCD_Write_Command(0xF7);  
	LCD_Write_Data(0x20); 
	LCD_Write_Command(0xEA);  
	LCD_Write_Data(0x00); 
	LCD_Write_Data(0x00); 
	LCD_Write_Command(0xC0);    //Power control 
	LCD_Write_Data(0x1B);   //VRH[5:0] 
	LCD_Write_Command(0xC1);    //Power control 
	LCD_Write_Data(0x00);   //SAP[2:0];BT[3:0] 01 
	LCD_Write_Command(0xC5);    //VCM control 
	LCD_Write_Data(0x30); 	 //3F
	LCD_Write_Data(0x30); 	 //3C
	LCD_Write_Command(0xC7);    //VCM control2 
	LCD_Write_Data(0XB7); 
	LCD_Write_Command(0x36);    // Memory Access Control 
	
	
	LCD_Write_Data(0x08); 
	LCD_Write_Command(0x3A);   
	LCD_Write_Data(0x55); 
	LCD_Write_Command(0xB1);   
	LCD_Write_Data(0x00);   
	LCD_Write_Data(0x1A); 
	LCD_Write_Command(0xB6);    // Display Function Control 
	LCD_Write_Data(0x0A); 
	LCD_Write_Data(0xA2); 
	LCD_Write_Command(0xF2);    // 3Gamma Function Disable 
	LCD_Write_Data(0x00); 
	LCD_Write_Command(0x26);    //Gamma curve selected 
	LCD_Write_Data(0x01); 
	/*
	LCD_Write_Command(0xE0);    //Set Gamma 
	LCD_Write_Data(0x0F); 
	LCD_Write_Data(0x2A); 
	LCD_Write_Data(0x28); 
	LCD_Write_Data(0x08); 
	LCD_Write_Data(0x0E); 
	LCD_Write_Data(0x08); 
	LCD_Write_Data(0x54); 
	LCD_Write_Data(0XA9); 
	LCD_Write_Data(0x43); 
	LCD_Write_Data(0x0A); 
	LCD_Write_Data(0x0F); 
	LCD_Write_Data(0x00); 
	LCD_Write_Data(0x00); 
	LCD_Write_Data(0x00); 
	LCD_Write_Data(0x00); 		 
	LCD_Write_Command(0XE1);    //Set Gamma 
	LCD_Write_Data(0x00); 
	LCD_Write_Data(0x15); 
	LCD_Write_Data(0x17); 
	LCD_Write_Data(0x07); 
	LCD_Write_Data(0x11); 
	LCD_Write_Data(0x06); 
	LCD_Write_Data(0x2B); 
	LCD_Write_Data(0x56); 
	LCD_Write_Data(0x3C); 
	LCD_Write_Data(0x05); 
	LCD_Write_Data(0x10); 
	LCD_Write_Data(0x0F); 
	LCD_Write_Data(0x3F); 
	LCD_Write_Data(0x3F); 
	LCD_Write_Data(0x0F); */
	
	
	LCD_Write_Command(0xE0);    //Set Gamma 
	LCD_Write_Data(0x0F); 
	LCD_Write_Data(0x28); 
	LCD_Write_Data(0x29); 
	LCD_Write_Data(0x0D); 
	LCD_Write_Data(0x11); 
	LCD_Write_Data(0x09); 
	LCD_Write_Data(0x54); 
	LCD_Write_Data(0XA8); 
	LCD_Write_Data(0x46); 
	LCD_Write_Data(0x0F); 
	LCD_Write_Data(0x1A); 
	LCD_Write_Data(0x0E); 
	LCD_Write_Data(0x14); 
	LCD_Write_Data(0x0C); 
	LCD_Write_Data(0x00); 		 
	LCD_Write_Command(0XE1);    //Set Gamma 
	LCD_Write_Data(0x00);
	LCD_Write_Data(0x1B); 
	LCD_Write_Data(0x1E); 
	LCD_Write_Data(0x07); 
	LCD_Write_Data(0x13); 
	LCD_Write_Data(0x07); 
	LCD_Write_Data(0x2A); 
	LCD_Write_Data(0x47); 
	LCD_Write_Data(0x39); 
	LCD_Write_Data(0x03); 
	LCD_Write_Data(0x09); 
	LCD_Write_Data(0x0C); 
	LCD_Write_Data(0x35); 
	LCD_Write_Data(0x3D); 
	LCD_Write_Data(0x0F); 
	 
	
	
	LCD_Write_Command(0x2B); 
	LCD_Write_Data(0x00);
	LCD_Write_Data(0x00);
	LCD_Write_Data(0x01);
	LCD_Write_Data(0x3f);
	LCD_Write_Command(0x2A); 
	LCD_Write_Data(0x00);
	LCD_Write_Data(0x00);
	LCD_Write_Data(0x00);
	LCD_Write_Data(0xef);	 
	LCD_Write_Command(0x11); //Exit Sleep
	Delay_ms(120);
	LCD_Write_Command(0x29); //display on		

}

void SPIv_WriteData(u8 Data)
{

	for(int i = 0 ;i<8;i++)
	{
		LCD_SCK_0;
		if (Data&0x80)
		{
			LCD_MOSI_1;
		}
		else 
		{
			LCD_MOSI_0;
		}
		LCD_SCK_1;
		Data <<=1;
		}
}

void LCD_Write_Data(u8 data)
{
    LCD_CS_Enable;
		LCD_DC_Data;
    SPIv_WriteData(data);
    LCD_CS_Disable;
}

void LCD_Write_Data16(u16 data)
{
    LCD_CS_Enable;
		LCD_DC_Data;
    SPIv_WriteData(data>>8);
    SPIv_WriteData(data);
		LCD_CS_Disable;
}


void LCD_Write_Command(u8 command)
{
    LCD_CS_Enable;
		LCD_DC_Command;
    SPIv_WriteData(command);
    LCD_CS_Disable;
}


void LCD_SetCursor(u16 Xpos, u16 Ypos)
{
	LCD_Write_Command(LCD_SetXCmd);
	LCD_Write_Data( Xpos >> 8);
	LCD_Write_Data( Xpos & 0xFF);
	LCD_Write_Command(LCD_SetYCmd);
	LCD_Write_Data( Ypos >> 8);
	LCD_Write_Data( Ypos & 0xFF);
}

void LCD_Clear(u16 color)
{
		int index;
    u32 totalpoint = LCD_Width;
    totalpoint *= LCD_Height;    // get number full point
    LCD_SetCursor(0x00, 0x0000);    
    LCD_Write_Command(LCD_WriteGramCmd);      
    for (index = 0; index < totalpoint; index++)
    {
        LCD_Write_Data16(color);
    }
}

void LCD_showPattern(Node* first)
{     
		Node* node = first;
		while (node != NULL) 
		{
			node = node->nextnode;
      LCD_Write_Data16(node->data);
    }
}




void LCD_setGamma(Node_8* first_8, u8* Gamma_setting)
{
	Node_8* node_8 = first_8;
	LCD_Write_Command(0xE0);
	int i = 0;
		while (node_8 != NULL && i <30) 
		{
			if(i==15)
				{
					LCD_Write_Command(0xE1);
					LCD_Write_Data(node_8->data);
					*(Gamma_setting + i) = node_8->data; 
					node_8 = node_8->nextnode_8;
					i++;
				}				
			else
				{
					LCD_Write_Data(node_8->data);
					*(Gamma_setting + i) = node_8->data; 
					node_8 = node_8->nextnode_8;
					i++;
				}		
		}
}

/*
void LCD_TestSetGamma(u8* PositiveGamma_setting)
{

}
*/





