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
int main()
{

    char filas[256];
    char columnas[256];
    char digito[256];
    int hilos = 0;
    int iteraciones=0;
    int t=0;
    FILE *archivo;

    archivo = fopen("test2.txt", "r");
    fscanf(archivo, "%s", &filas);
    fscanf(archivo, "%s", &columnas);

    pthread_barrier_init(&barrera, NULL, hilos+1);
    int filasInt = atoi(filas);
    int columnasInt = atoi(columnas);

    int placa[filasInt][columnasInt];

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

    int filasPorHilo = filasInt / hilos;

    pthread_t hilosArray[hilos];

    struct data *d;

    d = calloc(hilos, sizeof(struct data));

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
            d[i].inicio = 0;
        }else{
             d[i].inicio = i * filasPorHilo;
        }
        d[i].fin =d[i].inicio + filasPorHilo;

        pthread_create(&hilosArray[i], NULL, (void *)funcionHilo, (void *)&d[i]);
    }

    while(t<iteraciones){
        pthread_barrier_wait(&barrera);
        
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