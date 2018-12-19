//
// Created by Gilles on 07.11.2018.
//

#ifndef SNAPPY_DECOMPRESSION_H
#define SNAPPY_DECOMPRESSION_H

#include <stdio.h>

void decompress(FILE, FILE);
unsigned long dim(unsigned long);
char *literal(unsigned long);

#endif //SNAPPY_DECOMPRESSION_H
