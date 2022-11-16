#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *funcion_hilo(void *param);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int *vectorA;
int *vectorB;
int resultado=0;

struct data{
    int inicio;
    int fin;
};



int main(){
    FILE *archivo;
    int size;
    int child;

    archivo = fopen("test3.txt","r");

    fscanf(archivo,"%d",&size);

    vectorA = (int *)malloc(size*sizeof(int));
    vectorB = (int *)malloc(size*sizeof(int));
    int segmento=0;
    for(int i=0;i<size;i++){
        fscanf(archivo,"%d",&vectorA[i]);
    }
    for(int i=0;i<size;i++){
        fscanf(archivo,"%d",&vectorB[i]);
    }

    do{
        printf("Ingrese la cantidad de hilos que realizaran la tarea: \n");
        scanf("%d",&child);
        if(child>size || child<1 || size%child!=0){
            printf("La cantidad de hilos debe ser menor o igual al tamaño de la matriz\n");
        }else{
            segmento=size/child;
            child=child- 1;
            break;
        }
    }while (1);
    

    phtread_t tid[child];
    struct data  *d;
    d = (struct data *)malloc(child*sizeof(struct data));

    for(int i=0;i<child;i++){
       if(i==0){
         d[i].inicio=segmento;
       }else{
        d[i].inicio=d[i-1].fin;
       }
         d[i].fin=d[i].inicio+segmento;
        pthread_create(&tid[i],NULL,funcion_hilo,(void *)&d[i]);
    }

    for(int i=0;i<segmento;i++){
        pthread_mutex_lock(&mutex);
        resultado+=vectorA[i]*vectorB[i];
        pthread_mutex_unlock(&mutex);
    }

    for(int i=0;i<child;i++){
        pthread_join(tid[i],NULL);
    }

    printf("El resultado es: %d\n",resultado);


    return 0;
}

void *funcion_hilo(void *param){
    struct data *d = (struct data *)param;
    for(int i=d->inicio;i<d->fin;i++){
        pthread_mutex_lock(&mutex);
        resultado+=vectorA[i]*vectorB[i];
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(0);
}

