//
// Created by Gilles on 13.12.2018.
//

#ifndef SNAPPY_STRINGBUFFER_H
#define SNAPPY_STRINGBUFFER_H

#include <malloc.h>
#include <string.h>

typedef struct stringBuffer{
    unsigned char *value;
    int size;
}StringBuffer;

StringBuffer *createStringBuffer(int size);
unsigned char push(StringBuffer *strBfr);
void put(StringBuffer *strBfr, unsigned char *c);

#endif //SNAPPY_STRINGBUFFER_H
