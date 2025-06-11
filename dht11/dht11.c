#include "dht11.h"

GPIO_TypeDef *dht_port;
uint8_t dht_pin; 

extern volatile uint8_t dht_data[5] = {0};

void dht_init(GPIO_TypeDef *GPIOx,uint8_t pin) {
	dht_port = GPIOx;
	dht_pin = pin;
}
uint8_t DHT11_READ(void){
	return ((dht_port->IDR >> dht_pin) & 1);
}
void dht_start(void) {
    GPIOx_INIT(dht_port, dht_pin, MODE_OUTPUT_OD, NO_PULL, HIGH_SPEED);
		delay_us(1);
    GPIOx_WRITE(dht_port, dht_pin, 0);
    delay_ms(20);
    GPIOx_WRITE(dht_port, dht_pin, 1);
		delay_us(30);
		GPIOx_INIT(dht_port, dht_pin, MODE_INPUT_FLOAT, NO_PULL, HIGH_SPEED);
}
uint8_t dht_wait_state(uint8_t state, uint32_t timeout) {
    while (DHT11_READ() != state) {
        if (--timeout == 0) return 1;
        delay_us(1);
    }
    return 0;
}
uint8_t dht_read(void) {
    dht_start();
    if (dht_wait_state(0, 100) || dht_wait_state(1, 100) || dht_wait_state(0, 100)) {
        return 0; //dht not reponse
    }
		//READ RAW DATA 40 BIT
    for (uint8_t i = 0; i < 5; i++) {
        for (uint8_t j = 0; j < 8; j++) {
            while (!DHT11_READ());
            delay_us(40);
            dht_data[i] <<= 1;
            if (DHT11_READ()) dht_data[i] |= 1;
            while (DHT11_READ());
        }
    }
		//CHECK SUM
    if ((dht_data[0] + dht_data[1] + dht_data[2] + dht_data[3]) == dht_data[4]) {
        return 1; //finished
    }
    return 2; // error
}
float dht_hum(void)
{
	if(dht_read() == 1) 
	{
		if(dht_data[1]<10)
			return (float)dht_data[0] + (float)dht_data[1] / 10.0;
		else if (dht_data[1]>=100) 
			return (float)dht_data[0] + (float)dht_data[1] / 1000.0;
		else 
			return (float)dht_data[0] + (float)dht_data[1] / 100.0;
	}
	else 
		return 0; // can't read humidity
}

float dht_temp(void)
{
	if (dht_read() == 1)
	{
		if(dht_data[3]<10) 
			return (float)dht_data[2] + (float)dht_data[3] / 10.0;
		else if (dht_data[3]>=100) 
			return (float)dht_data[2] + (float)dht_data[3] / 1000.0;
		else 
			return (float)dht_data[2] + (float)dht_data[3] / 100.0;
		
	}
	else 	
		return 0; //cant read temp
}

void dht_temp_hum(float *temp,float *hum){
	if( dht_read() == 1)
	{
		if(dht_data[1]<10)
			*hum = (float)dht_data[0] + (float)dht_data[1] / 10.0;
		else if (dht_data[1]>=100) 
			*hum = (float)dht_data[0] + (float)dht_data[1] / 1000.0;
		else 
			*hum = (float)dht_data[0] + (float)dht_data[1] / 100.0;
		
		if(dht_data[3]<10) 
			*temp = (float)dht_data[2] + (float)dht_data[3] / 10.0;
		else if (dht_data[3]>=100) 
			*temp = (float)dht_data[2] + (float)dht_data[3] / 1000.0;
		else 
			*temp = (float)dht_data[2] + (float)dht_data[3] / 100.0;
	}
}