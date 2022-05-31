#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell-vNC.h"

pid_t pid;

char* userName;
char* hostName;

char comando[CMD_CHAR_MAX];
char* comandoVars[MAX_ARGS];

void pega_vars(){
    userName = getenv("USER");
    hostName = getenv("HOSTNAME");
}

void cmd(){
    printf("\n%s @ %s >> ", userName, hostName); // printa o prompt
    fgets(comando, CMD_CHAR_MAX, stdin); // captura o comando
    // remove o \n deixado pelo fgets
    if(comando[strlen(comando) - 1] == '\n') comando[strlen(comando) - 1] = '\0';
}

int shell(){
    int flag; // flag de selecao do comando

    while(1){
        cmd();
        splita();
        flag = read_arg();

        if(flag == EXIT){
            return 0;
        }
        // forkeia pra executar o comando
        pid = fork();
        if(pid == -1){
            fprintf(stderr, "Falha no fork");
            return -1;
        }else if(pid == 0){
            if(flag >= 0 && flag <= 9){
                execvp(comandoVars[0], comandoVars);
            }else{
                printf("comando invalido (\">> exit\" para fechar o shell)");
            }
            exit(1); // fecha o processo
        }else{
            // esperar a execucao do pid
            wait(NULL);
        }
    }
}


void splita(){
    int i = 0;
    char* aux = NULL;
    aux = strtok(comando, " "); // splita os argumentos separados por espaco

    while(aux != NULL){
        comandoVars[i] = aux;
        aux = strtok(NULL, " "); // continua splitando
        i++;
    }
}

// PRECISA SER EXECUTADO SO DEPOIS DO SPLIT
int read_arg(){ 
    char* validos[] = {"ps\0", "pwd\0", "cd\0", "top\0", "cp\0", "mv\0", "mkdir\0", "rmdir\0", "who\0", "cat\0"}; //lista de comandos validos (DEVEM ESTAR NA ORDEM DOS INDICES DEFINIDOS NO .h)
    int flag = -1;
    int idc = 0;
    
    if(!(strcmp(comandoVars[0], "exit\0"))){
        return EXIT;
    }
    while((idc < 10) && (flag == -1)){
        if(!(strcmp(comandoVars[0], validos[idc]))){
            flag = idc;
        }
        idc++;
    }
    return flag;
}

int main(void){
    return shell();
}