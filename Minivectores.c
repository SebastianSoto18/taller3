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

    fscanf(archivo,"%s", &cantidadDeElementos);

    printf("%s",cantidadDeElementos);
}