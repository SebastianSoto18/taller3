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
            bandera=0;
        }else{
            printf("La cantidad de hilos debe ser divisible entre la cantidad de elementos\n");
        }
    }while (bandera);
    
     
    
    return 0;
}