#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>

#define MAX_READ 1024
#define EOL '\0'
char buff[MAX_READ];

int main(){
    int sensorNum=0;
    int i=0;
    pid_t root=getpid();
    printf("Ingrese el numero de sensores a crear: \n");
    scanf("%d",&sensorNum);
    int fd[sensorNum][2], n;
    char mensaje2[100];
    char id[100];
    char time[100];
    
    for (int p = 0; p < sensorNum; ++p) pipe(fd[p]);

    for ( i = 0; i < sensorNum; i++)
    {
        if(fork()==0){
            printf("Soy el proceso hijo %d y mi padre es %d\n",i,getppid());
            break;
        }
    }

    if(root == getpid()){
       for (int h = 0; h < sensorNum; ++h) close(fd[h][0]);
        while(1){
            printf("Ingrese la orden para el sensor:\n");
            scanf("%s",mensaje2);    
            if(strcmp(mensaje2,"salir")==0){
                for (size_t j = 0; j < sensorNum; j++)
                {
                    char comando[1024]="";
                    strcat(comando,mensaje2);
                    strcat(comando,"/");
                    strcat(comando,"999");
                    strcat(comando,"/");
                    strcat(comando,"año");
                    write(fd[j][1],comando,sizeof(comando));
                }
                printf("Saliendo del programa\n");
                for (int h = 0; h < sensorNum; ++h) close(fd[h][1]);
                for (int h = 0; h < sensorNum; ++h) wait(NULL);
                break;
            }
            printf("Ingrese el id del sensor: \n");
            scanf("%s",id);
            printf("Ingrese el tiempo de espera del sensor:\n");
            scanf("%s",time);

            char comando[1024]="";
            strcat(comando,mensaje2);
            strcat(comando,"/");
            strcat(comando,id);
            strcat(comando,"/");
            strcat(comando,time);
            strcat(buff,comando);
            buff[strlen(buff)-1] = '\0';
            for(int g=0;g<sensorNum;++g)write(fd[atoi(g)][1],buff,sizeof(buff));

        }

    }else{
        for (int d = 0; d < sensorNum; ++d) close(fd[d][1]);
        int j=0;
        char *delimitador = "/";

        while((n=read(fd[j][0],buff, MAX_READ)) >0){
                buff[n] = '\0';
                char *orden=strtok(buff,delimitador);
                char *id=strtok(NULL,delimitador);
                char *time=strtok(NULL,delimitador);

                if(strcmp(orden,"salir")==0){
                    exit(0);
                }
                printf("tumama");
                if(atoi(id)==i){
                    printf("La orden enviada es: [%s]",orden);
                }
                j++;
        }
    } 

    return EXIT_SUCCESS;
}