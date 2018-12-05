//
// Created by Gilles on 07.11.2018.
//
#include "../header/compression.h"

unsigned char *getSize(FILE *fin){
    fseek(fin, 0, SEEK_END);
    //int intValueOfSize = ftell(fin);
    unsigned int intValueOfSize = 638;
    fclose(fin);
    //calcolo quanti bit servono per scrivere il numero della dimensione del file
    int numberOfBits = (int)log2(intValueOfSize)+1;
    //calcolo quanti byte servono per scrivere il numero della dimensione del file
    int numberOfBytes = ceil((double)numberOfBits/7);
    //istanzio un array di char lungo quanto i byte necessari per scrivere la  dimensione del file
    unsigned char *size;
    size = (char*)calloc(sizeof(char)*numberOfBytes, sizeof(char)*numberOfBytes);
    for(int i = 0; i < numberOfBytes; i++){
        for(int j = 0; j < 7; j++){
            int mask = 1 << i*8+j-i;
            size[i] = (unsigned char) ((size[i] - (char)(0)) | ((mask & intValueOfSize) >> (i*8-i)));
        }
        size[i] = (unsigned char)((size[i] - (char) (0)) | 0x80);
    }
    size[numberOfBytes-1] = (unsigned char)((size[numberOfBytes-1] - (char) (0)) & 0x7f);
    return size;
}

void compress(FILE *fin, FILE *fout)
{
    unsigned char *size = getSize(fin);
    printf("size[0]: %d = ", (size[0]+0));
    printf("%c\n", (unsigned char)(size[0]+0));
    printf("size[1]: %d = ", (size[1]+0));
    printf("%c\n", (unsigned char)(size[1]+0));
    free(size);
}

