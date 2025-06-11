#include "convt.h"

float Float8i8d_ToFloat(uint8_t int_part, uint8_t dec_part) {
    return (float)int_part + (float)dec_part / 100.0f;
}

float Float16d_ToFloat(uint8_t msb, uint8_t lsb) {
    uint16_t scaled = ((uint16_t)msb << 8) | lsb;
    return (float)scaled / 10000.0f;
}

void Float8i8d_FromFloat(float value, uint8_t *int_part, uint8_t *dec_part) {
    *int_part = (uint8_t)value;
    *dec_part = (uint8_t)(roundf((value - (int)value) * 100));
}

void Float16i8d_FromFloat(float value, uint8_t *msb, uint8_t *lsb, uint8_t *dec_part) {
    uint16_t whole = (uint16_t)value;
    *msb = (whole >> 8) & 0xFF;
    *lsb = whole & 0xFF;
    *dec_part = (uint8_t)(roundf((value - (float)whole) * 100));
}

void Float16d_FromFloat(float value, uint8_t *msb, uint8_t *lsb) {
    uint16_t scaled = (uint16_t)(value * 10000);
    *msb = (scaled >> 8) & 0xFF;
    *lsb = scaled & 0xFF;
}

