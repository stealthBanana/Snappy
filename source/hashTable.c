//
// Created by Gilles on 12.12.2018.
//

#include "../header/hashTable.h"

//questa funzione ritorna una struttura di tipo nodo in base ai parametri passati
Node *createNode(char *str, unsigned long cursorPos, Node *next, Table *table){
    Node *node = (Node *)malloc(sizeof(Node));
    strcpy(node->str, str);
    node->cursorPos = cursorPos;
    //calcolo l'hash già durante la creazione del nodo
    node->hash = hash(node->str, table->size);
    node->next = (Node*) calloc(sizeof(Node), sizeof(Node));
    return node;
}

//questa funzione ritorna un'hash-table della dimensione specificata dal parametro
Table *createTable(int size){
    Table *table;
    table = (Table*) malloc(sizeof(Table));
    table->size = size;
    table->list = (Node*) calloc(sizeof(Node), sizeof(Node)*(size-1));
    return table;
};

//funzione di hash dei 44 caratteri
unsigned int hash(unsigned char str[4], int tableSize){
    unsigned int intValueOfStr = 0;
    //prendo il valore in intero dei 4 caratteri
    for(int i = 1; i <= 4; i++)
        intValueOfStr = intValueOfStr | (str[i - 1] << (8 * abs(i - 4)));
    //riscrivo il valore in little-endian
    intValueOfStr = intToLittleEndian(intValueOfStr);
    //moltiplico il valore per un determinato numero
    unsigned long result = intValueOfStr * 0x1e35a7bd;
    //divido per 2 il numero fino a quando non diventa minore dell'indice massimo dell'hash-table
    while(result > tableSize)
        result = result >> 1;
    return (unsigned int)result;
};

//funzione che onserisce un nodo all'intero dell'hash-table
void insert(Node *node, Table *table){
    unsigned int key = node->hash;
    //controllo se il nodo alla posizione determinata dalla chiave di hassh èvuoto
    if((int)table->list[key].str[0] == 0)
        //inserisco il nodo
        memcpy(table->list+key, node, sizeof(Node));
    //se il nodo non è vuoto scorro la lista fino a trovare l'ultimo nodo
    else{
        Node *dum = table->list+key;
        while(dum->next->str[0] != 0)
            dum = dum->next;
        //inserisco il nodo all'ultima posizione
        dum->next = node;
    }
};

//funzione che controlla se esiste un match che corrisponde alla
// combinazione dei 4 caratteri del nodo passato come parametro.
//nel caso in cui esista ritona la posizione del cursore della combinazione
// e aggiorna la posizione del cursore
unsigned long searchAndUpdateMatch(Node *node, Table *table){
    unsigned int key = node->hash;
    Node *dum = table->list+key;
    //controllo se la prima posizione trovata è vuota
    while(dum->str[0] != 0) {
        //controllo se le combinazioni di caratteri del nodo corrispondono
        if (strcmp(dum->str, node->str) == 0) {
            unsigned long result = dum->cursorPos;
            dum->cursorPos = node->cursorPos;
            //ritorno la posizione del cursore della corrispondenza
            return result;
        }
        dum = dum->next;
    }
    //se non trovo una corrispondenza ritorno -1
    return (unsigned long)-1;
};

//funzione che resetta l'hash-table
void clearTable(Table *table){
    //scorro tutti gli indici e resetto la stringa della combinazione di caratteri
    for(int k = 0; k < table->size; k++) {
        if(table->list[k].str[0] != 0) {
            table->list[k].str[0] = 0;
            free(table->list[k].next);
        }
    }
};