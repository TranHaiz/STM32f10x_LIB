#ifndef CONVT_H
#define CONVT_H

#include <stdio.h>
#include <stdint.h>
#include <math.h>

float Float8i8d_ToFloat(uint8_t int_part, uint8_t dec_part);
float Float16d_ToFloat(uint8_t msb, uint8_t lsb);
void Float8i8d_FromFloat(float value, uint8_t *int_part, uint8_t *dec_part);
void Float16i8d_FromFloat(float value, uint8_t *msb, uint8_t *lsb, uint8_t *dec_part);
void Float16d_FromFloat(float value, uint8_t *msb, uint8_t *lsb);

#endif