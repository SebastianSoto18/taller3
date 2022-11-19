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
    FILE *archivo;
    archivo=fopen("test4.txt","r");
    int canHilos=0;
    f=fscanf(archivo,"%d",&f);
    c=fscanf(archivo,"%d",&c);
    printf("f: %d c: %d\n",f,c);
    imagen=(int**)malloc(f*sizeof(int*));
    imagenConFiltro=(int**)malloc(f*sizeof(int*));

    for(int i=0;i<f;i++){
        imagen[i]=(int*)malloc(c*sizeof(int));
        imagenConFiltro[i]=(int*)malloc(c*sizeof(int));
    }

    for(int i=0;i<f;i++){
        for(int j=0;j<c;j++){
            fscanf(archivo,"%d",&imagen[i][j]);
        }
    }

       for(int i=0;i<f;i++){
        for(int j=0;j<c;j++){
           printf("%d ",imagen[i][j]);
        }
        printf("\n");
    }

    fclose(archivo);
    free(imagen);
    free(imagenConFiltro);
    free(IsSobrante);

}
