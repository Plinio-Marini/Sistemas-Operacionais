/*
    SOLUCAO PARALELA
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define QNT_FILOSOFOS 5
#define ESQUERDA (filosofo+QNT_FILOSOFOS-1) % QNT_FILOSOFOS
#define DIREITA (filosofo+1) % QNT_FILOSOFOS
#define PENSANDO 0
#define COM_FOME 1
#define COMENDO 2

int estadoDoFilosofo[QNT_FILOSOFOS] = {0};
sem_t mutex;
sem_t filosofos_sem[QNT_FILOSOFOS];

#define FALSE 0
#define TRUE 1

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

void tentarPegar(int filosofo){
    if(estadoDoFilosofo[filosofo] == COM_FOME && estadoDoFilosofo[ESQUERDA] != COMENDO && estadoDoFilosofo[DIREITA] != COMENDO){
        estadoDoFilosofo[filosofo] = COMENDO;
        sem_post(&filosofos_sem[filosofo]);
    }
}

void pegarGarfos(int filosofo){
    sem_wait(&mutex);
    estadoDoFilosofo[filosofo] = COM_FOME;
    tentarPegar(filosofo);
    sem_post(&mutex);
    sem_wait(&filosofos_sem[filosofo]);
}

void devolverGarfos(int filosofo){
    sem_wait(&mutex);
    estadoDoFilosofo[filosofo] = PENSANDO;
    tentarPegar(ESQUERDA);
    tentarPegar(DIREITA);
    sem_post(&mutex);
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
    printf("criando...\n");
    sem_init(&mutex, 0, 1);
    for(int i = 0; i < QNT_FILOSOFOS; i++){
        sem_init(&filosofos_sem[i], 0, 0);
    }
    for(int i = 0; i < QNT_FILOSOFOS; i++){
        pthread_create(&filosofos[i], NULL, filosofo, &i);
    }
    printf("join...\n");
    for(int i = 0; i < QNT_FILOSOFOS; i++){
        pthread_join(filosofos[i], NULL); 
    }
    sem_destroy(&mutex);
    for(int i = 0; i < QNT_FILOSOFOS; i++){
        sem_destroy(&filosofos_sem[i]);
    }

    return 0;
}