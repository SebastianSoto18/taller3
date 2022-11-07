#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *funcion_hilo_todos_asignados(void *param);
void *funcion_hilo_sin_asignar(void *param);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int **matrisA;
int *vector;
int *resultado;
int *asignado;

int main(){
    int size=0;
    int child;


    do{
        printf("Ingrese el tamaño de la matriz: \n");
        scanf("%d",&size);
        if(size>1){
            printf("El tamaño debe ser mayor a 0 y mayor a 1\n");
        }else{
            break;
        }
    }while(1);

    do{
        printf("Ingrese la cantidad de hilos que realizaran la tarea: \n");
        scanf("%d",&child);
        if(child>size){
            printf("La cantidad de hilos debe ser menor o igual al tamaño de la matriz\n");
        }else{
            break;
        }
    }while(1);

    pthread_t tid[child];

    matrisA = (int **)malloc(size*sizeof(int *));
    vector = (int *)malloc(size*sizeof(int));
    resultado = (int *)malloc(size*sizeof(int));
    asignado = (int *)malloc(size*sizeof(int));

    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            matrisA[i] = rand()%20;
        }
    }

    for(int i=0;i<size;i++){
        vector[i] = rand()%20;
    }

    for(int i=0;i<size;i++){
        asignado[i] = 0;
    }

    printf("Matriz A: \n");
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            printf("%d ",matrisA[i][j]);
        }
        printf("\n");
    }

    printf("Vector: \n");
    for(int i=0;i<size;i++){
        printf("%d ",vector[i]);
    }

    return 0;

}