#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<string.h>


int main(){

    char filas[256] ;
    char columnas[256];

    FILE *archivo;

    archivo = fopen("test2.txt","r");
    fscanf(archivo,"%s", &filas);
    fscanf(archivo,"%s", &columnas);


    int filasInt = atoi(filas);
    int columnasInt = atoi(columnas);

   int placa[filasInt][columnasInt];



    fclose(archivo);

    return 0;
}