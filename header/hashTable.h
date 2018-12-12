//
// Created by Gilles on 12.12.2018.
//

#ifndef SNAPPY_HASHTABLE_H
#define SNAPPY_HASHTABLE_H

#include "../source/compression.c"

void insert(Literal literal);
int hash(Literal literal);
Literal *searchMatch(Literal literal);

#endif //SNAPPY_HASHTABLE_H
