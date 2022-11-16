#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

void *funcion_hilo(void *param);

int potencia(int base,int exponente){
    int resultado=1;
    for(int i=0;i<exponente;i++){
        resultado=resultado*base;
    }
    return resultado;
}

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

float resultado=0;

struct segment{
    int inicio;
    int fin;
};

int main(){
    int n=0;
    int child;
    int segmento=0;


    do{
        printf("Ingrese hasta donde se hara la estimacion: \n");
        scanf("%d",&n);
        if(n<1 ){
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

    printf("%d\n",potencia(2,2));

    printf("El valor de pi es: %f\n",4*(double)resultado/n);
    return 0;
}




void *funcion_hilo(void *param){
    struct segment *d = (struct segment *)param;
    int inicio=d->inicio;
    int fin=d->fin;
    int signoSerie=1;
    float  sumaHilo=0;
    for(int i=inicio;i<fin;i++){
        if(i==0){
            signoSerie=1;
        }else{
            signoSerie=potencia(-1,i);
        }

    if(signoSerie==1){
        sumaHilo+=1/(2*i+1);
    }else{
        sumaHilo-=1/(2*i+1);
    }
    }

    pthread_mutex_lock(&mutex);
    resultado+=sumaHilo;
    pthread_mutex_unlock(&mutex);

    pthread_exit(0);
}