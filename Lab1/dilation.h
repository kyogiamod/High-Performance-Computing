#ifndef _DILATION_H
#define _DILATION_H


void sequential_dilation(int** in, int** out, int row);
void simd_dilation(float** in, float** out, int rows);


#endif