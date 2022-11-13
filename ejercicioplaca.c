#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

struct data
{
    int inicio;
    int fin;
};

void *funcionHilo(void *param);
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barrera;
pthread_barrier_t muro;
int **placa;
int t=0;
 int iteraciones=0;
 int columnasInt=0;
 int  filasInt =0;
int main()
{

    char filas[256];
    char columnas[256];
    char digito[256];
    int hilos = 0;

    FILE *archivo;

    archivo = fopen("test2.txt", "r");
    fscanf(archivo, "%s", &filas);
    fscanf(archivo, "%s", &columnas);

    pthread_barrier_init(&barrera, NULL, hilos+1);
     filasInt = atoi(filas);
     columnasInt = atoi(columnas);

    placa = (int **)malloc(filasInt * sizeof(int *));

    for (int i = 0; i < filasInt; i++)
    {
        placa[i] = (int *)malloc(columnasInt * sizeof(int));
    }

    for (int i = 0; i < filasInt; i++)
    {
        for (int j = 0; j < columnasInt; j++)
        {
            fscanf(archivo, "%s", &digito);
            placa[i][j] = atoi(digito);
        }
    }

    do
    {
        printf("Ingrese el numero de hilos: ");
        scanf("%d", &hilos);

        if (hilos > filasInt)
        {
            printf("El numero de hilos no puede ser menor o igual  a las filas de la placa\n");
        }

        if (hilos <= filasInt)
        {
            break;
        }

    } while (1);

    int filasPorHilo = (filasInt-2) / hilos;

    pthread_t hilosArray[hilos];

    struct data *d;

    d =calloc(hilos, sizeof(struct data));

    do{
        printf("Ingrese el numero de iteraciones: \n");
        scanf("%d",&iteraciones);
        if(iteraciones<1){
            printf("El numero de iteraciones debe ser mayor a 0\n");
        }else{
            break;
        }
    }while(1);

    printf("Estado de la placa en el tiempo 0\n");
    for (int i = 0; i < filasInt; i++)
    {
        for (int j = 0; j < columnasInt; j++)
        {
            printf("%d ", placa[i][j]);
        }
        printf("\n");
    }


    for (int i = 0; i < hilos; i++)
    {
        if(i==0){
            d[i].inicio = 1;
             d[i].fin =(d[i].inicio + filasPorHilo)-1;
        }else{
             d[i].inicio = i * filasPorHilo;
             d[i].fin =d[i].inicio + filasPorHilo;
        }

        pthread_create(&hilosArray[i], NULL, (void *)funcionHilo, (void *)&d[i]);
    }
     pthread_barrier_init(&muro, NULL, hilos);


    while(t<iteraciones){
        if(t==0){
            pthread_barrier_wait(&barrera);
            pthread_barrier_init(&muro, NULL, hilos);
        }else{
             pthread_barrier_init(&barrera, NULL, hilos+1);
             pthread_barrier_init(&muro, NULL, hilos);
             pthread_barrier_wait(&barrera);
        }
       
        printf("Estado de la placa en el tiempo %d\n",t+1);
        for (int i = 0; i < filasInt; i++)
        {
            for (int j = 0; j < columnasInt; j++)
            {
                printf("%d ", placa[i][j]);
            }
            printf("\n");
        }
        
        t++;
    }

    for (int i = 0; i < hilos; i++)
    {
        pthread_join(hilosArray[i], NULL);
    }

    free(d);

    fclose(archivo);

    return 0;
}

void *funcionHilo(void *param)
{
    struct data *d = (struct data *)param;
    int inicio = d->inicio;
    int fin = d->fin;
    int i = 0;
    printf("hilo inicio %d fin %d\n", inicio, fin);

    do{
        pthread_barrier_wait(&muro);
        pthread_exit(NULL);
        for(int i=inicio;i<fin;i++){
            for(int j=1;j<columnasInt;j++){
               pthread_mutex_lock(&mutex);
                placa[i][j]=(placa[i-1][j]+placa[i+1][j]+placa[i][j-1]+placa[i][j+1])/4;
                pthread_mutex_unlock(&mutex);
            }
        }
        pthread_barrier_wait(&barrera);
    i++;
    }while (i<iteraciones);


    pthread_exit(NULL);
}