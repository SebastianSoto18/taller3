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
    char num[100];
    fscanf(archivo,"%s", &cantidadDeElementos);

    vector = (int*)malloc(sizeof(int)*atoi(cantidadDeElementos));

    for (int i = 0; i < atoi(cantidadDeElementos); i++)
    {
        fscanf(archivo,"%d", &num);
        printf("%d\n ",atoi(num));
    }
    
}