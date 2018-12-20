//
// Created by Gilles on 12.12.2018.
//

#ifndef SNAPPY_LITERAL_H
#define SNAPPY_LITERAL_H

#include <malloc.h>
#include <string.h>

#include <stdio.h>

typedef struct literal{
    unsigned char *value;
    unsigned int size:7;
}Literal;

//funzione che costruisce la codifica di un literal in base alla stringa passata come paramentro
Literal *getLiteral(unsigned char *str);

#endif //SNAPPY_LITERAL_H
