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
int canSobrantes ;
int columnas=0;
