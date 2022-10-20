#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>

#define MAX_READ 500


int main(){
    int sensorNum=0;
    int i=0;
    pid_t root=getpid();
    printf("Ingrese el numero de sensores a crear: \n");
    scanf("%d",&sensorNum);
    int fd[sensorNum][2];
    char mensaje2[100];
    char id[100];
    char time[100];
    
    for (int p = 0; p < sensorNum; ++p) pipe(fd[p]);

    for ( i = 0; i < sensorNum; i++)
    {
        if(fork()==0){
            printf("Soy el proceso hijo %d y mi padre es %d\n",getpid(),getppid());
            break;
        }
    }

    if(root == getpid()){
       for (int h = 0; h < sensorNum; ++h) close(fd[h][0]);
        while(1){
            printf("Ingrese el texto del sensor:\n");
            scanf("%s",mensaje2);    
            if(strcmp(mensaje2,"salir")==0){
                for (size_t j = 0; j < sensorNum; j++)
                {
                    char comando[1024]="";
                    strcat(comando,mensaje2);
                    strcat(comando,"/");
                    strcat(comando,"123");
                    strcat(comando,"/");
                    strcat(comando,"año");
                    printf("%s\n",comando);
                    write(fd[j][1],comando,sizeof(comando));
                }
                printf("Saliendo del programa\n");
                break;
            }
            //printf("Ingrese el id del sensor: \n");
            //scanf("%s",id);
            //printf("Ingrese el tiempo de espera del sensor:\n");
            //scanf("%s",time);

        }
        //close(fd[1]);
        //printf("Se ha terminado el programa\n");
        for(int i=0;i<sensorNum;i++){
            wait(NULL);
        }

    }else{
        for (int d = 0; d < sensorNum; ++d) close(fd[d][1]);
        //struct message childMsg;
        char mensaje[1024];
        int n=0;
        char *delimitador = "/";

        while((n=read(fd[i][0],&mensaje,sizeof(mensaje)))>0){
                char *orden=strtok(mensaje,delimitador);
                char *id=strtok(NULL,delimitador);
                char *time=strtok(NULL,delimitador);
                printf("El mensaje es: %s\n",orden);
                printf("El id es: %s\n",id);
                printf("El tiempo es: %s\n",time);
                if(strcmp(orden,"salir")==0){
                    printf("Saliendo del programa\n");
                    exit(0);
                }
        }
    } 

    return 0;
}