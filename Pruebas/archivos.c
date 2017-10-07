#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include "mymalloc.h"

#define BUFF_SIZE 10
/**Funcion de mips a la cual le cedo el control**/
extern void mips_foo(int fdi, int fdo,size_t buff_size);

int main(int argc, char* argv[]){
	//Abro el file y obtengo su fd
	FILE* archivo = fopen("prueba.txt","r+");
	FILE* output = fopen("output.txt","w+");
	int fdi = fileno(archivo);
	int fdo = fileno(output);
	//Le cedo el control a mips, esta funcion simplemente lee BUFF_SIZE caracteres
	//del archivo cuyo file descriptor es fdi, los coloca en un buffer y escribe sobre un 
	//archivo de salida output.txt
	mips_foo(fdi,fdo,BUFF_SIZE);
	
	//Al finalizar cierro los archivos
	fclose(archivo);
	fclose(output);
	return 0;
}
