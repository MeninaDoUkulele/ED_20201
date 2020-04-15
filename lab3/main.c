#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"

int main(){
    Lista* lista = inicializa_lista();

    insere(lista, inicializa_aluno("luana", 2018102324, 4.8));
    insere(lista, inicializa_aluno("andre", 2018102321, 7.5));
    insere(lista, inicializa_aluno("isaque", 2018102325, 10));
    puts("\nLISTA COMPLETA");
    imprime_lista(lista);

    Aluno* aluno = retira_lista(lista, "luana");
    puts("\nLISTA SEM ALUNO RETIRADO");
    imprime_lista(lista);

    puts("\nALUNO RETIRADO");
    imprime_aluno(aluno);

    free_lista(lista);

    // puts("\nLISTA LIBERADA, PROGRAMA ENCERRADO\n");
    return 0;
}