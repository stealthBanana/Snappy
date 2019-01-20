//
// Created by Gilles on 07.11.2018.
//

#ifndef SNAPPY_COMPRESSION_H
#define SNAPPY_COMPRESSION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <malloc.h>
#include <time.h>
#include "literal.h"
#include "match.h"
#include "hashTable.h"
#include "stringBuffer.h"
#include "utilities.h"

//funzione che prende la dimensione del file da comprimere come parametro e la restituisce in varint
unsigned char *getSize(int size);
//funzione che comprime il file di input nel file di output
void compress(FILE *fin, FILE *fout);

#endif //SNAPPY_COMPRESSION_H
