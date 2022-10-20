#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>


struct message {
    int id;
    int time;
    char text[];
};

int main(){
    int sensorNum=0;
    int i=0;
    pid_t root=getpid();
    printf("Ingrese el numero de sensores a crear: \n");
    scanf("%d",&sensorNum);
    int fd[sensorNum][2];
    char mensaje2[100];

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
            struct message *msg=malloc(sizeof(struct message));;
            printf("Ingrese el texto del sensor:\n");
            scanf("%s",mensaje2);
            if(strcmp(mensaje2,"salir")==0){
                for (size_t j = 0; i < sensorNum; i++)
                {
                    write(fd[j][1],mensaje2,sizeof(mensaje2));
                }
            
                break;
            }
            //printf("Ingrese el id del sensor: \n");
            //scanf("%d",&msg->id);
            //printf("Ingrese el tiempo de espera del sensor:\n");
            //scanf("%d",&msg->time);
            //write(fd[1],&msg,sizeof(struct message));
        }
        //close(fd[1]);
        //printf("Se ha terminado el programa\n");
        for(int i=0;i<sensorNum;i++){
            wait(NULL);
        }

    }else{
        for (int d = 0; d < sensorNum; ++d) close(fd[d][1]);
        //struct message childMsg;
        char mensaje[100];
        while(1){
            for (int j = 0; j < sensorNum; ++j){
                read(fd[j][0],&mensaje,sizeof(mensaje));
            }
            printf(" %d mensaje: %s\n",getpid(),mensaje);
            if(strcmp(mensaje,"salir")==0){
                break;
            }
        }
    } 

    return 0;
}