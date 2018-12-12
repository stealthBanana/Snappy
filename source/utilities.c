//
// Created by Gilles on 12.12.2018.
//

#include "../header/utilities.h"

//funzione che serve a stampare in un file le strutture literal/match
void printBytes(unsigned char *bytes, int size, FILE *fout){
    for(int i = 0; i < size; i++)
        fputc(bytes[i], fout);
}

//funzione che prende un valore intero e lo trasforma in little-endian
unsigned int intToLittleEndian(unsigned int val){
    unsigned int result = 0;
    for(int i = 0; i < 32; i++)
        result = result | (((val & (1 << i)) >> i) << 31-i);
    return result;
};