#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *funcion_hilo(void *param);
//compilar hilos gcc -o hilos.c hilos -lpthread
int sum ;
int matrisA[3][3];
int matrisB[3][3];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int res;

int main(){
    int i;

    int child;
    child=9;
    sum=0;
    res=200;
    pthread_t tid[child];
    

    for(int f=0;f<3;f++){
        for(int c=0;c<3;c++){
            matrisA[f][c]=rand()%10;
            matrisB[f][c]=rand()%10;
        }
    }

     for(int f=0;f<3;f++){
        for(int c=0;c<3;c++){
            printf("%d ",matrisA[f][c]);
        }
        printf("\n");
    }
     printf("\n");
      printf("\n");
       printf("\n");

     for(int f=0;f<3;f++){
        for(int c=0;c<3;c++){
            printf("%d ",matrisB[f][c]);
        }
        printf("\n");
    }

   
/*     pthread_create(&tid, NULL, funcion_hilo, NULL);

    for(i=0;i<100;i++){
        pthread_mutex_lock(&mutex);
        sum++;
        pthread_mutex_unlock(&mutex);
        pthread_mutex_lock(&mutex);
        res--;
        pthread_mutex_unlock(&mutex);
    }
    pthread_join(tid, NULL);
    printf("Suma total=%d\n",sum);
    printf("Resta total=%d\n",res);
    pthread_mutex_destroy(&mutex); */

    return 0;
}


void *funcion_hilo(void *param){
    int i;
    for(i=0;i<100;i++){
        pthread_mutex_lock(&mutex);
        sum++;
        pthread_mutex_unlock(&mutex);
        pthread_mutex_lock(&mutex);
        res--;
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(0);
}