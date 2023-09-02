#include "delay.h"
#include "stm32f30x.h"


void Delay_init()
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	 //choose HCLK and divided by 8
}


void Delay_ms(u16 ms)
{
	u32 temp;
	SysTick->LOAD = 9000*ms; // actual time convert
	SysTick->VAL = 0x00; // set value in register to 0
	SysTick->CTRL=0x01; // set first bit of ctrl to 1 -> enable the counting
	do
	{
	temp = SysTick->CTRL;
	}while((temp&0x01)&&(!(temp&(1<<16)))); 
	// check first bit is 1 (still working), check if 16th bit is 1 (counting finish) 
		SysTick->CTRL = 0x00;
		SysTick->VAL = 0x00;
}




void Delay_us(u16 us)
{
	u32 temp;
	SysTick->LOAD = 9*us; // actual time convert
	SysTick->VAL = 0x00; // set value in register to 0
	SysTick->CTRL=0x01; // set first bit of ctrl to 1 -> enable the counting
	do
	{
	temp = SysTick->CTRL;
	}while((temp&0x01)&&(!(temp&(1<<16)))); 
	// check first bit is 1 (still working), check if 16th bit is 1 (counting finish) 
		SysTick->CTRL = 0x00;
		SysTick->VAL = 0x00;
}



void Delay_110ns(u16 ns)
{
	u32 temp;
	SysTick->LOAD = ns; // actual time convert
	SysTick->VAL = 0x00; // set value in register to 0
	SysTick->CTRL=0x01; // set first bit of ctrl to 1 -> enable the counting
	do
	{
	temp = SysTick->CTRL;
	}while((temp&0x01)&&(!(temp&(1<<16)))); 
	// check first bit is 1 (still working), check if 16th bit is 1 (counting finish) 
		SysTick->CTRL = 0x00;
		SysTick->VAL = 0x00;
}

//CTRL is 32 bit 
//first bit enable the start counting when it is 1
//16th bit denote the counting finish when it is 1




/*

When enabled, the timer

¡ñcounts down from the reload value to zero,
¡ñreloads (wraps to) the value in the STK_RVR on the next clock cycle,
¡ñthen decrements on subsequent clock cycles.

Writing a value of zero to the STK_RVR disables the counter on the next wrap. 
When the counter transitions to zero, the COUNTFLAG status bit is set to 1.
Reading STK_CSR clears the COUNTFLAG bit to 0
Writing to the STK_CVR clears the register and the COUNTFLAG status bit to 0. The write does not trigger the SysTick exception logic.
Reading the register returns its value at the time it is accessed.
When the processor is halted for debugging the counter does not decrement





*/
