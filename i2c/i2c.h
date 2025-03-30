#ifndef I2C_H_
#define I2C_H_

#include <stm32f10x.h>
#include "gpio.h"

#define TIME_OUT_I2C 10000000

typedef enum 
{
	I2C1_Pin_PB6PB7,  // I2C1  SCL = PB6, SDA = PB7
	I2C1_Pin_PB8PB9,  // I2C1  SCL = PB8, SDA = PB9
	I2C2_Pin_PB10PB11 // I2C2  SCL = PB10, SDA = PB11
} I2C_Pin;

void I2Cx_INIT(I2C_TypeDef *I2Cx,I2C_Pin pin,uint32_t speed);
void checkBusy(void);
uint8_t i2c_Start(I2C_TypeDef *I2Cx,uint8_t add,uint8_t dir,uint8_t ack);
uint8_t i2c_sendData(I2C_TypeDef* I2Cx,uint8_t data);
//uint8_t i2c_readData(I2C_TypeDef *I2Cx,uint8_t ack);
uint8_t i2c_Stop(I2C_TypeDef* I2Cx);


#endif