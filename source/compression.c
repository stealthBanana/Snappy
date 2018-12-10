//
// Created by Gilles on 07.11.2018.
//
#include "../header/compression.h"

//funzione che legge la dimensione del file da comprimere e la restituisce in varint
unsigned char *getSize(FILE *fin){
    fseek(fin, 0, SEEK_END);
    unsigned int intValueOfSize = ftell(fin);
    //calcolo quanti bit servono per scrivere il numero della dimensione del file
    int numberOfBits = (int)log2(intValueOfSize)+1;
    //calcolo quanti byte servono per scrivere il numero della dimensione del file
    int numberOfBytes = ceil((double)numberOfBits/7);
    //istanzio un array di char lungo quanto i byte necessari per scrivere la  dimensione del file
    unsigned char *size;
    size = (char*)calloc(sizeof(char), sizeof(char)*numberOfBytes);
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

//funzione che ritorna la codifica di un literal
unsigned char *getLiteral(char *str){
    //lunghezza = la lughezza del literal -1
    unsigned char length = strlen(str)-1;
    //alloco la memoria per il literale (+2 perchè length è la lunghezza -1)
    unsigned char *literal;
    literal = calloc(sizeof(char), sizeof(char)*(length+2));
    //setto il tag
    literal[0] = literal[0] & 0;
    //setto la lunghezza del literale;
    literal[0] = literal[0] | (length << 2);
    //copio il literale dal secondo Byte in avanti
    strcat(&literal[1], str);
    return literal;
}

void compress(FILE *fin, FILE *fout)
{
    //stampo la dimensione del file
    unsigned char *size = getSize(fin);
    fputs(size, fout);
    free(size);

    

    fclose(fin);
    fclose(fout);
}

