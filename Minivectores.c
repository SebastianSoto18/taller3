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
    char cantidadDeElementos[100];
    int cantidadDeElementosInt;
    int cantidadDeHilos;
    int segmentos;
    int digito=0;
    int bandera=1;
    char num[100];
    fscanf(archivo,"%s", &cantidadDeElementos);
    cantidadDeElementosInt=atoi(cantidadDeElementos);
    vector = (int*)malloc(sizeof(int)*cantidadDeElementosInt);
    
    for (int i = 0; i <cantidadDeElementosInt; i++)
    {
        fscanf(archivo,"%s", &num);
        vector[i]=atoi(num);
    }

    for (int i = 0; i < cantidadDeElementosInt; i++)
    {
        printf("%d \n",vector[i]);
    }
    
    do{
        printf("Ingrese la cantidad de hilos que desea utilizar: \n");
        scanf("%d",&cantidadDeHilos);
        if(cantidadDeElementosInt%cantidadDeHilos==0){
            segmentos=cantidadDeElementosInt/cantidadDeHilos;
            bandera=0;
        }else{
            printf("La cantidad de hilos debe ser divisible entre la cantidad de elementos\n");
        }
    }while (bandera);
    bandera=1;
    
    pthread_t tid[cantidadDeHilos];
    repetidosPorHilo = (int*)malloc(sizeof(int)*cantidadDeHilos);

    struct parametros parametros[cantidadDeHilos];

    do{
        printf("Ingrese el digito que desea contar: \n");
        scanf("%d",&digito);
        if(digito<0){
            printf("El digito debe ser mayor a 0\n");
        }else{
            bandera=0;
        }
    }while(bandera);

    for (int i = 0; i < cantidadDeHilos; i++){
        if(i==0){
            parametros[i].inicio=0;
            parametros[i].final=segmentos;
            parametros[i].digito=digito;
        }else{
            parametros[i].inicio=i*segmentos;
            parametros[i].final=2*parametros[i].inicio;
            parametros[i].digito=digito;
        }
    }

    for(int i=0;i<cantidadDeHilos;i++){
        printf("inicio: %d final: %d digito: %d \n",parametros[i].inicio,parametros[i].final,parametros[i].digito);
    }
    
    return 0;
}