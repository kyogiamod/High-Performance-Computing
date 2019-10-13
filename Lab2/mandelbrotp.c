#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

typedef struct complejo
{
    double r;
    double i;
} complex;

typedef struct parametros
{
    int i;
    double a;
    double b;
    double c;
    double d;
    double muestreo;
    char* filename;
    int threads;
}params;


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

double** mandelbrot_parallel(params p)
{
    //printf("%f, %f\n", p.c, p.a);
    
    int pixels_x = (int)((p.c - p.a) / p.muestreo) + 1;
    int pixels_y = (int)((p.d - p.b) / p.muestreo) + 1;

    double **matrix = new_matrix(pixels_x, pixels_y);

    int i, j;
    #pragma omp parallel num_threads(p.threads)
    {
        #pragma omp for private(j)
        for (i = 0; i < pixels_x; i++)
        {
            for (j = 0; j < pixels_y; j++)
            {
                matrix[i][j] = mandel_algorithm((p.a + i * p.muestreo), (p.b + j * p.muestreo), p.i);
            }
        }
    }

    return matrix;
}

void saveIMG(char* filename, double** matrix, int rows, int cols)
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

params getParams(int argc, char** argv)
{
    params p;
    char c;

    while ((c = getopt(argc, argv, "i:a:b:c:d:s:f:t:")) != -1)
    {
        switch (c)
        {
        case 'i': //depth
            p.i = atoi(optarg);
            break;
        case 'a': //lim inferior real
            p.a = atof(optarg);
            break;
        case 'b': //lim inferior img
            p.b = atof(optarg);
            break;
        case 'c': //lim superior real
            p.c = atof(optarg);
            break;
        case 'd': //lim superior img
            p.d = atof(optarg);
            break;
        case 's': //muestreo
            p.muestreo = atof(optarg);
            break;
        case 'f': //archivo de salida
            p.filename = optarg;
            break;
        case 't': //numero hilos
            p.threads = atoi(optarg);
            break;
        }
    }
    return p;
}

int main(int argc, char** argv)
{
    params p = getParams(argc, argv);

    double muestreo = p.muestreo;

    double** img = mandelbrot_parallel(p);
    
    int pixels_x = (int)((p.c - p.a) / p.muestreo + 1.0);
    int pixels_y = (int)((p.d - p.b) / p.muestreo + 1.0);

    saveIMG(p.filename, img, pixels_x, pixels_y);

    return 0;
}