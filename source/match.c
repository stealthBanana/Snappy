//
// Created by Gilles on 12.12.2018.
//

#include "../header/match.h"

//funzione che ritorna la codifica di un match
//parametro lenght da 4 a 11 oppure da 1 a 64 se 2 Byte match
//parametro offset da 0 a 2047 oppure da 0 a 65535 se 2 Byte match
void writeMatch(unsigned char length, unsigned short offset, FILE *fout){
    unsigned char *value;
    short size;

    //1 BYTE MATCH
    if(length > 3 && length < 12 && offset < 2048) {
        //assegno alla struttura la lunghezza del match
        size = 2;
        //alloco la memoria per il match (2 Byte)
        value = (unsigned char*) calloc(sizeof(char), sizeof(char) * 2);
        //setto il tag del match (01)
        value[0] = value[0] | 0b1;
        //lunghezza = la lunghezza del match -4
        length -= 4;
        //setto la lunghezza del match
        value[0] = value[0] | (length << 2);
        //setto i primi 3 bit dell'offset del match nel primo Byte
        value[0] = value[0] | (unsigned char)((offset >> 8) << 5);
        //setto il resto dell'offset nel secondo Byte
        value[1] = value[1] | (unsigned char)(offset & 0xff);

        //2 BYTE MATCH
    }else if(length > 0 && length < 65 && offset < 65536) {
        //assegno alla struttura la lunghezza del match
        size = 3;
        //alloco la memoria per il match (3 Byte)
        value = (unsigned char*) calloc(sizeof(char), sizeof(char) * 3);
        //setto il tag del match (10)
        value[0] = value[0] | 0b10;
        //lunghezza = la lunghezza del match -1
        length -= 1;
        //setto la lunghezza del match
        value[0] = value[0] | (length << 2);
        //setto il primo Byte dell'offset del match nel secondo Byte
        value[1] = value[1] | (unsigned char)(offset >> 8);
        //setto il secondo Byte dell'offset nel terzo Byte
        value[2] = value[2] | (unsigned char)(offset & 0xff);
    }

    printBytes(value, size, fout);
}