#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

struct tree{
    int frequency;
    unsigned char character;
    Tree* left;
    Tree* right;
};

struct cell{
    List* actual;
    int items;
};

struct list{
    Tree* current;
    List* next;
};

/*===================================*/

List* new_list(Tree* tree){
    List* list = (List*) malloc(sizeof(List));
    
    list->current = tree;
    list->next = NULL;

    return list;
}

Tree* new_tree(unsigned char character, int frequency, Tree* left, Tree* right){
    Tree* tree = (Tree*) malloc(sizeof(Tree));
    tree->frequency = frequency;
    tree->character = character;
    tree->left = left;
    tree->right = right;

    return tree;
}

/*===================================*/

void add_list(List* list, Cell* cell){
    if(cell->actual == NULL){
        cell->actual = list;
        cell->items++;
        return;
    }

    if(list->current->frequency < cell->actual->current->frequency){
        list->next = cell->actual;
        cell->actual = list;
        cell->items++;
        return;
    }

    List* right_hand = cell->actual->next;
    List* left_hand = cell->actual;

    while(right_hand && right_hand->current->frequency <= list->current->frequency){
        left_hand = right_hand;
        right_hand = left_hand->next;
    }

    left_hand->next = list;
    list->next = right_hand;
    cell->items++;
}

Tree* remove_minor_list(Cell* cell){
    List* right_hand = cell->actual;
    Tree* left_hand = right_hand->current;

    cell->actual = right_hand->next;
    free(right_hand);
    right_hand = NULL;
    cell->items--;

    return left_hand;
}

void count_frequency(FILE* input, unsigned int* bytes){
    unsigned char character;

    while (fread(&character, 1, 1, input) >= 1){
        bytes[(unsigned char)character]++;
    }

    rewind(input);
}

// 0 verdadeiro, 1 falso;
int get_code(Tree* tree, unsigned char character, char* buffer, int size){
    if(!(tree->left || tree->right) && tree->character == character){
        buffer[size] = '\0';
        return 0;
    } else{
        int answer = 1;

        if(tree->left){
            buffer[size] = '0';
            answer = get_code(tree->left, character, buffer, size + 1);
        }

        if(!answer && tree->right){
            buffer[size] = '1';
            answer = get_code(tree->right, character, buffer, size + 1);
        }
        if(!answer){
            buffer[size] = '\0';
        }

        return answer;
    }
}

Tree* huffman_tree(unsigned int* bytes){
    Cell cell;
    cell.actual = NULL;
    cell.items = 0;

    for (int i = 0; i < 256; i++){
        if (bytes[i]){
            // Insere na lista 'l' um nó referente ao byte i e sua respectiva frequência (guardada em listaBytes[i]).
            add_list(new_list(new_tree(i, bytes[i], NULL, NULL)), &cell);
        }
    }

    while (cell.items > 1){
        Tree* left = remove_minor_list(&cell);
        Tree* right = remove_minor_list(&cell);

        Tree* sum = new_tree('#', left->frequency + right->frequency, left, right);

        add_list(new_list(sum), &cell);
    }

    return remove_minor_list(&cell);
}

void free_huffman(Tree* tree){
    if(tree == NULL) 
        return;

    Tree* left = tree->left;
    Tree* right = tree->right;
    free(tree);

    free_huffman(left);
    free_huffman(right);
}

void through_tree(Tree* root, unsigned int index, unsigned int size, FILE* input, FILE* output, unsigned char right_hand){
    while(index < size){
        // Salvando o Tree que encontramos
        Tree* tree = root;

        // Enquanto tree não for folha
        while(tree->left || tree->right )
        {
            tree = bit(input, index++, &right_hand) ? tree->right: tree->left;
        }

        fwrite(&(tree->character), 1, 1, output);
    }
}

int bit(FILE* input, int index, unsigned char* character ){
    (index % 8 == 0) ? fread(character, 1, 1, input): NULL == NULL ;

    // Exclamação dupla converte para '1' (inteiro) se não for 0. Caso contrário, deixa como está (0)
    return !!((* character) & (1 << (index % 8)));
}

void error_404(){
    printf("File not found\n");
    exit(0);
}