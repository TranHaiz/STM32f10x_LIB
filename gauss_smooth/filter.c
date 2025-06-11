#include "filter.h"
// kernel Gaussian
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
// Gaussian
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
// Average Filter
float avg_uint32_filter(uint32_t *input, int length) {
	float sum=0;
	for (int i = 0; i < length; i++)
	{
		sum += (float)input[i];
	}
    return sum / length; 
}
float avg_float_filter(float *input, int length) {
	float sum=0;
	for (int i = 0; i < length; i++)
	{
		sum += input[i];
	}
    return sum / length; 
}
