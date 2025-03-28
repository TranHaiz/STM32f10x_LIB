#ifndef SYSTICK_H__H
#define SYSTICK_H_

#include <stm32f10x.h>

void	delay_init(void);
void delay_us(uint32_t us);
void delay_ms(uint32_t ms);
void delay_s(uint32_t s);

#endif