#include "systick.h"

void delay_init(void)
{
	SysTick->CTRL = 0;
}
//delay us not right, +3 or 2 us.
void delay_us(uint32_t us) {
    SysTick->LOAD = (72 * us) - 1; //set time
    SysTick->VAL = 0; //reset counter
    SysTick->CTRL = 5; //internal clock and turn on
    while (!(SysTick->CTRL & (1 << 16)));
    SysTick->CTRL = 0;
}
void delay_ms(uint32_t ms) {
    while (ms--) delay_us(1000);
}

void delay_s(uint32_t s)
{
	while(s--) delay_ms(1000);
}