#include <stdio.h>
#include <string.h>
#include "../header/compression.h"
#include "../header/decompression.h"

void main(int argc, char *argv[]) {
    if(argc == 2){
        if(strcmp(argv[0], "-c") == 0) {
            compress(argv[1], argv[2]);
        }else if(strcmp(argv[0], "-d") == 0) {
            decompress(argv[1], argv[2]);
        }else{
            printf("Comando non valevole");
        }
    }else if(argc == 1){
        if(strcmp(argv[0], "-h") == 0){
            printf("Utilizzo: [opzione] [input file] [output file]\n\n"
                   "opzioni:\n"
                   "-c\tcomprime il file di input nel file di output\n"
                   "-d\tdecomprime il file di input nel file di output\n\n"
                   "codice sorgente: https://github.com/stealthBanana/Snappy.git\n"
                   "Autori: Manuel Grgic & Gilles Oldano\n\n");
        }else{
            printf("Argomenti non validi, per saperne di piu inserire l'opzione \"-h\"");
        }
    }else{
        printf("Argomenti non validi, per saperne di piu inserire l'opzione \"-h\"");
    }
}