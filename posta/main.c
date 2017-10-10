#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <setjmp.h>
#include <sys/types.h>
#include "palindrome.h"
#include "mymalloc.h"

#define TRY do{ jmp_buf ex_buf__; switch( setjmp(ex_buf__) ){ case 0:
#define CATCH(x) break; case x:
#define ETRY } }while(0)
#define THROW(x) longjmp(ex_buf__, x)
#define ERROR_IN_PROGRAM_EXCEPTION (1)

int main(int argc, char* argv[])
{
    int input_buffer_size = 1; //default value
    int output_buffer_size = 1; //default value
     
    FILE *input_file = NULL;
    FILE *output_file = NULL;
     
    bool inputByFile = false;
    bool outputByFile = false;
    int i;
    TRY
    {
        for (i = 1; i < argc; ++i){

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
                inputByFile = true;
                input_file = fopen(argv[i+1],"r");

                if (!input_file){
                    THROW( ERROR_IN_PROGRAM_EXCEPTION );
                }
            }

            if (!strcmp(argv[i], "-I") || !strcmp(argv[i], "--ibuf-bytes")){
                int ibufsize = atoi(argv[i+1]);
                if(ibufsize != 0){
                    input_buffer_size = ibufsize;
                }
                else 
                {
                    THROW (ERROR_IN_PROGRAM_EXCEPTION);
                }
            }

            if (!strcmp(argv[i], "-o") || !strcmp(argv[i], "--output")){
                if (strcmp(argv[i+1], "-")){
                    /**Podria ocurrir que ./tp0 -o -, 
                     * lo cual tambien implica que se usa stdout**/
                    outputByFile = true;
                    output_file = fopen(argv[i+1],"w");
                    if (!output_file){
                        THROW( ERROR_IN_PROGRAM_EXCEPTION );
                    }
                }
            }

            if (!strcmp(argv[i], "-O") || !strcmp(argv[i], "--obuf-bytes")){
                int obufsize = atoi(argv[i+1]);
                if(obufsize != 0){
                    output_buffer_size = obufsize;
                } 
                else 
                {
                    THROW (ERROR_IN_PROGRAM_EXCEPTION);
                }
            }
        }
        
        if(inputByFile){
            int ifd;
            ifd = fileno(input_file);
            if(ifd == -1){
                THROW (ERROR_IN_PROGRAM_EXCEPTION);
            }
            
            int ofd;
            ofd = fileno(output_file);
            
            if(ofd == -1){
                THROW (ERROR_IN_PROGRAM_EXCEPTION);
            }
            
            palindrome(ifd, input_buffer_size, 
                        ofd, output_buffer_size);
        } else {
            int fdin;
            fdin = fileno(stdin);
            if(fdin == -1){
                THROW (ERROR_IN_PROGRAM_EXCEPTION);
            }
            
            if (outputByFile){
                int ofd;
                ofd = fileno(output_file);

                if(ofd == -1){
                    THROW (ERROR_IN_PROGRAM_EXCEPTION);
                }
                palindrome(fdin, input_buffer_size, 
                            ofd, output_buffer_size);
            } else {
                int fdout;
                fdout = fileno(stdout);

                if(fdout == -1){
                    THROW (ERROR_IN_PROGRAM_EXCEPTION);
                }
                palindrome(fdin, input_buffer_size, 
                            fdout, output_buffer_size);
            }
        }
        
        if (inputByFile){
            THROW  (ERROR_IN_PROGRAM_EXCEPTION);
        }

        if (outputByFile){
            THROW  (ERROR_IN_PROGRAM_EXCEPTION);
        }
    }
    CATCH(ERROR_IN_PROGRAM_EXCEPTION)
    {
        if (fclose(input_file) == EOF){
          return -1;
        }
        
        if (fclose(output_file) == EOF){
          return -1;
        }
    }
    ETRY;
    
    return 0;
}
