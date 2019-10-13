#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct posMatrix
{
    double inf_x;
    double inf_y;
    double sup_x;
    double sup_y;
} coordinate;

typedef struct complejo
{
    double r;
    double i;
} complex;

double complex_distance(complex c)
{
    return sqrt(c.r * c.r + c.i * c.i);
}

complex pow2(complex c)
{
    complex final;
    final.r = pow(c.r, 2) - pow(c.i, 2);
    final.i = 2 * c.r * c.i;
    return final;
}

complex csum(complex c1, complex c2)
{
    complex c;
    c.r = c1.r + c2.r;
    c.i = c1.i + c2.i;
    return c;
}

double **new_matrix(int rows, int cols)
{
    double **matrix = (double **)malloc(sizeof(double *) * rows);
    int i, j;
    for (i = 0; i < rows; i++)
    {
        matrix[i] = (double *)malloc(sizeof(double) * cols);
    }
    return matrix;
}

char *new_string(int length)
{
    char *string = (char *)malloc(sizeof(char) * length);
    return string;
}

double mandel_algorithm(double x, double y, int depth)
{
    int n = 1;
    complex z, c;
    c.r = x;
    c.i = y;

    z = c;
    while (complex_distance(z) < 2 && n < depth)
    {
        z = pow2(z);
        z = csum(z, c);
        n++;
    }
    return (double)(log(n) + 1.0);
}

double** mandelbrot_parallel(coordinate c, int depth, double muestreo, int threads)
{
    int pixels_x = ((c.sup_x - c.inf_x) / muestreo) + 1;
    int pixels_y = ((c.sup_y - c.inf_y) / muestreo) + 1;

    double **matrix = new_matrix(pixels_x, pixels_y);

    int i, j, n;
    #pragma omp parallel num_threads(threads)
    #pragma omp for firstprivate(pixels_x, pixels_y, c)
    for (i = 0; i < pixels_x; i++)
    {
        for (j = 0; j < pixels_y; j++)
        {
            matrix[i][j] = mandel_algorithm((c.inf_x + i * muestreo), (c.inf_y + j * muestreo), depth);
        }
    }
    
    return matrix;
}

void saveIMG(char *filename, double **matrix, int rows, int cols)
{
    FILE *file = fopen(filename, "wb");

    if (!file)
    {
        printf("No se pudo abrir %s en modo wb\n", filename);
        exit(-1);
    }

    int i, j;
    int lengthFloat = sizeof(float);
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {
            float f = (float)matrix[i][j];
            //printf("%f ", f);
            if (fwrite(&f, lengthFloat, 1, file) < 1)
            {
                printf("Error al escribir en %s\n", filename);
                exit(-1);
            }
        }
        //printf("\n");
    }
    fclose(file);
}

int main()
{
    int depth = 500;

    coordinate c;
    c.inf_x = -0.748766713922161;
    c.inf_y = 0.123640844894862;
    c.sup_x = -0.748766707771757;
    c.sup_y = 0.123640851045266;

    double muestreo = 1e-11;
    char *fileout = "salida.raw";

    int pixels_x = (int)((c.sup_x - c.inf_x) / muestreo + 1.0);
    int pixels_y = (int)((c.sup_y - c.inf_y) / muestreo + 1.0);

    double **img = mandelbrot_parallel(c, depth, muestreo, 4);

    //saveIMG("out.raw", img, pixels_x, pixels_y);
}