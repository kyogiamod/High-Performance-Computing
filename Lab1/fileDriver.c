#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int** newMatrix(int rows){
    int** matrix = (int**)malloc(sizeof(int*)*rows);
    
    int i;
    for(i = 0; i < rows; i++){
        matrix[i] = (int*)malloc(sizeof(int)*rows);
    }
    return matrix;
}

int readFile(char* fileName, int** in){

    FILE* file = fopen(fileName, "rb");

    if(!file) { printf("No se puede abrir el archivo"); return 0; }

    // Unknown imagen's dimension, so
    fseek(file, 0L, SEEK_END);
    //ftell will return the total amount of bytes in the file
    int length = ftell(file);
    unsigned char* imgArray = (unsigned char*)malloc(sizeof(char)*length);
    fseek(file, 0L, SEEK_SET);
    fread(imgArray, length, 1, file); //All content is in imgArray
    
    int enteros = (int)(length/4);    

    int i, j;
    int k = 0;
    for(i = 0; i < (int)sqrt(enteros); i++){
        for(j = 0; j < sqrt(enteros); j++){
            in[i][j] = (int)imgArray[4*k];
            k++;
        }
        
    }

    fclose(file);

    return 1;
}

int saveFile(char* fileName, int** out, int rows){

    FILE* file = fopen(fileName, "wb");

    if(!file) { printf("No se pudo abrir el archivo"); return 0; }

    int i,j; 
    for(i = 0; i < rows; i++){
        fwrite(out[i], sizeof(int), rows, file);
    }

    fclose(file);
    return 1;
}

/*
int main(){
    
    int filas = 6;
    int** in = newMatrix(filas);
    int read = readFile("test/my64int.raw", in);
    
    int i,j;
    
	for (i = 0; i < filas; i++)
	{
        for(j = 0; j < filas; j++){
            printf("%d ", in[i][j]);
        }
		printf("\n");
    }

    printf("\n");
    //Testing out
    saveFile("test/out.raw", in, filas);

    int** in2 = newMatrix(filas);
    int read2 = readFile("test/out.raw", in2);

    for (i = 0; i < filas; i++)
	{
        for(j = 0; j < filas; j++){
            printf("%d ", in2[i][j]);
        }
		printf("\n");
    }


    return 0;
}
*/
