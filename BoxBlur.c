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
float *calcularpos(int i, int j);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int **imagen;
float **imagenConFiltro;
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
    imagenConFiltro=(float**)malloc(f*sizeof(float*));
    int segmento=0;
    for(int i=0;i<f;i++){
        imagen[i]=(int*)malloc(c*sizeof(int));
        imagenConFiltro[i]=(float*)malloc(c*sizeof(float));
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
        if(canHilos>f || f%canHilos!=0){
            printf("La cantidad de hilos no puede ser mayor a la cantidad de filas\n");
        }else{
            segmento=f/canHilos;
            break;
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

    for(int i=0;i<canHilos;i++){
        pthread_join(hilos[i],NULL);
    }

    for(int i=0;i<f;i++){
        for(int j=0;j<c;j++){
           printf("%.2f ",imagenConFiltro[i][j]);
        }
        printf("\n");
    }

    fclose(file);
    free(imagen);
    free(imagenConFiltro);
    free(IsSobrante);
    return 0;
}


float *calcularpos(int i, int j){
    float pos=0.0;

      if(i ==0 && j==0){
                pos=(float)(imagen[i][j]+imagen[i][j+1]+imagen[i+1][j]+imagen[i+1][j+1])/4;
        }
            if(i==f-1 && j==0){
                pos=(float)(imagen[i][j]+imagen[i][j+1]+imagen[i-1][j]+imagen[i-1][j+1])/4;
            }
            if(i==0 && j==c-1){
                pos=(float)(imagen[i][j]+imagen[i][j-1]+imagen[i+1][j]+imagen[i+1][j-1])/4;
            }
            if(i==f-1 && j==c-1){
                pos=(float)(imagen[i][j]+imagen[i][j-1]+imagen[i-1][j]+imagen[i-1][j-1])/4;
            }
            if(i==0 && j!=0 && j!=c-1){
                pos=(imagen[i][j]+imagen[i][j-1]+imagen[i][j+1]+imagen[i+1][j]+imagen[i+1][j-1]+imagen[i+1][j+1])/6;
            }
            if(i==f-1 && j!=0 && j!=c-1){
                pos=(imagen[i][j]+imagen[i][j-1]+imagen[i][j+1]+imagen[i-1][j]+imagen[i-1][j-1]+imagen[i-1][j+1])/6;
            }
            if(j==0 && i!=0 && i!=f-1){
                pos=(imagen[i][j]+imagen[i-1][j]+imagen[i+1][j]+imagen[i][j+1]+imagen[i-1][j+1]+imagen[i+1][j+1])/6;
            }
            if(j==c-1 && i!=0 && i!=f-1){
                pos=(imagen[i][j]+imagen[i-1][j]+imagen[i+1][j]+imagen[i][j-1]+imagen[i-1][j-1]+imagen[i+1][j-1])/6;
            }
            if(i!=0 && i!=f-1 && j!=0 && j!=c-1){
                pos=(imagen[i][j]+imagen[i-1][j]+imagen[i+1][j]+imagen[i][j-1]+imagen[i][j+1]+imagen[i-1][j-1]+imagen[i-1][j+1]+imagen[i+1][j-1]+imagen[i+1][j+1])/9;
            }

    return pos;
}

void *funcionHilo(void *param){
    struct data *pixel=(struct data*)param;

    for(int i=pixel->inicio;i<pixel->fin;i++){
        for(int j=0;j<c;j++){
                imagenConFiltro[i][j]=calcularpos(i,j);
         }
    }
    pthread_exit(NULL);
}
