#include <stdio.h>
#include "fileDriver.h"
#include "dilation.h"
#include "miscellaneous.h"

int main(){

    int filas = 6;
    int** in = newMatrix(filas);
    int read = readFile("test/my64int.raw", in);
    
    int i,j;
    
	showFigure(in, filas);

    printf("\n");
    //Testing out
    saveFile("test/out.raw", in, filas);

    int** in2 = newMatrix(filas);
    int read2 = readFile("test/out.raw", in2);

    showFigure(in2, filas);


    return 0;
}