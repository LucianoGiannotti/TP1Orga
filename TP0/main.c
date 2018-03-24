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
    double resWidth;
    double resHeight;
    double realPart;
    double imaginaryPart;
    double width;
    double height;
    double realSeed;
    double imaginarySeed;
    const char delimitator[4] = "x+-i";
    char *pSeparator;

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
                    pSeparator = strtok(argv[i+1],delimitator);
                    resWidth = atof(pSeparator);
                    pSeparator = strtok (NULL,delimitator);
                    resHeight = atof(pSeparator);
                }
        }

        if (!strcmp(argv[i], "-C") ||
            !strcmp(argv[i], "--center")){
                if(!argv[i+1]){
                    printf("Error: valor de centro ingresado no valido\n");
                    return 0;
                } else {
                    pSeparator = strtok(argv[i+1],delimitator);
                    realPart = atof(pSeparator);
                    pSeparator = strtok (NULL,delimitator);
                    imaginaryPart = atof(pSeparator);
                }
        }

        if (!strcmp(argv[i], "-w") ||
            !strcmp(argv[i], "--width")){
                if(!argv[i+1]){
                    printf("Error: valor de ancho ingresado no valido\n");
                    return 0;
                } else {
                    width = atof(argv[i+1]);
                }
        }

        if (!strcmp(argv[i], "-H") ||
            !strcmp(argv[i], "--height")){
                if(!argv[i+1]){
                    printf("Error: valor de altura ingresado no valido\n");
                    return 0;
                } else {
                    height = atof(argv[i+1]);
                }
        }

        if (!strcmp(argv[i], "-s") ||
            !strcmp(argv[i], "--seed")){
                if(!argv[i+1]){
                    printf("Error: valor de seed ingresado no valido\n");
                    return 0;
                } else {
                    pSeparator = strtok(argv[i+1],delimitator);
                    realSeed = atof(pSeparator);
                    pSeparator = strtok (NULL,delimitator);
                    imaginarySeed = atof(pSeparator);
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
        printf("%lf",resHeight);
        printf("\n");
        printf("%lf",resWidth);
        printf("\n");
        printf("%lf",width);
        printf("\n");
        printf("%lf",height);
        printf("\n");
    return 0;
}
