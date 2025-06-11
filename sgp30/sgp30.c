#include "sgp30.h"

extern I2C_TypeDef *I2Cn=0;

void SGP30_INIT(I2C_TypeDef *I2Cx,I2C_Pin pin)
{
	I2Cn=I2Cx;
	I2Cx_INIT(I2Cx,(I2C_Pin)pin,100000);
}

void SGP30_START(void){
	i2c_Start(I2Cn,0x58,0,0);
	i2c_sendData(I2Cn,0x20); //MSB command
	i2c_sendData(I2Cn,0x03); //LSB command
	i2c_Stop(I2Cn);
}
uint32_t SGP30_READ(void)
{
	uint32_t buff[6];
	
	i2c_Start(I2Cn,0x58,0,0);
	i2c_sendData(I2Cn,0x20); //MSB command
	i2c_sendData(I2Cn,0x08); //LSB command
	i2c_Stop(I2Cn);
	delay_ms(50);
	i2c_Start(I2Cn,0x58,1,0);
	for(int i=0;i<6;i++)
	{
		if(i==5) buff[i] = i2c_readData(I2Cn,0);
		else buff[i] = i2c_readData(I2Cn,1);
	}
	i2c_Stop(I2Cn);
	return (uint32_t) (buff[0]<<8) | buff[1];
}