#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "imagelib.h"
#define PER_LINE 16

/*
 * Aloca memoria para uma imagem
 * @param: numero de linhas e numero de colunas
 * @return: alocamento de memoria para uma imagem
*/
image img_alloc(int nr, int nc)
{
    return (image)malloc(nr * nc * sizeof(int));
}

/*
 * Desaloca memoria de uma imagem
 * @param: imagem a ser desaloca
*/
int img_free(image Im)
{
    free(Im);
}

/*
 * Define o nome da imagem de input e output 
 * @param: nome do arquivo da imagem, nome da imagem de input
 * nome da imagem de output e tipo da imagem
*/
void img_name(char *name, char *in, char *out, int tp)
{
    char *ext[3] = {".pbm", ".pgm", ".ppm"};
    char *p = strstr(name, ext[tp - 1]);
    if (p)
        *p = 0;
    sprintf(in, "%s%s", name, ext[tp - 1]);
    sprintf(out, "result.txt");
}

/*
 * Mostra as informacoes da imagem
 * @param: nome da imagem, numero de linhas, numero de colunas
 * nivel de grayscale e tipo da imagem
*/
void img_info(char *name, int nr, int nc, int ml, int tp)
{
    printf("\nImage Informations:");
    printf("\n--------------------------\n");
    printf("Image file name.............: %s \n", name);
    printf("Image type..................: P%d\n", tp);
    printf("Number of rows..............: %d \n", nr);
    printf("Number of columns...........: %d \n", nc);
    printf("Max intensity level.........: %d \n\n", ml);
}

/*
 * Mensagem de erro
 * @param: string de controle
*/
void errormsg(char *str, ...)
{
    char format[255];
    va_list arg;
    va_start(arg, str);
    sprintf(format, "ERROR: %s\n\n", str);
    vprintf(format, arg);
    va_end(arg);
    exit(1);
}

/*
 * Le a imagem pnm ascii
 * @param(input): nome, tipo da imagem
 * @param(out): numero de linhas, numero de colunas, nivel maximo de intensidade
 * @return: vetor da imagem
*/
image img_get(char *name, int *nr, int *nc, int *ml, int tp)
{
    char lines[100];
    image img;
    FILE *fimg;
    ERROR((fimg = fopen(name, "r")) == NULL, errormsg("File open error: <%s>", name));
    /*--- PNM = "P1" or "P2" or "P3" ---*/
    fgets(lines, 80, fimg);
    ERROR((lines[0] != 'P' || (lines[1] != tp + '0')), errormsg("File type image error: <%s>", name));
    /*--- Comment lines ---*/
    fgets(lines, 80, fimg);
    while (strchr(lines, '#'))
        fgets(lines, 80, fimg);
    sscanf(lines, "%d %d", nc, nr);
    if (tp != BW)
        fscanf(fimg, "%d", ml);
    else
        *ml = 1;
    ERROR(*nc == 0 || *nr == 0 || *ml == 0, errormsg("Image dimensions error: <%s>", name));
    img = img_alloc(*nr, *nc);
    ERROR(!img, errormsg("Image allocation error: %s\n\n img_get routine", name));
    for (int i = 0; i < (*nr) * (*nc); i++)
        if (tp != COLOR)
        {
            int k;
            fscanf(fimg, "%d", &k);
            ERROR(k > *ml, errormsg("Max pixel intensity in the image error: <%s>", name));
            img[i] = k;
        }
        else
        {
            int r, g, b;
            fscanf(fimg, "%d %d %d", &r, &g, &b);
            ERROR(r > *ml || r < 0 || g > *ml || g < 0 || b > *ml || b < 0,
                  errormsg("Max intensity of color in the image error: <%s>", name));
            img[i] = (r << 16) + (g << 8) + b;
        }
    fclose(fimg);
    img_info(name, *nr, *nc, *ml, tp);
    return img;
}

/*
 * Escreve a imagem pnm
 * @param: imagem, nome da imagem, numero de linhas, numero de colunas, nivel maximo de intensidade e tipo de imagem
*/
void img_put(image img, char *name, int nr, int nc, int ml, int tp)
{
    int count;
    FILE *fimg;
    ERROR((fimg = fopen(name, "wt")) == NULL, errormsg("Image creation error: <%s>", name));
    count = 0;
    for (int i = 0; i < nr * nc; i++)
    {
        if (tp != COLOR)
        {
            int x = img[i];
            fprintf(fimg, "%c", x);
        }
        else
        {
            int r = (img[i] >> 16) & 0xFF;
            int g = (img[i] >> 8) & 0xFF;
            int b = img[i] & 0xFF;
            fprintf(fimg, "%3d %3d %3d ", r, g, b);
        }
        count++;
        if (count >= nc)
        {
            fprintf(fimg, "\n");
            count = 0;
        }
    }
    fclose(fimg);
}

