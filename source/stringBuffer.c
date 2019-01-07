//
// Created by Gilles on 13.12.2018.
//

#include "../header/stringBuffer.h"

StringBuffer *createStringBuffer(int size) {
    StringBuffer *strBfr;
    strBfr = (StringBuffer*) malloc(sizeof(StringBuffer));
    strBfr->size = size;
    strBfr->value = (unsigned char*) calloc(sizeof(char), sizeof(char)*size);
    return strBfr;
}

unsigned char push(StringBuffer *strBfr){
    unsigned char c = strBfr->value[0];
    strcpy(strBfr->value, strBfr->value+1);
    return c;
}

void put(StringBuffer *strBfr, unsigned char *c){
    if(strlen(strBfr->value) == strBfr->size)
        push(strBfr);
    strcpy(strBfr->value, strcat(strBfr->value, (const char *) c));
}

unsigned char *clearStringBuffer(StringBuffer *strBfr) {
    unsigned char *str = strBfr->value;
    strcpy(strBfr->value, "");
    return str;
}

void unqueue(StringBuffer *strBfr, int n) {
    if (strlen(strBfr->value) < n || strBfr->size < n)
        clearStringBuffer(strBfr);
    else {
        n = strlen(strBfr->value) - n;
        strcpy(strBfr->value + n, "");
    }
}