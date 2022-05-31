// versao sem plagio
// falta tratamento de erro e talvez refatoracao?
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){	
	FILE* arquivoOrigem;
	FILE* arquivoDestino;

	long tamanhoOrigem;
	char* bufferDestino;

	// resolver depois
	//if(strcmp(argv[1], argv[2]) == 0){
	//
	//}
	
	// abre o arquivo de origem
	arquivoOrigem = fopen(argv[1], "rb");
	if (arquivoOrigem == NULL) {
		return -1;
	}

	// escreve o arquivo de destino
	arquivoDestino = fopen(argv[2], "wb");
	if (arquivoDestino == NULL){
		fclose(arquivoOrigem);
		return -1; 
	}

	// pega o tamanho do arquivo
	fseek (arquivoOrigem, 0, SEEK_END); // vai pro fim do arquivo
	tamanhoOrigem = ftell(arquivoOrigem); // pega a posicao atual do ponteiro
	rewind(arquivoOrigem); // retorna pro comeco do arquivo

	// aloca memoria pro conteudo do arquivo de origem
	bufferDestino = malloc(sizeof(char) * tamanhoOrigem);
	if(bufferDestino == NULL){
		fclose(arquivoOrigem);
		fclose(arquivoDestino);
		return -1;
	}
	
	// copia o conteudo do arquivo pro buffer
	if(fread(bufferDestino, sizeof(char), tamanhoOrigem, arquivoOrigem) != tamanhoOrigem){
		return -1; // erro no numero de elementos lidos
	}

	// joga o conteudo do buffer para o arquivo de destino
	fwrite(bufferDestino, sizeof(char), tamanhoOrigem, arquivoDestino);
	
	// libera a memoria e os arquivos
	free(bufferDestino);
	fclose(arquivoDestino);
	fclose(arquivoOrigem);

	return 0;
}
