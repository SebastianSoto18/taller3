#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int i, **pipes, id, n, t;

  printf("\t\tCliente/Servidor\n");
  printf("Cantidad de procesos: ");
  scanf("%d",&n);

  if (n < 1) {
    return -1;
  }

  int ids[n];

  pipes = (int**)calloc(n+1, sizeof(int*));
  for (i = 0; i <= n; i++) {
    pipes[i] = (int*)calloc(2, sizeof(int));
  }

  for (i = 0; i <= n; i++) {
    if (pipe(pipes[i])) {
      return -1;
    }
  }

  for (id = 0; id < n; id++) {
    ids[id] = fork();

    if(!ids[id]) {
      printf("Proceso hijo #%d e idSensor = %d\n", id, getpid());
      break;
    }
  }

  if (id == n) {
    sleep(1);
    for(int i = 0 ; i <= n; i++) {
      close(pipes[i][0]);
    }

    close(pipes[n][1]);

    int idSensor, time, orderValue, sensorPosicion;
    char order[20];

    while (1) {

      printf("\n\n\t***Servidor***\n");
      printf("Orden (habilitar | desabilitar | salir): ");
      scanf("%s", &order);

      if (strcmp(order, "salir") == 0) {
        orderValue = -1;
        for(int i = 0 ; i < n; i++) {
          write(pipes[i][1], &orderValue, sizeof(int));
        }
        return 0;
      } else {
        orderValue = (strcmp(order, "habilitar") == 0);
      }

      printf("Identificador del sensor: ");
      scanf("%d", &idSensor);
      printf("Tiempo en nanosegundos: ");
      scanf("%d", &time);


      sensorPosicion = -1;
      for(int i = 0 ; i <= n; i++) {
        if (ids[i] == idSensor) {
          sensorPosicion = i;
          break;
        }
      }

      write(pipes[sensorPosicion][1], &orderValue, sizeof(int));
      write(pipes[sensorPosicion][1], &time, sizeof(int));
    }
  } else {
    for(int i = 0; i <= n; i++) {
      close(pipes[i][1]);

      if (i != id) {
        close(pipes[i][0]);
      }
    }

    close(pipes[n][1]);

    int orderValue;
    int time;

    while (1) {
      read(pipes[id][0], &orderValue, sizeof(int));

      if (orderValue == -1) {
        return 0;
      }

      read(pipes[id][0], &time, sizeof(int));

      sleep(time / 1000);

      if (orderValue == 1) {
        printf("\n\nSensor #%d habilitado\n", id);
      } else {
        printf("\n\nSensor #%d deshabilitado\n", id);
      }
    }
  }

  return 0;
}
