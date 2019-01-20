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

    //lunghezza del literal < 60
    if(length <= 60){
        tagSize = 1;
        value = (unsigned char*) calloc(sizeof(char), sizeof(char));
        //setto il tag del literal (00)
        value[0] = value[0] & 0;
        //setto la lunghezza del literal;
        value[0] = value[0] | (((char)length) << 2);


    //lunghezza del literal < 2 elevato 8
    }else if(length < pow(2, 8)){
        length++;
        tagSize = 2;
        value = (unsigned char*) calloc(sizeof(char), sizeof(char)*2);
        //setto il tag del literal (00)
        value[0] = value[0] & 0;
        //setto i Byte di lunghezza a 0
        value[1] = value[1] & 0;
        //setto i primi 6 bit a 60;
        value[0] = value[0] | (60 << 2);
        //setto la lunghezza del literal in little-endian nel prossimo byte
        int leLength = intToLittleEndian(length);
        value[1] = value[1] | (char)(leLength >> 24);

    //lunghezza del literal < 2 elevato 16
    }else if(length < pow(2, 16)){
        length++;
        tagSize = 3;
        value = (unsigned char*) calloc(sizeof(char), sizeof(char)*3);
        //setto il tag del literal (00)
        value[0] = value[0] & 0;
        //setto i Byte di lunghezza a 0
        value[1] = value[1] & 0;
        value[2] = value[2] & 0;
        //setto i primi 6 bit a 61;
        value[0] = value[0] | (61 << 2);
        //setto la lunghezza del literal in little-endian nei prossimi byte
        int leLength = intToLittleEndian(length);
        value[1] = value[1] | (char)(leLength >> 24);
        value[2] = value[2] | (char)((leLength >> 16) & 0x00ff);

    //lunghezza del literal < 2 elevato 24
    }else if(length < pow(2, 24)){
        length++;
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
        //setto la lunghezza del literal in little-endian nei prossimi byte
        int leLength = intToLittleEndian(length);
        value[1] = value[1] | (char)(leLength >> 24);
        value[2] = value[2] | (char)((leLength >> 16) & 0x00ff);
        value[2] = value[2] | (char)((leLength >> 8) & 0x0000ff);

    //lunghezza del literal < 2 elevato 32
    }else if(length < pow(2, 32)){
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
        //setto la lunghezza del literal in little-endian nei prossimi byte
        int leLength = intToLittleEndian(length);
        value[1] = value[1] | (char)(leLength >> 24);
        value[2] = value[2] | (char)((leLength >> 16) & 0x00ff);
        value[2] = value[2] | (char)((leLength >> 8) & 0x0000ff);
        value[2] = value[2] | (char)(leLength & 0x000000ff);
    }

    //stampo i byte di tag
    printBytes(value, tagSize, fout);

    //torno in dietro in base alla lunghezza del literal
    fseek(fin, -literalLength-4, SEEK_CUR);
    //stampo tutti i caratteri del literal
    for(int i = 0; i < literalLength; i++)
        fputc(fgetc(fin), fout);
    fseek(fin, 4, SEEK_CUR);
}