#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "zip.h"
#include "lib.h"

void zip_file(const char* input, const char* output){
    clock_t outset, close;
    double gap;
    outset = clock();

    unsigned int bytes[256] = {0};

    // Abre arquivo do parâmetro input no modo leitura de binário
    FILE* alpha = fopen(input, "rb");
    (!alpha) ? error_404(): NULL == NULL ;

    // Abre arquivo do parâmetro arquivoomega no modo escrita de binário
    FILE* omega = fopen(output, "wb");
    (!omega) ? error_404(): NULL == NULL ;

    count_frequency(alpha, bytes);

    // Populando a árvore com a lista de frequência de bytes
    Tree* root = huffman_tree(bytes);

    // Grava a lista de frequência nos primeiros 256 bytes do arquivo
    fwrite(bytes, 256, sizeof(bytes[0]), omega);

    // Move o ponteiro do stream 'omega' para a posição posterior ao size de um unsigned int
    // É aqui que posteriormente será salvo o valor da variável 'size'
    fseek(omega, sizeof(unsigned int), SEEK_CUR);

    unsigned char character;
    unsigned size = 0;
    unsigned char right_hand = 0;

    while (fread(&character, 1, 1, alpha) >= 1)
    {

        // Cria um buffer vazio
        char buffer[1024] = {0};

        // Busca o código começando no nó 'root', utilizando o byte salvo em 'c', preenchendo 'buffer', desde o bucket deste último
        get_code(root, character, buffer, 0);

        // Laço que percorre o buffer
        for (char *i = buffer; *i; i++){
            // Se o caractere na posição tree for '1'
            if (*i == '1'){
                // right_hand = right_hand | (1 << (size % 8));
                right_hand = right_hand + pow(2, size % 8);
            }

            size++;

            if (size % 8 == 0){
                fwrite(&right_hand, 1, 1, omega);
                right_hand = 0;
            }
        }
    }

    fwrite(&right_hand, 1, 1, omega);

    // Move o ponteiro do stream para 256 vezes o size de um unsigned int, a partir do início dele (SEEK_SET)
    fseek(omega, 256 * sizeof(unsigned int), SEEK_SET);

    fwrite(&size, 1, sizeof(unsigned), omega);

    close = clock();
    gap = (double)(close - outset)/CLOCKS_PER_SEC;

    fseek(alpha, 0L, SEEK_END);
    double size_in = ftell(alpha);

    fseek(omega, 0L, SEEK_END);
    double size_out = ftell(omega);

    free_huffman(root);

    printf("Input: %s [%g bytes]\nOutput: %s [%g bytes]\nTime Gap: [%gs]\n", input, size_in/1000, output, size_out/1000, gap);
    printf("Compression Ratio: %d%%\n", (int)((100 * size_out)/size_in));

    fclose(alpha);
    fclose(omega);
}

void unzip_file(const char* input, const char* output){
    clock_t outset, close;
    double gap;
    outset = clock();

    unsigned bytes[256] = {0};

    // Abre arquivo do parâmetro input no modo leitura de binário
    FILE* alpha = fopen(input, "rb");
    (!alpha) ? error_404(): NULL == NULL ;

    // Abre arquivo do parâmetro arquivoomega no modo escrita de binário
    FILE* omega = fopen(output, "wb");
    (!omega) ? error_404(): NULL == NULL ;

    // Lê a lista de frequência que encontra-se nos primeiros 256 bytes do arquivo
    fread(bytes, 256, sizeof(bytes[0]), alpha);

    // Constrói árvore
    Tree* root = huffman_tree(bytes);

    // Lê o valor dessa posição do stream para dentro da variável size
    unsigned int size;
    fread(&size, 1, sizeof(size), alpha);

    unsigned int index = 0;
    unsigned char left_hand = 0;

    through_tree(root, index, size, alpha, omega, left_hand);

    free_huffman(root);

    close = clock();
    gap = (double)(close - outset) / CLOCKS_PER_SEC;

    fseek(alpha, 0L, SEEK_END);
    double size_in = ftell(alpha);

    fseek(omega, 0L, SEEK_END);
    double size_out = ftell(omega);

    printf("Input: %s [%g bytes]\nOutput: %s [%g bytes]\nTime Gap: [%gs]\n", input, size_in / 1000, output, size_out / 1000, gap);
    printf("Descompression Ratio: %d%%\n", (int)((100 * size_out)/ size_in));

    fclose(omega);
    fclose(alpha);
}