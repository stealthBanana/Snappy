//
// Created by Gilles on 12.12.2018.
//

#ifndef SNAPPY_HASHTABLE_H
#define SNAPPY_HASHTABLE_H

#include <stdlib.h>
#include <string.h>
#include "utilities.h"

//struttura dei nodi contenuti nell'hash-table
typedef struct node{
    //combinazione di 4 caratteri
    unsigned char str[5];
    //posizione del cursore in cui si trova la combinazione
    unsigned long cursorPos;
    //hash della combinazione
    unsigned int hash;
    struct node *next;
}Node;

//struttura dell'hash-table
typedef struct table{
    int size;
    Node *list;
}Table;

Node * createNode(char str[4], unsigned long cursorPos, Node *next, Table *table);
Table *createTable(int size);
void insert(Node *node, Table *table);
unsigned int hash(unsigned char str[4], int tableSize);
unsigned long searchAndUpdateMatch(Node *node, Table *table);
void clearTable(Table *table);

#endif //SNAPPY_HASHTABLE_H
