#include <stdio.h>
#include <stdlib.h>

int readFile(char* fileName, int* in){

    FILE* file = fopen(fileName, "rb");

    if(!file) { printf("No se puede abrir el archivo"); return 0; }

    // Unknown imagen's dimension, so
    fseek(file, 0L, SEEK_END);
    //ftell will return the total amount of bytes in the file
    int length = ftell(file);

    char* imgArray = (char*)malloc(sizeof(char)*length);
    fseek(file, 0L, SEEK_SET);
    fread(imgArray, length, 1, file); //All content is in imgArray
    
    int i;
    for(i = 0; i < length; i++){
        in[i] = (int)imgArray[4*i];
    }

    fclose(file);

    return 1;
}

int saveFile(char* fileName, int* out, int rows){

    FILE* file = fopen(fileName, "wb");

    if(!file) { printf("No se pudo abrir el archivo"); return 0; }

    int length = rows * rows * sizeof(int);
    if(fwrite(out, length, 1, file) < 1) { 
        printf("Error guardando en el archivo");
        return 0;
    }
    return 1;
}
