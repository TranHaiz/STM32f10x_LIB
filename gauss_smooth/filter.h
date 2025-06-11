#ifndef FILTER_H
#define FILTER_H

#include <math.h>
#include <stdlib.h>
#include "gpio.h"

// kernel Gaussian
void generate_gaussian_kernel(double *kernel, int size, double sigma);
// Gaussian smoothy
void apply_gaussian_filter(double *input, double *output, int length, double *kernel, int kernel_size);
// Average Filter
float avg_uint32_filter(uint32_t *input, int length);
float avg_float_filter(float *input, int length);

#endif
