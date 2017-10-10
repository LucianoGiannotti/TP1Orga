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

void putch2(char src, char* dest,int indice){
	dest[indice]=src;
}
/**Funcion de mips a la cual le cedo el control**/
//extern void palindrome(int ifd, size_t ibytes, int ofd, size_t obytes);


char* initBufferInterno(size_t size){
	char* buffer = (char*)mymalloc(size);
	memset(buffer, size,0);
	return (buffer);
}

/**Funcion de mips a la cual le cedo el control**/
void palindrome(int ifd, size_t ibytes, int ofd, size_t obytes){
	int indice = 0;
	int i1 = 0;
	//Cargo el buffer de entrada
	char* ibuffer = (char*)mymalloc(ibytes);
	char* obuffer = (char*)mymalloc(obytes);
	char a = 1;
	char* buff_interno = initBufferInterno(ibytes);
	while (read(ifd, ibuffer, ibytes) > 0){
		while (indice < ibytes){
			a = getch(ibuffer,indice);
			//TODO: chequear que el caracter no sea separador
			putch2(a,buff_interno,i1);
			i1++;
			//char* buff_interno = /*REFERENCIA A*/initBufferInterno(ibytes);
			//if (palabraCapicua(buff_interno) == 1){
			   //llenarbuffext
			//}
			++indice;
		}
		
		indice = 0;
	}
	i1=0;
	while (indice < ibytes){
		a = getch(buff_interno,i1);
		putch2(a,obuffer,indice);
		indice++;
		i1++;
	}
	write(ofd,obuffer,obytes);
	//write(ofd, &a, sizeof(char));
	myfree(ibuffer);
	myfree(obuffer);
}
/*
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

int palabraCapicua(const char** cadena){
    int indice = 0;
    return llenarBufferInternoYVerificarCapicua(getch(*cadena,indice),cadena);
}
*/
/*
int llenarBufferInternoYVerificarCapicua(char caracter, char** buffer_interno){
     if (strlen(*buffer_interno) == sizeof(*buffer_interno)){
	/**Version casera del realloc**/
	/*char* nuevo_buffer = (char*)mymalloc(sizeof(*buffer_interno)*2);
	memset(nuevo_buffer,0, sizeof(nuevo_buffer));
	strncpy(nuevo_buffer, *buffer_interno, sizeof(*buffer_interno));
	myfree(buffer_interno);
	buffer_interno = &nuevo_buffer;
     }	     
     if (caracter == '\0'){
	if(esCapicua(*buffer_interno) == 1) {
	    return 1;
	}
     } else {
	*buffer_interno[strlen(*buffer_interno)] = caracter;
     }
     return 0;
}

int esCapicua(const char* cadena){
    if (strlen(cadena) == 0){
        return 0;
    }

    cadena = convertToMinus(cadena);

    char* inversa = invertir(cadena, strlen(cadena));
    if (!inversa){
        free(inversa);
        return -1;//Error de calloc
    }

    if (strcmp(cadena, inversa) == 0){
        free(inversa);
        return 1;
    }

    free(inversa);
    return 0;
}

char* convertToMinus(const char* cadena){
    char minuscula[strlen(cadena) + 1];
    memset(minuscula, 0, sizeof(minuscula));
     /**Convierto a minuscula**/
    /*for (int i = 0; i < strlen(cadena) ; ++i){
        minuscula[i] = tolower(cadena[i]);
    }
    return &minuscula;
}


char* initBufferExterno(size_t size){
	char* buffer = (char*)mymalloc(size);
	memset(buffer, size,0);
}
*/
void llenarBufferExterno(char caracter, char** buffer_externo){

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

