#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

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
int columnas=0;
int *IsSobrante;


int main(){
    FILE *archivo;
    archivo=fopen("test4.txt","r");
    int filas=0;
    int canHilos=0;
    filas=fscanf(archivo,"%d",&filas);
    columnas=fscanf(archivo,"%d",&columnas);

    imagen=(int**)malloc(filas*sizeof(int*));
    imagenConFiltro=(int**)malloc(filas*sizeof(int*));

    for(int i=0;i<filas;i++){
        imagen[i]=(int*)malloc(columnas*sizeof(int));
        imagenConFiltro[i]=(int*)malloc(columnas*sizeof(int));
    }

    for(int i=0;i<filas;i++){
        for(int j=0;j<columnas;j++){
            fscanf(archivo,"%d",&imagen[i][j]);
        }
    }

       for(int i=0;i<filas;i++){
        for(int j=0;j<columnas;j++){
           printf("%d ",imagen[i][j]);
        }
        printf("\n");
    }

    fclose(archivo);
    free(imagen);
    free(imagenConFiltro);
    free(IsSobrante);

}
