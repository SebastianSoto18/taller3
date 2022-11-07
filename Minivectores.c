#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *Contar_Digito_hilo(void *param);

struct parametros{
    int inicio;
    int final;
    int digito;
};

int *vector;
int *repetidosPorHilo;


int main(){
    FILE *archivo;
    archivo=fopen("test.txt","r");
    char cantidadDeElementos[2];
    int cantidadDeElementosInt;
    char num[100];
    fscanf(archivo,"%s", &cantidadDeElementos);
    cantidadDeElementosInt=atoi(cantidadDeElementos);
    vector = (int*)malloc(sizeof(int)*cantidadDeElementosInt);
    printf("%d"cantidadDeElementosInt);
    for (int i = 0; i <cantidadDeElementosInt; i++)
    {
        fscanf(archivo,"%s", &num);
        printf("%d\n ",atoi(num));
    }
    
}