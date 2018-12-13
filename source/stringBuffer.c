//
// Created by Gilles on 13.12.2018.
//

#include "../header/stringBuffer.h"

StringBuffer *createStringBuffer(int size) {
    StringBuffer *strBfr;
    strBfr = malloc(sizeof(StringBuffer));
    strBfr->size = size;
    strBfr->value = calloc(sizeof(char), sizeof(char)*size);
    return strBfr;
}

char push(StringBuffer *strBfr){
    char c = strBfr->value[0];
    strcpy(strBfr->value, strBfr->value+1);
    return c;
}

void put(StringBuffer *strBfr, unsigned char *c){
    if(strlen(strBfr->value) == strBfr->size)
        push(strBfr);
    strcpy(strBfr->value, strcat(strBfr->value, c));
}

char *clear(StringBuffer *strBfr) {
    char *str = strBfr->value;
    strBfr->value = realloc(strBfr->value, sizeof(char)*strBfr->size);
    return str;
}