#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fileDriver.h"
#include "dilation.h"
#include "miscellaneous.h"
#include <math.h>

int main(int argc, char** argv){

    parameters params= getopts(argc, argv);

    int length = params.n;

    int** in = newMatrixInt(length);
    int read = readFile(params.i, in);
    
    int** outSeq = newMatrixInt(length);
    double seqTime = sequential_dilation(in, outSeq, length);
    saveFile(params.s, outSeq, length);

    float** in2 = int_to_float(in, length);
    float** outSIMD = newMatrixFloat(length);
    double simdTime = simd_dilation(in2, outSIMD, length);
    int** intSIMD = float_to_int(outSIMD, length);
    saveFile(params.p, intSIMD, length);
    
    printf("El tiempo secuencial es: %f[s]\nEl tiempo SIMD es: %f[s]\n", seqTime, simdTime);

    if(params.d){
        printf("Imagen secuencial:\n");
        showFigureInt(outSeq, length);
        printf("\nImagen SIMD:\n");
        showFigureFloat(outSIMD, length);
    }
    return 0;
}

