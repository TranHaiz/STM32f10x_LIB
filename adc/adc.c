#include "adc.h"

/*	
 * Pinout
 *	CHANNEL				ADC1	ADC2	ADC3
 *	0							PA0		PA0		PA0
 *	1							PA1		PA1		PA1
 *	2							PA2		PA2		PA2
 *	3							PA3		PA3		PA3
 *	4							PA4		PA4		PF6
 *	5							PA5		PA5		PF7
 *	6							PA6		PA6		PF8
 *	7							PA7		PA7		PF9
 *	8							PB0		PB0		PF10
 *	9							PB1		PB1		PF3
 *	10						PC0		PC0		PC0
 *	11						PC1		PC1		PC1
 *	12						PC2		PC2		PC2
 *	13						PC3		PC3		PC3
 *	14						PC4		PC4		PF4
 *	15						PC5		PC5		PF5
 */
void ADCx_init(ADC_TypeDef* ADCx, uint8_t channel)
{
//ENABLE RCC
if(ADCx==ADC1)
	RCC->APB2ENR|= (1<<9)|(1<<0);
else if (ADCx==ADC2)
	RCC->APB2ENR|= (1<<10);

//CONFIG CHANNEL ADC
if(channel==ADC_Channel_0)
	GPIOx_INIT(GPIOA,0,MODE_INPUT_ANALOG,NO_PULL,HIGH_SPEED);
else if(channel==ADC_Channel_1)
	GPIOx_INIT(GPIOA,1,MODE_INPUT_ANALOG,NO_PULL,HIGH_SPEED);
else if(channel==ADC_Channel_2)
	GPIOx_INIT(GPIOA,2,MODE_INPUT_ANALOG,NO_PULL,HIGH_SPEED);
else if(channel==ADC_Channel_3)
	GPIOx_INIT(GPIOA,3,MODE_INPUT_ANALOG,NO_PULL,HIGH_SPEED);
else if(channel==ADC_Channel_4)
	GPIOx_INIT(GPIOA,4,MODE_INPUT_ANALOG,NO_PULL,HIGH_SPEED);
else if(channel==ADC_Channel_5)
	GPIOx_INIT(GPIOA,5,MODE_INPUT_ANALOG,NO_PULL,HIGH_SPEED);
else if(channel==ADC_Channel_6)
	GPIOx_INIT(GPIOA,6,MODE_INPUT_ANALOG,NO_PULL,HIGH_SPEED);
else if(channel==ADC_Channel_7)
	GPIOx_INIT(GPIOA,7,MODE_INPUT_ANALOG,NO_PULL,HIGH_SPEED);
else if(channel==ADC_Channel_8)
	GPIOx_INIT(GPIOB,0,MODE_INPUT_ANALOG,NO_PULL,HIGH_SPEED);
else if(channel==ADC_Channel_9)
	GPIOx_INIT(GPIOB,1,MODE_INPUT_ANALOG,NO_PULL,HIGH_SPEED);
else if(channel==ADC_Channel_10)
	GPIOx_INIT(GPIOC,0,MODE_INPUT_ANALOG,NO_PULL,HIGH_SPEED);
else if(channel==ADC_Channel_11)
	GPIOx_INIT(GPIOC,1,MODE_INPUT_ANALOG,NO_PULL,HIGH_SPEED);
else if(channel==ADC_Channel_12)
	GPIOx_INIT(GPIOC,2,MODE_INPUT_ANALOG,NO_PULL,HIGH_SPEED);
else if(channel==ADC_Channel_13)
	GPIOx_INIT(GPIOC,3,MODE_INPUT_ANALOG,NO_PULL,HIGH_SPEED);
else if(channel==ADC_Channel_14)
	GPIOx_INIT(GPIOC,4,MODE_INPUT_ANALOG,NO_PULL,HIGH_SPEED);
else if(channel==ADC_Channel_15)
	GPIOx_INIT(GPIOC,5,MODE_INPUT_ANALOG,NO_PULL,HIGH_SPEED);

ADCx->CR1 |= (1<<8); //enable scan mode
ADCx->CR2 |= (1<<1)|(1<<0); //enable ContinuousConvMode 
ADCx->CR2 &= (uint32_t)(~(7<<17)); //delete 
ADCx->CR2 |= (7<<17); //ADC_SOFTWARE_START
ADCx->CR2 |= (0<<11); //Right Alignment
ADCx->SQR1 &= (uint32_t)(~(0xF<<20)); //delete so kenh
ADCx->SQR1 |= (0<<20); //adjust so kenh = 1 


if(channel<ADC_Channel_10)
{
	ADCx->SMPR2 &= (uint32_t) (~(7<<(channel*3)));
	ADCx->SMPR2 |= (uint32_t) (7<<(channel*3));
}
else
{
	ADCx->SMPR1 &= (uint32_t) (~(7<<((channel-10)*3)));
	ADCx->SMPR1 |= (uint32_t) (7<<((channel-10)*3));
}

ADCx->SQR3 = channel; //rank channel

ADCx->CR2 |= 1<<3; //reset calib
while( ADCx->CR2 & (1<<3));

ADCx->CR2 |= 1<<2; //calib
while( ADCx->CR2 & (1<<2));

ADCx->CR2 |= 1<<0; //ADC ENABLE
}
uint16_t ADCx_READ(ADC_TypeDef* ADCx, uint8_t channel)
{
	if(channel<ADC_Channel_10)
	{
		ADCx->SMPR2 &= (uint32_t) (~(7<<(channel*3)));
		ADCx->SMPR2 |= (uint32_t) (7<<(channel*3));
	}
	else
	{
		ADCx->SMPR1 &= (uint32_t) (~(7<<((channel-10)*3)));
		ADCx->SMPR1 |= (uint32_t) (7<<((channel-10)*3));
	}
	ADCx->SQR3 = channel; //rank channel
	
	ADCx->CR2 |= (1<<22)|(1<0); //start convert
	while(!(ADCx->SR & (1<<1))); //EOC check
	
	return (uint16_t)(ADCx->DR);
}
uint16_t ADCx_READ_AVG(ADC_TypeDef* ADCx, uint8_t channel, uint16_t sample) 
{
    if (sample == 0) return 0;  

    uint32_t value_sum = 0;  
    for (uint16_t i = 0; i < sample; i++) 
    {
        value_sum += ADCx_READ(ADCx, channel);
    }
    return (uint16_t)(value_sum / sample);
}