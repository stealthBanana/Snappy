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
void literal(FILE *, FILE *, unsigned long, unsigned int);
void printLiteral(unsigned long, FILE *);
unsigned int oneMatch(char, FILE *, FILE *);
unsigned int twoMatch(char, FILE *, FILE *);
unsigned int getLength(FILE *, unsigned int);
void decompress(FILE *, FILE *);




#endif //SNAPPY_DECOMPRESSION_H
