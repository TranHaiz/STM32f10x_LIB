/*
	 HUYNH NGOC THUONG
	 DA NANG UNIVERSITY OF SCIENCE AND TECHNOLOGY
	 Last modified: 1/05/2018 - Version 2
	 **Describe: 
	 +SDcard by module SD and STM32F103C8T6
	 +In this project i had used: 
	 +Thirt party: FreeRTOS
	 +Thirt party: FATFS
	 +Comunicate protocol: SPI1 or you can change other SPI if you want
	 +Timer: TIM2 for turn on or turn off
	 +UART: UART1 for observation data from SPI
 *Facebook: ngocthuong0208 - huynhngocthuong0208@gmail.com - 01216911759
*/

#ifndef SD_H_
#define SD_H_
//--------------------------------------------------
#include "spi.h"
#include "systick.h"
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
//--------------------------------------------------

#define CS_SD_GPIO_PORT GPIOA
#define CS_SD_PIN 3
#define SPI_SD SPI1

#define SS_SD_SELECT() GPIOx_WRITE(CS_SD_GPIO_PORT, CS_SD_PIN, 0)
#define SS_SD_DESELECT() GPIOx_WRITE(CS_SD_GPIO_PORT, CS_SD_PIN, 1)
#define LD_ON GPIOx_WRITE(GPIOC, 13, 0); //LED13 OFF
#define LD_OFF GPIOx_WRITE(GPIOC, 13, 1); //LED13 ON
//--------------------------------------------------
/* Card type flags (CardType) */
#define CT_MMC 0x01 /* MMC ver 3 */
#define CT_SD1 0x02 /* SD ver 1 */
#define CT_SD2 0x04 /* SD ver 2 */
#define CT_SDC (CT_SD1|CT_SD2) /* SD */
#define CT_BLOCK 0x08 /* Block addressing */
//--------------------------------------------------
// Definitions for MMC/SDC command
#define CMD0 (0x40+0) // GO_IDLE_STATE
#define CMD1 (0x40+1) // SEND_OP_COND (MMC)
#define ACMD41 (0xC0+41) // SEND_OP_COND (SDC)
#define CMD8 (0x40+8) // SEND_IF_COND
#define CMD9 (0x40+9) // SEND_CSD
#define CMD16 (0x40+16) // SET_BLOCKLEN
#define CMD17 (0x40+17) // READ_SINGLE_BLOCK
#define CMD24 (0x40+24) // WRITE_BLOCK
#define CMD55 (0x40+55) // APP_CMD
#define CMD58 (0x40+58) // READ_OCR
//--------------------------------------------------
typedef struct sd_info 
{
  volatile uint8_t type;//type of card that we use
} sd_info_ptr;
struct sd_data
{
	uint8_t size;
	uint8_t rdata[1000];
  char wdata[100];
	char filename[];
};
//--------------------------------------------------
//FATFS SDFatFs; //File system object structure (FATFS)
//FATFS *fs;		 //File system object structure (FATFS)
extern 
uint8_t sect[512];
extern 
uint32_t bytesread; //byte doc va ghi
//--------------------------------------------------
void SD_PowerOn(void);
uint8_t sd_init(void);
void SPI_Release(void);
uint8_t SD_Read_Block (uint8_t *buff, uint32_t lba);
uint8_t SD_Write_Block (uint8_t *buff, uint32_t lba);
uint8_t SPI_wait_ready(void);
//--------------------------------------------------

//FRESULT ReadLongFile(void);

//void SD_Write_File(const char* filename, const char* buffer, uint8_t size);
//uint8_t* SD_Read_File(const char* filename);
//void SD_List_File(void);
//unsigned long SD_Amount_Space(void);
//void SD_creatSubDir(char* filename);
//void SD_deleteFile(char* filename);
//void SD_deleteFolder(char* foldername);
//void SD_deleteAllFile(void);
//int32_t getFileSize(char* filename);
//uint8_t* _SD_Read_File(const char* filename,uint16_t numbyte,uint16_t index);
//FRESULT _ReadLongFile(uint16_t numbyte,uint16_t index);

//--------------------------------------------------
void display(char* data);

#endif /* SD_H_ */
