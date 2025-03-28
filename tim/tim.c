#include "tim.h"

extern volatile uint16_t IC_Last = 0, IC_Now = 0, IC_Delta = 0;

void TIM2_PinInit(PWM_CH channel,PWM_Pin Pin)
{
	if(channel==PWM_CH1)
	{		
		if(Pin==TIM2_CH1_PA0) 
			GPIOx_INIT(GPIOA,0,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED);
		else if (Pin==TIM2_CH1_PA15) 
		{
			GPIOx_INIT(GPIOA,15,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED);
			AFIO->MAPR &= ~(3<<8); //delete remap
			AFIO->MAPR |= (3<<8);//set full remap
		}
	}
	else if(channel==PWM_CH2)
	{		
		if(Pin==TIM2_CH2_PA1) 
			GPIOx_INIT(GPIOA,1,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED);
		else if (Pin==TIM2_CH2_PB3)
		{
			GPIOx_INIT(GPIOB,3,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED);
			AFIO->MAPR &= ~(3<<8); //delete remap
			AFIO->MAPR |= (3<<8);//set full remap
		}
	}
	else if(channel==PWM_CH3)
	{		
		if(Pin==TIM2_CH3_PA2) 
			GPIOx_INIT(GPIOA,2,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED);
		else if (Pin==TIM2_CH3_PB10) 
		{
			GPIOx_INIT(GPIOB,10,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED);
			AFIO->MAPR &= ~(3<<8); //delete remap
			AFIO->MAPR |= (3<<8);//set full remap
		}
	}
	else if(channel==PWM_CH4)
	{		
		if(Pin==TIM2_CH4_PA3) 
			GPIOx_INIT(GPIOA,3,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED);
		else if (Pin==TIM2_CH4_PB11) 
		{
			GPIOx_INIT(GPIOB,11,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED);
			AFIO->MAPR &= ~(3<<8); //delete remap
			AFIO->MAPR |= (3<<8);//set full remap
		}
	}
}
void TIM3_PinInit(PWM_CH channel, uint16_t Pin)
{
    if(channel == PWM_CH1)
    {
        if(Pin == TIM3_CH1_PA6)
            GPIOx_INIT(GPIOA,6,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED);
        else if (Pin == TIM3_CH1_PB4)
        {
            GPIOx_INIT(GPIOB,4,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED);
            AFIO->MAPR &= ~(3<<10); //delete remap
            AFIO->MAPR |= (2<<10);  //set partial remap
        }
        else if (Pin == TIM3_CH1_PC6)
        {
            GPIOx_INIT(GPIOC,6,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED);
            AFIO->MAPR &= ~(3<<10); //delete remap
            AFIO->MAPR |= (3<<10);  //set full remap
        }
    }
    else if(channel == PWM_CH2)
    {
        if(Pin == TIM3_CH2_PA7)
            GPIOx_INIT(GPIOA,7,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED);
        else if (Pin == TIM3_CH2_PB5)
        {
            GPIOx_INIT(GPIOB,5,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED);
            AFIO->MAPR &= ~(3<<10); //delete remap
            AFIO->MAPR |= (2<<10);  //set partial remap
        }
        else if (Pin == TIM3_CH2_PC7)
        {
            GPIOx_INIT(GPIOC,7,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED);
            AFIO->MAPR &= ~(3<<10); //delete remap
            AFIO->MAPR |= (3<<10);  //set full remap
        }
    }
    else if(channel == PWM_CH3)
    {
        if(Pin == TIM3_CH3_PB0)
            GPIOx_INIT(GPIOB,0,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED);
        else if (Pin == TIM3_CH3_PC8)
        {
            GPIOx_INIT(GPIOC,8,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED);
            AFIO->MAPR &= ~(3<<10); //delete remap
            AFIO->MAPR |= (3<<10);  //set full remap
        }
    }
    else if(channel == PWM_CH4)
    {
        if(Pin == TIM3_CH4_PB1)
            GPIOx_INIT(GPIOB,1,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED);
        else if (Pin == TIM3_CH4_PC9)
        {
            GPIOx_INIT(GPIOC,9,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED);
            AFIO->MAPR &= ~(3<<10); //delete remap
            AFIO->MAPR |= (3<<10);  //set full remap
        }
    }
}
void TIM4_PinInit(PWM_CH channel, uint16_t Pin)
{
    if(channel == PWM_CH1 && Pin == TIM4_CH1_PB6)
        GPIOx_INIT(GPIOB,6,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED);
    else if(channel == PWM_CH2 && Pin == TIM4_CH2_PB7)
        GPIOx_INIT(GPIOB,7,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED);
    else if(channel == PWM_CH3 && Pin == TIM4_CH3_PB8)
        GPIOx_INIT(GPIOB,8,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED);
    else if(channel == PWM_CH4 && Pin == TIM4_CH4_PB9)
        GPIOx_INIT(GPIOB,9,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED);
}
//-----------------------------------------------------------------
void TIM2_InCap_PinInit(PWM_CH channel,PWM_Pin Pin)
{
	if(channel==PWM_CH1)
	{		
		if(Pin==TIM2_CH1_PA0) 
			GPIOx_INIT(GPIOA,0,MODE_INPUT_AF,NO_PULL,HIGH_SPEED);
		else if (Pin==TIM2_CH1_PA15) 
		{
			GPIOx_INIT(GPIOA,15,MODE_INPUT_AF,NO_PULL,HIGH_SPEED);
			AFIO->MAPR &= ~(3<<8); //delete remap
			AFIO->MAPR |= (3<<8);//set full remap
		}
	}
	else if(channel==PWM_CH2)
	{		
		if(Pin==TIM2_CH2_PA1) 
			GPIOx_INIT(GPIOA,1,MODE_INPUT_AF,NO_PULL,HIGH_SPEED);
		else if (Pin==TIM2_CH2_PB3)
		{
			GPIOx_INIT(GPIOB,3,MODE_INPUT_AF,NO_PULL,HIGH_SPEED);
			AFIO->MAPR &= ~(3<<8); //delete remap
			AFIO->MAPR |= (3<<8);//set full remap
		}
	}
	else if(channel==PWM_CH3)
	{		
		if(Pin==TIM2_CH3_PA2) 
			GPIOx_INIT(GPIOA,2,MODE_INPUT_AF,NO_PULL,HIGH_SPEED);
		else if (Pin==TIM2_CH3_PB10) 
		{
			GPIOx_INIT(GPIOB,10,MODE_INPUT_AF,NO_PULL,HIGH_SPEED);
			AFIO->MAPR &= ~(3<<8); //delete remap
			AFIO->MAPR |= (3<<8);//set full remap
		}
	}
	else if(channel==PWM_CH4)
	{		
		if(Pin==TIM2_CH4_PA3) 
			GPIOx_INIT(GPIOA,3,MODE_INPUT_AF,NO_PULL,HIGH_SPEED);
		else if (Pin==TIM2_CH4_PB11) 
		{
			GPIOx_INIT(GPIOB,11,MODE_INPUT_AF,NO_PULL,HIGH_SPEED);
			AFIO->MAPR &= ~(3<<8); //delete remap
			AFIO->MAPR |= (3<<8);//set full remap
		}
	}
}
void TIM3_InCap_PinInit(PWM_CH channel, PWM_Pin Pin) 
{
    if(channel == PWM_CH1)
    {
			
			
        if(Pin == TIM3_CH1_PA6)
            GPIOx_INIT(GPIOA,6,MODE_INPUT_AF
				,NO_PULL,HIGH_SPEED);
        else if (Pin == TIM3_CH1_PB4)
        {
            GPIOx_INIT(GPIOB,4,MODE_INPUT_AF,NO_PULL,HIGH_SPEED);
            AFIO->MAPR &= ~(3<<10); // delete remap
            AFIO->MAPR |= (2<<10);  // set partial remap
        }
        else if (Pin == TIM3_CH1_PC6)
        {
            GPIOx_INIT(GPIOC,6,MODE_INPUT_AF,NO_PULL,HIGH_SPEED);
            AFIO->MAPR &= ~(3<<10); // delete remap
            AFIO->MAPR |= (3<<10);  // set full remap
        }
    }
    else if(channel == PWM_CH2)
    {
        if(Pin == TIM3_CH2_PA7)
            GPIOx_INIT(GPIOA,7,MODE_INPUT_AF,NO_PULL,HIGH_SPEED);
        else if (Pin == TIM3_CH2_PB5)
        {
            GPIOx_INIT(GPIOB,5,MODE_INPUT_AF,NO_PULL,HIGH_SPEED);
            AFIO->MAPR &= ~(3<<10); // delete remap
            AFIO->MAPR |= (2<<10);  // set partial remap
        }
        else if (Pin == TIM3_CH2_PC7)
        {
            GPIOx_INIT(GPIOC,7,MODE_INPUT_AF,NO_PULL,HIGH_SPEED);
            AFIO->MAPR &= ~(3<<10); // delete remap
            AFIO->MAPR |= (3<<10);  // set full remap
        }
    }
    else if(channel == PWM_CH3)
    {
        if(Pin == TIM3_CH3_PB0)
            GPIOx_INIT(GPIOB,0,MODE_INPUT_AF,NO_PULL,HIGH_SPEED);
        else if (Pin == TIM3_CH3_PC8)
        {
            GPIOx_INIT(GPIOC,8,MODE_INPUT_AF,NO_PULL,HIGH_SPEED);
            AFIO->MAPR &= ~(3<<10); // delete remap
            AFIO->MAPR |= (3<<10);  // set full remap
        }
    }
    else if(channel == PWM_CH4)
    {
        if(Pin == TIM3_CH4_PB1)
            GPIOx_INIT(GPIOB,1,MODE_INPUT_AF,NO_PULL,HIGH_SPEED);
        else if (Pin == TIM3_CH4_PC9)
        {
            GPIOx_INIT(GPIOC,9,MODE_INPUT_AF,NO_PULL,HIGH_SPEED);
            AFIO->MAPR &= ~(3<<10); // delete remap
            AFIO->MAPR |= (3<<10);  // set full remap
        }
    }
}

void TIM4_InCap_PinInit(PWM_CH channel, PWM_Pin Pin)
{
    if(channel == PWM_CH1 && Pin == TIM4_CH1_PB6)
        GPIOx_INIT(GPIOB,6,MODE_INPUT_AF,NO_PULL,HIGH_SPEED);
    else if(channel == PWM_CH2 && Pin == TIM4_CH2_PB7)
        GPIOx_INIT(GPIOB,7,MODE_INPUT_AF,NO_PULL,HIGH_SPEED);
    else if(channel == PWM_CH3 && Pin == TIM4_CH3_PB8)
        GPIOx_INIT(GPIOB,8,MODE_INPUT_AF,NO_PULL,HIGH_SPEED);
    else if(channel == PWM_CH4 && Pin == TIM4_CH4_PB9)
        GPIOx_INIT(GPIOB,9,MODE_INPUT_AF,NO_PULL,HIGH_SPEED);
}
//-----------------------------------------------------------------
void TIMx_INIT(TIM_TypeDef* TIMx,uint16_t PSC,uint16_t ARR) //this function dont config DUTY so PWM can't run
{
	if(TIMx==TIM2) RCC->APB1ENR |= 1<<0;
	else if(TIMx==TIM3) RCC->APB1ENR |= 1<<1;
	else if(TIMx==TIM4) RCC->APB1ENR |= 1<<2;
	
	//config thoi gian dem
	TIMx->ARR = ARR-1;
	TIMx->PSC = PSC-1;
	
	TIMx->DIER |= 1<<0; //Update interrupt enable
	TIMx->CR1 |= 1<<0; //turn on TIM
	TIMx->SR &= ~(1<<0);
	
	//Enable ngat
	if(TIMx==TIM2) NVIC_EnableIRQ(TIM2_IRQn);
	else if(TIMx==TIM3) NVIC_EnableIRQ(TIM3_IRQn);
}

void PWMx_INIT(TIM_TypeDef* TIMx,PWM_CH channel,PWM_Pin Pin,uint16_t PSC,uint16_t ARR)
{
	//config Clock
	RCC->APB2ENR |= 1<<0; //Enable AFIO
	
	if(TIMx==TIM2)
	{
		RCC->APB1ENR |= 1<<0; //enanable tim2
		TIM2_PinInit(channel,Pin);
	}
	else if(TIMx==TIM3) 
	{
		RCC->APB1ENR |= 1<<1; //enanable tim3
		TIM3_PinInit(channel,Pin);
	}
	else if(TIMx==TIM4) 
	{
		RCC->APB1ENR |= 1<<2; //enanable tim4
		TIM4_PinInit(channel,Pin);
	}
	//config chu ky
	TIMx->ARR = ARR-1; //he so dem
	TIMx->PSC = PSC-1; //prescale
	TIMx->CR1 |= 1<<0; //turn on TIM
	TIMx->CR1 |= 1<<7; //turn on AutoReload
	
	//config channel
	if(channel==PWM_CH1)
	{
	TIMx->CCMR1 &= ~(7<<4); //delete old timer mode 
	TIMx->CCMR1 |= 6<<4; //set PWM mode 1
	TIMx->CCMR1 |= (1<<3);//enable preload
	TIMx->CCMR1 &= ~(3<<0);//delete old select 
	TIMx->CCMR1 |= (0<<0); //select channel is configured as output.
	TIMx->CCER |= 1<<0; //turn on channel 1
	TIMx->CCER |= 0<<1; //pwm high then low
	
	}
	else if(channel==PWM_CH2)
	{
	TIMx->CCMR1 &= ~(7<<12); //delete old timer mode 
	TIMx->CCMR1 |= 6<<12; //set PWM mode 1
	TIMx->CCMR1 |= (1<<11);//enable preload
	TIMx->CCMR1 &= ~(3<<8);//delete old select
	TIMx->CCMR1 |= (0<<8); //select channel is configured as output.
	TIMx->CCER |= 1<<4; //turn on channel 2
	TIMx->CCER |= 0<<5; //pwm high then low
	
	}
	else if(channel==PWM_CH3)
	{
	TIMx->CCMR2 &= ~(7<<4); //delete old timer mode 
	TIMx->CCMR2 |= 6<<4; //set PWM mode 1
	TIMx->CCMR2 |= (1<<3);//enable preload
	TIMx->CCMR2 &= ~(3<<0);//delete old select 
	TIMx->CCMR2 |= (0<<0); //select channel is configured as output.
	TIMx->CCER |= 1<<8; //turn on channel 3
	TIMx->CCER |= 0<<9; //pwm high then low
		
	}
	else if(channel==PWM_CH4)
	{
	TIMx->CCMR2 &= ~(7<<12); //delete old timer mode 
	TIMx->CCMR2 |= 6<<12; //set PWM mode 1
	TIMx->CCMR2 |= (1<<11);//enable preload
	TIMx->CCMR2 &= ~(3<<8);//delete old select
	TIMx->CCMR2 |= (0<<8); //select channel is configured as output.
	TIMx->CCER |= 1<<12; //turn on channel 4
	TIMx->CCER |= 0<<13; //pwm high then low
		
	}
}
void INPUTCAPx_INIT(TIM_TypeDef* TIMx,PWM_CH channel,PWM_Pin pin,uint16_t PSC,uint16_t ARR)
{
	//config Clock
	RCC->APB2ENR |= 1<<0; //Enable AFIO
	
	if(TIMx==TIM2)
	{
		RCC->APB1ENR |= 1<<0; //enanable tim2
		TIM2_InCap_PinInit(channel,pin);
	}
	
	else if(TIMx==TIM3) 
	{
		RCC->APB1ENR |= 1<<1; //enanable tim3
		TIM3_InCap_PinInit(channel,pin);
	}
	else if(TIMx==TIM4) 
	{
		RCC->APB1ENR |= 1<<2; //enanable tim4
		TIM4_InCap_PinInit(channel,pin);
	}
	
	TIMx->ARR=ARR-1; //he so dem
	TIMx->PSC=PSC-1; //preScale
	
	if(channel==PWM_CH1)
	{
		TIMx->CCMR1 &= ~(3<<0); //delete old select mode
		TIMx->CCMR1 |= 1<<0; //config mode input capture
		TIMx->CCER |= 0<<1; //rising trigger
		TIMx->CCER |= 1<<0; //turn on CH1
		TIMx->DIER |= 1<<1; //turn on interrupt input capture 1
	}
	else if(channel==PWM_CH2)
	{
		TIMx->CCMR1 &= ~(3<<8); //delete old select mode
		TIMx->CCMR1 |= 1<<8; //config mode input capture
		TIMx->CCER |= 0<<5; //rising trigger
		TIMx->CCER |= 1<<4; //turn on CH2
		TIMx->DIER |= 1<<2; //turn on interrupt input capture 2
	}
	else if(channel==PWM_CH3)
	{
		TIMx->CCMR2 &= ~(3<<0); //delete old select mode
		TIMx->CCMR2 |= 1<<0; //config mode input capture
		TIMx->CCER |= 0<<19; //rising trigger
		TIMx->CCER |= 1<<8; //turn on CH1
		TIMx->DIER |= 1<<3; //turn on interrupt input capture 3
	}
	else if(channel==PWM_CH4)
	{
		TIMx->CCMR2 &= ~(3<<8); //delete old select mode
		TIMx->CCMR2 |= 1<<8; //config mode input capture
		TIMx->CCER |= 0<<13; //rising trigger
		TIMx->CCER |= 1<<12; //turn on CH1
		TIMx->DIER |= 1<<4; //turn on interrupt input capture 4
	}
	
	if(TIMx==TIM2) NVIC_EnableIRQ(TIM2_IRQn);
	else if(TIMx==TIM3) NVIC_EnableIRQ(TIM3_IRQn);
	else if(TIMx==TIM4) NVIC_EnableIRQ(TIM4_IRQn);
	
	TIMx->CR1 |= 1<<0; //turn on timer
}
void PWMx_SETUP(TIM_TypeDef* TIMx,PWM_CH channel,PWM_Pin Pin,uint32_t period,uint32_t duty)
{
	uint16_t PSC=0,ARR=0;
	
	if(period>=100000) PSC=1;
	else if(period>=10000) PSC=10;
	else if(period>=1000) PSC=100;
	else PSC=1000;
	
	ARR=(SystemCoreClock/(period*PSC));
	
	PWMx_INIT(TIMx,channel,Pin,PSC,ARR);
	
	//config Duty Cycle
	if(channel==PWM_CH1)
	{		
		TIMx->CCR1 = (duty*ARR)/100;
	}
	else if(channel==PWM_CH2)
	{
		TIMx->CCR2 = (duty*ARR)/100;
	}
	else if(channel==PWM_CH3)
	{
		TIMx->CCR3 = (duty*ARR)/100;
	}
	else if(channel==PWM_CH4)
	{
		TIMx->CCR4 = (duty*ARR)/100;
	}
}
