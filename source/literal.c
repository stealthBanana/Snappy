//
// Created by Gilles on 12.12.2018.
//

#include "../header/literal.h"

//funzione che ritorna la codifica di un literal
//parametro str da 1 a 64 caratteri
Literal *getLiteral(unsigned char *str){
    //creo una struttura per il literal
    Literal *literal;
    literal = (Literal*) malloc(sizeof(Literal));

    //lunghezza = la lughezza del literal -1
    unsigned char length = strlen(str)-1;
    //alloco la memoria per il literale (+2 perchè length è la lunghezza -1)
    unsigned char *value;
    value = (unsigned char*) calloc(sizeof(char), sizeof(char)*(length+2));
    //setto il tag del literal (00)
    value[0] = value[0] & 0;
    //setto la lunghezza del literal;
    value[0] = value[0] | (length << 2);
    //copio il literale dal secondo Byte in avanti
    strcat(&value[1], str);

    //assegno i valori alla struttura
    literal->value = (unsigned char*) calloc(sizeof(char), sizeof(char)*(length+2));
    //memcpy(literal->value, value, sizeof(char)*(length+2));
    strcpy(literal->value, value);
    literal->size = length+1;
    return literal;
}