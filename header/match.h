//
// Created by Gilles on 12.12.2018.
//

#ifndef SNAPPY_MATCH_H
#define SNAPPY_MATCH_H

#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include "utilities.h"

//funzione che costruisce la codifica di un match in base ai parametri
void writeMatch(unsigned char length, unsigned short offset, FILE *fout);

#endif //SNAPPY_MATCH_H
