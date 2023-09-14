#ifndef __LCD_H__
#define __LCD_H__
#include "stm32f30x.h"
#include "delay.h"
#include "list.h"



// LCD Chip select
#define LCD_CS_Port 	 GPIOA
#define LCD_CS_Pin  	 GPIO_Pin_0
// LCD Reset
#define LCD_Reset_Port GPIOA
#define LCD_Reset_Pin  GPIO_Pin_1
// LCD Command or Data port
#define LCD_DC_Port 	 GPIOA
#define LCD_DC_Pin     GPIO_Pin_2
// LCD SPI input pin
#define LCD_MOSI_Port  GPIOA
#define LCD_MOSI_Pin	 GPIO_Pin_3
#define LCD_SCK_Port   GPIOA
#define LCD_SCK_Pin	   GPIO_Pin_4
// LCD BackLight port
#define LCD_BackLight_Port GPIOA
#define LCD_BackLight_Pin GPIO_Pin_5
// LCD output
#define LCD_MISO_Port  GPIOA
#define LCD_MISO_Pin	 GPIO_Pin_6

// LCD usart, we use usart3 with pc10 as tx px11 as rx (for mcu)  


// Define some useful switch function
#define LCD_BackLight_Enable  GPIO_SetBits(LCD_BackLight_Port,LCD_BackLight_Pin)
#define LCD_BackLight_Disable GPIO_ResetBits(LCD_BackLight_Port,LCD_BackLight_Pin)
/*
#define LCD_CS_Enable  GPIO_ResetBits(LCD_CS_Port,LCD_CS_Pin)
#define LCD_CS_Disable GPIO_SetBits(LCD_CS_Port,LCD_CS_Pin)
#define LCD_DC_Data    GPIO_SetBits(LCD_DC_Port,LCD_DC_Pin)
#define LCD_DC_Command GPIO_ResetBits(LCD_DC_Port,LCD_DC_Pin)
#define LCD_Reset_Off GPIO_SetBits(LCD_Reset_Port,LCD_Reset_Pin)
#define LCD_Reset_On GPIO_ResetBits(LCD_Reset_Port,LCD_Reset_Pin)
#define LCD_SCK_1 GPIO_SetBits(LCD_SCK_Port,LCD_SCK_Pin)
#define LCD_SCK_0 GPIO_ResetBits(LCD_SCK_Port,LCD_SCK_Pin)
#define LCD_MOSI_1 GPIO_SetBits(LCD_MOSI_Port,LCD_MOSI_Pin)
#define LCD_MOSI_0 GPIO_ResetBits(LCD_MOSI_Port,LCD_MOSI_Pin)
*/

#define LCD_CS_Disable  LCD_CS_Port->BSRR = LCD_CS_Pin
#define LCD_CS_Enable LCD_CS_Port->BRR = LCD_CS_Pin
#define LCD_DC_Data    LCD_DC_Port->BSRR = LCD_DC_Pin
#define LCD_DC_Command LCD_DC_Port->BRR = LCD_DC_Pin
#define LCD_Reset_Off LCD_Reset_Port->BSRR = LCD_Reset_Pin
#define LCD_Reset_On LCD_Reset_Port->BRR = LCD_Reset_Pin
#define LCD_MOSI_1 LCD_MOSI_Port->BSRR = LCD_MOSI_Pin
#define LCD_MOSI_0 LCD_MOSI_Port->BRR = LCD_MOSI_Pin
#define LCD_SCK_1 LCD_SCK_Port->BSRR = LCD_SCK_Pin
#define LCD_SCK_0 LCD_SCK_Port->BRR = LCD_SCK_Pin

// Define some useful command 
#define Dummy_Byte 0xFFFF  
#define LCD_WriteGramCmd 0x2C
#define LCD_SetXCmd 0X2A
#define LCD_SetYCmd 0x2B
#define LCD_Width 240
#define LCD_Height 320
#define WHITE           0xFFFF
#define BLACK           0x0000
#define BLUE            0x001F
#define BRED            0XF81F
#define GRED            0XFFE0
#define GBLUE           0X07FF
#define RED             0xF800
#define MAGENTA         0xF81F
#define GREEN           0x07E0
#define CYAN            0x7FFF
#define YELLOW          0xFFE0
#define BROWN           0XBC40  
#define BRRED           0XFC07  
#define GRAY            0X8430  



// Define Init
void LCD_Init();
// Define communication
void SPIv_WriteData(u8 Data);
void LCD_Write_Command(u8 input);
void LCD_Write_Data(u8 input);
void LCD_Write_Data16(u16 data);
// Define LCD function
void LCD_SetCursor(u16 Xpos, u16 Ypos);
void LCD_Clear(u16 color);
void LCD_showPattern(Node* first);
// modify gamma
void LCD_setGamma(Node_8* first_8, u8 *Gamma_setting);
void LCD_TestSetGamma(u8* PositiveGamma_setting);

#endif

