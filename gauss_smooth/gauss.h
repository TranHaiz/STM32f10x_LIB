#ifndef GAUSS_H
#define GAUSS_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

// Ð?nh nghia bi?n toàn c?c
extern int signal_length;
extern int kernel_size;
extern double sigma;

// Khai báo các hàm
void generate_gaussian_kernel(double *kernel, int size, double sigma);
void apply_gaussian_filter(double *input, double *output, int length, double *kernel, int kernel_size);
void apply_mean_filter(double *input, double *output, int length, int window_size);
void generate_noisy_signal(double *signal, int length);

#endif
