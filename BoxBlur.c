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
   fscanf(file,"%d",&c);

    printf("f: %d c: %d\n",f,c);
    int canHilos=0;
    imagen=(int**)malloc(f*sizeof(int*));
    imagenConFiltro=(int**)malloc(f*sizeof(int*));
    int segmento=0;
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

    do{
        printf("Ingrese la cantidad de hilos: ");
        scanf("%d",&canHilos);
        if(canHilos>f && f%canHilos!=0){
            printf("La cantidad de hilos no puede ser mayor a la cantidad de filas\n");
        }else{
            segmento=f/canHilos;
        }
    }while(1);

    pthread_t hilos[canHilos];
    struct data *datos=(struct data*)malloc(canHilos*sizeof(struct data));

    for(int i=0;i<canHilos;i++){
        if(i==0){
            datos[i].inicio=0;
        }else{
            datos[i].inicio=i*segmento;
        }
        datos[i].fin=datos[i].inicio+ segmento;
        pthread_create(&hilos[i],NULL,funcionHilo,(void*)&datos[i]);
    }

    fclose(file);
    free(imagen);
    free(imagenConFiltro);
    free(IsSobrante);
    return 0;
}

void *funcionHilo(void *param){
    struct data *pixel=(struct data*)param;

    for(int i=pixel->inicio;i<pixel->fin;i++){
        for(int j=0;j<c;j++){
            
            if(i ==0 && j==0){
                imagenConFiltro[i][j]=(float)(imagen[i][j]+imagen[i][j+1]+imagen[i+1][j]+imagen[i+1][j+1])/4;
        }
            if(i==f-1 && j==0){
                imagenConFiltro[i][j]=(float)(imagen[i][j]+imagen[i][j+1]+imagen[i-1][j]+imagen[i-1][j+1])/4;
            }
            if(i==0 && j==c-1){
                imagenConFiltro[i][j]=(float)(imagen[i][j]+imagen[i][j-1]+imagen[i+1][j]+imagen[i+1][j-1])/4;
            }
            if(i==f-1 && j==c-1){
                imagenConFiltro[i][j]=(float)(imagen[i][j]+imagen[i][j-1]+imagen[i-1][j]+imagen[i-1][j-1])/4;
            }
            if(i==0 && j!=0 && j!=c-1){
                imagenConFiltro[i][j]=(imagen[i][j]+imagen[i][j-1]+imagen[i][j+1]+imagen[i+1][j]+imagen[i+1][j-1]+imagen[i+1][j+1])/6;
            }
            if(i==f-1 && j!=0 && j!=c-1){
                imagenConFiltro[i][j]=(imagen[i][j]+imagen[i][j-1]+imagen[i][j+1]+imagen[i-1][j]+imagen[i-1][j-1]+imagen[i-1][j+1])/6;
            }
            if(j==0 && i!=0 && i!=f-1){
                imagenConFiltro[i][j]=(imagen[i][j]+imagen[i-1][j]+imagen[i+1][j]+imagen[i][j+1]+imagen[i-1][j+1]+imagen[i+1][j+1])/6;
            }
            if(j==c-1 && i!=0 && i!=f-1){
                imagenConFiltro[i][j]=(imagen[i][j]+imagen[i-1][j]+imagen[i+1][j]+imagen[i][j-1]+imagen[i-1][j-1]+imagen[i+1][j-1])/6;
            }
            if(i!=0 && i!=f-1 && j!=0 && j!=c-1){
                imagenConFiltro[i][j]=(imagen[i][j]+imagen[i-1][j]+imagen[i+1][j]+imagen[i][j-1]+imagen[i][j+1]+imagen[i-1][j-1]+imagen[i-1][j+1]+imagen[i+1][j-1]+imagen[i+1][j+1])/9;
            }
    }
    }
}
