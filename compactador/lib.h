#ifndef lib_h_
#define lib_h_

#include <stdio.h>

typedef struct tree Tree;

typedef struct cell Cell;

typedef struct list List;

/*===================================*/

List* new_list(Tree* tree);

Tree* new_tree(unsigned char character, int frequency, Tree* left, Tree* right);

/*===================================*/

void add_list(List* list, Cell* cell);

Tree* remove_minor_list(Cell* cell);

void count_frequency(FILE* input, unsigned int* bytes);

int get_code(Tree* tree, unsigned char character, char* buffer, int size);

Tree* huffman_tree(unsigned int* bytes);

void free_huffman(Tree* tree);

void through_tree(Tree* root, unsigned int index, unsigned int size, FILE* input, FILE* output, unsigned char right_hand);

int bit(FILE* input, int index, unsigned char* character );

void error_404();

#endif /* lib_h_ */