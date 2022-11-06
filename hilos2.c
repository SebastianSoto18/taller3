#include <stdio.h>
#include <pthread.h>

void *funcion_hilo(void *param);
//compilar hilos gcc -o hilos.c hilos -lpthread
int sum ;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int res;
int main(){
    int i;
    pthread_t tid;

    sum=0;
    res=200;
    printf("Creacion previa a los hijos sum=%d\n",sum);

    pthread_create(&tid, NULL, funcion_hilo, NULL);

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
    pthread_mutex_destroy(&mutex);
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