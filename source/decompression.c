//
// Created by Gilles on 07.11.2018.
//
#include "../header/decompression.h"

unsigned long dim(unsigned long d){
    unsigned long c = d;
    int n = 0;
    //conto il nummero di byte usati nella codifica della dimensione
    while(c){
        n++;
        c = c >> 7;
    }
    unsigned long p = 0;
    //algoritmo per la trasformazione dei byte nella lunghezza del file
    for(int i = 0; i < n; i++){
        p = (p << 7) | ((d >> (i*7)) & 0x7F);
    }
    return p;
}

unsigned long inv(unsigned long b){
    unsigned long inv = 0;
    while(b){
        inv = (inv << 8) | (b & 0xFF);
        b = b >> 8;
    }
    return inv;
}

void literal(unsigned long x, FILE *fout){
    char c;
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
        fseek(fout, -offset, SEEK_END);
        c = fgetc(fout);
        fseek(fout, 0, SEEK_END);
        fputc(c, fout);
    }
}

void twoMatch(unsigned int len, unsigned int offset, FILE *fout){
    char c;
    for(int i = 0; i < len; i++){
        fseek(fout, -offset, SEEK_END);
        c = fgetc(fout);
        fseek(fout, 0, SEEK_END);
        fputc(c, fout);
    }
}

void decompress(FILE *fin, FILE *fout) {
    unsigned char c = fgetc(fin);
    unsigned long dimbits = 0;
    unsigned long dimension = 0;
    char tag = 0;
    unsigned long input = 0;
    unsigned int length = 0;
    unsigned int offset = 0;
    if(((c & 0x80) >> 7) == 0){
        dimbits = dimbits | (c & 0x7F);
    }
    else {
        while (((c & 0x80) >> 7) == 1) {
            dimbits = dimbits | (c & 0x7F);
            dimbits = dimbits << 7;
            c = fgetc(fin);
        }
        dimbits = dimbits | (c & 0x7F);
    }
    dimension = dim(dimbits);
    while(dimension > 0){
        c = fgetc(fin);
        tag = c & 0x3;
        switch(tag){
            case 0:
                length = ((c & 0xFC) >> 2);
                switch(length){
                    case 60:
                        length = intToLittleEndian(fgetc(fin))>>24;
                        break;
                    case 61:
                        length = (intToLittleEndian(fgetc(fin)) | (intToLittleEndian(fgetc(fin)) << 8))>>16;
                        break;
                    case 62:
                        length = 0;
                        for(int i = 0; i < 3; i++){
                            length = length | (intToLittleEndian(fgetc(fin)) << (i*8));
                        }
                        length = length >> 8;
                        break;
                    case 63:
                        length = 0;
                        for(int i = 0; i < 4; i++){
                            length = length | (intToLittleEndian(fgetc(fin)) << (i*8));
                        }
                        break;
                    default:
                        length = length + 1;
                        break;
                }
                int cycle = ceil((length*1.0)/4);
                for(int i = 0; i < cycle; i++){
                    int a = 4;
                    if((i == (cycle-1)) && (length%4!=0)){
                        a = length%4;
                    }
                    while(a){
                        input = input << 8;
                        input = input | fgetc(fin);
                        a--;
                    }
                    literal(input, fout);
                    input = 0;
                }
                dimension = dimension - length;
                break;
            case 1:
                length = (c & 0x1c) + 4;
                offset = ((c & 0xE0) << 3) | fgetc(fin);
                oneMatch(length, offset, fout);
                dimension = dimension - length;
                break;
            case 2:
                length = (c & 0xFC) + 1;
                offset = fgetc(fin);
                offset = offset << 8;
                offset = offset | fgetc(fin);
                twoMatch(length, offset, fout);
                dimension = dimension - length;
                break;
            default:
                printf("tag sbagliato");
                dimension = 0;
                break;
        }
    }
}