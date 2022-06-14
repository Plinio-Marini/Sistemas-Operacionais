#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// numero maximo de numeros
#define MAX_NUM 100

// lista de numeros
int valores[MAX_NUM] = {0};

// faz o parse dos itens recebidos pela linha de comando como argumento do programa;
// quantidade é o numero de argumentos do programa - 1; (argc - 1)
// argumentos é o proprio argv; (começa o parse no segundo argumento (i +1))
void obtemNumeros(int quantidade, char *argumentos[]){
    int i = 0;
    char *p;
    // percorre os argumentos até o ultimo ou até atingir o limite maximo definido em MAX_NUM
    while((i < quantidade) && (i < MAX_NUM)){ 
        valores[i] = strtol(argumentos[i+1], &p, 10); // converte o argumento em int e guarda na lista
        i++;
    }
}

void *valorMax(void *argumento){
    int qntNumeros = * (int *) argumento;
    int valorMax = valores[0];

    int i = 1;
    while(i < qntNumeros){
        if(valorMax < valores[i]){
            valorMax = valores[i];
        }
        i++;
    }

    printf("O valor máximo é %d\n", valorMax);
}

void *valorMin(void *argumento){
    int qntNumeros = * (int *) argumento;
    int valorMin = valores[0];
    
    int i = 1;
    while(i < qntNumeros){
        if(valorMin > valores[i]){
            valorMin = valores[i];
        }
        i++;
    }

    printf("O valor mínimo é %d\n", valorMin);
}

void *media(void *argumento){
    int qntNumeros = * (int *) argumento;
    int mediaValores = 0;

    int i = 0;
    while(i < qntNumeros){
        mediaValores += valores[i];
        i++;
    }
    mediaValores = mediaValores / qntNumeros;

    printf("O valor médio é %d\n", mediaValores);
}

int main(int argc, char *argv[]){
    pthread_t threadMedia, threadMaxval, threadMinval;
    int numeroDeValores = argc - 1;
    int flags[3];

    if(argc < 2){
        printf("numero de argumentos invalido\n");
        return 0;
    }

    obtemNumeros(numeroDeValores, argv); // popula a lista de numeros

    flags[0] = pthread_create(&threadMedia, NULL, media, &numeroDeValores);
    flags[1] = pthread_create(&threadMaxval, NULL, valorMax, &numeroDeValores);
    flags[2] = pthread_create(&threadMinval, NULL, valorMin, &numeroDeValores);
    for(int i = 0; i < 3; i++){
        if(flags[i]){
            printf("Erro na criacao da thread %d\n", i);
        }
    }
    pthread_exit(NULL);
    
    return 0;
}