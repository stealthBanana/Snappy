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
#include "literal.h"
#include "match.h"
#include "hashTable.h"
#include "stringBuffer.h"
#include "utilities.h"

unsigned char *getSize(FILE *fin);
void compress(FILE *fin, FILE *fout);

#endif //SNAPPY_COMPRESSION_H
