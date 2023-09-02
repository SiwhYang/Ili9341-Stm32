#ifndef _DELAY_H_
#define _DELAY_H_
#include "stm32f30x.h"

void Delay_init(void);
void Delay_s(u16 s);
void Delay_ms(u16 ms);
void Delay_us(u16 us);
void Delay_110ns(u16 ns);



#endif

