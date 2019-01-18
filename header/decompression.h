//
// Created by Gilles on 07.11.2018.
//

#ifndef SNAPPY_DECOMPRESSION_H
#define SNAPPY_DECOMPRESSION_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "utilities.h"

unsigned long dim(unsigned long);
unsigned long inv(unsigned long);
void literal(unsigned long, FILE *);
void oneMatch(unsigned int, unsigned int, FILE *);
void twoMatch(unsigned int, unsigned int, FILE *);
void decompress(FILE *, FILE *);




#endif //SNAPPY_DECOMPRESSION_H
