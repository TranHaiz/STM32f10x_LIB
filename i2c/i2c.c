#include "i2c.h"

extern uint32_t timeout_i2c=0;


void I2Cx_INIT(I2C_TypeDef *I2Cx,I2C_Pin pin,uint32_t speed)
{
	unsigned int PCLKx=0;
  //Turn on CLOCK
	RCC->APB2ENR |= 1<<0;//turn on clk AFIO
	if(I2Cx==I2C1) 
	{
		RCC->APB1ENR |= 1<<21; //turn on clk I2C1
		PCLKx=36000000;
	}
	else if(I2Cx==I2C2) 
	{
		RCC->APB1ENR |= 1<<22; //turn on clk I2C2
		PCLKx=36000000;
	}
	
	//Pin config	
	if(pin==I2C1_Pin_PB6PB7)
	{
		GPIOx_INIT(GPIOB,6,MODE_OUTPUT_AF_OD,NO_PULL,HIGH_SPEED); //SCL
		GPIOx_INIT(GPIOB,7,MODE_OUTPUT_AF_OD,NO_PULL,HIGH_SPEED); //SDA
	}
	else if(pin==I2C1_Pin_PB8PB9)
	{
		AFIO->MAPR |= 1<<1; //REMAP I2C1
		GPIOx_INIT(GPIOB,8,MODE_OUTPUT_AF_OD,NO_PULL,HIGH_SPEED); //SCL
		GPIOx_INIT(GPIOB,9,MODE_OUTPUT_AF_OD,NO_PULL,HIGH_SPEED); //SDA
	}
	else if(pin==I2C2_Pin_PB10PB11)
	{
		GPIOx_INIT(GPIOB,10,MODE_OUTPUT_AF_OD,NO_PULL,HIGH_SPEED); //SCL
		GPIOx_INIT(GPIOB,11,MODE_OUTPUT_AF_OD,NO_PULL,HIGH_SPEED); //SDA
	}
	
	I2Cx->CR1 |= 0<<10; //disable ACK
	I2Cx->CR2 &= ~(0x3F); //delete old Freq peripheral
	I2Cx->CR2 |= PCLKx/1000000; //new Freq peripheral 
	I2Cx->CCR &= ~(0xFF); //delete old config CCR
	I2Cx->CCR |= PCLKx/(speed*2); //set up new speed SCL
	I2Cx->TRISE &= ~(0x3F<<0); //delete old rise time
	I2Cx->TRISE |= (PCLKx/1000000)+1; //set new rise time
	
	I2Cx->CR1 |= (0<<1)|(1<<0); //enable I2C and i2c mode
}
void checkBusy(void)
{
	while((I2C1->SR2 & (1<<1)) != 0); //wiait until the bus is ready
}
uint8_t i2c_Start(I2C_TypeDef *I2Cx,uint8_t add,uint8_t dir,uint8_t ack)
{
	checkBusy();
	
	if(ack) I2Cx->CR1 |= (1<<10); //turn on ACK
	else I2Cx->CR1 &= ~(1<<10); //turn off ACK
	
	I2Cx->CR1 |= (1<<8); //start
	timeout_i2c=TIME_OUT_I2C;
	while(((I2Cx->SR1)&(1<<0))==0)
	{
		if(--timeout_i2c==0) return 0;
	}
	
	I2Cx->DR = (add<<1)+dir; //+0 = write, write address slave
	timeout_i2c=TIME_OUT_I2C;
	while(!(I2Cx->SR1&(1<<1)))
	{
		if(--timeout_i2c==0) return 0;
	} //wait address has been sent
	(void) I2Cx->SR2; //read => delete ADDR 
	return 1;
}
uint8_t i2c_sendData(I2C_TypeDef* I2Cx,uint8_t data)
{
	timeout_i2c=TIME_OUT_I2C;
	while (!(I2Cx->SR1 & (1<<7)))
	{
		if(--timeout_i2c==0) return 0;
	} //check TX can run? 
    I2Cx->DR = data;  // send data
	timeout_i2c=TIME_OUT_I2C;
	while (!(I2Cx->SR1 & (1<<2)))
	{
		if(--timeout_i2c==0) return 0;
	} //wait TX finished
	return 3;
}
//uint8_t i2c_Stop(I2C_TypeDef* I2Cx)
//{
//	timeout_i2c=TIME_OUT_I2C;
//	while((!(I2Cx->SR1 & (1<<7)))|(!(I2Cx->SR1 & (1<<2)))) //TX+tranfer finished?
//	{
//		if(--timeout_i2c==0) return 0;
//	}
//	
//	I2Cx->CR1 &= ~(1<<10); //disable ACK
//	I2Cx->CR1 |= (1<<9); //STOP
//	return 2;
//}

uint8_t i2c_Stop(I2C_TypeDef* I2Cx)
{
    I2C1->CR1 |= (1<<9); // G?i Stop
	timeout_i2c=TIME_OUT_I2C;
   while((I2C1->SR2 & (1<<0)) != 0)
	{
			if(timeout_i2c--==0) return 0;
	};
	return 2;
}
uint8_t i2c_readData(I2C_TypeDef *I2Cx,uint8_t ack)
{
    if (ack != 0)
        I2Cx->CR1 |= 1<<10;
    else
        I2Cx->CR1 &= ~(1<<10);
    
    while ((I2Cx->SR1 & (1<<6)) == 0); // Ch? RxNE = 1
    return I2Cx->DR;
}
