#ifndef _shell_
#define _shell_

// defs
#define MAX_ARGS 8
#define CMD_CHAR_MAX 256

// indices dos cmds
#define EXIT -2
#define PS 0
#define PWD 1
#define CD 2
#define TOP 3
#define CP 4
#define MV 5
#define MKDIR 6
#define RMDIR 7
#define WHO 8
#define CAT 9

// funcs
void pega_vars(); // captura as vars de ambiente para exibir no shell
void splita(); // separa os argumentos
void cmd(); // pega os comandos do usuario
int read_arg(); // valida o comando recebido
int shell(); // loop do shell

#endif