#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<string.h>


int main(){
    char cadena[] = "Hola,mundo,soy,una,cadena,separa,por,comas",
    delimitador[] = ",";
    char *token = strtok(cadena, delimitador);
    if(token != NULL){
        while(token != NULL){
            // Sólo en la primera pasamos la cadena; en las siguientes pasamos NULL
            printf("Token: %s\n", token);
            token = strtok(NULL, delimitador);
        }
    }
}