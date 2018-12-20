//
// Created by Gilles on 07.11.2018.
//
#include "../header/compression.h"

#define HASH_TABLE_SIZE 16385
#define WINDOW_SIZE 32000

//funzione che legge la dimensione del file da comprimere e la restituisce in varint
unsigned char *getSize(FILE *fin){
    //posiziono il cursore alla fine
    fseek(fin, 0, SEEK_END);
    unsigned int intValueOfSize = ftell(fin);
    //posiziono il cursore all'inizio
    fseek(fin, 0, SEEK_SET);
    //calcolo quanti bit servono per scrivere il numero della dimensione del file
    int numberOfBits = (int)log2(intValueOfSize)+1;
    //calcolo quanti byte servono per scrivere il numero della dimensione del file
    int numberOfBytes = ceil((double)numberOfBits/7);
    //istanzio un array di char lungo quanto i byte necessari per scrivere la  dimensione del file
    unsigned char *size;
    size = (unsigned char*) calloc(sizeof(char), sizeof(char)*numberOfBytes);
    //per ogni byte della dimensione del file scorro tutti i bit (i byte vengono letti al contrario)
    for(int i = 0; i < numberOfBytes; i++){
        for(int j = 0; j < 7; j++){
            int mask = 1 << i*8+j-i;
            size[i] = (unsigned char) ((size[i] - (char)(0)) | ((mask & intValueOfSize) >> (i*8-i)));
        }
        //setto il bit più significativo a 1 per ogni byte che non è l'ultimo
        size[i] = (unsigned char)((size[i] - (char) (0)) | 0x80);
    }
    //nell'ultimo byte setto il bit più significativo a 0
    size[numberOfBytes-1] = (unsigned char)((size[numberOfBytes-1] - (char) (0)) & 0x7f);
    return size;
}

void compress(FILE *fin, FILE *fout)
{
    //stampo la dimensione del file
    unsigned char *size = getSize(fin);
    fputs(size, fout);
    free(size);

    unsigned char *c = (unsigned char*) calloc(sizeof(char), sizeof(char));
    StringBuffer *str = createStringBuffer(4);
    StringBuffer *literalStr = createStringBuffer(64);
    Table *table = createTable(HASH_TABLE_SIZE);
    int cursorPos = 0;
    int matchPos = -1;
    int matchLength = 0;
    int matchOffset = 0;
    int matchCounter = 0;
    int writeMatchFlag = 0;
    c[0] = fgetc(fin);
    c[1] = 0;
    while((char)c[0] != EOF){

        put(str, c);
        put(literalStr, c);

        if(strlen(str->value) == 4) {
            Node *node = createNode(str->value, cursorPos, NULL, table);
            matchPos = searchAndUpdateMatch(node, table);

            //no match
            if (matchPos == -1) {
                insert(node, table);
                matchCounter = 0;
                writeMatchFlag = 1;
            }

            //match
            else {

                //primo match
                if(matchLength == 0) {
                    matchLength = 4;
                    matchOffset = cursorPos - matchPos;
                    matchCounter = 1;
                    unqueue(literalStr, 4);
                }

                //prossimo match consecutivo
                else if(matchLength > 0 && (cursorPos-matchPos-matchOffset+matchCounter-1) == 0){
                    matchLength++;
                    matchOffset++;
                    matchCounter++;
                    unqueue(literalStr, 1);
                }

                //prossimo match non consecutivo
                else{
                    matchCounter--;
                    writeMatchFlag = 1;
                }
            }

            cursorPos++;
        }

        //creo e scrivo il match
        if(writeMatchFlag && (matchLength != 0)){
            Match *match = getMatch(matchLength, matchOffset);
            printf("%d : %d\n", matchLength, matchOffset);
            printBytes(match->value, match->size, fout);
            matchLength = 0;
            matchOffset = 0;
        }
        writeMatchFlag = 0;

        //creo e scrivo il literal
        if((matchPos != -1 && strlen(literalStr->value) != 0) || strlen(literalStr->value) == literalStr->size){
            Literal *literal = getLiteral(literalStr->value);
            printf("%s\n", literal->value);
            printBytes(literal->value, literal->size, fout);
            clearStringBuffer(literalStr);
        }

        if((cursorPos % WINDOW_SIZE) == WINDOW_SIZE-1)
            clearTable(table);

        c[0] = fgetc(fin);
        c[1] = 0;
    }

    Literal *literal = getLiteral(literalStr->value);
    printBytes(literal->value, literal->size, fout);
    clearStringBuffer(literalStr);


    free(c);
    free(str);
    free(literalStr);

    fclose(fin);
    fclose(fout);
}