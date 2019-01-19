//
// Created by Gilles on 12.12.2018.
//

#include "../header/hashTable.h"

Node *createNode(char *str, unsigned long cursorPos, Node *next, Table *table){
    Node *node = (Node *)malloc(sizeof(Node));
    strcpy(node->str, str);
    node->cursorPos = cursorPos;
    node->hash = hash(node->str, table->size);
    node->next = (Node*) calloc(sizeof(Node), sizeof(Node));
    return node;
}

Table *createTable(int size){
    Table *table;
    table = (Table*) malloc(sizeof(Table));
    table->size = size;
    table->list = (Node*) calloc(sizeof(Node), sizeof(Node)*(size-1));
    return table;
};

unsigned int hash(unsigned char str[4], int tableSize){
    unsigned int intValueOfStr = 0;
    for(int i = 1; i <= 4; i++)
        intValueOfStr = intValueOfStr | (str[i - 1] << (8 * abs(i - 4)));
    intValueOfStr = intToLittleEndian(intValueOfStr);
    unsigned long result = intValueOfStr * 0x1e35a7bd;
    while(result > tableSize)
        result = result >> 1;
    return (unsigned int)result;
};

void insert(Node *node, Table *table){
    unsigned int key = node->hash;
    if((int)table->list[key].str[0] == 0)
        memcpy(table->list+key, node, sizeof(Node));
    else{
        Node *dum = table->list+key;
        while(dum->next->str[0] != 0)
            dum = dum->next;
        dum->next = node;
    }
};

unsigned long searchAndUpdateMatch(Node *node, Table *table){
    unsigned int key = node->hash;
    Node *dum = table->list+key;
    while(dum->str[0] != 0) {
        if (strcmp(dum->str, node->str) == 0) {
            unsigned long result = dum->cursorPos;
            dum->cursorPos = node->cursorPos;
            return result;
        }
        dum = dum->next;
    }
    return (unsigned long)-1;
};

void clearTable(Table *table){
    for(int k = 0; k < table->size; k++) {
        if(table->list[k].str[0] != 0) {
            table->list[k].str[0] = 0;
            free(table->list[k].next);
        }
    }
};