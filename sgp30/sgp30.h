#ifndef SGP30_H_
#define SGP30_H_

#include "i2c.h"
#include "systick.h"


void SGP30_INIT(I2C_TypeDef *I2Cx,I2C_Pin pin);\
void SGP30_START(void);
uint32_t SGP30_READ(void);

#endif