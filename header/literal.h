//
// Created by Gilles on 12.12.2018.
//

#ifndef SNAPPY_LITERAL_H
#define SNAPPY_LITERAL_H

#include <malloc.h>
#include <string.h>

typedef struct literal{
    unsigned char *value;
    unsigned long size:7;
}Literal;

//funzione che costruisce la codifica di un literal in base alla stringa passata come paramentro
Literal *getLiteral(char *str);

#endif //SNAPPY_LITERAL_H
