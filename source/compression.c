//
// Created by Gilles on 07.11.2018.
//
#include "../header/compression.h"

char *getSize(FILE *fin){
    fseek(fin, 0, SEEK_END);
    //int intValueOfSize = ftell(fin);
    int intValueOfSize = 638;
    fclose(fin);
    //calcolo quanti bit servono per scrivere il numero della dimensione del file
    int numberOfBits = (int)log2(intValueOfSize)+1;
    //calcolo quanti byte servono per scrivere il numero della dimensione del file
    int numberOfBytes = ceil((double)numberOfBits/7);
    //istanzio un array di char lungo quanto i byte necessari per scrivere la  dimensione del file
    char *size;
    size = malloc(sizeof(char)*numberOfBytes);
    //azzero i valori della stringa
    size[0] = 0;
    /*for(int i = 0; i < numberOfBytes; i++)
        size[i] = 0;*/
    for(int i = 0; i < (8*numberOfBytes); i++){
        int mask = 1 << i;
        int index = i/8;
        //ogni 8 bit setto il flag del varint a 1
        if(i % 8 == 7){
            if(i != (8*numberOfBytes -1))
                size[index] = atoi(&size[index]) | (mask >> (index*8));
            //se si tratta dell'ultimo bit setto il flag a 0
            else
                size[index] = atoi(&size[index]) & 0x7f;
        }else {
            //aggiungo al char il bit alla i-esima posizione della dimensione
            size[index] = atoi(&size[index]) | ((mask & intValueOfSize) >> (index*8));
        }
    }
    return size;
}

void compress(FILE *fin, FILE *fout)
{
    printf("size: %s", getSize(fin));
}

