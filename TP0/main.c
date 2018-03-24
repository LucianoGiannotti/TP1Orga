#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_WIDTH_RES 640;
#define DEFAULT_HEIGHT_RES 480;
#define DEFAULT_REALIMAGINARY 0;
#define DEFAULT_WIDTH_HEIGHT 2;
#define DEFAULT_REALSEED -0.726895347709114071439;
#define DEFAULT_IMAGINARYSEED 0.188887129043845954792;

int main(int argc, char* argv[])
{
    int resWidth;
    int resHeight;
    double realPart;
    double imaginaryPart;
    int width;
    int height;
    double realSeed;
    double imaginarySeed;

    resWidth = DEFAULT_WIDTH_RES;
    resHeight = DEFAULT_HEIGHT_RES;
    realPart = DEFAULT_REALIMAGINARY;
    imaginaryPart = DEFAULT_REALIMAGINARY;
    width = DEFAULT_WIDTH_HEIGHT;
    height = DEFAULT_WIDTH_HEIGHT;
    realSeed = DEFAULT_REALSEED;
    imaginarySeed = DEFAULT_IMAGINARYSEED;

    for (int i = 1; i < argc; ++i){
        if (((!strcmp(argv[i],"-V")))
            || ((!strcmp(argv[i],"--version")))){
            printf("TP0 Organizacion de Computadoras version \"1.0.0\"\
                   \n\nIntegrantes:\n Fabrizio Cozza\n Kevin Kajachuán\n Luciano Giannotti\n");
            return 0;
        }
        if (((!strcmp(argv[i],"-h"))) || ((!strcmp(argv[i],"--help")))){
            printf("\
Uso:\n\
  tp0 -h\n\
  tp0 -V\n\
  tp0 [options]\n\
Opciones:\n\
  -V, --version     Version del programa.\n\
  -h, --help        Informacion acerca de los comandos.\n\
  -r, --resolution  Cambiar resolucion de la imagen.\n\
  -c, --center      Coordenadas correspondientes al punto central.\n\
  -w, --width       Especifica el ancho de la región del plano complejo por dibujar.\n\
  -H, --height      Especifica el alto de la región del plano complejo por dibujar.\n\
  -s, --seed        Configurar el valor complejo de la semilla usada para generar el fractal.\n\
  -o, --output      Colocar la imagen de salida.\n\
Ejemplos:\n\
  tp0 -o uno.pgm\n");
            return 0;
        }

        if (!strcmp(argv[i], "-r") ||
            !strcmp(argv[i], "--resolution")){
                if(!argv[i+1]){
                    printf("Error: valor de ancho resolucion ingresado no valido\n");
                    return 0;
                } else {
                    resWidth = atoi(argv[i+1]);
                }

                if(!argv[i+2]){
                    printf("Error: valor de altura resolucion ingresado no valido\n");
                    return 0;
                } else {
                    resHeight = atoi(argv[i+2]);
                }
        }

        if (!strcmp(argv[i], "-C") ||
            !strcmp(argv[i], "--center")){
                if(!argv[i+1]){
                    printf("Error: valor de parte real de centro ingresado no valido\n");
                    return 0;
                } else {
                    realPart = atof(argv[i+1]);
                }

                if(!argv[i+2]){
                    printf("Error: valor de parte imaginaria de centro ingresada no valido\n");
                    return 0;
                } else {
                    imaginaryPart = atof(argv[i+2]);
                }


        }

        if (!strcmp(argv[i], "-w") ||
            !strcmp(argv[i], "--width")){
                if(!argv[i+1]){
                    printf("Error: valor de ancho ingresado no valido\n");
                    return 0;
                } else {
                    width = atoi(argv[i+1]);
                }
        }

        if (!strcmp(argv[i], "-H") ||
            !strcmp(argv[i], "--height")){
                if(!argv[i+1]){
                    printf("Error: valor de altura ingresado no valido\n");
                    return 0;
                } else {
                    height = atoi(argv[i+1]);
                }
        }

        if (!strcmp(argv[i], "-s") ||
            !strcmp(argv[i], "--seed")){
                if(!argv[i+1]){
                    printf("Error: valor de parte real de seed ingresado no valido\n");
                    return 0;
                } else {
                    realSeed = atof(argv[i+1]);
                }

                if(!argv[i+2]){
                    printf("Error: valor de parte imaginaria de seed ingresado no valido\n");
                    return 0;
                } else {
                    imaginarySeed = atof(argv[i+2]);
                }
        }

        if (!strcmp(argv[i], "-o") ||
            !strcmp(argv[i], "--output")){

            /**CASO DE COUT**/
            if (strcmp(argv[i+1], "-")){
            }
        }
     }
        printf("%lf",realPart);
        printf("\n");
        printf("%lf",imaginaryPart);
        printf("\n");
        printf("%lf",realSeed);
        printf("\n");
        printf("%lf",imaginarySeed);
        printf("\n");
        printf("%i",resHeight);
        printf("\n");
        printf("%i",resWidth);
        printf("\n");
        printf("%i",width);
        printf("\n");
        printf("%i",height);
        printf("\n");
    return 0;
}
