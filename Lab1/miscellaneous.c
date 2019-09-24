#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>  
#include "miscellaneous.h"


int** newMatrixInt(int rows){
    int** matrix = (int**)malloc(sizeof(int*)*rows);
    
    int i;
    for(i = 0; i < rows; i++){
        matrix[i] = (int*)malloc(sizeof(int)*rows);
    }
    return matrix;
}

float** newMatrixFloat(int rows){
    float** matrix = (float**)malloc(sizeof(float*)*rows);
    
    int i;
    for(i = 0; i < rows; i++){
        matrix[i] = (float*)malloc(sizeof(float)*rows);
    }
    return matrix;
}

int max(int up, int down, int left, int right){
    int v = up > down ? up : down;
    int h = left > right ? left : right;
    int max = v > h ? v : h;
    return max;
}


void showFigureInt(int** img, int length){
    int i,j;
    
	for (i = 0; i < length; i++)
	{
        for(j = 0; j < length; j++){
            printf("%d ", img[i][j]==0?0:1);
        }
		printf("\n");
    }
}

void showFigureFloat(float** img, int length){
    int i,j;
    
	for (i = 0; i < length; i++)
	{
        for(j = 0; j < length; j++){
            printf("%d ", img[i][j]==0.0?0:1);
        }
		printf("\n");
    }
}

float** int_to_float(int** in, int rows){

    float** out = (float**)malloc(sizeof(float*)*rows);
    
    int i,j;
    for(i = 0; i < rows; i++){
        out[i] = (float*)malloc(sizeof(float)*rows);
        for(j = 0; j < rows; j++){
            out[i][j] = (float)in[i][j];
        }
    }
    return out;
}

int** float_to_int(float**in, int length){

    int** out = newMatrixInt(length);
    int i,j;
    for(i = 0; i < length; i++){
        for(j = 0; j < length; j++){
            out[i][j] = (int)in[i][j];
        }
    }

    return out;
}

parameters getopts(int argc, char **argv){

    parameters params;

    int opt;
    while((opt = getopt (argc, argv, "i:s:p:N:D:")) != -1){
        switch(opt){
            case 'i':
                params.i = optarg;
                break;
            case 's':
                params.s = optarg;
                break;
            case 'p':
                params.p = optarg;
                break;
            case 'N':
                params.n = atoi(optarg);
                break;
            case 'D':
                params.d = atoi(optarg);
                break;
            case ':':
                printf("La opcion %s necesita un valor\n", optarg);
                break;
            case '?':
                printf("Existe una opcion desconocida\n");
                exit(-1);
        }
    }
    for(; optind < argc; optind++){      
        printf("Argumentos extras: %s\n", argv[optind]); 
        exit(-1); 
    } 
    return params;
}


