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
int size;
int asignados=0;

struct possition{
    int x;
};

int main(){

    int child;


    do{
        printf("Ingrese el tamaño de la matriz: \n");
        scanf("%d",&size);
        if(size<1){
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
    asignados=child;

     for(int i=0;i<size;i++){
        matrisA[i] = (int *)malloc(size*sizeof(int));
    }

    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            matrisA[i][j] = rand()%20;
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

    printf("\n");

    struct possition pos[child];

    for(int i=0;i<child;i++){
        pos[i].x = i;
    }

    if(child==size){
        for(int i=0;i<size;i++){
            pthread_create(&tid[i],NULL,funcion_hilo_todos_asignados,(void *)&pos[i]);
        }
    }else{
        for(int i=0;i<child;i++){
            asignado[i] = 1;
            pthread_create(&tid[i],NULL,funcion_hilo_sin_asignar,(void *)&pos[i]);
        }
    }

    for(int i=0;i<size;i++){
        pthread_join(tid[i],NULL);
    }

    printf("Resultado: \n");
    for(int i=0;i<size;i++){
        printf("%d \n",resultado[i]);
    }

    return 0;

}


void *funcion_hilo_todos_asignados(void *param){
    struct possition *pos = (struct possition *)param;
    int suma=0;
    for(int i=0;i<size;i++){
        suma+=matrisA[pos->x][i]*vector[i];
    }
    resultado[pos->x]=suma;
    printf("El hilo %d realizo la tarea y el resultado es: %d \n",pos->x+1,suma);
    pthread_exit(0);
}

void *funcion_hilo_sin_asignar(void *param){
    struct possition *pos = (struct possition *)param;
    int suma=0;
    int i=0;

    for(int j=0;j<size;j++){
        suma+=matrisA[pos->x][j]*vector[j];
    }

    resultado[pos->x]=suma;
    printf("El hilo %d realizo la tarea en la fila %d y el resultado es: %d \n",pos->x+1,pos->x,suma);
    suma=0;
    while(1){
        pthread_mutex_lock(&mutex);
        if(asignados==size){
            pthread_mutex_unlock(&mutex);
            break;
        }
        if(asignado[i]==0 && i!=pos->x){
            asignado[i]=1;
            asignados++;
            pthread_mutex_unlock(&mutex);
            for(int j=0;j<size;j++){
                suma+=matrisA[i][j]*vector[j];
            }
             printf("El hilo %d realizo la tarea en la fila %d y el resultado es: %d \n",pos->x+1,i,suma);
            resultado[i]=suma;
            suma=0;
        }
        pthread_mutex_unlock(&mutex);
        i++;
    }
    pthread_exit(0);
}