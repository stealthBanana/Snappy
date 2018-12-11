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
//parametro str da 1 a 64 caratteri
unsigned char *getLiteral(char *str){
    //lunghezza = la lughezza del literal -1
    unsigned char length = strlen(str)-1;
    //alloco la memoria per il literale (+2 perchè length è la lunghezza -1)
    unsigned char *literal;
    literal = calloc(sizeof(char), sizeof(char)*(length+2));
    //setto il tag del literal (00)
    literal[0] = literal[0] & 0;
    //setto la lunghezza del literal;
    literal[0] = literal[0] | (length << 2);
    //copio il literale dal secondo Byte in avanti
    strcat(&literal[1], str);
    return literal;
}

//funzione che ritorna la codifica di un match
//parametro lenght da 4 a 11 oppure da 1 a 64 se 2 Byte match
//parametro offset da 0 a 2047 oppure da 0 a 65535 se 2 Byte match
unsigned char *getMatch(unsigned char length, unsigned short offset){
    unsigned char *match;

    //1 BYTE MATCH
    if(length > 3 && length < 12 && offset < 2048) {
        //alloco la memoria per il match (2 Byte)
        match = calloc(sizeof(char), sizeof(char) * 2);
        //setto il tag del match (01)
        match[0] = match[0] | 0b1;
        //lunghezza = la lunghezza del match -4
        length -= 4;
        //setto la lunghezza del match
        match[0] = match[0] | (length << 2);
        //setto i primi 3 bit dell'offset del match nel primo Byte
        match[0] = match[0] | (unsigned char)((offset >> 8) << 5);
        //setto il resto dell'offset nel secondo Byte
        match[1] = match[1] | (unsigned char)(offset & 0xff);

    //2 BYTE MATCH
    }else if(length > 0 && length < 65 && offset < 65536) {
        //alloco la memoria per il match (3 Byte)
        match = calloc(sizeof(char), sizeof(char) * 3);
        //setto il tag del match (10)
        match[0] = match[0] | 0b10;
        //lunghezza = la lunghezza del match -1
        length -= 1;
        //setto la lunghezza del match
        match[0] = match[0] | (length << 2);
        //setto il primo Byte dell'offset del match nel secondo Byte
        match[1] = match[1] | (unsigned char)(offset >> 8);
        //setto il secondo Byte dell'offset nel terzo Byte
        match[2] = match[2] | (unsigned char)(offset & 0xff);
    }
    return match;
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

