#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define DEFAULT_WIDTH_RES 640;
#define DEFAULT_HEIGHT_RES 480;
#define DEFAULT_REALIMAGINARY 0;
#define DEFAULT_WIDTH_HEIGHT 2;
#define DEFAULT_REALSEED -0.726895347709114071439;
#define DEFAULT_IMAGINARYSEED 0.188887129043845954792;

typedef struct{
	double x,y;
}complex;


complex add(complex a,complex b){
	complex c;
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	return c;
}

complex sqr(complex a){
	complex c;
	c.x = a.x*a.x - a.y*a.y;
	c.y = 2*a.x*a.y;
	return c;
}

double mod(complex a){
	return sqrt(a.x*a.x + a.y*a.y);
}

int processImage(double resW, double resH,
                 complex pPos, complex seed,
                 double w, double h,
                 FILE* im,int N){

    /* allocate memory for data */
   char *buff = (char *) malloc (resW*resH*sizeof(char));

    complex z0,z1;
    z0 = pPos;
    z1 = pPos;

    for(int y=0;y<resH;y++){
        for(int x=0;x<resW;x++){
            for(int i=0;i<N-1;i++){
                if (mod(z1) > 2){
                        return 0;
                }
                z1 = add(sqr(z0),seed);
				z0 = z1;
            }
            /* añadir al buffer */
        }
    }


    /* write the header */
    fprintf(im, "P5\n%u %u 255\n", resW, resH);

    /* write the array */
    fwrite(buff, 1, resW*resH*sizeof(char), im);

    /* free memory */
    free(buff);

    return 0;
}


int main(int argc, char* argv[])
{
    double resWidth;
    double resHeight;
    complex pixelPos;
    double width;
    double height;
    complex seed;

    const char delimitator[4] = "x+-i";
    char *pSeparator;

    resWidth = DEFAULT_WIDTH_RES;
    resHeight = DEFAULT_HEIGHT_RES;
    pixelPos.x = DEFAULT_REALIMAGINARY;
    pixelPos.y = DEFAULT_REALIMAGINARY;
    width = DEFAULT_WIDTH_HEIGHT;
    height = DEFAULT_WIDTH_HEIGHT;
    seed.x = DEFAULT_REALSEED;
    seed.y = DEFAULT_IMAGINARYSEED;

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
                    printf("Error: valor de resolucion ingresado no valido\n");
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
                    pixelPos.x = atof(pSeparator);
                    pSeparator = strtok (NULL,delimitator);
                    pixelPos.y = atof(pSeparator);
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
                    seed.x = atof(pSeparator);
                    pSeparator = strtok (NULL,delimitator);
                    seed.y = atof(pSeparator);
                }
        }

        if (!strcmp(argv[i], "-o") ||
            !strcmp(argv[i], "--output")){

               /* open output file */
               FILE* image = fopen(argv[1], "wb");
               if (image == NULL)
               {
                  fprintf(stderr, "Can't open output file %s!\n", argv[1]);
                  exit(1);
               }

            /**CASO DE COUT**/
            if (strcmp(argv[i+1], "-")){
            }
            processImage(resWidth,resHeight,pixelPos,seed,width,height,image,100/*PASO*/);
        }

     }



    return 0;
}
