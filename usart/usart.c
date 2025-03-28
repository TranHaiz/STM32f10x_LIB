#include "usart.h"

void USARTx_INIT(USART_TypeDef *USARTx,Pins_USART Pinx,uint32_t Baud)
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
	if(Pinx==USART1_PA9PA10) 
	{
		GPIOx_INIT(GPIOA,9,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED);
		GPIOx_INIT(GPIOA,10,MODE_INPUT_FLOAT,NO_PULL,HIGH_SPEED);
	}
	else if (Pinx==USART1_PB6PB7)
	{
		AFIO->MAPR |= 1<<2;
		GPIOx_INIT(GPIOB,6,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED);
		GPIOx_INIT(GPIOB,7,MODE_INPUT_FLOAT,NO_PULL,HIGH_SPEED);
	}
	else if (Pinx==USART2_PA2PA3)
	{
		GPIOx_INIT(GPIOA,2,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED);
		GPIOx_INIT(GPIOA,3,MODE_INPUT_FLOAT,NO_PULL,HIGH_SPEED);
	}
	else if (Pinx==USART2_PD5PD6)
	{
		AFIO->MAPR |= 1<<3;
		GPIOx_INIT(GPIOD,5,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED);
		GPIOx_INIT(GPIOD,6,MODE_INPUT_FLOAT,NO_PULL,HIGH_SPEED);
	}
	else if (Pinx==USART3_PB10PB11)
	{
		AFIO->MAPR &= ~(3<<4);
		AFIO->MAPR |= 0<<4;
		GPIOx_INIT(GPIOB,10,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED);
		GPIOx_INIT(GPIOB,11,MODE_INPUT_FLOAT,NO_PULL,HIGH_SPEED);
	}
	else if ((Pinx==USART3_PC10PC11) || (Pinx==USART4_PC10PC11))
	{
		AFIO->MAPR &= ~(3<<4);
		AFIO->MAPR |= 2<<4;
		GPIOx_INIT(GPIOC,10,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED);
		GPIOx_INIT(GPIOC,11,MODE_INPUT_FLOAT,NO_PULL,HIGH_SPEED);
	}
	else if (Pinx==USART3_PD8PD9)
	{
		AFIO->MAPR &= ~(3<<4);
		AFIO->MAPR |= 3<<4;
		GPIOx_INIT(GPIOD,8,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED);
		GPIOx_INIT(GPIOD,9,MODE_INPUT_FLOAT,NO_PULL,HIGH_SPEED);
	}
	else if (Pinx==UART4_PA0PA1)
	{
		GPIOx_INIT(GPIOA,0,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED);
		GPIOx_INIT(GPIOA,1,MODE_INPUT_FLOAT,NO_PULL,HIGH_SPEED);
	}
	else if (Pinx==UART5_PC12PD2)
	{
		GPIOx_INIT(GPIOC,12,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED);
		GPIOx_INIT(GPIOD,2,MODE_INPUT_FLOAT,NO_PULL,HIGH_SPEED);
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
	
	USARTx->CR1 |= 1<<5; //enable receive interrupt
	if(USARTx==USART1)
		NVIC_EnableIRQ(USART1_IRQn);
	else if (USARTx==USART2)
		NVIC_EnableIRQ(USART2_IRQn);
		
}
void USARTx_WRTITE(USART_TypeDef* USARTx,char* data)
{
	int n=0;
	int buffer=0;
	while(*(data+n) != NULL)
	{	
		while(!(USARTx->SR&(1<<7)));
		buffer=*(data+n);
		USARTx->DR=*(data+n);
		while(!(USARTx->SR&(1<<6)));
		n++;
	}
}
unsigned char USARTx_READ(USART_TypeDef *USARTx)
{
	while(!(USARTx->SR&(1<<5)));
	return (unsigned char) (USARTx->DR);
}