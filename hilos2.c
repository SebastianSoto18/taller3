#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *funcion_hilo(void *param);
//compilar hilos gcc -o hilos.c hilos -lpthread

int matrisA[3][3];
int matrisB[3][3];
int matrisC[3][3];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

struct possition{
    int x;
    int y;
};

int main(){
    int i;
    int child;
    child=9;
    pthread_t tid[child];

 
    

    for(int f=0;f<3;f++){
        for(int c=0;c<3;c++){
            matrisA[f][c]=rand()%10;
            matrisB[f][c]=rand()%10;
        }
    }

     for(int f=0;f<3;f++){
        for(int c=0;c<3;c++){
            matrisC[f][c]=0;
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

    for(int f=0;f<3;f++){
        for(int c=0;c<3;c++){
            struct possition pos;
            pos.x=f;
            pos.y=c;
            pthread_create(&tid[i], NULL, funcion_hilo, (void*)&pos);
        }
    }

   
    for(int f=0;f<3;f++){
            pthread_join(tid[f], NULL);
    }

    for(int f=0;f<3;f++){
        for(int c=0;c<3;c++){
            printf("%d ",matrisC[f][c]);
        }
        printf("\n");
    }

    pthread_mutex_destroy(&mutex); 

    return 0;
}


void *funcion_hilo(void *param){
    int suma=0;
    struct possition* pos = (struct possition *)param;

    for(int i=0;i<3;i++){
        suma+=matrisA[pos->x][i]*matrisB[i][pos->y];
    }

    printf("Hilo [%lu] dato[%d | %d | %d]\n", pthread_self(), pos->x, pos->y, suma);

    pthread_mutex_lock(&mutex);
    matrisC[pos->x][pos->y]=suma;
    pthread_mutex_unlock(&mutex);

    pthread_exit(0);
}