#include <stdio.h> 
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

struct Data{
    int x;
    int y;
    int val;
};


int main(int argc, char **argv){

    struct Data dato;

    int maxtub, **mtub, idx, n,FA,CA,FB,CB;
    int  flag = 1;
    int i=0;
    maxtub=3;

    do{
    printf("Ingrese la cantidad de filas de la primera matriz: ");
    scanf("%d",&FA);
    printf("Ingrese la cantidad de columnas de la primera matriz: ");
    scanf("%d",&CA);
    printf("Ingrese la cantidad de filas de la segunda matriz: ");
    scanf("%d",&FB);
    printf("Ingrese la cantidad de columnas de la segunda matriz: ");
    scanf("%d",&CB);

    if(CA!=FB){
        printf("Las matrices no son compatibles para la multiplicacion\n");
        printf("Ingrese nuevamente los datos\n");
    }
    else{
        flag=0;
    }
    }while(flag);
   
   int matrizA[FA][CA];
   int matrizB[FB][CB];
   int matrizC[FA][CB];

    printf("Ingrese los valores de la primera matriz\n");
    for(int i=0;i<FA;i++){
        for(int j=0;j<CA;j++){
            printf("Ingrese el valor de la posicion [%d][%d]: ",i,j);
            scanf("%d",&matrizA[i][j]);
        }
    }

    printf("Ingrese los valores de la segunda matriz\n");
    for(int i=0;i<FB;i++){
        for(int j=0;j<CB;j++){
            printf("Ingrese el valor de la posicion [%d][%d]: ",i,j);
            scanf("%d",&matrizB[i][j]);
        }
    }

    printf("La primera matriz es:\n");
    for(int i=0;i<FA;i++){
        for(int j=0;j<CA;j++){
            printf("%d ",matrizA[i][j]);
        }
        printf("\n");
    }

    printf("La segunda matriz es:\n");
    for(int i=0;i<FB;i++){
        for(int j=0;j<CB;j++){
            printf("%d ",matrizB[i][j]);
        }
        printf("\n");
    }

    mtub = (int **)calloc(maxtub,sizeof(int *));

    for(int f = 0; f <= maxtub; f++)
        mtub[f] = (int *) calloc(2, sizeof(int));
        
    for(int tub = 0; tub <= maxtub; tub++) pipe(mtub[tub]);



    for(idx = 0; idx < maxtub; idx++)
        if(!fork()) break;
    //bloque de cada proceso

    if(idx == maxtub){ 
        printf("[%d] padre\n", getpid());
        for(int tub = 0; tub < maxtub; tub++)
            close(mtub[tub][1]);
            
        while ((n=read(mtub[3][0], &dato, sizeof(struct Data))) > 0){
            if(FA*CB < i ){
                i++;
            }
            printf("dato.x: %d, dato.y: %d, dato.val: %d\n",dato.x,dato.y,dato.val);
            matrizC[dato.x][dato.y] = dato.val;
        }
                
        close(mtub[idx][0]);
        for(int tub = 0; tub < maxtub; tub++)
            close(mtub[tub][0]);

        for(int chld = 0; chld < maxtub; chld++)
            wait(NULL);
        printf("termino padre\n");

        printf("La matriz resultante es:\n");
        for(int i=0;i<FA;i++){
            for(int j=0;j<CB;j++){
                printf("%d ",matrizC[i][j]);
            }
            printf("\n");
        }
    }
    else{ //codigo hijo
    printf("[%d] hijo %d\n", getpid(), idx);
        for(int tub = 0; tub < maxtub; tub ++){
            if(tub != idx){
                close(mtub[tub][0]);
                close(mtub[tub][1]);
            }
        }
        close(mtub[idx][0]);


       switch (idx){
       {
       case 0:
        for(int i=1;i<FA;i++){
            for(int j=0;j<CB-1;j++){

                dato.x=i;
                dato.y=j;
                dato.val=0;
                for(int k=0;k<CA;k++){
                    dato.val+=matrizA[i][k]*matrizB[k][j];
                }
                
            write(mtub[3][1], &dato, sizeof(struct Data));
            }
        }
        break;

         case 1:
         
        for(int i=0;i<FA-1;i++){
            for(int j=1;j<CB;j++){
                dato.x=i;
                dato.y=j;
                dato.val=0;
                for(int k=0;k<CA;k++){
                    dato.val+=matrizA[i][k]*matrizB[k][j];
                }
           
            write(mtub[3][1], &dato, sizeof(struct Data));
            }
        }
        break;

         case 2:
            for(int i=0;i<FA;i++){
                dato.x=i;
                dato.y=i;
                dato.val=0;
                for(int k=0;k<CA;k++){
                    dato.val+=matrizA[i][k]*matrizB[k][i];
                    
                }
                
                write(mtub[3][1], &dato, sizeof(struct Data));
            }
        break;
       
       }


        printf("[%d] termino\n", getpid());
    }
    }
    return 0;
}