#include <stdio.h>
#include <fcntl.h>

#define buf_size 1024

int main (int argc, char* argv[])
{	
	// --- declaração de variáveis --- //
	int fp, fq; 
	ssize_t bytesLidos, bytesEscritos; 
	char buffer [buf_size]; 
	
	// --- permissões para o arquivo --- //
	mode_t mode = S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IROTH | S_IXOTH;
	
	// --- abre o arquivo original --- // 
	fp = open (argv[1], O_RDONLY); 
	if (fp == -1) 
	{
		perror ("O arquivo não pôde ser aberto no mode leitura");  
		return 1; 
	}
	
	// --- abre o arquivo cópia --- //
	fq = open(argv[2], O_WRONLY | O_EXCL | O_CREAT, mode); 
	if (fq == -1)
	{
		perror ("o arquivo não pôde ser aberto no mode escrita");
		return 2; 
	}
	
	while ((bytesLidos = read (fp, &buffer, buf_size)) > 0)
	{
		bytesEscritos = write (fq, &buffer, (ssize_t) bytesLidos); 
	}
	
	close (fp);
	close (fq);
	return 0; 
	
}//final main
