/**=============================================================
 *          UNIFAL = Universidade Federal de Alfenas
 *      BACHARELADO EM CIÊNCIA DA COMPUTAÇÃO
 * Trabalho...: Imagem ASCII
 * Disciplina.: Processamento de Imagens
 * Professor..: Luiz Eduardo da Silva
 * Aluno......: Barbara Silveira Rodrigues
 * Data.......: 02/05/2022
*===============================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "imagelib.h"


/**
 * Cria a amostra da imagem
 * A logica criada foi, ao inves de usar a media dos pixels, a img e dividida em "subimagens" e vai pegar a proporcao dessas subimagens
 * @param: imagem de entrada e saida, numero de linhas e colunas da imagem de entrada, numero de linhas e colunas da imagem de saida
*/
void img_sampling(image img, image out, int nr, int nc, int height, int width) {
    int pNr, pNc;

    pNr = (int)nr/height;
    pNc = (int)nc/width;

    for(int i = 0, k = 0; i < nr; i += pNr) {
        for(int j = 0; j < nc; j += pNc) {
            out[k++] = img[i * nc + j];
        }
    }
}

/**
 * Troca os pixels da imagem por uma string de caracteres
 * Percorre toda a imagem e calcula o indice que adequa melhor o tom de cinza da img
 * @param: imagem de entrada, numero de linhas e colunas, maximo valor e um vetor com os caracteres
 * @return: imagem de saida 
*/
image ascii(image in, int nr, int nc, int ml, char *string){
    image out = img_alloc(nr, nc);
    int tons = (ml+1)/strlen(string);
    int indice;

    for(int i = 0; i < nr * nc; i++){
        
        indice = floor(in[i]/tons);
        out[i] = string[indice];
    }

    return out;

}

void msg(char *s)
{
    printf("\nConvolucao");
    printf("\n-------------------------------");
    printf("\nUso:  %s  nome-imagem[.pgm] \n\n", s);
    printf("    nome-imagem[.pgm] é o nome do arquivo da imagem \n");
    exit(1);
}

// Funcao main
int main(int argc, char *argv[])
{
    // Declaracao de variavel
    int nc, nr, ml, tp, numRow, numCol;
    char *p, nameIn[100], nameOut[100], cmd[110], *vetAscii;
    image In, Out, Aux; 

    // Erro nos argumentos
    if (argc < 5)
        msg(argv[0]);
    
    // Atribuicao das variaveis para o argumento
    numCol = atoi(argv[2]);
    numRow = atoi(argv[3]);
    vetAscii = argv[4];

    // Atribui o nome de entrada
    img_name(argv[1], nameIn, nameOut, GRAY);

    // Le a imagem
    In = img_get(nameIn, &nr, &nc, &ml, GRAY);

    // Aloca e faz a amostra
    Aux = img_alloc(nr, nc);
    img_sampling(In, Aux, nr, nc, numRow, numCol);


    // Transformacao
    Out = ascii(Aux, numRow, numCol, ml, vetAscii);
     
    // Salva a imagem
    img_put(Out, nameOut, numRow, numCol, ml, GRAY);
    img_free(In);
    img_free(Out);
    return 0;
}
