//
// Created by Gilles on 13.12.2018.
//

#ifndef SNAPPY_STRINGBUFFER_H
#define SNAPPY_STRINGBUFFER_H

#include <malloc.h>
#include <string.h>

//struttura del buffer di caratteri
typedef struct stringBuffer{
    //caratteri nel buffer
    unsigned char *value;
    //dimensione massima del buffer
    int size;
}StringBuffer;

StringBuffer *createStringBuffer(int size);
unsigned char push(StringBuffer *strBfr);
void put(StringBuffer *strBfr, unsigned char *c);

#endif //SNAPPY_STRINGBUFFER_H
