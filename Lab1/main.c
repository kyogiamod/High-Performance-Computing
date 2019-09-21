#include <stdio.h>
#include <stdlib.h>
#include "fileDriver.h"
#include "dilation.h"
#include "miscellaneous.h"

int main(){

    int filas = 8;
    int** in = newMatrix(filas);
    int read = readFile("test/my64int.raw", in);
    
    int** outSeq = newMatrix(filas);
    sequential_dilation(in, outSeq, filas);
    saveFile("test/my64intoutsequential.raw", outSeq, filas);

    float** in2 = int_to_float(in, filas);
    float** outSIMD = (float**)malloc(sizeof(float*)*filas);
    int i,j;
    for(i = 0; i < filas; i++){ outSIMD[i] = (float*)malloc(sizeof(float)*filas); }

    simd_dilation(in2, outSIMD, filas);

    int** toInt = float_to_int(outSIMD, filas);

    saveFile("test/my64intout.raw", toInt, filas);
    
    return 0;
}