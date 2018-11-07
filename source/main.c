#include <stdio.h>
#include <string.h>
#include "../header/compression.h"
#include "../header/decompression.h"

int main(int argc, char *argv[]) {
    if(argc == 2){
        if(strcmp(argv[0], "-c") == 0) {
            compress(argv[1], argv[2]);
        }else if(strcmp(argv[0], "-c") == 0) {
            decompress(argv[1], argv[2]);
        }else{
            printf("Comando non valevole");
        }
    }
    return 0;
}