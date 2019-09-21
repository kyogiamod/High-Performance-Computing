#include <stdlib.h>
#include <stdio.h>

int** newMatrix(int rows){
    int** matrix = (int**)malloc(sizeof(int*)*rows);
    
    int i;
    for(i = 0; i < rows; i++){
        matrix[i] = (int*)malloc(sizeof(int)*rows);
    }
    return matrix;
}

int max(int up, int down, int left, int right){
    int v = up > down ? up : down;
    int h = left > right ? left : right;
    int max = v > h ? v : h;
    return max;
}


void showFigure(int** img, int length){
    int i,j;
    
	for (i = 0; i < length; i++)
	{
        printf("%d: ", i);
        for(j = 0; j < length; j++){
            printf("%d ", img[i][j]==0?0:1);
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

void showFigureFloat(float** img, int length){

    int i,j;
	for (i = 0; i < length; i++)
	{
        printf("%d: ", i);
        for(j = 0; j < length; j++){
            printf("%d ", img[i][j]==0?0:1);
        }
		printf("\n");
    }
}

int** float_to_int(float**in, int length){

    int** out = newMatrix(length);
    int i,j;
    for(i = 0; i < length; i++){
        for(j = 0; j < length; j++){
            out[i][j] = (int)in[i][j];
        }
    }

    return out;
}