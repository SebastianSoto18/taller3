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

    int placa[atoi(filas)][atoi(columnas)];

    for(int i=0;i<atoi(filas);i++){
        for(int j=0;j<atoi(columnas);j++){
            fscanf(archivo,"%s", &filas);
            placa[i][j]=atoi(filas);
        }
    }

    for(int i=0;i<atoi(filas);i++){
        for(int j=0;j<atoi(columnas);j++){
            printf("%d ",placa[i][j]);
        }
        printf("\n");
    }

    fclose(archivo);

    return 0;
}