#ifndef TIM_H_
#define TIM_H_

#include <stm32f10x.h>
#include "gpio.h"

typedef enum
{
	PWM_CH1,
	PWM_CH2,
	PWM_CH3,
	PWM_CH4
} PWM_CH;
typedef enum 
{
    TIM2_CH1_PA0,
    TIM2_CH2_PA1,
    TIM2_CH3_PA2,
    TIM2_CH4_PA3,

    TIM2_CH1_PA15,
    TIM2_CH2_PB3,
    TIM2_CH3_PB10,
    TIM2_CH4_PB11,

    TIM3_CH1_PA6,
    TIM3_CH2_PA7,
    TIM3_CH3_PB0,
    TIM3_CH4_PB1,

    TIM3_CH1_PB4,
    TIM3_CH2_PB5,

    TIM3_CH1_PC6,
    TIM3_CH2_PC7,
    TIM3_CH3_PC8,
    TIM3_CH4_PC9,

    TIM4_CH1_PB6,
    TIM4_CH2_PB7,
    TIM4_CH3_PB8,
    TIM4_CH4_PB9

} PWM_Pin;

void TIMx_INIT(TIM_TypeDef* TIMx,uint16_t PSC,uint16_t ARR);
void PWMx_INIT(TIM_TypeDef* TIMx,PWM_CH channel,PWM_Pin Pin,uint16_t PSC,uint16_t ARR);
void PWMx_SETUP(TIM_TypeDef* TIMx,PWM_CH channel,PWM_Pin Pin,uint32_t period,uint32_t duty);
void INPUTCAPx_INIT(TIM_TypeDef* TIMx,PWM_CH channel,PWM_Pin pin,uint16_t PSC,uint16_t ARR);

#endif