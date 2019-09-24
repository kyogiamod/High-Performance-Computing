#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <emmintrin.h>
#include "miscellaneous.h"



double sequential_dilation(int** in, int** out, int row){
    
    clock_t start = clock();	

    int i, j;
    //Bordes horizontales
    for(i = 0; i < row; i=(i+row-1)){
        for(j = 0; j < row; j++){
            out[i][j] = in[i][j];
        }        
    }

    //Bordes verticales
    for(i = 0; i < row; i++){
        for(j = 0; j < row; j=(j+row-1)){
            out[i][j] = in[i][j];
        }
    }

    //Centro
    for(i = 1; i < (row - 1); i++){
        for(j = 1; j < (row - 1); j++){
            out[i][j] = max(in[i-1][j], in[i+1][j], in[i][j-1], in[i][j+1]);
        }
    }

    clock_t finish = clock();
    return ((double)(finish-start)/CLOCKS_PER_SEC);	

}

double simd_dilation(float** in, float** out, int rows){

    clock_t start = clock();	

    __m128 R0, R1, R2, R3, R4, R_max_vertical, R_max_horizontal, R_max;

    int i,j;

    for(i = 1; i < rows; i++){
        for(j = 1; j < rows; j=(j+4)){
            //load data
            R0 = _mm_loadu_ps(&in[i-1][j]);
            R1 = _mm_loadu_ps(&in[i][j-1]);
            if((i + 1 ) >= rows){ //just border condition
                R2 = _mm_setzero_ps();
            } else {
                R2 = _mm_loadu_ps(&in[i+1][j]);
            }
            R3 = _mm_loadu_ps(&in[i][j+1]);
            R4 = _mm_setzero_ps();

            //max in all R
            R_max_vertical = _mm_max_ps(R0, R2);
            R_max_horizontal = _mm_max_ps(R1, R3);
            R_max = _mm_max_ps(R_max_horizontal, R_max_vertical);

            //R4 is the max of all registers
            R4 = _mm_max_ps(R4, R_max);

            // save in the position
            _mm_storeu_ps(&out[i][j], R4);
        }
    }

    clock_t finish = clock();	
    return ((double)(finish-start)/CLOCKS_PER_SEC);	

}
