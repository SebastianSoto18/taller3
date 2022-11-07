#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *Contar_Digito_hilo(void *param);

struct parametros{
    int inicio;
    int final;
    int digito;
    int id;
};

int *vector;
int *repetidosPorHilo;
int contadorGlobal=0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(){
    FILE *archivo;
    archivo=fopen("test.txt","r");
    char cantidadDeElementos[100];
    int cantidadDeElementosInt;
    int cantidadDeHilos;
    int segmentos;
    int esImpar=1;
    int digito=0;
    int bandera=1;
    char num[100];

    /*Obteniendo numero de elementos de la primera linea del archivo*/
    fscanf(archivo,"%s", &cantidadDeElementos);

    cantidadDeElementosInt=atoi(cantidadDeElementos);
    /*Si la candidad de elementos es par, se apaga la bandera que indica lo contrario*/
    if(cantidadDeElementosInt%2==0){
        esImpar=0;
    }

    /*Inicializando el vector que contendra los elementos*/
    vector = (int*)malloc(sizeof(int)*cantidadDeElementosInt);
    
    /*Cargue de numeros en el vector*/
    for (int i = 0; i <cantidadDeElementosInt; i++)
    {
        fscanf(archivo,"%s", &num);
        vector[i]=atoi(num);
    }



    do{
        printf("Ingrese la cantidad de hilos que desea utilizar: \n");
        scanf("%d",&cantidadDeHilos);
        if(esImpar){
            /*Si la bandeja esta encendida, se asume que el elemento tiene un elemento de mas para hacer mas facil la particion de los segmentos*/
            if((cantidadDeElementosInt+1)%cantidadDeHilos==0){
                segmentos=(cantidadDeElementosInt+1)/cantidadDeHilos;
                bandera=0;
            }else{
                printf("La cantidad de hilos debe ser divisible entre la cantidad de elementos\n");
            }
        }else{
            if(cantidadDeElementosInt%cantidadDeHilos==0){
                segmentos=cantidadDeElementosInt/cantidadDeHilos;
                bandera=0;
            }else{
                printf("La cantidad de hilos debe ser divisible entre la cantidad de elementos\n");
            }
        }
    }while (bandera);
    bandera=1;
    
    /*Inicializando el vector que contiene los hilos*/
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

    /*Generando las estructuras que se le pasaran al metodo que contara los digitos segun el segmento*/
    for (int i = 0; i < cantidadDeHilos; i++){
        if(i==0){
            parametros[i].inicio=0;
            parametros[i].final=segmentos;
        }else{
            parametros[i].inicio=i*segmentos;
            parametros[i].final=segmentos+parametros[i].inicio;
        }
        parametros[i].digito=digito;
        parametros[i].id=i;

        if(i==cantidadDeHilos-1 && esImpar){
            /*Si la bandera esta activa, el ultimo hilo contara hasta el elemento anterior,
            debido a que por facilidades de operacion, se le asigno un elemento de mas a la hora de sacar los segmentos
            */
            parametros[i].final=parametros[i].final-1;
        }
    }

    /*Creando los hilos*/
    for (int  i = 0; i < cantidadDeHilos; i++){
        pthread_create(&tid[i],NULL,Contar_Digito_hilo,(void *)&parametros[i]);
    }
    
    /*Esperando terminacion de los hilos*/
    for (int  i = 0; i < cantidadDeHilos; i++){
        pthread_join(tid[i],NULL);
    }

    /*Imprimiendo los resultados*/
    if(contadorGlobal==0){
        printf("El digito %d no se repite en el vector\n",digito);
        exit(0);
    }else{
        for(int i=0;i<cantidadDeHilos;i++){
            printf("El hilo %d encontro %d veces el digito %d\n",i,repetidosPorHilo[i],digito);
        }
    }
    return 0;
}

void *Contar_Digito_hilo(void *param){
    struct parametros *p = (struct parametros *)param;
    int inicio=p->inicio;
    int final=p->final;
    int digito=p->digito;
    int id=p->id;
    int contador=0;

    for (int i = inicio; i < final; i++){
        if(vector[i]==digito){
            contador++;
        }
    }

    repetidosPorHilo[id]=contador;
    pthread_mutex_lock(&mutex);
    contadorGlobal+=contador;
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}