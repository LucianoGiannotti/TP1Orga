#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include "mymalloc.h"

#define INPUT_BUFF_SIZE 5
#define OUTPUT_BUFF_SIZE 5
extern void putch(char* src, char** dest, size_t indice);
extern char getch(char* src,size_t indice);
/**Funcion de mips a la cual le cedo el control**/
extern void palindrome(int ifd, size_t ibytes, int ofd, size_t obytes);

char* invertir(const char* cadena, const size_t tamanio){
    char* inverso = (char*)calloc(tamanio + 1, sizeof(char));
    if (!inverso){
       return NULL;
    }
    for (unsigned int i = 1; i<tamanio + 1; ++i){
         strncat(inverso,cadena + (tamanio-i), 1);
    }
    return inverso;
}


char* initBufferInterno(size_t size){
	char* buffer = (char*)mymalloc(size);
	memset(buffer, size,0);
}

void llenarBufferInterno(char caracter, char** buffer_interno){
     if (strlen(buffer_interno) == sizeof(buffer_interno)){
	/**Version casera del realloc**/
	char* nuevo_buffer = (char*)mymalloc(sizeof(*buffer_interno)*2);
	memset(nuevo_buffer,0, sizeof(nuevo_buffer));
	strncpy(nuevo_buffer, *buffer_interno, sizeof(*buffer_interno));
	myfree(buffer_interno);
	buffer_interno = &nuevo_buffer;
     }	     
     if (caracter == '\0'){
	/**Se termino la palabra, ya puedo invertirla**/
     } else {
	*buffer_interno[strlen(*buffer_interno)] =  caracter;
     }
     
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

