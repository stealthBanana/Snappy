//
// Created by Gilles on 07.11.2018.
//
#include "../header/compression.h"

char getSize(FILE *fin){
    fseek(fin, 0, SEEK_END);
    int intValueOfSize = ftell(fin);
    int numberOfBits = (int)log2(intValueOfSize);
    int numberOfBytes = ((double)numberOfBits/7 > 7) ? numberOfBits/7 +1 : numberOfBits/7;
    char size;
    size = malloc(numberOfBytes);
    for(int i = 0; i < (8*numberOfBytes); i++){
        int mask = 1 << (i%8);
        if(i % 8 == 0 && i != 0){
            if(i != (8*numberOfBytes -1))
                size[numberOfBytes - (i / 8)] = atoi(size[7 - (i / 8)]) + mask;
            else
                size[numberOfBytes - (i / 8)] = atoi(size[7 - (i / 8)]) & 0x7f;
        }else {
            size[numberOfBytes - (i / 8)] = atoi(size[7 - (i / 8)]) + (mask & intValueOfSize);
        }
    }
    return size;
}

void compress(FILE *fin, FILE *fout)
{
    printf("size: %s", getSize(fin));
}

