#include <stdio.h>
#include <stdlib.h>
#include <string.h> // ???
#include <fcntl.h> // ???

int main()
{
	// USAR ARGV

	char ch, arq_raiz[25], arq_destino[25];
	FILE *raiz, *destino; 

	printf("Entre com o nome do arquivo a ser copiado!\n");
	scanf("%s", arq_raiz); 

	// USAR ARGV

	raiz = fopen(arq_raiz,"r"); 

	if(raiz == NULL)
	{
		printf("\nO arquivo está vazio! Aperte qualquer tecla para sair do programa."); 
		exit(EXIT_FAILURE); // RETURN 
	}

	printf("Entre com o nome do arquivo clone!\n");
	scanf("%s", arq_destino); 

	destino = fopen(arq_destino, "w");

	if(arq_raiz == NULL)
	{
		fclose(raiz);
		printf("\nO arquivo está vazio! Aperte qualquer tecla para sair do programa."); 
		exit(EXIT_FAILURE); // RETURN 
	}

	// USAR LEITURA BINARIA? copiar mais bytes de uma vez usando int/long e diminuir o numero de iteracoes
	while(( ch = fgetc(raiz)) != EOF )
	{
		fputc(ch, destino);
	}

	fclose(raiz);
	fclose(destino);

	return 0;
}

/* REF
https://en.wikipedia.org/wiki/C_data_types
https://www.cplusplus.com/reference/cstdio/fread/
https://en.cppreference.com/w/c/io/fread
*/