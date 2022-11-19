#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


struct data
{
    int inicio;
    int fin;
};

void *funcionHilo(void *param);
void *funcionHiloSobrantes(void *param);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int **imagen;
int **imagenConFiltro;
int canSobrantes=0 ;
int c=0;
int f=0;
int *IsSobrante;


int main(){
    FILE *file;
   file=fopen("test4.txt","r");
    fscanf(file,"%d",&f);
   fscanf(file,"%d",&f);

    printf("f: %d c: %d\n",f,c);
    int canHilos=0;
    imagen=(int**)malloc(f*sizeof(int*));
    imagenConFiltro=(int**)malloc(f*sizeof(int*));

    for(int i=0;i<f;i++){
        imagen[i]=(int*)malloc(c*sizeof(int));
        imagenConFiltro[i]=(int*)malloc(c*sizeof(int));
    }

    for(int i=0;i<f;i++){
        for(int j=0;j<c;j++){
            fscanf(file,"%d",&imagen[i][j]);
        }
    }

       for(int i=0;i<f;i++){
        for(int j=0;j<c;j++){
           printf("%d ",imagen[i][j]);
        }
        printf("\n");
    }

    fclose(file);
    free(imagen);
    free(imagenConFiltro);
    free(IsSobrante);
    return 0;
}
