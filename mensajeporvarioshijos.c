#include <stdio.h> 
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

#define MAX_READ 256
#define EOL '\0'
char buff[MAX_READ];

int main(){


    int maxtub, **mtub, idx, n;


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
         fgets(buff, MAX_READ, stdin );         
         if(strlen(buff)>1){
            buff[strlen(buff)-1] = '\0';
            printf("[%d]write-->:%s\n",getpid(),buff);
            write(mtub[0][1], buff, strlen(buff));
         }
       }while(strcmp(buff,"salir") !=0);

        for(int tub = 0; tub < maxtub; tub++){
            close(mtub[tub][1]);
            close(mtub[tub][0]);
        }

        for(int chld = 0; chld < maxtub; chld++)
            wait(NULL);
        printf("termino padre\n");
    }
    else{ //codigo hijo

    printf("[%d] hijo %d\n", getpid(), idx);
    close(mtub[idx][1]);
    close(mtub[idx+1][0]);


        for(int tub = idx+2; tub < maxtub; tub ++){
            close(mtub[tub][0]);
            close(mtub[tub][1]);
        }
         
         while( (n=read(mtub[0][0],buff, MAX_READ)) >0 ){
            buff[n] = '\0';
            printf("[%d]read<--:%s\n",getpid(),buff);                       
          }

        printf("[%d] termino\n", getpid());
    }
    return EXIT_SUCCESS;
}