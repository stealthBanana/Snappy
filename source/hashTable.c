//
// Created by Gilles on 12.12.2018.
//

#include "../header/hashTable.h"

Node *createNode(char *str, int cursorPos, Node *next){
    Node *node = malloc(sizeof(Node));
    strcpy(node->str, str);
    node->cursorPos = cursorPos;
    node->next = calloc(sizeof(Node), sizeof(Node));
}

Table *createTable(int size){
    Table *table;
    table = malloc(sizeof(Table));
    table->size = size;
    table->list = calloc(sizeof(Node), sizeof(Node)*size);
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

void insert(Node node, Table *table){
    unsigned int key = hash(node.str, table->size);
    if((int)table->list[key].str[0] == 0)
        table->list[key] = node;
    else{
        Node dum = table->list[key];
        while(dum.next != NULL)
            dum = *dum.next;
        dum.next = &node;
    }
};

int searchAndUpdateMatch(Node node, Table *table){
    unsigned int key = hash(node.str, table->size);
    Node dum = table->list[key];
    do{
        if(strcmp(dum.str, node.str) == 0) {
            int result = dum.cursorPos;
            dum.cursorPos = node.cursorPos;
            return result;
        }
    }while(dum.next != NULL);
    return -1;
};

void clearTable(Table *table){
    table->list = realloc(table->list, sizeof(Node)*table->size);
};