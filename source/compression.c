//
// Created by Gilles on 07.11.2018.
//
#include "../header/compression.h"

#define HASH_TABLE_SIZE 32768
#define WINDOW_SIZE 65536

//funzione che legge la dimensione del file da comprimere e la restituisce in varint
unsigned char *getSize(int size){
    if(size != 0) {
        //calcolo quanti bit servono per scrivere il numero della dimensione del file
        int numberOfBits = (int) log2(size) + 1;
        //calcolo quanti byte servono per scrivere il numero della dimensione del file
        int numberOfBytes = ceil((double) numberOfBits / 7);
        //istanzio un array di char lungo quanto i byte necessari per scrivere la  dimensione del file
        unsigned char *value;
        value = (unsigned char *) calloc(sizeof(char), sizeof(char) * numberOfBytes);
        //per ogni byte della dimensione del file scorro tutti i bit (i byte vengono letti al contrario)
        for (int i = 0; i < numberOfBytes; i++) {
            for (int j = 0; j < 7; j++) {
                int mask = 1 << i * 8 + j - i;
                value[i] = (unsigned char) ((value[i] - (char) (0)) | ((mask & size) >> (i * 8 - i)));
            }
            //setto il bit più significativo a 1 per ogni byte che non è l'ultimo
            value[i] = (unsigned char) ((value[i] - (char) (0)) | 0x80);
        }
        //nell'ultimo byte setto il bit più significativo a 0
        value[numberOfBytes - 1] = (unsigned char) ((value[numberOfBytes - 1] - (char) (0)) & 0x7f);
        return value;
    } else
        return 0;
}

void compress(FILE *fin, FILE *fout)
{
    clock_t start, end;
    start = clock();

    //stampo la dimensione del file
    int size = getFileSize(fin);
    fputs(getSize(size), fout);

    unsigned char *c = (unsigned char*) calloc(sizeof(char), sizeof(char));
    StringBuffer *str = createStringBuffer(4);
    Table *table = createTable(HASH_TABLE_SIZE);
    unsigned long cursorPos = 0;
    unsigned long literalLength = 3;
    int matchPos = -1;
    int matchLength = 0;
    int matchOffset = 0;
    int writeMatchFlag = 0;
    int matchCountDown = 0;
    c[0] = fgetc(fin);
    c[1] = 0;

    while(1){

        put(str, c);

        if(feof(fin)){
            break;
        }

        if(strlen(str->value) == 4) {
            Node *node = createNode(str->value, cursorPos, NULL, table);
            matchPos = searchAndUpdateMatch(node, table);

            //no match
            if (matchPos == -1) {
                insert(node, table);
                literalLength++;
                writeMatchFlag = 1;
            }
            //match
            else if(matchCountDown == 0){
                //primo match
                if(matchLength == 0) {
                    matchLength = 4;
                    matchOffset = cursorPos - matchPos;
                }

                //prossimo match consecutivo
                else if(matchLength > 0 && (cursorPos-matchPos-matchOffset+matchLength-4) == 0){
                    matchLength++;
                    matchOffset++;
                }

                //prossimo match non consecutivo
                else{
                    writeMatchFlag = 1;
                }
            }
            else
                matchCountDown--;
            cursorPos++;
        }

        //creo e scrivo il match
        if(writeMatchFlag && (matchLength != 0)){
            writeMatch(matchLength, matchOffset, fout);
            //printf("%d\t%d\t%d\t%d\n", cursorPos, matchPos, matchLength, matchOffset);
            matchLength = 0;
            matchOffset = 0;
            matchCountDown = 4; //4 o 3 ? boH!!
        }
        writeMatchFlag = 0;

        //creo e scrivo il literal
        if((matchPos != -1 && literalLength != 0) || literalLength == pow(2, 33)){
            writeLiteral(literalLength, fin, fout);
            literalLength = 0;
        }

        if((cursorPos % WINDOW_SIZE) == WINDOW_SIZE-1) {
            clearTable(table);
            cursorPos = 0;
        }

        c[0] = fgetc(fin);
        c[1] = 0;
    }

    if(literalLength != 0) {
        writeLiteral(literalLength, fin, fout);
    }

    end = clock();
    unsigned long timeTaken = (unsigned long)(((double)(end - start)/CLOCKS_PER_SEC)*3600);
    printf("\n\nTempo impiegato: %lu ms\n", timeTaken);

    unsigned long inSize = getFileSize(fin);
    unsigned long outSize = getFileSize(fout);
    double compressionRateo = (double)outSize/inSize;
    printf("\nDimensioni: iniziale = %lu Byte\tcompresso = %lu Byte\t\n"
           "Rateo di compressione: %lf\n", inSize, outSize, compressionRateo);

    fclose(fin);
    fclose(fout);
}