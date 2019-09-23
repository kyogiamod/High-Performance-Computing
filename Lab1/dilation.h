#ifndef _DILATION_H
#define _DILATION_H


double sequential_dilation(int** in, int** out, int row);
double simd_dilation(float** in, float** out, int rows);


#endif