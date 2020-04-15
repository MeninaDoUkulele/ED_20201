#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"

struct matriz{
    int** matriz;
    int ncol;
    int nlin;
};

Matriz* inicializaMatriz (int nlinhas, int ncolunas){
    Matriz* matriz = (Matriz*) malloc(sizeof(Matriz));
    matriz->matriz = (int**) malloc(nlinhas*sizeof(int*));
    for(int i = 0; i < nlinhas; i++){
        matriz->matriz[i] = (int*) malloc(ncolunas*sizeof(int));
    }
    matriz->nlin = nlinhas;
    matriz->ncol = ncolunas;

    return matriz;
}

void modificaElemento (Matriz* mat, int linha, int coluna, int elem){
    mat->matriz[linha][coluna] = elem;
}

int recuperaElemento(Matriz* mat, int linha, int coluna){
    return mat->matriz[linha][coluna];
}

int recuperaNColunas (Matriz* mat){
    return mat->ncol;
}

int recuperaNLinhas (Matriz* mat){
    return mat->nlin;
}

Matriz* transposta (Matriz* mat){
    Matriz* aux = inicializaMatriz(mat->ncol, mat->nlin);
    
    for(int i = 0; i < mat->nlin; i++){
        for(int j = 0; j < mat->ncol; j++){
            aux->matriz[j][i] = mat->matriz[i][j];
        }
    }
    return aux;
}

Matriz* multiplicacao (Matriz* mat1, Matriz* mat2){
    Matriz* aux = inicializaMatriz(mat1->nlin, mat2->ncol);

    for(int i = 0; i < mat1->nlin; i++){
        for(int j = 0; j < mat1->ncol; j++){
            for(int k = 0; k < mat2->ncol; k++){
                aux->matriz[i][k] = mat1->matriz[i][j] * mat2->matriz[j][k];
            }
        }
    }
    return aux;
}

void imprimeMatriz(Matriz* mat){
    for(int i = 0; i < mat->nlin; i++){
        for(int j = 0; j < mat->ncol; j++){
            printf("%i  ", mat->matriz[i][j]);
        }
        puts("\n");
    }
}

void destroiMatriz(Matriz* mat){
    for(int i = 0; i < mat->nlin; i++){
        free(mat->matriz[i]);
    }
    free(mat->matriz);
    free(mat);
}