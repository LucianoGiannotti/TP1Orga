#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include "mymalloc.h"

#define INPUT_BUFF_SIZE 9
#define OUTPUT_BUFF_SIZE 9
//extern void putch(char* src, char** dest, size_t indice);
extern char getch(char* src,size_t indice);

void putch(char src, char* dest,int indice){
	dest[indice]=src;
}
/**Funcion de mips a la cual le cedo el control**/
//extern void palindrome(int ifd, size_t ibytes, int ofd, size_t obytes);

char* invertir(const char* cadena, const size_t tamanio){
	unsigned int i;
    char* inverso = (char*)mymalloc((sizeof(char)*tamanio)+1);
    memset(inverso,0,sizeof(inverso));
    if (!inverso){
       return NULL;
    }
    for (i = 1; i < tamanio + 1; ++i){
         strncat(inverso,cadena + (tamanio-i), 1);
    }
    return inverso;
}



int esCapicua(const char* cadena){
	int i;
    if (strlen(cadena) == 0){
        return 0;
    }

    //Convert to minus
    char minuscula[strlen(cadena) + 1];
    memset(minuscula, 0, sizeof(minuscula));
     /**Convierto a minuscula**/

    for (i=0; i < strlen(cadena) ; ++i){
        minuscula[i] = tolower(cadena[i]);
    }

    
    char* inversa = invertir(minuscula, strlen(cadena));
    if (!inversa){
        myfree(inversa);
        return -1;//Error de calloc
    }

    if (strcmp(minuscula, inversa) == 0){
        myfree(inversa);
        return 1;
    }

    myfree(inversa);
    return 0;
}




char* initBufferInterno(size_t size){
	char* buffer = (char*)mymalloc(size*sizeof(char));
	memset(buffer,0,size);
	return (buffer);
}


/**Funcion de mips a la cual le cedo el control**/
void palindrome(int ifd, size_t ibytes, int ofd, size_t obytes){
	int indice = 0;
	int i = 0;
	//Cargo el buffer de entrada
	char* ibuffer = (char*)mymalloc(ibytes);
	char* obuffer = (char*)mymalloc(obytes);
	char caracter = 1;
	char* buff_interno = initBufferInterno(ibytes);
	char* nuevo_buffer;
	while (read(ifd, ibuffer, ibytes) > 0){
		while (indice < ibytes){
			caracter = getch(ibuffer,indice);
			//chequear que el buff interno no este lleno

			if (strlen(buff_interno) == sizeof(buff_interno)){
				/**Version casera del realloc**/
				size_t nuevo_size;
				nuevo_size = sizeof(buff_interno)*4;
				nuevo_buffer = (char*)mymalloc(nuevo_size);
				memset(nuevo_buffer,0, nuevo_size);
				strncpy(nuevo_buffer,buff_interno, strlen(buff_interno));
				//memcpy(nuevo_buffer,buff_interno, sizeof(buff_interno));
				
				//printf("%d\n",nuevo_size);
				printf("%d\n",strlen(buff_interno));
				//printf("%d\n",strlen(nuevo_buffer));
				myfree(buff_interno);
				
				buff_interno = nuevo_buffer;

			 }
		     if ((caracter == ' ')|| (caracter == ',') || (caracter == ';') || (caracter == '.') || (caracter == '?') || (caracter == '!')){
		     	//putch('\0',buff_interno,strlen(buff_interno));
		     	
		     	printf("\nbuffer interno: ");
		     	printf(buff_interno);
				if(esCapicua(buff_interno) == 1) {
			    	//return 1;
			    	printf("\ncapicua");

			    	//escribo en el obuffer
		    		i=0;
	    			while ((strlen(obuffer) < obytes)&&(i<strlen(buff_interno))){
	    				if (i == obytes){ 
	    					//si el buff interno es mas grande que el buff de salida
	    					//imprimo lo que tengo y reseteo el buff de salida
	    					write(ofd,obuffer,strlen(obuffer));
							write(ofd,"\n",1);
	    					memset(obuffer,0,obytes);
	    				}
						caracter = getch(buff_interno,i);
						putch(caracter,obuffer,strlen(obuffer));
						i++;
					}

					write(ofd,obuffer,strlen(obuffer));
					write(ofd,"\n",1);
					memset(obuffer,0,obytes);
					//indice=0;
					
				}
				else{

				}
				//tirar el buff interno a la mierda
				
				
				myfree(buff_interno);
				buff_interno = initBufferInterno(ibytes);
		     } 
		     else {
		     	putch(caracter,buff_interno,strlen(buff_interno));
				//buffer_interno[strlen(buffer_interno)] = caracter;
		     }
			++indice;
		}
		
		indice = 0;
	}
	i=0;
	/*while (indice < obytes){
		caracter = getch(buff_interno,i);
		putch(caracter,obuffer,indice);
		indice++;
		i++;
	}*/
	//write(ofd,obuffer,obytes);
	//write(ofd, &a, sizeof(char));
	myfree(ibuffer);
	myfree(obuffer);
}



/*

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

