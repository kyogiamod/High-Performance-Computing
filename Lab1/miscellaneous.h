#ifndef _MISCELLANEOUS_H
#define _MISCELLANEOUS_H


typedef struct params{
    char* i;
    char* s;
    char* p;
    int n;
    int d;
}parameters;

int** newMatrixInt(int rows);
float** newMatrixFloat(int rows);
int max(int up, int down, int left, int right);
void showFigureInt(int** img, int length);
void showFigureFloat(float** img, int length);
float** int_to_float(int** in, int rows);
int** float_to_int(float**in, int length);
parameters getopts(int argc, char** argv);

#endif