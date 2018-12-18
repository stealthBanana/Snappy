//
// Created by Gilles on 12.12.2018.
//

#include "../header/hashTable.h"

Node *createNode(char *str, int cursorPos, Node *next){
    Node *node = (Node*) malloc(sizeof(Node));
    strcpy(node->str, str);
    node->cursorPos = cursorPos;
    node->next = (Node*) calloc(sizeof(Node), sizeof(Node));
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
    unsigned int key = hash(node->str, table->size);
    if((int)table->list[key].str[0] == 0)
        memcpy(table->list+key, node, sizeof(Node));
    else{
        Node *dum = table->list+key;
        while(dum->next->str[0] != 0)
            memcpy(dum, dum->next, sizeof(Node));
        memcpy(dum->next, node, sizeof(Node));
    }
};

int searchAndUpdateMatch(Node *node, Table *table){
    unsigned int key = hash(node->str, table->size);
    Node *dum = table->list+key;
    if(memcmp(dum->str, node->str, 4) == 0) {
        int result = dum->cursorPos;
        dum->cursorPos = node->cursorPos;
        return result;
    }
    return -1;
};

void clearTable(Table *table){
    table->list = (Table*) realloc(table->list, sizeof(Node)*table->size);
};