#include "sd.h"


static void system_init(void){
	//enable clk n config pin
	if(SPIx==SPI1) {
		RCC->APB2ENR |= 1<<12; // SPI1
		GPIOx_INIT(GPIOA,4,MODE_OUTPUT_PP,NO_PULL,HIGH_SPEED);			//CS
		GPIOx_INIT(GPIOA,5,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED); // SCK
		GPIOx_INIT(GPIOA,7,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED); // MOSI
		GPIOx_INIT(GPIOA,6,MODE_INPUT,NO_PULL,HIGH_SPEED);        // MISO
	}
	else if(SPIx==SPI2) {
		RCC->APB1ENR |= 1<<14; // SPI2
		GPIOx_INIT(GPIOB,12,MODE_OUTPUT_PP,NO_PULL,HIGH_SPEED);	 		//CS
		GPIOx_INIT(GPIOB,13,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED); // SCK
		GPIOx_INIT(GPIOB,15,MODE_OUTPUT_AF_PP,NO_PULL,HIGH_SPEED); // MOSI
		GPIOx_INIT(GPIOB,14,MODE_INPUT,NO_PULL,HIGH_SPEED);        // MISO
	}
	//RESET BEFORE CONFIG
	SPIx->CR1 = 0;
	SPIx->CR2 = 0;
	// Master mode, baud rate th?p nh?t, software NSS
	SPIx-> CR1 = (1 << 2) |       // Master mode
               (7 << 3) |      	// Baud rate = fPCLK/256 (slowest)
               (1 << 9) |         // Software slave management
               (1 << 8);          // Internal slave select
	
	SPIx->CR1 |= (1 << 6); //SPI ENABLE
}

//DUPLEX
uint8_t spi_transfer(uint8_t data) {    
    // Wait for TXE (transmit buffer empty)
    uint16_t timeout = 1000;
    while (!(SPIx->SR & (1 << 1)) && timeout > 0) {
        timeout--;
    }
		if (timeout == 0) {
        return 0xFE;
    }
    // Send data
    SPIx->DR = data;
    // Wait for RXNE (receive buffer not empty)
    timeout = 1000;
    while (!(SPIx->SR & (1 << 0)) && timeout > 0) {
        timeout--;
    }
    if (timeout == 0) {
        return 0xFF;
    }
    return (uint8_t)SPIx->DR;
}
//SEND CMD TO SD CARD
uint8_t sd_send_command(uint8_t cmd, uint32_t arg) {    
    uint8_t response;
    uint8_t retry = 0;
    
    // Select SD card
    cs_low;
		delay_ms(1);
    // G?i command packet (6 bytes)
    spi_transfer(0x40 | cmd);           // Command index v?i start bit
    spi_transfer((arg >> 24) & 0xFF);   // Argument [31:24]
    spi_transfer((arg >> 16) & 0xFF);   // Argument [23:16] 
    spi_transfer((arg >> 8) & 0xFF);    // Argument [15:8]
    spi_transfer(arg & 0xFF);           // Argument [7:0]
    
    // CRC cho các command c? th?
    if (cmd == CMD0) {
        spi_transfer(0x95);  // CRC7 + end bit cho CMD0
    } else if (cmd == CMD8) {
        spi_transfer(0x87);  // CRC7 + end bit cho CMD8
    } else {
        spi_transfer(0x01);  // Dummy CRC + end bit
    }
    
    // WAIT FOR RESPONSE
    for (retry = 0; retry < 8; retry++) {
        response = spi_transfer(0xFF);
        if (response != 0xFF) {
            break;
        }
    }
    
    // Deselect SD card
    cs_high;
    spi_transfer(0xFF); // Extra clock cycles
    return response;
}

//START IDLE		
bool sd_init_idle_state(void) {
    uint8_t response;
    uint16_t retry_count = 0;
    
	// stp1: config system và SPI
    system_init();
    
    // STEP 2: GENERATE 74 CLK PULSE AND CS = HIGH
    cs_high;
    for (uint8_t i = 0; i < 10; i++) {
        spi_transfer(0xFF);
    }
    
    // STEP 3: TRANMIT CMD0 TO ENTER IDLE STATE
    for (retry_count = 0; retry_count < 100; retry_count++) {
        response = sd_send_command(CMD0, 0);
        
        if (response == R1_IDLE_STATE) {
            break;
        }
        
        delay_ms(10);
    }
    
    if (response != R1_IDLE_STATE) {
        return 0;
    }
    
    // STEP 4: TRANSMIT CMD8 TO CHECK voltage range (cho SDHC)
    response = sd_send_command(CMD8, 0x000001AA);
    
    if (response == R1_IDLE_STATE) {        
        // READ ADITIONAL 4 bytes response FOR CMD8
        cs_low;
        for (uint8_t i = 0; i < 4; i++) {
            spi_transfer(0xFF);
        }
        cs_high;
        spi_transfer(0xFF);
        
    } 
		else if (response == (R1_IDLE_STATE | R1_ILLEGAL_COMMAND)) 
			return 0;
     
		else 
			return 0;
    
    
    // STEP 5: TRANSMIT ACMD41 TO COMPLETE GENERATE
    for (retry_count = 0; retry_count < 1000; retry_count++) {
        // TRANSMIT CMD55 BEFORE ACMD41
        response = sd_send_command(CMD55, 0);
        if (response > 1) {
            continue;
        }
        
        // TRANSMIT ACMD41 FOR SHDC
        response = sd_send_command(ACMD41, 0x40000000);
        
        if (response == 0x00) {
            return 1;
        }
        
        if (response != R1_IDLE_STATE) {
            return 0;
        }
        
        delay_ms(50);
    }
    
    return 0;
}

bool sd_wait_data_token(void) {    
    uint16_t timeout = 5000; // Timeout cho data token
    uint8_t token;
    
    while (timeout > 0) {
        token = spi_transfer(0xFF);
        
        if (token == DATA_START_TOKEN) {
            return 1;
        }
        
        if (token != 0xFF) {
            return 0;
        }
        
        timeout--;
    }
    return 0;
}
//ADDITIONAL FUNC
uint16_t sd_calculate_crc16(uint8_t* data, uint16_t length) {
    uint16_t crc = 0;
    
    for (uint16_t i = 0; i < length; i++) {
        crc ^= ((uint16_t)data[i]) << 8;
        
        for (uint8_t bit = 0; bit < 8; bit++) {
            if (crc & 0x8000) {
                crc = (crc << 1) ^ 0x1021; // CRC-16-CCITT polynomial
            } else {
                crc <<= 1;
            }
        }
    }
    
    return crc;
}
//READ SIGNLE BLOCK

bool sd_read_single_block(uint32_t block_addr, uint8_t* buffer) {    
    if (buffer == 0) {
        return 0; //FAIL BECAUSE POINTER IS NULL
    }
    
    // SEND CMD17 (READ_SINGLE_BLOCK)
    uint8_t response = sd_send_command(CMD17, block_addr);
    
    if (response != 0x00) {
        return 0; //FAIL TRANSMIT
    }
        
    // Select SD card và d?i data token
    cs_low;
    
    if (!sd_wait_data_token()) {
        cs_high;
        return 0; // check dã du?c set trong sd_wait_data_token
    }
        
    // READ 512 bytes data
    for (uint16_t i = 0; i < 512; i++) {
        buffer[i] = spi_transfer(0xFF);
    }
        
    // READ 2 bytes CRC
    uint8_t crc_high = spi_transfer(0xFF);
    uint8_t crc_low = spi_transfer(0xFF);
    uint16_t received_crc = (crc_high << 8) | crc_low;
    
    // Deselect SD card
    cs_high;
    spi_transfer(0xFF); // Extra clock cycles    
    
		//FUNCTION CHECK CRC ( OPTIONAL)
		uint16_t calculated_crc = sd_calculate_crc16(buffer, 512);
    if (calculated_crc != received_crc) {
        //DO SOMETHING
    }
		
		return 1; //COMPLETED READING SINGLE BLOCK
}

//READ MULTI BLOCK
bool sd_read_multiple_blocks(uint32_t start_block, uint32_t block_count, uint8_t* buffer) {
    if (buffer == 0 || block_count == 0) {
        return 0;
    }
    
    // SEND CMD18 (READ_MULTIPLE_BLOCK)
    uint8_t response = sd_send_command(CMD18, start_block);
    
    if (response != 0x00) {
        return 0;
    }
        
    // Select SD card
    cs_low;
    
    // READING BLOCKS
    for (uint32_t block = 0; block < block_count; block++) {
        
        // Ð?i data token cho block này
        if (!sd_wait_data_token()) {
            // SEND CMD12 TO stop transmission
            cs_high;
            sd_send_command(CMD12, 0);
            return 0;
        }
        
        // READ BLOCK
        uint8_t* block_buffer = buffer + (block * 512);
        for (uint16_t i = 0; i < 512; i++) {
            block_buffer[i] = spi_transfer(0xFF);
        }
        
        // READ 2 BYTES FOR THIS BLOCK 
        uint8_t crc_high = spi_transfer(0xFF);
        uint8_t crc_low = spi_transfer(0xFF);
        uint16_t received_crc = (crc_high << 8) | crc_low;
        
        // CHECK CRC ( OPTIONAL)
        uint16_t calculated_crc = sd_calculate_crc16(block_buffer, 512);
        if (calculated_crc != received_crc) {
            // DO SOMETHINGS
        }
    }
    
    // Deselect SD card
    cs_high;
    
    // SEND CMD12 TO STOP TRANSMIT
    response = sd_send_command(CMD12, 0);
    
    if (response != 0x00) {
        // NOT RETURN BECAUSE DATA IS READ
    }
    return 1;
}

//WRITE SINGLE BLOCK

//THIS FUNC BELOW NOT USE FOR CMD24 hay CMD17.
uint8_t sd_send_command_hold_cs(uint8_t cmd, uint32_t arg) 
{
    uint8_t response;
    uint8_t retry = 0;

    cs_low;
    delay_ms(1);

    spi_transfer(0x40 | cmd);
    spi_transfer((arg >> 24) & 0xFF);
    spi_transfer((arg >> 16) & 0xFF);
    spi_transfer((arg >> 8) & 0xFF);
    spi_transfer(arg & 0xFF);

    if (cmd == CMD0)
        spi_transfer(0x95);
    else if (cmd == CMD8)
        spi_transfer(0x87);
    else
        spi_transfer(0x01);

    for (retry = 0; retry < 8; retry++) {
        response = spi_transfer(0xFF);
        if (response != 0xFF) break;
    }

    return response;
}

uint8_t sd_write_single_block(uint32_t block_addr, const uint8_t *buffer) {
    uint16_t timeout = 0xFFFF;
    while ((spi_transfer(0xFF) != 0xFF) && timeout--);
    if (timeout == 0) {
        cs_high;
        return 4; // BUSY BEFORE WRITE
    }

    // SEND CMD24
    uint8_t response = sd_send_command_hold_cs(CMD24, block_addr);
    if (response != 0x00) {
        cs_high;
        return 5; //CANT WRITE
    }

    spi_transfer(0xFE); // Start block token

    for (int i = 0; i < 512; i++) {
        spi_transfer(buffer[i]);
    }

    spi_transfer(0xFF);
    spi_transfer(0xFF);

    uint8_t data_resp = spi_transfer(0xFF);
    if ((data_resp & 0x1F) != 0x05) {
        cs_high;
        return 6; //NOT ACP DATA SENDED
    }

    timeout = 0xFFFF;
    while ((spi_transfer(0xFF) == 0x00) && timeout--);
    if (timeout == 0) {
        cs_high;
        return 3;
    }

    cs_high;
    spi_transfer(0xFF);
		
		if(sd_send_command(CMD12,0)==0)
			return 7; // SUCCESS
		else return 8; //FAIL TO STOP TRANSMIT
}


