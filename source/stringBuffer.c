//
// Created by Gilles on 13.12.2018.
//

#include "../header/stringBuffer.h"

//questa funzione crea un buffer di caratteri della dimensione specificata da parametro
StringBuffer *createStringBuffer(int size) {
    StringBuffer *strBfr;
    strBfr = (StringBuffer*) malloc(sizeof(StringBuffer));
    strBfr->size = size;
    strBfr->value = (unsigned char*) calloc(sizeof(char), sizeof(char)*size);
    return strBfr;
}

//funzione che ritorna il primo carattere del buffer e lo rimuove
unsigned char push(StringBuffer *strBfr){
    unsigned char c = strBfr->value[0];
    //shifto il puntatore del primo carattere del buffer
    strcpy(strBfr->value, strBfr->value+1);
    //ritorno quello che prima era il primo carattere del buffer
    return c;
}

//funzione che inserisce un nuovo carattere nel buffer
void put(StringBuffer *strBfr, unsigned char *c){
    //se in buffer è pieno eseguo un push del primo carattere
    if(strlen(strBfr->value) == strBfr->size)
        push(strBfr);
    //inserisco il nuovo carattere
    strcpy(strBfr->value, strcat(strBfr->value, (const char *) c));
}