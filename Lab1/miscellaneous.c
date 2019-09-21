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