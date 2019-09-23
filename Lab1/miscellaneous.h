#ifndef _MISCELLANEOUS_H
#define _MISCELLANEOUS_H


typedef struct params{
    char* i;
    char* s;
    char* p;
    int n;
    int d;
}parameters;

int** newMatrix(int rows);
int max(int up, int down, int left, int right);
void showFigure(int** img, int length);
float** int_to_float(int** in, int rows);
void showFigureFloat(float** img, int length);
int** float_to_int(float**in, int length);

#endif