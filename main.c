/*
 * Programa en C para ver si un String es capicua
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

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

int esCapicua(const char* cadena){
    if (strlen(cadena) == 0){
        return 0;
    }
    char minuscula[strlen(cadena) + 1];
    memset(minuscula, 0, sizeof(minuscula));
     /**Convierto a minuscula**/
    for (int i = 0; i < strlen(cadena) ; ++i){
        minuscula[i] = tolower(cadena[i]);
    }
    char* inversa = invertir(minuscula, strlen(cadena));
    if (!inversa){
        free(inversa);
        return -1;//Error de calloc
    }
    if (strcmp(minuscula, inversa) == 0){
        free(inversa);
        return 1;
    }
    free(inversa);
    return 0;
}

int main(int argc, char* argv[])
{
     int buffer_size = 256;
     FILE *input_file = NULL;
     FILE *output_file = NULL;
     bool entradaPorArch = false;
     bool salidaPorArch = false;
     bool commandEntered = false;
     bool validCommand = false;
     bool abort = false;
     for (int i = 1; i < argc; ++i){
        if (((!strcmp(argv[i],"-V"))) || ((!strcmp(argv[i],"--version")))){
            printf("TP0 Organizacion de Computadoras version \"1.0.0\"\
                   \n\nIntegrantes:\n Fabrizio Cozza\n Santiago Pinto\n Luciano Giannotti\n");
            return 0;
        }
        if (((!strcmp(argv[i],"-h"))) || ((!strcmp(argv[i],"--help")))){
            printf("\
Usage:\n\
  tp0 -h\n\
  tp0 -V\n\
  tp0 [options]\n\
Options:\n\
  -V, --version     Print version and quit.\n\
  -h, --help        Print this information.\n\
  -i, --input       Location of the input file.\n\
  -o, --output      Location of the output file.\n\
Examples:\n\
  tp0 -i ~/input -o ~/output\n");
            return 0;
        }
        if (!strcmp(argv[i], "-i") || !strcmp(argv[i], "--input")){
            entradaPorArch = true;
            validCommand = true;
            input_file = fopen(argv[i+1],"r");
        }
        if (!strcmp(argv[i], "-o") || !strcmp(argv[i], "--output")){
            if(!argv[i+1]){
                printf("%s", "Error: Output file must have a name\n");
                return 0;
            }
            if (strcmp(argv[i+1], "-")){
                /**Podria ocurrir que ./tp0 -o -  , lo cual tambien implica que se usa stdout**/
                salidaPorArch = true;
                validCommand = true;
                output_file = fopen(argv[i+1],"w");
                if (!output_file){
                    abort = true;
                    if (fclose(input_file) == EOF){
                        abort = true;
                    }
                }
            }
        }
        commandEntered = true;
     }
    /****/
    int index_palabra=0;
    int i=0;

    char * buffer = (char*)calloc(buffer_size,sizeof(char));
    char * input_string = (char*)calloc(buffer_size,sizeof(char));
    int letra = ' ';

    if (!input_file){
        if (!commandEntered){
            fgets(input_string, buffer_size, stdin);
            letra = input_string[i];
        } else {
            if(validCommand){
                printf("%s\n","Error: Input file does not exist");
            } else {
                printf("%s\n","Error: Command does not exist, enter tp0 -h to see available commands");
            }
            free(input_string);
            free(buffer);
            return 0;
        }
    }

    if (entradaPorArch){
        letra = fgetc(input_file);
    }

    while ((entradaPorArch && letra!=EOF && !abort) ||
            (!entradaPorArch && i<strlen(input_string)+1)) {
        if(isdigit(letra) || (tolower(letra)>='a' && tolower(letra)<='z')){
            buffer[index_palabra]=letra;
            index_palabra++;
            if (index_palabra >= buffer_size) {
                char *new_buffer;
                buffer_size *= 2; // try a buffer that's twice as big as before
                new_buffer = realloc(buffer, buffer_size);
                if (new_buffer == NULL) {
                    free(buffer);
                    /* Abort - out of memory */
                }
                buffer = new_buffer;
            }
        }
        else
        {
			if(esCapicua(buffer) == 1){
                if (salidaPorArch){
                    fprintf(output_file,"%s\n",buffer);
                }
                else{
                    printf("%s\n",buffer);
                }
			} else if (esCapicua(buffer) == -1){
                entradaPorArch = false;
                fclose(input_file);
			}


            index_palabra = 0;
            memset(buffer, 0, strlen(buffer));
        }

        if (entradaPorArch){
            letra = fgetc(input_file);
        }
        else{
            i = i+1;
            letra = input_string[i];
        }
    }

    free(input_string);
    free(buffer); /**libero ultimo buffer**/

    if (entradaPorArch){
        if (fclose(input_file) == EOF){
            abort = true;
        }
    }

    if (salidaPorArch){
        if (fclose(output_file) == EOF){
           abort = true;
        }
    }
    if (abort){
        return -1;
    }
    return 0;
}
