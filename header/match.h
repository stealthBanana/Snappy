//
// Created by Gilles on 12.12.2018.
//

#ifndef SNAPPY_MATCH_H
#define SNAPPY_MATCH_H

#include <malloc.h>
#include <string.h>

typedef struct match{
    unsigned char *value;
    unsigned short size:2;
}Match;

//funzione che costruisce la codifica di un match in base ai parametri
Match *getMatch(unsigned char length, unsigned short offset);

#endif //SNAPPY_MATCH_H
