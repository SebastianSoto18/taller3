#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *funcion_hilo(void *param);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int resultado=0;

struct segment{
    int inicio;
    int fin;
};

    int suma=0;

int main(){
    int n=0;
    int child;
    int segmento=0;


    do{
        printf("Ingrese hasta donde se hara la estimacion: \n");
        scanf("%d",&n);
        if(n<1 || n>2){
            printf("El tamaño debe ser mayor a 0 y mayor a 1\n");
        }else{
            break;
        }
    }while(1);

    do{
        printf("Ingrese la cantidad de hilos que realizaran la tarea: \n");
        scanf("%d",&child);
        if(child>n){
            printf("La cantidad de hilos debe ser menor o igual al tamaño de los elementos\n");
        }else{
            segmento=n/child;
            break;
        }
         }while(1);

    pthread_t tid[child];
    struct segment  *d;
    d = (struct segment *)malloc(child*sizeof(struct segment));

    for(int i=0;i<child;i++){
       if(i==0){
         d[i].inicio=0;
       }else{
        d[i].inicio=i*segmento;
       }
       d[i].fin=d[i].inicio+segmento;
       pthread_create(&tid[i],NULL,funcion_hilo,(void *)&d[i]);
    }

    for(int i=0;i<child;i++){
        pthread_join(tid[i],NULL);
    }

    printf("El valor de pi es: %f\n",4*(float)resultado/n);
    return 0;
}

void *funcion_hilo(void *param){
    struct segment *d = (struct segment *)param;
    int inicio=d->inicio;
    int fin=d->fin;

    for(int i=inicio;i<fin;i++){
        suma+=1/(2*i+1);
    }
    pthread_mutex_lock(&mutex);
    resultado+=suma;
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}