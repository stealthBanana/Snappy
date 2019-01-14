//
// Created by Gilles on 07.11.2018.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned long dim(unsigned long d){
    unsigned long c = d;
    int n = 0;
    //conto il nummero di byte usati nella codifica della dimensione
    while(c){
        n++;
        c = c >> 8;
    }
    unsigned long p = 0;
    //algoritmo per la trasformazione dei byte nella lunghezza del file
    for(int i = 0; i < n; i++){
        p = (p << 7) | ((d >> (i*8)) & 0x7F);
    }
    return p;
}

unsigned long inv(unsigned long b){
    unsigned long inv = 0;
    while(b){
        inv = (inv << 1) | (b & 1);
        b = b >> 1;
    }
    return inv;
}

void literal(unsigned long x, FILE *fout){
    int c;
    unsigned long lit = inv(x);
    while(lit){
        c = lit & 0xFF;
        lit = lit >> 8;
        fputc(c, fout);
    }
}

void oneMatch(unsigned int len, unsigned int offset, FILE *fout){
    char c;
    for(int i = 0; i < len; i++){
        fseek(fout, -offset+i, SEEK_END);
        c = fgetc(fout);
        fseek(fout, 0, SEEK_END);
        fputc(c, fout);
    }
}

void twoMatch(unsigned int len, unsigned int offset, FILE *fout){
    char c;
    for(int i = 0; i < len; i++){
        fseek(fout, -offset+i, SEEK_END);
        c = fgetc(fout);
        fseek(fout, 0, SEEK_END);
        fputc(c, fout);
    }
}

void decompress(FILE *fin, FILE *fout) {
    unsigned char c;
    unsigned long dimbits = 0;
    unsigned long dimension = 0;
    unsigned char tag = 0;
    unsigned long input = 0;
    unsigned length = 0;
    unsigned int offset = 0;
    if((c = fgetc(fin)) & 0x80 == 0){
        dimbits = dimbits | (c & 0x7F);
    }
    else {
        while ((c = fgetc(fin)) & 0x80 == 1) {
            dimbits = dimbits | (c & 0x7F);
            dimbits = dimbits << 7;
        }
        dimbits = dimbits | (c & 0x7F);
    }
    dimension = dim(dimbits);
    while(dimension){
        c = fgetc(fin);
        tag = c & 0x3;
        switch(tag){
            case 0:
                length = c & 0xFC;
                int a = length;
                while(a){
                    input = input << 8;
                    input = input | fgetc(fin);
                    a--;
                }
                literal(input, fout);
                dimension = dimension - length - 1;
                break;
            case 1:
                length = c & 0x1c;
                offset = ((c & 0xE0) << 3) | fgetc(fin);
                oneMatch(length, offset, fout);
                dimension = dimension - 2;
                break;
            case 2:
                length = c & 0xFC;
                offset = (fgetc(fin) << 8) & fgetc(fin);
                twoMatch(length, offset, fout);
                dimension = dimension - 3;
                break;
            default:
                printf("4 byte match not allowed!");
                break;
        }
    }
}