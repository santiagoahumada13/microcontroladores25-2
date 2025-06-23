#include "SysTick_Delay.h"

void SysTick_Init()
{
	SysTick->VAL=0;
	SysTick->CTRL=0x05;
}

void delay_s(volatile float time)
{
	SysTick->VAL=0;
		volatile float N= time*8e6;
	SysTick->LOAD=N-1;
	while(!(SysTick->CTRL & (1<<16)));
	return;
}