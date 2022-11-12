#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<string.h>


int main(){

    char filas[256] ;
    char columnas[256];
    char digito[256];
    FILE *archivo;

    archivo = fopen("test2.txt","r");
    fscanf(archivo,"%s", &filas);
    fscanf(archivo,"%s", &columnas);


    int filasInt = atoi(filas);
    int columnasInt = atoi(columnas);

   int placa[filasInt][columnasInt];

    for(int i=0;i<filasInt;i++){
        for(int j=0;j<columnasInt;j++){
            fscanf(archivo,"%s", &digito);
            placa[i][j]=atoi(digito);
        }
    }

    fclose(archivo);

    return 0;
}