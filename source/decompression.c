//
// Created by Gilles on 07.11.2018.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//ci ho giocato un po' ma non fa ancora niente, questo metodo dovrebbe gestire l'interazione dei vari altri metodi
void decompress(FILE *fin, FILE *fout) {
    char *buffer;
    long filelen;

    fseek(fin, 0, SEEK_END);
    filelen = ftell(fin);
    rewind(fin);

    buffer = (char *)malloc((filelen+1)* sizeof(char));
    fread(buffer, filelen, 1, fin);
}

//Finora questo è l'unico metodo che funziona al 100%
unsigned long dim(unsigned long d){
    unsigned long c = d;
    int n = 0;
    //conto il nummero di byte usati nella codifica della dimensione
    while(c){
        n++;
        c = c >> 8;
    }
    unsigned long p = 0;
    //algoritmo per la trasformazione dei byte nella lunghezza del file
    for(int i = 0; i < n; i++){
        p = (p << 7) | ((d >> (i*8)) & 0x7F);
    }
    return p;
}

//Questo metodo assume che venga passato il numero di caratteri giusto, senza il byte con la lunghezza del literal e il tag;
char *literal(unsigned long x){
    char *str;
    unsigned long c = x;
    int n = 0;
    int p = 0;
    //conto quanti caratteri ci sono
    while(c){
        n++;
        c = c >> 8;
    }
    //applico una maschera 1111 1111 su ogni byte e lo concateno alla stringa di ritorno
    while(n){
        strcat(&str[p], (char *)(x & (0xFF << (8*(n-1-p)))));
    }
    return str;
}

char *oneMatch(unsigned int y){
    char *str;
    //applico una maschera 1110 0000 1111 1111 che prende gli 11 bit di offset
    unsigned int offset = y & 0xE0FF;
    //applico una maschera 0001 1100 0000 0000 per prendere la lunghezza del match
    unsigned char length = y & 0x1C00;
    return str;
}

char *twoMatch(unsigned long z){
    char *str;
    //applico una maschera 0000 0000 1111 1111 1111 1111 che prende i 2 byte di offset
    unsigned int offset = z & 0xFFFF;
    //applico una maschera 1111 1100 0000 0000 per prendere la lunghezza del match
    unsigned char length = z & 0xFC0000;
    return str;
}

/*in realtà non fa ancora niente, dovrei passarli lo stream e dovrebbe applicare una maschera
 * 0000 0011 ai byte che vengono passati per la lettura del tag e, a dipendenza del tag, chiamare
 * il metodo ad esso associato per le trasformazioni necessarie
 */
void tagRead(unsigned long c){
    int c1 = (int) c & 0x3;
    switch(c1) {
        case 0:
            /* al metodo literal dovrebbero essere passati solo i byte con i caratteri, il primo byte (con tag e lunghezza)
             * non serve
             */
            literal(c);
            break;
            /* ai metodi di match invece serve anche il primo byte visto che nel primo caso aiuta a
             * completare l'offset e nel secondo c'è la lunghezza del match
             */
        case 1:
            oneMatch(c);
            break;
        case 2:
            twoMatch(c);
            break;
        case 3:
            printf("4 byte match not permited!");
            break;
        default:
            break;
    }
}