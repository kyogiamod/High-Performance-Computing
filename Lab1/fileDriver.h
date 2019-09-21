#ifndef _FILEDRIVER_H
#define _FILEDRIVER_H


int readFile(char* fileName, int** in);
int saveFile(char* fileName, int** out, int rows);


#endif