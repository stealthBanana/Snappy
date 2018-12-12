//
// Created by Gilles on 12.12.2018.
//

#ifndef SNAPPY_HASHTABLE_H
#define SNAPPY_HASHTABLE_H

#include <stdlib.h>
#include <string.h>

typedef struct node{
    unsigned char str[4];
    int cursorPos;
    struct node *next;
}Node;

typedef struct table{
    int size;
    Node *list;
}Table;

unsigned int intToLittleEndian(unsigned int i);
void insert(Node node, Table *table);
unsigned int hash(unsigned char str[4], int tableSize);
int searchAndUpdateMatch(Node node, Table *table);
void clearTable(Table *table);

#endif //SNAPPY_HASHTABLE_H
