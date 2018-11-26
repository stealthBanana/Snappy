//
// Created by Gilles on 07.11.2018.
//

#ifndef SNAPPY_COMPRESSION_H
#define SNAPPY_COMPRESSION_H

#include <stdio.h>

void compress(FILE *fin, FILE *fout);
char getLength(FILE *fin);

#endif //SNAPPY_COMPRESSION_H
