#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <emmintrin.h>
#include "miscellaneous.h"



void sequential_dilation(int** in, int** out, int row){
    
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
}
