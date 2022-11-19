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
    int UnoMas=0;
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
        if(canHilos>f ){
            printf("La cantidad de hilos no puede ser mayor a la cantidad de filas\n");
        }else{
            if(f%canHilos!=0){
               float aux = (float)(f/canHilos);
                segmento=(int)aux;
                canSobrantes=f-canHilos;
                if (canSobrantes<2)
                {
                   UnoMas=1;
                }else{
                     IsSobrante=(int*)malloc(canSobrantes*sizeof(int));
                    for (int i = 0; i < canSobrantes  ; i++)
                    {
                        IsSobrante[i]=0;
                    }
                }  
            }else{

            segmento=f/canHilos;
            }
            break;
        }
    }while(1);

    pthread_t hilos[canHilos];
    struct data *datos=(struct data*)malloc(canHilos*sizeof(struct data));

    if(UnoMas){
    for(int i=0;i<canHilos;i++){
                if(i==0){
                    datos[i].inicio=0;
                }else{
                    datos[i].inicio=i*segmento;
                }
                if(i==canHilos-1){
                    datos[i].fin=f;
                }else{
                datos[i].fin=datos[i].inicio+ segmento;
                }
                pthread_create(&hilos[i],NULL,funcionHilo,(void*)&datos[i]);
    }
    }
    if(!UnoMas){
            for(int i=0;i<canHilos;i++){
                        if(i==0){
                            datos[i].inicio=0;
                        }else{
                            datos[i].inicio=i*segmento;
                        }
                        datos[i].fin=datos[i].inicio+ segmento;
                    
                        pthread_create(&hilos[i],NULL,funcionHilo,(void*)&datos[i]);
            }
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


void *funcionHiloSobrantes(void *param){
        struct data *pixel=(struct data*)param;
        int h=0;

        for(int i=pixel->inicio;i<pixel->fin;i++){
        for(int j=0;j<c;j++){
            
            if(i ==0 && j==0){
                imagenConFiltro[i][j]=(imagen[i][j]+imagen[i][j+1]+imagen[i+1][j]+imagen[i+1][j+1])/4;
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
                imagenConFiltro[i][j]=(float)(imagen[i][j]+imagen[i][j-1]+imagen[i][j+1]+imagen[i+1][j]+imagen[i+1][j-1]+imagen[i+1][j+1])/6;
            }
            if(i==f-1 && j!=0 && j!=c-1){
                imagenConFiltro[i][j]=(float)(imagen[i][j]+imagen[i][j-1]+imagen[i][j+1]+imagen[i-1][j]+imagen[i-1][j-1]+imagen[i-1][j+1])/6;
            }
            if(j==0 && i!=0 && i!=f-1){
                imagenConFiltro[i][j]=(float)(imagen[i][j]+imagen[i-1][j]+imagen[i+1][j]+imagen[i][j+1]+imagen[i-1][j+1]+imagen[i+1][j+1])/6;
            }
            if(j==c-1 && i!=0 && i!=f-1){
                imagenConFiltro[i][j]=(float)(imagen[i][j]+imagen[i-1][j]+imagen[i+1][j]+imagen[i][j-1]+imagen[i-1][j-1]+imagen[i+1][j-1])/6;
            }
            if(i!=0 && i!=f-1 && j!=0 && j!=c-1){
                imagenConFiltro[i][j]=(float)(imagen[i][j]+imagen[i-1][j]+imagen[i+1][j]+imagen[i][j-1]+imagen[i][j+1]+imagen[i-1][j-1]+imagen[i-1][j+1]+imagen[i+1][j-1]+imagen[i+1][j+1])/9;
            }
         }
        }

    while(1){
        if(h==canSobrantes){
            break;
        }
        pthread_mutex_lock(&mutex);
        if(IsSobrante[h]==0){
            IsSobrante[h]=1;
        pthread_mutex_unlock(&mutex);     
        for(int j=0;j<c;j++){
            
            if(h ==0 && j==0){
                imagenConFiltro[h][j]=(imagen[h][j]+imagen[h][j+1]+imagen[h+1][j]+imagen[h+1][j+1])/4;
        }
            if(h==f-1 && j==0){
                imagenConFiltro[h][j]=(float)(imagen[h][j]+imagen[h][j+1]+imagen[h-1][j]+imagen[h-1][j+1])/4;
            }
            if(h==0 && j==c-1){
                imagenConFiltro[h][j]=(float)(imagen[h][j]+imagen[h][j-1]+imagen[h+1][j]+imagen[h+1][j-1])/4;
            }
            if(h==f-1 && j==c-1){
                imagenConFiltro[h][j]=(float)(imagen[h][j]+imagen[h][j-1]+imagen[h-1][j]+imagen[h-1][j-1])/4;
            }
            if(h==0 && j!=0 && j!=c-1){
                imagenConFiltro[h][j]=(float)(imagen[h][j]+imagen[h][j-1]+imagen[h][j+1]+imagen[h+1][j]+imagen[h+1][j-1]+imagen[h+1][j+1])/6;
            }
            if(h==f-1 && j!=0 && j!=c-1){
                imagenConFiltro[h][j]=(float)(imagen[h][j]+imagen[h][j-1]+imagen[h][j+1]+imagen[h-1][j]+imagen[h-1][j-1]+imagen[h-1][j+1])/6;
            }
            if(j==0 && h!=0 && h!=f-1){
                imagenConFiltro[h][j]=(float)(imagen[h][j]+imagen[h-1][j]+imagen[h+1][j]+imagen[h][j+1]+imagen[h-1][j+1]+imagen[h+1][j+1])/6;
            }
            if(j==c-1 &&h!=0 && h!=f-1){
                imagenConFiltro[h][j]=(float)(imagen[h][j]+imagen[h-1][j]+imagen[h+1][j]+imagen[h][j-1]+imagen[h-1][j-1]+imagen[h+1][j-1])/6;
            }
            if(h!=0 && h!=f-1 && j!=0 && j!=c-1){
                imagenConFiltro[h][j]=(float)(imagen[h][j]+imagen[h-1][j]+imagen[h+1][j]+imagen[h][j-1]+imagen[h][j+1]+imagen[h-1][j-1]+imagen[h-1][j+1]+imagen[h+1][j-1]+imagen[h+1][j+1])/9;
            }
         }
            if(h==canSobrantes)break;
        }
         pthread_mutex_unlock(&mutex);
         printf(" %d \n",h);
         h++;
    }

        pthread_exit(NULL);
}


void *funcionHilo(void *param){
    struct data *pixel=(struct data*)param;

    for(int i=pixel->inicio;i<pixel->fin;i++){
        for(int j=0;j<c;j++){
            
            if(i ==0 && j==0){
                imagenConFiltro[i][j]=(imagen[i][j]+imagen[i][j+1]+imagen[i+1][j]+imagen[i+1][j+1])/4;
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
                imagenConFiltro[i][j]=(float)(imagen[i][j]+imagen[i][j-1]+imagen[i][j+1]+imagen[i+1][j]+imagen[i+1][j-1]+imagen[i+1][j+1])/6;
            }
            if(i==f-1 && j!=0 && j!=c-1){
                imagenConFiltro[i][j]=(float)(imagen[i][j]+imagen[i][j-1]+imagen[i][j+1]+imagen[i-1][j]+imagen[i-1][j-1]+imagen[i-1][j+1])/6;
            }
            if(j==0 && i!=0 && i!=f-1){
                imagenConFiltro[i][j]=(float)(imagen[i][j]+imagen[i-1][j]+imagen[i+1][j]+imagen[i][j+1]+imagen[i-1][j+1]+imagen[i+1][j+1])/6;
            }
            if(j==c-1 && i!=0 && i!=f-1){
                imagenConFiltro[i][j]=(float)(imagen[i][j]+imagen[i-1][j]+imagen[i+1][j]+imagen[i][j-1]+imagen[i-1][j-1]+imagen[i+1][j-1])/6;
            }
            if(i!=0 && i!=f-1 && j!=0 && j!=c-1){
                imagenConFiltro[i][j]=(float)(imagen[i][j]+imagen[i-1][j]+imagen[i+1][j]+imagen[i][j-1]+imagen[i][j+1]+imagen[i-1][j-1]+imagen[i-1][j+1]+imagen[i+1][j-1]+imagen[i+1][j+1])/9;
            }
    }
    }

    pthread_exit(NULL);
}
