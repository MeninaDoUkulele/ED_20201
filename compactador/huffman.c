#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zip.h"

void sintax_error();

void zip();

void unzip();

/*===================================*/

int main(int argc, char *argv[]){
    if(argc < 4){
        sintax_error();
        return 0;
    }

    if(strcmp("-zip", argv[1]) == 0){
        zip(argv);
        return 0;
    }

    if (strcmp("-unzip", argv[1]) == 0){
        unzip(argv);
        return 0;
    }

    sintax_error();
    return 0;
}

/*===================================*/

void sintax_error(){
    puts("\n============================================================\n");
    printf("Sintax: huffman [flag] [input] [output]\n\n");
    printf("   Flag options:\n");
    printf("     [-zip] Compress the file\n");
    printf("     [-unzip] Descompress the file\n");
    printf("\nex: ./huffman -zip original.mp3 modified.loo\n");
    puts("============================================================\n");
}

void zip(char** argv){
    if(strstr(argv[3], ".loo")){
        zip_file(argv[2], argv[3]);
        printf("Successful file compression\n");
        return;
    }
    printf("The output name must have '.loo'.\n");
}

void unzip(char** argv){
    if (strstr(argv[2], ".loo")){
        unzip_file(argv[2], argv[3]);
        printf("Successful file descompression\n");
        return;
    }

    printf("The input file has to be '.loo'.\n");
}