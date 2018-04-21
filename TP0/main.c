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

complex addComplexNumbers(complex a,complex b){
	complex c;
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	return c;
}

complex sqrComplex(complex a){
	complex c;
	c.x = a.x*a.x - a.y*a.y;
	c.y = 2*a.x*a.y;
	return c;
}

double absComplex(complex a){
	return sqrt(a.x*a.x + a.y*a.y);
}

int processImage(int resW, int resH,
                 complex pPos, complex seed,
                 double w, double h,
                 FILE* im, int N){

	int x,y,i;
  complex z0,z1;

	fprintf(im, "P2 \n");
  fprintf(im, "%d %d \n",resW,resH);
  fprintf(im, "%d \n", N);

  for(y=0;y<resH;y++){
  	for(x=0;x<resW;x++){
			// Valor z segun posicion del pixel
      z1.x=pPos.x-w/2+w/(double)resW/2+w/(double)resW*x;
      z1.y=pPos.y+h/2-h/(double)resH/2-h/(double)resH*y;
      z0.x = 0;
      z0.y = 0;
      for(i=0;i<N-1;i++){
				z0 = addComplexNumbers(sqrComplex(z1),seed);
        z1=z0;
        if (absComplex(z0) > 2.0){
        	break;
        }
        i++;
    	}
      //agregar al buffer el brillo
      fprintf(im, "%3d ", i);
    }
		fprintf(im, "\n");
	}

	/* close the file */
	return fclose(im);
}


int main(int argc, char* argv[]){
	int exitCode = 0;
	int pasoN = 500;

  int resWidth;
  int resHeight;
  complex pixelPos;
  double width;
  double height;
  complex seed;
	FILE* image = stdout;

  const char* delRes = "x";
	const char* delimitator = "+-i";
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
  	if (((!strcmp(argv[i],"-V"))) || ((!strcmp(argv[i],"--version")))){
    	printf("TP0 Organizacion de Computadoras version \"1.0.0\"\
              \n\nIntegrantes:\n Fabrizio Cozza\n Kevin Cajachuán\n Luciano Giannotti\n");
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
  -w, --width       Especifica el ancho de la region del plano complejo por dibujar.\n\
  -H, --height      Especifica el alto de la region del plano complejo por dibujar.\n\
  -s, --seed        Configurar el valor complejo de la semilla usada para generar el fractal.\n\
  -o, --output      Colocar la imagen de salida.\n\
Ejemplos:\n\
  tp0 -o uno.pgm\n");
      return 0;
		}

    if (!strcmp(argv[i], "-r") || !strcmp(argv[i], "--resolution")){
			if(!argv[i+1]){
      	printf("Error: valor de resolucion ingresado no valido\n");
      	return -1;
      } else {
        pSeparator = strtok(argv[i+1],delRes);
        if(pSeparator != NULL){
        	resWidth = atof(pSeparator);
          if(resWidth <= 0){
          	exitCode = -2;
          }
        } else {
        	exitCode = -1;
        }

				pSeparator = strtok (NULL,delRes);
				if(pSeparator != NULL){
        	resHeight = atof(pSeparator);
          if(resHeight <= 0){
          	exitCode = -2;
          }
      	} else {
      		exitCode = -1;
        }

			}
		}

		if (!strcmp(argv[i], "-c") || !strcmp(argv[i], "--center")){
			if(!argv[i+1]){
				printf("Error: valor de centro ingresado no valido\n");
        return -1;
      } else {
        char *copy = strdup(argv[i+1]);
        if(copy == NULL){
        	exitCode = -1;
        }
				int sign = 1;
				if(copy[0] == '-') sign = -1;

        pSeparator = strtok(argv[i+1],delimitator);
        if(pSeparator != NULL){
        	pixelPos.x = sign * atof(pSeparator);
					int len = strlen(pSeparator);
					if(sign == -1) sign = copy[len + 1] == '-' ? -1 : 1;
					else sign = copy[len] == '-' ? -1 : 1;
      	} else {
          exitCode = -1;
        }

        pSeparator = strtok (NULL,delimitator);
      	if(pSeparator != NULL){
        	pixelPos.y = sign * atof(pSeparator);
        } else {
          exitCode = -1;
        }
				free(copy);
  		}
		}

		if (!strcmp(argv[i], "-w") || !strcmp(argv[i], "--width")){
			if(!argv[i+1]){
				printf("Error: valor de ancho ingresado no valido\n");
				return -1;
			} else {
				width = atof(argv[i+1]);
			}
		}

		if (!strcmp(argv[i], "-H") || !strcmp(argv[i], "--height")){
			if(!argv[i+1]){
				printf("Error: valor de altura ingresado no valido\n");
				return -1;
			} else {
				height = atof(argv[i+1]);
			}
		}

		if (!strcmp(argv[i], "-s") || !strcmp(argv[i], "--seed")){
			if(!argv[i+1]){
				printf("Error: valor de seed ingresado no valido\n");
				return -1;
			} else {
				char *copy = strdup(argv[i+1]);
				if(copy == NULL){
					exitCode = -1;
				}
				int sign = 1;
				if(copy[0] == '-') sign = -1;

				pSeparator = strtok(argv[i+1],delimitator);
				if(pSeparator != NULL){
					seed.x = sign * atof(pSeparator);
					int len = strlen(pSeparator);
					if(sign == -1) sign = copy[len + 1] == '-' ? -1 : 1;
					else sign = copy[len] == '-' ? -1 : 1;
				} else {
					exitCode = -1;
				}

				pSeparator = strtok (NULL,delimitator);
				if(pSeparator != NULL){
  				seed.y = sign * atof(pSeparator);
				} else {
  				exitCode = -1;
				}
				free(copy);
			}
		}

		if (!strcmp(argv[i], "-o") || !strcmp(argv[i], "--output")){
			/* open output file */
			if (!strcmp(argv[i+1], "-")){
				continue;
			}
			else {
				image = fopen(argv[i+1], "w");
				if (image == NULL) {
					fprintf(stderr, "No se puede abrir el archivo file %s!\n", argv[i+1]);
					return -1;
				}
			}
		}
	}

	if(exitCode == 0) {
		exitCode = processImage(resWidth,resHeight,pixelPos,seed,width,height,image,pasoN);
	}

	switch (exitCode){
		case 0:
			return exitCode;
			break;
		case -1:
			fprintf(stderr, "La imagen no se pudo procesar, por favor revise los valores ingresados\n");
			return exitCode;
			break;
		case -2:
			fprintf(stderr, "Valores ingresados de resolucion invalidos\n");
			return exitCode;
			break;
	}
	return 0;
}
