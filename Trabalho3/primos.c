#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int verificaPrimo(int numero){
    int flagDivisao = 0;

    for(int i = 1; i <= numero; i++){
        if(numero % i == 0){
            flagDivisao++; // verifica a divisibilidade do numero (quantos sao divisiveis) / caso mais de 2 (ele mesmo e 1) ele nao eh primo
        }
    }

    if(flagDivisao != 2){
        return 0; // numero nao eh primo -> retorna 0
    } else return numero; // numero eh primo -> retorna o numero
}

void *produzirPrimos(void *argumento){
    int numero = * (int *) argumento;

    int i = 2; // numeros primos comecam em 2
    while(numero >= i){
        if(verificaPrimo(numero) != 0){ // verifica se o numero eh primo
            printf("%d ", numero); // se sim printa o numero
        }
        numero--; // vai pro proximo numero inferior
    }
    printf("\n");
}

int main(void){
    pthread_t thread;
    int flag;
    int numero;

    printf("Insira o numero: ");
    scanf("%d", &numero);

    flag = pthread_create(&thread, NULL, produzirPrimos, &numero);
    if(flag != 0) printf("Erro na criacao da thread\n");
    pthread_exit(NULL);
    return 0;
}