/*
    SOLUCAO SERIAL
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define QNT_FILOSOFOS 5

#define PENSANDO 0
#define COMENDO 2

#define EM_USO 0
#define LIVRE 1

#define FALSE 0
#define TRUE 1

int estadoDosFilosofos[QNT_FILOSOFOS] = {0};
int estadoDosGarfos[QNT_FILOSOFOS] = {0};

void pensar(){
    int x = rand() % 6;
    sleep(x);
    // sleep rand 0 - 5
}

void comer(){
    int x = rand() % 6;
    sleep(x);
    // sleep rand 0 - 5
}

void pegarGarfos(int filosofo){
    int alguemComendo = FALSE;
    
    while (TRUE){
        alguemComendo = FALSE;
        for(int i = 0; i < QNT_FILOSOFOS; i++){
            if(estadoDosFilosofos[i] == COMENDO){
                alguemComendo = TRUE;
            }
        }
        if(alguemComendo == FALSE){
            estadoDosFilosofos[filosofo] = COMENDO;
            break;
        }
    }
}

void devolverGarfos(int filosofo){
    estadoDosFilosofos[filosofo] = PENSANDO;
}

void *filosofo(void * numeroDoFilosofoVoid){
    int numeroDoFilosofo = *(int *) numeroDoFilosofoVoid;

    while(TRUE){
        printf("filosofo pensando...\n");
        pensar();
        pegarGarfos(numeroDoFilosofo);
        printf("filosofo comendo...\n");
        comer();
        devolverGarfos(numeroDoFilosofo);
    }
}

int main(void){
    pthread_t filosofos[QNT_FILOSOFOS];
    
    printf("criando\n");
    for(int i = 0; i < QNT_FILOSOFOS; i++){
        pthread_create(&filosofos[i], NULL, filosofo, &i);
    }
    printf("join\n");
    for(int i = 0; i < QNT_FILOSOFOS; i++){
        pthread_join(filosofos[i], NULL); 
    }

    return 0;
}