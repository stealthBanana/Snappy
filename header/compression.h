//
// Created by Gilles on 07.11.2018.
//

#ifndef SNAPPY_COMPRESSION_H
#define SNAPPY_COMPRESSION_H

#include <rpcndr.h>
#include <stdio.h>

void compress(char inputFile[], char outputFile[]);
char getLength(FILE in);

#endif //SNAPPY_COMPRESSION_H
