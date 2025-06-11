#include "gpio.h"

////-----------CLOCK-------------------------------
unsigned int get_system_clock(void) {
    unsigned int sysclk;
    unsigned int clk_src = (RCC->CFGR >> 2) & 0x3; // L?y bit SWS (2:3)

    if (clk_src == 0) {  
        sysclk = 8000000; // HSI = 8 MHz
    } 
    else if (clk_src == 1) {  
        sysclk = 8000000; // HSE = 8 MHz (gi? s?)
    } 
    else if (clk_src == 2) {  
        unsigned int pll_src = (RCC->CFGR >> 16) & 0x1; // PLLSRC (bit 16)
        unsigned int pll_mul = ((RCC->CFGR >> 18) & 0xF) + 2; // PLLMUL (18:21)

        if (pll_src == 0) {  
            sysclk = (8000000 / 2) * pll_mul; // PLL t? HSI/2
        } else {  
            sysclk = 8000000 * pll_mul; // PLL t? HSE
        }
    } 
    else {
        sysclk = 0; // Kh?ng h?p l?
    }

    unsigned int ahb_prescaler = ((RCC->CFGR >> 4) & 0xF); // HPRE
		
    if (ahb_prescaler >= 8) {
        sysclk /= (1 << (ahb_prescaler - 7)); // Chia theo AHB Prescaler
    }

    return sysclk;
}
uint32_t Get_PCLK1_Frequency(void) 
	{
		unsigned int SystemCoreClock=get_system_clock();
    uint32_t hclk = SystemCoreClock;
    uint32_t prescaler = ((RCC->CFGR >> 8) & 0x07);  // APB1 prescaler (Bits 10:8)

    if (prescaler >= 4)  // N?u gi? tr? t? 4 tr? l?n, th?c t? l? 2^(prescaler - 3)
        return hclk >> (prescaler - 3);
    else
        return hclk;  // Kh?ng chia n?u prescaler < 4
}
uint32_t Get_PCLK2_Frequency(void) 
	{
		unsigned int SystemCoreClock=get_system_clock();
    uint32_t hclk = SystemCoreClock;
    uint32_t prescaler = ((RCC->CFGR >> 11) & 0x07);  // APB2 prescaler (Bits 13:11)

    if (prescaler >= 4)
        return hclk >> (prescaler - 3);
    else
        return hclk;
}

void GPIOx_INIT(GPIO_TypeDef* GPIOx,uint8_t pin, uint8_t mode, uint8_t pull, uint8_t speed)
{
	uint8_t config=0;
	
	if(GPIOx==GPIOA) RCC_GPIOA_EN;
	else if(GPIOx==GPIOB) RCC_GPIOB_EN;
	else if(GPIOx==GPIOC) RCC_GPIOC_EN;
	
	switch(mode)
	{
		case MODE_OUTPUT_PP:
		{
			config=(uint8_t)(speed+(mode<<2));
			break;
		}
		case MODE_OUTPUT_OD:
		{
			config=(uint8_t)(speed+(mode<<2));
			break;
		}
		case MODE_OUTPUT_AF_PP:
		{
			config=(uint8_t)(speed+(mode<<2));
			break;
		}
		case MODE_OUTPUT_AF_OD:
		{
			config=(uint8_t)(speed+(mode<<2));
			break;
		}
		case MODE_INPUT_ANALOG:
		{
			config=0;
			break;
		}
		default:
		{
			config=(uint8_t)(mode<<0);
		}
	}
	
	if(pin<8)
	{
		GPIOx->CRL &=(uint32_t) ~(0xF<<(pin*4));
		GPIOx->CRL |=(uint32_t) config<<(pin*4);
	}
	else
	{
		GPIOx->CRH &=(uint32_t) (~(0xF<<((pin-8)*4)));
		GPIOx->CRH |=(uint32_t) (((config)<<((pin-8)*4)));
	}
	if(pull==PULL_UP) GPIOx->ODR |= 1<<pin;
	else GPIOx->ODR &= ~(1<<pin);
}

void GPIOx_WRITE(GPIO_TypeDef* GPIOx,uint8_t pin,uint8_t state)
{
	if(state) GPIOx->BSRR |= 1<<pin;
	else GPIOx->BSRR |= 1<<(pin+16);
}
uint8_t GPIOx_READ(GPIO_TypeDef* GPIOx,uint8_t pin)
{
	return (GPIOx->IDR >> pin) & 1;
}
void GPIOx_TOGGLE(GPIO_TypeDef* GPIOx,uint8_t pin)
{
	GPIOx->ODR ^= 1<<pin;
}
//---------------------------------------------------------------------------------------
void NVICx_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority)
{ 
  uint32_t prioritygroup = 0x00U;
  prioritygroup = NVIC_GetPriorityGrouping();
  NVIC_SetPriority(IRQn, NVIC_EncodePriority(prioritygroup, PreemptPriority, SubPriority));
	NVIC_EnableIRQ(IRQn);
}