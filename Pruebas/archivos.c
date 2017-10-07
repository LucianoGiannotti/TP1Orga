#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include "mymalloc.h"

#define INPUT_BUFF_SIZE 10
#define OUTPUT_BUFF_SIZE 5
extern void getch(char* src, char** dest, size_t indice);

/**Funcion de mips a la cual le cedo el control**/
void palindrome(int ifd, size_t ibytes, int ofd, size_t obytes){
	unsigned int indice = 1;
	//Cargo el buffer de entrada
	char* buffer = (char*)mymalloc(ibytes);
	read(ifd,buffer,ibytes);
	//Paso 1 byte a un buffer interno
	char* buffer_interno = (char*)mymalloc(20);
	//pasa un byte desde buffer a buffer_interno
	getch(buffer, &buffer_interno, indice);
	++indice;
	write(ofd,buffer_interno,1);
}

int main(int argc, char* argv[]){
	//Abro el file y obtengo su fd
	FILE* archivo = fopen("prueba.txt","r+");
	FILE* output = fopen("output.txt","w+");
	int fdi = fileno(archivo);
	int fdo = fileno(output);
	//palindrome por ahora simplemente lee INPUT_BUFF_SIZE caracteres del archivo de entrad
	//prueba.txt, los carga en un buffer, y hace un llamado a una funcion getch que carga
	//en un buffer interno de a 1 byte
	palindrome(fdi,INPUT_BUFF_SIZE,fdo,OUTPUT_BUFF_SIZE);
	//Al finalizar cierro los archivos
	fclose(archivo);
	fclose(output);
	return 0;
}

