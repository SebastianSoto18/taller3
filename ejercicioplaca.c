#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

struct data
{
    int inicio;
    int fin;
};

void *funcionHilo(void *param);
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barrera;
pthread_barrier_t muro;
float **placa;
int t = 0;
int iteraciones = 0;
int columnasInt = 0;
int filasInt = 0;
int bandera = 1;
int main()
{
    int hilos = 0;
    FILE *archivo;

    archivo = fopen("test2.txt", "r");
    fscanf(archivo, "%d", &filasInt);
    fscanf(archivo, "%d", &columnasInt);
    fscanf(archivo, "%d", &hilos);
    fscanf(archivo, "%d", &iteraciones);
    printf("filas: %d columnas: %d hilos: %d iteraciones: %d\n", filasInt, columnasInt, hilos, iteraciones);

    placa = (float **)malloc(filasInt * sizeof(float *));

    for (int i = 0; i < filasInt; i++)
    {
        placa[i] = (float *)malloc(columnasInt * sizeof(float));
    }

    for (int i = 0; i < filasInt; i++)
    {
        for (int j = 0; j < columnasInt; j++)
        {
            fscanf(archivo, "%f", &placa[i][j]);
        }
        
    }

    

    int filasPorHilo = (filasInt - 2) / hilos;

    pthread_t hilosArray[hilos];

    struct data *d;

    d = calloc(hilos, sizeof(struct data));

    printf("La placa en el tiempo 0 : \n");

    for (int i = 0; i < filasInt; i++)
    {
        for (int j = 0; j < columnasInt; j++)
        {
            printf("%.1f", placa[i][j]);
        }
        printf("\n");
    }

    int hilosmasprincipal = hilos + 1;
    pthread_barrier_init(&barrera, NULL, hilosmasprincipal);
      pthread_barrier_init(&muro, NULL, hilosmasprincipal);
    for (int i = 0; i < hilos; i++)
    {
        if (i == 0)
        {
            d[i].inicio = 1;
            d[i].fin = (d[i].inicio + filasPorHilo) - 1;
        }
        else
        {
            d[i].inicio = i * filasPorHilo;
            d[i].fin = d[i].inicio + filasPorHilo;
        }

        pthread_create(&hilosArray[i], NULL, (void *)funcionHilo, (void *)&d[i]);
    }

    pthread_barrier_wait(&barrera);
     pthread_barrier_init(&barrera, NULL, hilosmasprincipal);
     pthread_barrier_wait(&muro);
    while (t < iteraciones)
    {
        
            printf("Estado de la placa en el tiempo %d\n", t + 1);
            for (int i = 0; i < filasInt; i++)
            {
                for (int j = 0; j < columnasInt; j++)
                {
                    printf("%.1f ", placa[i][j]);
                }
                printf("\n");
            }
            t++;
            if (t == iteraciones) break;

            printf("\n");
            printf("\n");
            printf("\n");       
            printf("Inicio de el procesamiento de los datos...\n");
             pthread_barrier_wait(&barrera);
             printf("Fin procesamiento de los datos...\n");
            pthread_barrier_init(&barrera, NULL, hilosmasprincipal);
            printf("Preparando para mostrar datos...\n");
            pthread_barrier_wait(&muro);
            printf("Desplegando datos...\n");
            pthread_barrier_init(&muro, NULL, hilosmasprincipal);
             

    }

    for (int i = 0; i < hilos; i++)
    {
        pthread_join(hilosArray[i], NULL);
    }

    free(d);
    free(placa);
    fclose(archivo);
    pthread_barrier_destroy(&barrera);
    pthread_barrier_destroy(&muro);
    return 0;
}

void *funcionHilo(void *param)
{
    struct data *d = (struct data *)param;
    int inicio = d->inicio;
    int fin = d->fin;
    int f = 0;

    while (1)
    {

        pthread_barrier_wait(&barrera);

        for (int i = inicio; i < fin; i++)
        {
            for (int j = 1; j < columnasInt - 1; j++)
            {
                pthread_mutex_lock(&mutex);
                placa[i][j] = (placa[i - 1][j] + placa[i + 1][j] + placa[i][j - 1] + placa[i][j + 1]) / 4;
                pthread_mutex_unlock(&mutex);
            }
        }
        f++;

         pthread_barrier_wait(&muro);

        if(iteraciones == 1) break;
        if (f == iteraciones)break;
    }

    pthread_exit(NULL);
}