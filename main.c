#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"

int main(int argc, char **argv) {
    FILE *fp;
    if (argc != 2) {
        fprintf(stderr, "Usage : %s fichier.pas\n", argv[0]);
        return 1;
    }
    fp = fopen(argv[1], "r");
    if (!fp) {
        perror(argv[1]);
        return 1;
    }
    lexer_init(fp);
    parse();
    fclose(fp);
    return 0;
}

