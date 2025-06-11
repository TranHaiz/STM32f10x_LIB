#ifndef SPI_H
#define SPI_H

#include "gpio.h"


typedef enum{
	slave,
	master
	
} SPI_MODE;
typedef enum{
	size8bit,
	size16bit
	
} SPI_SIZE;
typedef enum
{
	fplk_div2,
	fplk_div4,
	fplk_div8,
	fplk_div16,
	fplk_div32,
	fplk_div64,
	fplk_div128,
	fplk_div256
} SPI_SPEED;

void SPIx_INIT(SPI_TypeDef *SPIx,SPI_MODE mode, SPI_SPEED speed,SPI_SIZE data_size);
void SPIx_WRITE(SPI_TypeDef *SPIx,uint8_t data);
uint8_t SPIx_READ(SPI_TypeDef *SPIx);
void SPIx_Duplex_8bit(SPI_TypeDef *master, SPI_TypeDef *slave,
                      uint8_t tx_data_master, uint8_t tx_data_slave,
                      uint8_t *rx_master, uint8_t *rx_slave);
uint8_t SPIxx_Duplex_8bit(SPI_TypeDef *SPIx,uint8_t tx_data);

#endif
