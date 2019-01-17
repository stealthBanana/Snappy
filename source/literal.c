//
// Created by Gilles on 12.12.2018.
//

#include "../header/literal.h"

//funzione che ritorna la codifica di un literal
//parametro str da 1 a 8589934592 caratteri
void writeLiteral(unsigned long literalLength, FILE *fin, FILE *fout){

    unsigned long tagSize = 0;
    //lunghezza = la lughezza del literal -1
    unsigned int length = literalLength-1;
    //alloco la memoria per il literale (+2 perchè length è la lunghezza -1)
    unsigned char *value;

    if(length <= 60){
        tagSize = 1;
        value = (unsigned char*) calloc(sizeof(char), sizeof(char));
        //setto il tag del literal (00)
        value[0] = value[0] & 0;
        //setto la lunghezza del literal;
        value[0] = value[0] | (((char)length) << 2);
    }else if(length < pow(2, 9)){
        tagSize = 2;
        value = (unsigned char*) calloc(sizeof(char), sizeof(char)*2);
        //setto il tag del literal (00)
        value[0] = value[0] & 0;
        //setto i Byte di lunghezza a 0
        value[1] = value[1] & 0;
        //setto i primi 6 bit a 60;
        value[0] = value[0] | (60 << 2);
        int leLength = intToLittleEndian(length);
        value[1] = value[1] | (char)(leLength >> 24);
    }else if(length < pow(2, 17)){
        tagSize = 3;
        value = (unsigned char*) calloc(sizeof(char), sizeof(char)*3);
        //setto il tag del literal (00)
        value[0] = value[0] & 0;
        //setto i Byte di lunghezza a 0
        value[1] = value[1] & 0;
        value[2] = value[2] & 0;
        //setto i primi 6 bit a 61;
        value[0] = value[0] | (61 << 2);
        int leLength = intToLittleEndian(length);
        value[1] = value[1] | (char)(leLength >> 24);
        value[2] = value[2] | (char)((leLength >> 16) & 0x00ff);
    }else if(length < pow(2, 25)){
        tagSize = 4;
        value = (unsigned char*) calloc(sizeof(char), sizeof(char)*4);
        //setto il tag del literal (00)
        value[0] = value[0] & 0;
        //setto i Byte di lunghezza a 0
        value[1] = value[1] & 0;
        value[2] = value[2] & 0;
        value[3] = value[3] & 0;
        //setto i primi 6 bit a 62;
        value[0] = value[0] | (62 << 2);
        int leLength = intToLittleEndian(length);
        value[1] = value[1] | (char)(leLength >> 24);
        value[2] = value[2] | (char)((leLength >> 16) & 0x00ff);
        value[2] = value[2] | (char)((leLength >> 8) & 0x0000ff);
    }else if(length < pow(2, 33)){
        tagSize = 5;
        value = (unsigned char*) calloc(sizeof(char), sizeof(char)*5);
        //setto il tag del literal (00)
        value[0] = value[0] & 0;
        //setto i Byte di lunghezza a 0
        value[1] = value[1] & 0;
        value[2] = value[2] & 0;
        value[3] = value[3] & 0;
        value[4] = value[4] & 0;
        //setto i primi 6 bit a 63;
        value[0] = value[0] | (63 << 2);
        int leLength = intToLittleEndian(length);
        value[1] = value[1] | (char)(leLength >> 24);
        value[2] = value[2] | (char)((leLength >> 16) & 0x00ff);
        value[2] = value[2] | (char)((leLength >> 8) & 0x0000ff);
        value[2] = value[2] | (char)(leLength & 0x000000ff);
    }

    printBytes(value, tagSize, fout);

    fseek(fin, -literalLength+2, SEEK_CUR);
    for(int i = 0; i < literalLength; i++)
        fputc(fgetc(fin), fout);
}