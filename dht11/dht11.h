#ifndef DHT11_H_
#define DHT11_H_

#include "systick.h"
#include "gpio.h"

float dht_hum(void);
float dht_temp(void);
void dht_temp_hum(float *temp,float *hum);
void dht_init(GPIO_TypeDef *GPIOx,uint8_t pin);

#endif