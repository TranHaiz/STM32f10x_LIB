#include "gauss.h"

int signal_length = 100;
int kernel_size = 7;
double sigma = 1.0;

// Gaussian Kernel
void generate_gaussian_kernel(double *kernel, int size, double sigma) {
    double sum = 0.0;
    int half = size / 2;
    for (int i = 0; i < size; i++) {
        double x = i - half;
        kernel[i] = exp(-(x * x) / (2 * sigma * sigma));
        sum += kernel[i];
    }
    for (int i = 0; i < size; i++) {
        kernel[i] /= sum;
    }
}

// Gaussian Smoothing
void apply_gaussian_filter(double *input, double *output, int length, double *kernel, int kernel_size) {
    int half = kernel_size / 2;
    for (int i = 0; i < length; i++) {
        double sum = 0.0;
        for (int j = 0; j < kernel_size; j++) {
            int index = i + j - half;
            if (index >= 0 && index < length) {
                sum += input[index] * kernel[j];
            }
        }
        output[i] = sum;
    }
}

// B? l?c trung bình (Mean Filter)
void apply_mean_filter(double *input, double *output, int length, int window_size) {
    int half = window_size / 2;
    for (int i = 0; i < length; i++) {
        double sum = 0.0;
        int count = 0;
        for (int j = -half; j <= half; j++) {
            int index = i + j;
            if (index >= 0 && index < length) {
                sum += input[index];
                count++;
            }
        }
        output[i] = sum / count;
    }
}


