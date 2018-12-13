//
// Created by Gilles on 07.11.2018.
//
#include "../header/compression.h"

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
    size = (char*)calloc(sizeof(char), sizeof(char)*numberOfBytes);
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

    unsigned char *c = calloc(sizeof(char), sizeof(char));
    StringBuffer *str = createStringBuffer(4);
    int cursorPos = 0;
    Table *table = createTable(16384);
    c[0] = fgetc(fin);
    c[1] = 0;
    while((char)c[0] != EOF){

        put(str, c);

        printf("%c",str->value[0]);

        /*if(strlen(str->value) != 4){

        }else {
            Node *node = createNode(str->value, cursorPos, NULL);
            int matchPos = searchAndUpdateMatch(*node, table);
            if (matchPos == -1)
                insert(*node, table);
        }*/

        if((cursorPos % 32000) == 31999)
            clearTable(table);

        cursorPos++;
        c[0] = fgetc(fin);
        c[1] = 0;
    }

    free(c);
    free(str);
    free(table);

    fclose(fin);
    fclose(fout);
}