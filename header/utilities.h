//
// Created by Gilles on 12.12.2018.
//

#ifndef SNAPPY_UTILITIES_H
#define SNAPPY_UTILITIES_H

#include <stdio.h>

void printBytes(unsigned char *bytes, int size, FILE *fout);

unsigned int intToLittleEndian(unsigned int val);

#endif //SNAPPY_UTILITIES_H
