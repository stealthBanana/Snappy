#include <stdio.h>
#include <string.h>
#include "../header/compression.h"
#include "../header/decompression.h"

void main(int argc, char *argv[]) {

    //2 arguments
    if(argc == 4){
        FILE *fin, *fout;
        //check if file esxists
        if((fin = fopen(argv[2], "rb")) && (fout = fopen(argv[3], "wb"))) {

            //COMPRESS
            if (strcmp(argv[1], "-c") == 0) {
                compress(fin, fout);

            //DECOMPRESS
            } else if (strcmp(argv[1], "-d") == 0) {
                decompress(fin, fout);
            } else {
                printf("Comando non valevole");
            }
        }else{
            //Se non riesco ad aprire il file
        }
        fclose(fin);
        fclose(fout);

    //1 argument
    }else if(argc == 2){
        //HELP
        if(strcmp(argv[1], "-h") == 0){
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