#ifndef SD_H
#define SD_H

#include "gpio.h"
#include "systick.h"

#define SPI1_ID 1
#define SPI2_ID 2

#define SPIx_ID SPI1_ID

#if SPIx_ID == SPI1_ID
		#define SPIx SPI1
    #define cs_high GPIOx_WRITE(GPIOA,4,1)
		#define cs_low GPIOx_WRITE(GPIOA,4,0)
#elif SPIx_ID == SPI2_ID
    #define SPIx SPI2
		#define SPIx SPI2
    #define cs_high GPIOx_WRITE(GPIOB,12,1)
		#define cs_low GPIOx_WRITE(GPIOB,12,0)
#endif

// SD Card Commands
#define CMD0    0   // GO_IDLE_STATE
#define CMD8    8   // SEND_IF_COND
#define CMD9    9   // SEND_CSD
#define CMD10   10  // SEND_CID
#define CMD17   17  // READ_SINGLE_BLOCK
#define CMD18   18  // READ_MULTIPLE_BLOCK
#define CMD12   12  // STOP_TRANSMISSION
#define CMD55   55  // APP_CMD
#define ACMD41  41  // SD_SEND_OP_COND
#define CMD13		13
#define CMD24		24
#define CMD59		59

// SD Card Response types
#define R1_IDLE_STATE           0x01
#define R1_ILLEGAL_COMMAND      0x04

// Data tokens
#define DATA_START_TOKEN        0xFE
#define DATA_ERROR_TOKEN        0x01
#define DATA_REJECTED_CRC       0x05
#define DATA_REJECTED_WRITE     0x06

uint8_t spi_transfer(uint8_t data);
uint8_t sd_send_command(uint8_t cmd, uint32_t arg);
bool sd_init_idle_state(void);
bool sd_read_single_block(uint32_t block_addr, uint8_t* buffer);
bool sd_read_multiple_blocks(uint32_t start_block, uint32_t block_count, uint8_t* buffer);
bool sd_wait_data_token(void);
uint16_t sd_calculate_crc16(uint8_t* data, uint16_t length);
uint8_t sd_write_single_block(uint32_t block_addr, const uint8_t *buffer);

#endif