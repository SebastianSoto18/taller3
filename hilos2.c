#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *funcion_hilo(void *param);
//compilar hilos gcc -o hilos.c hilos -lpthread


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
/* int **matrisA;
int **matrisB;
int **matrisC; */

int matrisA[3][3];
int matrisB[3][3];
int matrisC[3][3];
int i;
struct possition{
    int x;
    int y;
};

int main(){
    i=0;
    int child;
    child=9;
    pthread_t tid[child];

 
    /* matrisA = (int **)malloc(3*sizeof(int *));
    matrisB = (int **)malloc(3*sizeof(int *));
    matrisC = (int **)malloc(3*sizeof(int *));

    for(i=0;i<3;i++){
        matrisA[i] = (int *)malloc(3*sizeof(int));
        matrisB[i] = (int *)malloc(3*sizeof(int));
        matrisC[i] = (int *)malloc(3*sizeof(int));
    } */


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


    for(int f=0;f<3;f++){
        for(int c=0;c<3;c++){
            if(i<child){
            struct possition pos;
            pos.x=f;
            pos.y=c;
            printf("posicion %d %d\n",pos.x,pos.y);
            pthread_create(&tid[i], NULL, funcion_hilo, (void*)&pos);
            i++;
            }
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
  /*   free(matrisA);
    free(matrisB);
    free(matrisC); */
    return 0;
}


void *funcion_hilo(void *param){
    int suma=0;
    struct possition* pos = (struct possition *)param;
    printf("%d\n",i);    
    pthread_mutex_lock(&mutex);
    for(int i=0;i<3;i++){
        suma+=matrisA[pos->x][i]*matrisB[i][pos->y];
    }

    printf("Hilo [%lu] dato[%d | %d | %d]\n", pthread_self(), pos->x, pos->y, suma);

    pthread_mutex_unlock(&mutex);
    matrisC[pos->x][pos->y]=suma;
    pthread_exit(0);
}