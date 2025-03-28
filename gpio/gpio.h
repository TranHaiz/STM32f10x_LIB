#ifndef GPIO_HA_
#define GPIO_HA_

#include "stm32f10x.h"

//--------------------------------------------
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
//--------------------------------------------
#define ENABLE 1
#define DISABLE 0
#define HIGH 1
#define LOW 0
#define NULL 0
//--------------------------------------------
#define RCC_GPIOA_EN (RCC->APB2ENR |= (1<<2))
#define RCC_GPIOB_EN (RCC->APB2ENR |= (1<<3))
#define RCC_GPIOC_EN (RCC->APB2ENR |= (1<<4))
#define RCC_GPIOD_EN (RCC->APB2ENR |= (1<<5))
#define RCC_GPIOE_EN (RCC->APB2ENR |= (1<<6))
#define RCC_GPIOF_EN (RCC->APB2ENR |= (1<<7))
#define RCC_GPIOG_EN (RCC->APB2ENR |= (1<<8))
//------------------------------------------------------
//pull
#define NO_PULL 0
#define PULL_UP 1
#define PULL_DOWN 2
//speed
#define LOW_SPEED 2
#define MEDIUM_SPEED 1
#define HIGH_SPEED 3
//MODE
#define MODE_OUTPUT_PP 0
#define MODE_OUTPUT_OD 1
#define MODE_OUTPUT_AF_PP 2
#define MODE_OUTPUT_AF_OD 3

#define MODE_INPUT_FLOAT 4
#define MODE_INPUT_ANALOG 5
#define MODE_INPUT_PP 8
#define MODE_INPUT MODE_INPUT_PP
#define MODE_INPUT_AF MODE_INPUT
//------------------------------------------------------

void GPIOx_INIT(GPIO_TypeDef* GPIOx,uint8_t pin, uint8_t mode, uint8_t pull, uint8_t speed);
void GPIOx_WRITE(GPIO_TypeDef* GPIOx,uint8_t pin,uint8_t state);
uint8_t GPIOx_READ(GPIO_TypeDef* GPIOx,uint8_t pin);
void GPIOx_TOGGLE(GPIO_TypeDef* GPIOx,uint8_t pin);

void NVICx_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority);

#endif