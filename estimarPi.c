#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

void *funcion_hilo(void *param);
void *funcion_hilo_sin_asignar(void *param);

int potencia(int base,int exponente){
    int resultado=1;
    for(int i=0;i<exponente;i++){
        resultado=resultado*base;
    }
    return resultado;
}

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

float resultado=0;
int  *terminos;
int *calculados;
int tamanoFaltante;

struct segment{
    int inicio;
    int fin;
};

int main(){
    int n=0;
    int child;
    int segmento=0;
    int bandera=0;
      int cobertura=0;
    do{
        printf("Ingrese hasta donde se hara la estimacion: \n");
        scanf("%d",&n);
        if(n<1 ){
            printf("El tamaño debe ser mayor a 0 y mayor a 1\n");
        }else{
            break;
        }
    }while(1);

    do{
        printf("Ingrese la cantidad de hilos que realizaran la tarea: \n");
        scanf("%d",&child);
        if(child>n){
            printf("La cantidad de hilos debe ser menor o igual al tamaño de los elementos\n");
        }else{
            if(n%child==0){
               segmento=n/child;
            }else{
                printf("La cantidad de hide los elementos\n");
                float aux=n/child;
                segmento=(int)aux;
                bandera=1;

            }
            break;
        }
         }while(1);
            
    pthread_t tid[child];
    struct segment  *d;
    d = (struct segment *)malloc(child*sizeof(struct segment));

    if(bandera){
       
        cobertura=child*segmento;

         tamanoFaltante=n-cobertura;

        if(tamanoFaltante>1){
                            terminos = (int *)malloc(tamanoFaltante*sizeof(int));
                            calculados = (int *)malloc(tamanoFaltante*sizeof(int));

                                        int aux=0;
                        for(int i=0;i<tamanoFaltante;i++){
                            if(i==0){
                                terminos[i]=cobertura;
                            }else{
                            terminos[i]=i+cobertura;
                            }
                            calculados[i]=0;
                            printf("%d\n",terminos[i]);
                        }

                        
                        for(int i=0;i<tamanoFaltante;i++){
                            printf("%d\n",terminos[i]);
                        }


                    for(int i=0;i<child;i++){
                            if(i==0){
                                d[i].inicio=0;
                            }else{
                                d[i].inicio=i*segmento;
                            }
                            d[i].fin=d[i].inicio+segmento;
                            pthread_create(&tid[i],NULL,funcion_hilo_sin_asignar,(void *)&d[i]);
                    }
          
        }else{
            printf("No se puede realizar la estimacion con la cantidad de hilos ingresada\n");
             for(int i=0;i<child;i++){
                    if(i==0){
                        d[i].inicio=0;
                    }else{
                        d[i].inicio=i*segmento;
                    }
                    if(i==child-1){
                        d[i].fin=d[i].inicio+segmento+1;
                    }else{
                    d[i].fin=d[i].inicio+segmento;

                    }
       pthread_create(&tid[i],NULL,funcion_hilo,(void *)&d[i]);
    }
        }

    }else{

    for(int i=0;i<child;i++){
       if(i==0){
         d[i].inicio=0;
       }else{
        d[i].inicio=i*segmento;
       }
       d[i].fin=d[i].inicio+segmento;
       pthread_create(&tid[i],NULL,funcion_hilo,(void *)&d[i]);
    }
    }

    for(int i=0;i<child;i++){
        pthread_join(tid[i],NULL);
    }

    printf("El valor de pi es: %f\n",4*(double)resultado);

    free(d);
    free(terminos);
    free(calculados);

    return 0;
}




void *funcion_hilo(void *param){
    struct segment *d = (struct segment *)param;
    int inicio=d->inicio;
    int fin=d->fin;
    int signoSerie=1;
    double  sumaHilo=0;

    for(int i=inicio;i<fin;i++){
        if(i==0){
            signoSerie=1;
        }else{
            signoSerie=potencia(-1,i);
        }

        if(signoSerie==1){
           sumaHilo=sumaHilo + (double)1/(2*i+1);
        }else{
            sumaHilo=sumaHilo - (double)1/(2*i+1);
        }
    }

    pthread_mutex_lock(&mutex);
    resultado+=sumaHilo;
    pthread_mutex_unlock(&mutex);

    pthread_exit(0);
}

void  *funcion_hilo_sin_asignar(void *param){
    struct segment *d = (struct segment *)param;
    int inicio=d->inicio;
    int fin=d->fin;
    int signoSerie=1;
    double  sumaHilo=0;
    double auxsumahilo=0;
    int j=0;

    for(int i=inicio;i<fin;i++){
        if(i==0){
            signoSerie=1;
        }else{
            signoSerie=potencia(-1,i);
        }

        if(signoSerie==1){
           sumaHilo=sumaHilo + (double)1/(2*i+1);
        }else{
            sumaHilo=sumaHilo - (double)1/(2*i+1);
        }
    }

        while(1){

              if(j==tamanoFaltante)break;
          pthread_mutex_lock(&mutex);
            if(calculados[j]==0){
                      calculados[j]=1;
                      int ter = terminos[j];
                if(ter==0){
                    signoSerie=1;
                }else{
                    signoSerie=potencia(-1,ter);
                }
                pthread_mutex_unlock(&mutex);
                if(signoSerie==1){
                   sumaHilo=sumaHilo + (double)1/(2*ter+1);
                }else{
                    sumaHilo=sumaHilo - (double)1/(2*ter+1);
                }

                            j++;
                    if(j==tamanoFaltante) break;
             }
                             pthread_mutex_unlock(&mutex);
                                         j++;
        }

        
    pthread_mutex_lock(&mutex);
    resultado+=sumaHilo;
    pthread_mutex_unlock(&mutex);
    
    pthread_exit(0);
}