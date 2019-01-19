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
    //leggo il tempo di partenza
    clock_t start, end;
    start = clock();

    //stampo la dimensione del file
    int size = getFileSize(fin);
    fputs(getSize(size), fout);

    //carattere che viene letto
    unsigned char *c = (unsigned char*) calloc(sizeof(char), sizeof(char));
    //buffer di 4 caratteri per la ricerca dei match
    StringBuffer *str = createStringBuffer(4);
    //hash-table
    Table *hash_table = createTable(HASH_TABLE_SIZE);
    //posizione del cursore relativa alla finestra
    unsigned long cursorPos = -3;
    //lunghezza del literal
    unsigned long literalLength = 0;
    //posizione del match all'interno dell'hash-table
    int matchPos = -1;
    //lunghezza del match
    int matchLength = 0;
    //offset del match
    int matchOffset = 0;
    //flag che indica se devo scrivere il match
    int writeMatchFlag = 0;
    //periodo in cui non devo scrivere i match
    int matchCountDown = 0;

    //leggo il primo carattere
    c[0] = fgetc(fin);
    c[1] = 0;

    while(1){

        //inserisco il carattere corrente nel buffer
        put(str, c);

        //se il file è finito esco dal ciclo
        if(feof(fin)){
            break;
        }

        printf("%d\t", literalLength);

        //controllo se il buffer dei caratteri è pieno
        if(strlen(str->value) == 4) {
            Node *node = createNode(str->value, cursorPos, NULL, hash_table);
            matchPos = searchAndUpdateMatch(node, hash_table);
            //no match
            if (matchPos == -1) {
                //inserisco il nodo
                insert(node, hash_table);
                literalLength++;
                //setto il flag per scrivere il match
                writeMatchFlag = 1;
            }
            //match
            else if(matchCountDown == 0){
            //else {
                //primo match
                if (matchLength == 0) {
                    matchLength = 4;
                    matchOffset = cursorPos - matchPos;
                }
                //prossimo match consecutivo
                else if (matchLength > 0 && (cursorPos - matchPos - matchOffset + matchLength - 4) == 0) {
                    matchLength++;
                    matchOffset++;
                }
                //prossimo match non consecutivo
                else {
                    //setto il flag per scrivere il match
                    writeMatchFlag = 1;
                }
            }
        }

        if(matchCountDown > 0)
            matchCountDown--;

        //scrivo il match
        if(writeMatchFlag && (matchLength != 0)){
            writeMatch(matchLength, matchOffset, fout);
            matchLength = 0;
            matchOffset = 0;
            matchCountDown = 3; //4 o 3 o 2 ? boH!!
            literalLength = -matchLength;
        }
        //resetto il flag per scrivere il match
        writeMatchFlag = 0;

        //scrivo il literal
        if((matchPos != -1 && literalLength != 0) || literalLength == pow(2, 33)){
            writeLiteral(literalLength, fin, fout);
            //imposto la lunghezza del literal a 0
            literalLength = 0;
        }

        //tra una finestra e l'altra svuoto l'hash-table e resetto il cursore
        if(cursorPos == WINDOW_SIZE-1) {
            clearTable(hash_table);
            cursorPos = 0;
        }

        //prendo il prossimo carattere
        c[0] = (char)fgetc(fin);
        c[1] = '\0';
        //incremento il cursore
        cursorPos++;
    }

    //controllo se è rimasto ancora qualcosa da scrivere
    if(literalLength != 0) {
        //scrivo gli ultimi caratteri
        writeLiteral(literalLength, fin, fout);
    }

    //leggo il tempo di fine
    end = clock();
    //calcolo il tempo in millisecondi
    unsigned long timeTakenms = (unsigned long)(((double)(end - start)/CLOCKS_PER_SEC)*1000);

    //scrivo il tempo impiegato
    //in millisecondi
    if(timeTakenms < 1000)
        printf("\n\nTempo impiegato: %lu ms\n", timeTakenms);
    //in secondi
    else{
        double timeTakens = (double)timeTakenms/1000;
        printf("\n\nTempo impiegato: %.3lf s\n", timeTakens);
    }

    unsigned long inSize = getFileSize(fin);
    unsigned long outSize = getFileSize(fout);
    //calcolo il rateo di compressione
    double compressionRateo = (double)outSize/inSize;
    printf("\nDimensioni: iniziale = %lu Byte\tcompresso = %lu Byte\t\n"
           "Rateo di compressione: %.2lf\n", inSize, outSize, compressionRateo);

}