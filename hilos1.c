#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void* funcion_hilo1(void*);


pthread_t tid1;
pthread_t tid2;
int main(){

    int dato = 10;

	pthread_create(&tid1, NULL, funcion_hilo1, (void *) dato);	//fork()	
    pthread_create(&tid2, NULL, funcion_hilo2, NULL);	//fork()
	printf("Hilo principal[%lu]\n", pthread_self());
	pthread_join(tid1, NULL);  //wait()
    pthread_join(tid2, NULL);  //wait()
	return EXIT_SUCCESS;
}
void* funcion_hilo1(void* arg){
    int dato = (int) arg;
	printf("Hilo1 [%lu], y el dato es [%d]\n", pthread_self(),dato);
	pthread_exit(0);
}
void* funcion_hilo2(void* arg){
	printf("Hilo2 [%lu]\n", pthread_self());
	pthread_exit(0);
}