#include "stm32f1xHaq.h"

//-----------CLOCK-------------------------------
unsigned int get_system_clock(void) {
    unsigned int sysclk;
    unsigned int clk_src = (RCC_CFGR >> 2) & 0x3; // L?y bit SWS (2:3)

    if (clk_src == 0) {  
        sysclk = 8000000; // HSI = 8 MHz
    } 
    else if (clk_src == 1) {  
        sysclk = 8000000; // HSE = 8 MHz (gi? s?)
    } 
    else if (clk_src == 2) {  
        unsigned int pll_src = (RCC_CFGR >> 16) & 0x1; // PLLSRC (bit 16)
        unsigned int pll_mul = ((RCC_CFGR >> 18) & 0xF) + 2; // PLLMUL (18:21)

        if (pll_src == 0) {  
            sysclk = (8000000 / 2) * pll_mul; // PLL t? HSI/2
        } else {  
            sysclk = 8000000 * pll_mul; // PLL t? HSE
        }
    } 
    else {
        sysclk = 0; // Không h?p l?
    }

    unsigned int ahb_prescaler = (RCC_CFGR >> 4) & 0xF; // HPRE (4:7)
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

    if (prescaler >= 4)  // N?u giá tr? t? 4 tr? lên, th?c t? là 2^(prescaler - 3)
        return hclk >> (prescaler - 3);
    else
        return hclk;  // Không chia n?u prescaler < 4
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
//-----------GPIO-------------------------------
//	GPIO_INIT(GPIOA,3,INPUT,MODE_INPUT,PULL_UP);
//	GPIO_INIT(GPIOC,13,OUTPUT_HIGH_SPEED,MODE_OUTPUT_PUSH_PULL,NO_PULL);
void GPIO_INIT(GPIO_TypeDef* GPIOx, uint8_t pin, uint8_t io_speed, uint8_t mode, uint8_t pull)
{
	if(GPIOx==GPIOA) RCC_GPIOA_EN;
	else if(GPIOx==GPIOB) RCC_GPIOB_EN;
	else if(GPIOx==GPIOC) RCC_GPIOC_EN;
	if(pin<8)
	{
		GPIOx->CRL &= (uint32_t) (~(0xF<<(pin*4)));
		GPIOx->CRL |= (uint32_t) (((mode<<2)+io_speed)<<(pin*4));
	}
	else 
	{
		GPIOx->CRH &= (uint32_t) (~(0xF<<((pin-8)*4)));
		GPIOx->CRH |= (uint32_t) (((mode<<2)+io_speed)<<((pin-8)*4));
	}
	if(pull==PULL_UP) GPIOx->ODR |= 1<<pin;
	else GPIOx->ODR &= ~(1<<pin);
}
void GPIO_WRITE(GPIO_TypeDef* GPIOx,uint8_t pin,uint8_t state)
{
	if(state) GPIOx->BSRR |= 1<<pin;
	else GPIOx->BSRR |= 1<<(pin+16);
}
uint8_t GPIO_READ(GPIO_TypeDef* GPIOx,uint8_t pin)
{
	return (GPIOx->IDR >> pin) & 1;
}
void GPIO_TOGGLE(GPIO_TypeDef* GPIOx,uint8_t pin)
{
	GPIOx->ODR ^= 1<<pin;
}
//-----------ADC-------------------------------
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
	GPIO_INIT(GPIOA,0,INPUT,MODE_INPUT_ANALOG,NO_PULL);
else if(channel==ADC_Channel_1)
	GPIO_INIT(GPIOA,1,INPUT,MODE_INPUT_ANALOG,NO_PULL);
else if(channel==ADC_Channel_2)
	GPIO_INIT(GPIOA,2,INPUT,MODE_INPUT_ANALOG,NO_PULL);
else if(channel==ADC_Channel_3)
	GPIO_INIT(GPIOA,3,INPUT,MODE_INPUT_ANALOG,NO_PULL);
else if(channel==ADC_Channel_4)
	GPIO_INIT(GPIOA,4,INPUT,MODE_INPUT_ANALOG,NO_PULL);
else if(channel==ADC_Channel_5)
	GPIO_INIT(GPIOA,5,INPUT,MODE_INPUT_ANALOG,NO_PULL);
else if(channel==ADC_Channel_6)
	GPIO_INIT(GPIOA,6,INPUT,MODE_INPUT_ANALOG,NO_PULL);
else if(channel==ADC_Channel_7)
	GPIO_INIT(GPIOA,7,INPUT,MODE_INPUT_ANALOG,NO_PULL);
else if(channel==ADC_Channel_8)
	GPIO_INIT(GPIOB,0,INPUT,MODE_INPUT_ANALOG,NO_PULL);
else if(channel==ADC_Channel_9)
	GPIO_INIT(GPIOB,1,INPUT,MODE_INPUT_ANALOG,NO_PULL);
else if(channel==ADC_Channel_10)
	GPIO_INIT(GPIOC,0,INPUT,MODE_INPUT_ANALOG,NO_PULL);
else if(channel==ADC_Channel_11)
	GPIO_INIT(GPIOC,1,INPUT,MODE_INPUT_ANALOG,NO_PULL);
else if(channel==ADC_Channel_12)
	GPIO_INIT(GPIOC,2,INPUT,MODE_INPUT_ANALOG,NO_PULL);
else if(channel==ADC_Channel_13)
	GPIO_INIT(GPIOC,3,INPUT,MODE_INPUT_ANALOG,NO_PULL);
else if(channel==ADC_Channel_14)
	GPIO_INIT(GPIOC,4,INPUT,MODE_INPUT_ANALOG,NO_PULL);
else if(channel==ADC_Channel_15)
	GPIO_INIT(GPIOC,5,INPUT,MODE_INPUT_ANALOG,NO_PULL);

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
uint16_t ADCx_read(ADC_TypeDef* ADCx, uint8_t channel)
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
uint16_t ADC_avg(ADC_TypeDef* ADCx, uint8_t channel, uint16_t sample) 
{
    if (sample == 0) return 0;  

    uint32_t value_sum = 0;  
    for (uint16_t i = 0; i < sample; i++) 
    {
        value_sum += ADCx_read(ADCx, channel);
    }
    return (uint16_t)(value_sum / sample);
}
//-----------USART-------------------------------
void UARTx_init(USART_TypeDef *USARTx,Pins_USART Pinx,uint32_t Baud)
{
	float USART_DIV=0;
	uint16_t fraction=0;
	uint16_t mantissa=0;
	uint32_t PCLKx;
	uint32_t Boud=0;
	
	//ENABLE RCC
	RCC->APB2ENR |= 1<<0; //AFIO
	
	if(USARTx==USART1) 
	{
		RCC->APB2ENR |= (1<<14);
		PCLKx=Get_PCLK2_Frequency(); 
	}
	else if(USARTx==USART2) 
	{
		RCC->APB1ENR |= (1<<17);
		PCLKx=Get_PCLK1_Frequency();
	}
	else if(USARTx==USART3) 
	{
		RCC->APB1ENR |= (1<<18);
		PCLKx=Get_PCLK1_Frequency();
	}
	
	//PIN CONFIG
	if(Pinx==Pins_PA9PA10) 
	{
		GPIO_INIT(GPIOA,9,OUTPUT_HIGH_SPEED,MODE_OUTPUT_ALT_PUSH_PULL,NO_PULL);
		GPIO_INIT(GPIOA,10,INPUT,MODE_INPUT_FLOAT,NO_PULL);
	}
	else if (Pinx==Pins_PB6PB7)
	{
		GPIO_INIT(GPIOB,6,OUTPUT_HIGH_SPEED,MODE_OUTPUT_ALT_PUSH_PULL,NO_PULL);
		GPIO_INIT(GPIOB,7,INPUT,MODE_INPUT_FLOAT,NO_PULL);
	}
	else if (Pinx==Pins_PA2PA3)
	{
		GPIO_INIT(GPIOA,2,OUTPUT_HIGH_SPEED,MODE_OUTPUT_ALT_PUSH_PULL,NO_PULL);
		GPIO_INIT(GPIOA,3,INPUT,MODE_INPUT_FLOAT,NO_PULL);
	}
	else if (Pinx==Pins_PD5PD6)
	{
		GPIO_INIT(GPIOD,5,OUTPUT_HIGH_SPEED,MODE_OUTPUT_ALT_PUSH_PULL,NO_PULL);
		GPIO_INIT(GPIOD,6,INPUT,MODE_INPUT_FLOAT,NO_PULL);
	}
	else if (Pinx==Pins_PB10PB11)
	{
		GPIO_INIT(GPIOB,10,OUTPUT_HIGH_SPEED,MODE_OUTPUT_ALT_PUSH_PULL,NO_PULL);
		GPIO_INIT(GPIOB,11,INPUT,MODE_INPUT_FLOAT,NO_PULL);
	}
	else if (Pinx==Pins_PC10PC11)
	{
		GPIO_INIT(GPIOC,10,OUTPUT_HIGH_SPEED,MODE_OUTPUT_ALT_PUSH_PULL,NO_PULL);
		GPIO_INIT(GPIOC,11,INPUT,MODE_INPUT_FLOAT,NO_PULL);
	}
	else if (Pinx==Pins_PD8PD9)
	{
		GPIO_INIT(GPIOD,8,OUTPUT_HIGH_SPEED,MODE_OUTPUT_ALT_PUSH_PULL,NO_PULL);
		GPIO_INIT(GPIOD,9,INPUT,MODE_INPUT_FLOAT,NO_PULL);
	}
	else if (Pinx==Pins_PA0PA1)
	{
		GPIO_INIT(GPIOA,0,OUTPUT_HIGH_SPEED,MODE_OUTPUT_ALT_PUSH_PULL,NO_PULL);
		GPIO_INIT(GPIOA,1,INPUT,MODE_INPUT_FLOAT,NO_PULL);
	}
	else if (Pinx==Pins_PC12PD2)
	{
		GPIO_INIT(GPIOC,12,OUTPUT_HIGH_SPEED,MODE_OUTPUT_ALT_PUSH_PULL,NO_PULL);
		GPIO_INIT(GPIOD,2,INPUT,MODE_INPUT_FLOAT,NO_PULL);
	}
	
	//baud rate PCLK1 cho usart234, pclk2 cho usart1
	USART_DIV=PCLKx/(Baud*16);
	mantissa=(uint16_t) (USART_DIV);
	fraction=(uint16_t)((USART_DIV-mantissa)*16);
	Boud = (uint32_t)((mantissa<<4)+fraction);
	USARTx->BRR &= 0x0; //delete old baud rate
	USARTx->BRR |= Boud; //set new baud rate
	
	USARTx->CR1 |= 0<<12; //8 bit dataa
	USARTx->CR1 |= 0<<10; //disable parity bit
	USARTx->CR1 |= 1<<13; //usart enable
	USARTx->CR1 |= 1<<2; //read enable
	USARTx->CR1 |= 1<<3; //receive enable
	USARTx->CR2 &= ~(3<<12); //delete old stop bits
 	USARTx->CR2 |= 0<<12; //config 1 stop bits
}
void USARTx_WRITE(USART_TypeDef *USARTx,unsigned char data)
{
	while(!(USARTx->SR&(1<<7)));
	USARTx->DR = data;
	while(!(USARTx->SR&(1<<6)));
}

