#include <stdio.h> 
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>


int main(){


    int maxtub, **mtub, idx, n;

    char message[100];

    scanf("%d", &maxtub);
    
    mtub = (int **)calloc(maxtub,sizeof(int *));

    for(int f = 0; f <= maxtub; f++)
        mtub[f] = (int *) calloc(2, sizeof(int));
        
    for(int tub = 0; tub <= maxtub; tub++) pipe(mtub[tub]);


    for(idx = 0; idx < maxtub; idx++)
        if(!fork()) break;
    //bloque de cada proceso

    if(idx == maxtub){ //codigo padre
        printf("[%d] padre\n", getpid());
            
        do{
            printf("ingrese el mensaje:\n");
            scanf("%s",message);
            
            write(mtub[0][1], &message, strlen(message));

            while((n = read(mtub[maxtub][0], &message, strlen(message))) > 0){
                printf("%d recibido: %s\n",getpid(), message);
                break;
            }
            
        }while(strcmp(message, "end") !=0);

        for(int tub = 0; tub < maxtub; tub++){
            close(mtub[tub][1]);
            close(mtub[tub][0]);
        }

        for(int chld = 0; chld < maxtub; chld++)
            wait(NULL);
        printf("termino padre\n");
    }
    else{ //codigo hijo

    char messageR[100];

    printf("[%d] hijo %d\n", getpid(), idx);
    close(mtub[idx][1]);
    close(mtub[idx+1][0]);


        for(int tub = idx+2; tub < maxtub; tub ++){
                close(mtub[tub][0]);
                close(mtub[tub][1]);
        }

        while ((n=read(mtub[idx][0], &messageR, strlen(messageR))) > 0){
            printf("%d recibido: %s\n", getpid(), messageR);

            if(strcmp(messageR, "end") == 0) break;
            write(mtub[idx+1][1], &messageR, strlen(messageR));
        }

        printf("[%d] termino\n", getpid());
    }

}