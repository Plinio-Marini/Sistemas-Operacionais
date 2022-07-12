/*
    SOLUCAO SEM CONTROLE DE IMPASSES
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define QNT_FILOSOFOS 5

#define EM_USO 0
#define LIVRE 1

#define TRUE 1

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

void pegarGarfos(int garfo){
    while(TRUE){
        printf("filosofo esperando garfo\n");
        if(estadoDosGarfos[garfo] == LIVRE){
            estadoDosGarfos[garfo] = EM_USO;
            break;
        }
    }
}

void devolverGarfos(int garfo){
    estadoDosGarfos[garfo] = LIVRE;
}

void *filosofo(void * numeroDoFilosofoVoid){
    int numeroDoFilosofo = *(int *) numeroDoFilosofoVoid;

    while(TRUE){
        printf("filosofo pensando...\n");
        pensar();
        pegarGarfos(numeroDoFilosofo); //pega o garfo da esquerda
        pegarGarfos((numeroDoFilosofo + 1) % QNT_FILOSOFOS); //pega o garfo da direita
        printf("filosofo comendo...\n");
        comer();
        devolverGarfos(numeroDoFilosofo); // devolve o garfo da esquerda
        devolverGarfos((numeroDoFilosofo + 1) % QNT_FILOSOFOS); // devolve o garfo da direita
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