//
// Created by Gilles on 12.12.2018.
//

#ifndef SNAPPY_LITERAL_H
#define SNAPPY_LITERAL_H

#include <malloc.h>
#include <string.h>
#include <math.h>
#include "utilities.h"

//funzione che costruisce la codifica di un literal in base alla stringa passata come paramentro
// e la scrive nel file di output
void writeLiteral(unsigned long literalLength, FILE *fin, FILE *fout);

#endif //SNAPPY_LITERAL_H
