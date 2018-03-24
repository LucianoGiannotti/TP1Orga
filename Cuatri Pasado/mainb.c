#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <setjmp.h>

#define TRY do{ jmp_buf ex_buf__; switch( setjmp(ex_buf__) ){ case 0:
#define CATCH(x) break; case x:
#define ETRY } }while(0)
#define THROW(x) longjmp(ex_buf__, x)
#define ERROR_IN_PROGRAM_EXCEPTION (1)

int main(int argc, char* argv[])
{
    int input_buffer_size = 1;
    int output_buffer_size = 1;
     
    FILE *input_file = NULL;
    FILE *output_file = NULL;
     
    bool inputByFile = false;
    bool outputByFile = false;
     
    //bool commandEntered = false;
    //bool validCommand = false;
     
    //bool abort = false;
    
    TRY
    {
        for (int i = 1; i < argc; ++i){

           if (((!strcmp(argv[i],"-V"))) || ((!strcmp(argv[i],"--version")))){
               printf("TP1 Organizacion de Computadoras version \"1.0.0\"\
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
      -I, --ibuf-bytes  Byte-count of the input buffer.\n\
      -O, --obuf-bytes  Byte-count of the output buffer.\n\
    Examples:\n\
      tp0 -i ~/input -o ~/output\n");
                return 0;
            }

            if (!strcmp(argv[i], "-i") || !strcmp(argv[i], "--input")){
                if(!argv[i+1]){
                    //TODO locacion by default / crear un documento?
                    //return -1;
                }

                if (!strcmp(argv[i+1], "-")){
                    /**Podria ocurrir que ./tp0 -i -, lo cual tambien implica que se usa stdin**/
                    inputByFile = true;
                    //validCommand = true;

                    char * fileLocation = (char*)calloc(256,sizeof(char));
                    printf("%s\n","Por favor, ingrese ubicacion del archivo de entrada: ");
                    fgets(fileLocation, 256, stdin);

                    input_file = fopen(fileLocation,"r");

                    if (!input_file){
                        //abort = true;
                        THROW( ERROR_IN_PROGRAM_EXCEPTION );
                        }

                    }
                    else 
                    {
                    inputByFile = true;
                    //validCommand = true;
                    input_file = fopen(argv[i+1],"r");

                    if (!input_file){
                       //abort = true;
                       THROW( ERROR_IN_PROGRAM_EXCEPTION );
                       }
                    } 
            }

            if (!strcmp(argv[i], "-I") || !strcmp(argv[i], "--ibuf-bytes")){
                if(!argv[i+1]){
                    //TODO explota o lo dejo en 1?
                } 
                else
                {
                    //(IF) verificar que sea un numero?
                    input_buffer_size = argv[i+1];
                    //(ELSE) explota o lo dejo en 1?
                }
            }

            if (!strcmp(argv[i], "-o") || !strcmp(argv[i], "--output")){
                if(!argv[i+1]){
                    //TODO locacion by default / crear un documento?
                }

                if (strcmp(argv[i+1], "-")){
                    /**Podria ocurrir que ./tp0 -o -, lo cual tambien implica que se usa stdout**/
                    outputByFile = true;
                    //validCommand = true;
                    output_file = fopen(argv[i+1],"w");
                    if (!output_file){
                        //abort = true;
                        THROW( ERROR_IN_PROGRAM_EXCEPTION );
                        if (fclose(input_file) == EOF){
                            //abort = true;
                            THROW( ERROR_IN_PROGRAM_EXCEPTION );
                        }
                    }
                }
            }

            if (!strcmp(argv[i], "-O") || !strcmp(argv[i], "--obuf-bytes")){
                if(!argv[i+1]){
                    //TODO explota o lo dejo en 1?
                } 
                else
                {
                    //(IF) verificar que sea un numero?
                    output_buffer_size = argv[i+1];
                    //(ELSE) explota o lo dejo en 1?
                }
            }
        }
        
     /*
     *
     * CODIGO DE MIPS32
     * 
     */
        
        if (inputByFile){
           if (fclose(input_file) == EOF){
               //abort true
               return -1;
           }
       }

        if (outputByFile){
            if (fclose(output_file) == EOF){
                //abort true
               return -1;
            }
        }
    }
    CATCH( ERROR_IN_PROGRAM_EXCEPTION)
    {
        //free algo si se necesita
        
        if (fclose(input_file) == EOF){
          return -1;
        }
        
        if (fclose(output_file) == EOF){
          return -1;
        }
    }
    ETRY;
    
    /*
    if (abort){
        return -1;
    }*/
    
    return 0;
}