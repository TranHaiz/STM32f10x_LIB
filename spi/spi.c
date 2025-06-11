#include "spi.h"
//------------------------------------------------------------------------------------
#define TIMEOUT 100000
//------------------------------------------------------------------------------------
//void SPIx_INIT(SPI_TypeDef *SPIx,SPI_MODE mode, SPI_SPEED speed,SPI_SIZE data_size){
//	//CONFIG RCC and PIN
//	RCC->APB2ENR |= 1<<0; //AFIO
//	if(SPIx==SPI1) { 
//		RCC->APB2ENR |= 1<<12;
//		GPIOx_INIT(GPIOA,5,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED); //CLK
//		GPIOx_INIT(GPIOA,7,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED); //MOSI
//		GPIOx_INIT(GPIOA,6,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED); //MISO
////		GPIOx_INIT(GPIOA,4,MODE_OUTPUT_PP,NO_PULL,HIGH_SPEED); //CHIP SELECT
//		
//	}
//	else if(SPIx==SPI2) {
//		RCC->APB1ENR |= 1<<14;
//		GPIOx_INIT(GPIOB,13,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED); //CLK
//		GPIOx_INIT(GPIOB,15,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED); //MOSI
//		GPIOx_INIT(GPIOB,14,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED); //MISO
////		GPIOx_INIT(GPIOB,12,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED); //CHIP SELECT
//	}
//	
//	//select mode master or slave
//	SPIx->CR1 |= mode<<2; //mode master or slave
//	if(mode) SPIx->CR1 |= 1<<8; 
//	SPIx->CR1 &= ~(1<<10); //FULL DUPLEX
//	SPIx->CR1 |= data_size<<11; //fram 8bit or 16 bit
//	SPIx->CR1 |= (0<<0)|(1<<1); //Clock polarity and  Clock phase
//	SPIx->CR1 |= 1<<9; //Software slave management enaabled 
//	SPIx->CR1 &= ~(7<<3); //delete old speed
//	SPIx->CR1 |= speed<<3; //set new speed
//	SPIx->CR1 |= 0<<7; //MSB transmitted first
//	
//	SPIx->CR1 |= 1<<6; //enable SPI
//}

//init cho spi
void SPIx_INIT(SPI_TypeDef *SPIx, SPI_MODE mode, SPI_SPEED speed, SPI_SIZE data_size){
	RCC->APB2ENR |= 1<<0; // AFIO enable

	if(SPIx==SPI1) {
		RCC->APB2ENR |= 1<<12; // SPI1
		GPIOx_INIT(GPIOA,5,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED); // SCK
		GPIOx_INIT(GPIOA,7,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED); // MOSI
		GPIOx_INIT(GPIOA,6,MODE_INPUT,NO_PULL,HIGH_SPEED);        // MISO
	}
	else if(SPIx==SPI2) {
		RCC->APB1ENR |= 1<<14; // SPI2
		GPIOx_INIT(GPIOB,13,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED); // SCK
		GPIOx_INIT(GPIOB,15,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED); // MOSI
		GPIOx_INIT(GPIOB,14,MODE_INPUT,NO_PULL,HIGH_SPEED);        // MISO
	}

	SPIx->CR1 = 0; // reset tru?c
	SPIx->CR2 = 0;

	SPIx->CR1 |= mode<<2; // MSTR n?u có

	if(mode) SPIx->CR1 |= 1<<8; // SSI n?u master

	SPIx->CR1 &= ~(1<<10); // full duplex
	SPIx->CR1 |= data_size<<11; // 8bit ho?c 16bit
	SPIx->CR1 &= ~((1<<1)|(1<<0)); // CPOL = 0, CPHA = 0 ? SPI mode 0
	SPIx->CR1 |= 1<<9; // SSM enable
	SPIx->CR1 &= ~(7<<3); // clear BR bits
	SPIx->CR1 |= speed<<3; // set BR
	SPIx->CR1 &= ~(1<<7); // MSB first
	SPIx->CR1 |= 1<<6; // enable SPI
}


void SPIx_WRITE(SPI_TypeDef *SPIx,uint8_t data){
	uint32_t timeout=TIMEOUT;
	SPIx->DR = data;
	while(!(SPIx->SR & (1<<1)))
	{
		if(--timeout==0) return;
	}; //wait transmit finished
}

uint8_t SPIx_READ(SPI_TypeDef *SPIx){
	uint32_t timeout=TIMEOUT;
	while(!(SPIx->SR & (1<<0)))
	{
		if(--timeout==0) return 0;
	}; //wait data
	return SPIx->DR;
}

//uint8_t SPIx_Duplex_8bit(SPI_TypeDef *SPIx,uint8_t tx_data){
//	
//	SPIx->DR = tx_data;
//	timeout=TIMEOUT;
//	while(!(SPIx->SR & (1<<1)))
//	{
//		if(--timeout==0) return 8;
//	}; //wait transmit finished
//	
//	while(!(SPIx->SR & (1<<0)))
//	{
//		if(--timeout==0) return 8;
//	}; //wait data
//	return SPIx->DR;
//}

void SPIx_Duplex_8bit(SPI_TypeDef *master, SPI_TypeDef *slave,
                      uint8_t tx_data_master, uint8_t tx_data_slave,
                      uint8_t *rx_master, uint8_t *rx_slave){
    uint32_t timeout = TIMEOUT;
    slave->DR = tx_data_slave;     // slave preload
    master->DR = tx_data_master;   // master sends

    while (!(master->SR & (1 << 1))) if (--timeout == 0) return;
    while (!(master->SR & (1 << 0))) if (--timeout == 0) return;
    *rx_master = master->DR;

    while (!(slave->SR & (1 << 0))) if (--timeout == 0) return;
    *rx_slave = slave->DR;
}
uint8_t SPIxx_Duplex_8bit(SPI_TypeDef *SPIx,uint8_t tx_data)
{	
	uint32_t timeout=TIMEOUT;
	while (!(SPI1->SR & SPI_SR_TXE))
	{
		if(--timeout == 0) return 2; //cant tran
	};
  SPI1->DR = tx_data;
	timeout=TIMEOUT;
  while (!(SPI1->SR & SPI_SR_RXNE))
	{
		if(--timeout == 0) return 3; //cant reac
	};
  return (uint8_t) SPI1->DR;
}
