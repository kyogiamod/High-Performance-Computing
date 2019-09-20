#include <stdio.h>
#include <stdlib.h>

int readFile(char* fileName, int* in){

    FILE* file = fopen(fileName, "rb");

    if(!file) { printf("No se puede abrir el archivo"); return 0; }

    // Unknown imagen's dimension, so
    fseek(file, 0L, SEEK_END);
    //ftell will return the total amount of bytes in the file
    int length = ftell(file);
    unsigned char* imgArray = (unsigned char*)malloc(sizeof(char)*length);
    fseek(file, 0L, SEEK_SET);
    fread(imgArray, length, 1, file); //All content is in imgArray
    
    int i;
    for(i = 0; i < length/4; i++){
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

/*
int main(){
    

    int* in = (int*)malloc(sizeof(int)*65536);
    int read = readFile("test/circulos.raw", in);
    
    int i;
	for (i = 0; i < 65536; i++)
	{
		if (i % 256 == 0)
		{
			printf("\n");
		}
		printf("%d ", in[i]);
		
    }

    return 0;
}
*/