#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>


struct message {
    int id;
    int time;
    char text[100];
};

int main(){
    int fd[2];
    int pid;
    int id=0;
    pipe(fd);
    int sensorNum=0;

    printf("Ingrese el numero de sensores a crear: \n");
    scanf("%d",&sensorNum);


    for (int i = 0; i < sensorNum; i++)
    {
        pid=fork();
        if(pid==0){
            id=getpid();
            printf("%d\n",id);
            break;
        }
    }

    if(pid!=0){
        close(fd[0]);
        while(1){
            struct message *msg=malloc(sizeof(struct message));;
            printf("Ingrese el texto del sensor:\n");
            scanf("%s",msg->text);
            if(strcmp(msg->text,"salir")==0){
                msg->id=1;
                msg->time=0;
                write(fd[1],&msg,sizeof(msg));
                break;
            }
            printf("Ingrese el id del sensor: \n");
            scanf("%d",&msg->id);
            printf("Ingrese el tiempo de espera del sensor:\n");
            scanf("%d",&msg->time);
            write(fd[1],&msg,sizeof(struct message));
        }
        close(fd[1]);
        printf("Se ha terminado el programa\n");
        for(int i=0;i<sensorNum;i++){
            wait(NULL);
        }

    }else{
        close(fd[1]);
        struct message childMsg;
        while(1){
            read(fd[0],&childMsg,sizeof(struct message));
            printf("mensaje: %d\n",childMsg.id);

            //if(strcmp(childMsg.text, "salir") == 0){
                    //break;
            //}
            //if(childMsg.id == getpid()){
                //printf("ID: %d, Time: %d, Text: %s\n",childMsg.id,childMsg.time,childMsg.text);
            //}
        }
    } 

    return 0;
}