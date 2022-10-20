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
    struct message msg;
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
            printf("Ingrese el texto del sensor:\n");
            scanf("%s",msg.text);
            if(strcmp(msg.text,"salir")==0){
                break;
            }
            printf("Ingrese el id del sensor: \n");
            scanf("%d",&msg.id);
            printf("Ingrese el tiempo de espera del sensor:\n");
            scanf("%d",&msg.time);
            write(fd[1],&msg,sizeof(struct message));
        }
        close(fd[1]);

        for(int i=0;i<sensorNum;i++){
            wait(NULL);
        }

    }else{
        close(fd[1]);
        while(1){
            read(fd[0],&msg,sizeof(msg));

            if(msg.id == id){
                printf("ID: %d, Time: %d, Text: %s\n",msg.id,msg.time,msg.text);
                if(strcmp(msg.text, "salir") != 0){
                         break;
                    }
            }
        }
    } 

    return 0;
}