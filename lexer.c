#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "lexer.h"

const char *noms[] = {
    "program", "var", "integer", "char", "begin", "end", "if", "then", "else",
    "while", "do", "read", "readln", "write", "writeln", "not",
    "id", "nb", "oprel", "opadd", "opmul",
    ";", ".", ",", ":", ":=", "(", ")", "EOF"
};

FILE *f;
int ch;
int line = 1;
char lexeme[64];

void avancer(void) {
    ch = fgetc(f);
    if (ch == '\n') {
        line = line + 1;
    }
}

void lexer_init(FILE *fp) {
    f = fp;
    avancer();
}

int get_line(void) {
    return line;
}

const char *token_name(int t) {
    return noms[t];
}

int next_token(void) {
    int i, k, prev;

    while (1) {
        while (isspace(ch)) {
            avancer();
        }
        if (ch != '(') {
            break;
        }
        avancer();
        if (ch != '*') {
            return T_PO;
        }
        avancer();
        prev = 0;
        while (ch != EOF && !(prev == '*' && ch == ')')) {
            prev = ch;
            avancer();
        }
        if (ch == EOF) {
            fprintf(stderr, "Erreur : commentaire non ferme\n");
            exit(1);
        }
        avancer();
    }

    if (ch == EOF) {
        return T_EOF;
    }

    if (isalpha(ch)) {
        i = 0;
        while (isalnum(ch) && i < 63) {
            lexeme[i] = ch;
            i = i + 1;
            avancer();
        }
        lexeme[i] = '\0';
        for (k = T_PROGRAM; k <= T_NOT; k = k + 1) {
            if (strcmp(lexeme, noms[k]) == 0) {
                return k;
            }
        }
        return T_ID;
    }

    if (isdigit(ch)) {
        while (isdigit(ch)) {
            avancer();
        }
        return T_NB;
    }

    if (ch == ';') { avancer(); return T_PV; }
    if (ch == '.') { avancer(); return T_PT; }
    if (ch == ',') { avancer(); return T_VIR; }
    if (ch == ')') { avancer(); return T_PF; }
    if (ch == '=') { avancer(); return T_OPREL; }
    if (ch == '+') { avancer(); return T_OPADD; }
    if (ch == '-') { avancer(); return T_OPADD; }
    if (ch == '*') { avancer(); return T_OPMUL; }
    if (ch == '/') { avancer(); return T_OPMUL; }
    if (ch == '%') { avancer(); return T_OPMUL; }

    if (ch == ':') {
        avancer();
        if (ch == '=') {
            avancer();
            return T_AFF;
        }
        return T_DP;
    }

    if (ch == '<') {
        avancer();
        if (ch == '>' || ch == '=') {
            avancer();
        }
        return T_OPREL;
    }

    if (ch == '>') {
        avancer();
        if (ch == '=') {
            avancer();
        }
        return T_OPREL;
    }

    if (ch == '|') {
        avancer();
        if (ch == '|') {
            avancer();
            return T_OPADD;
        }
    }

    if (ch == '&') {
        avancer();
        if (ch == '&') {
            avancer();
            return T_OPMUL;
        }
    }

    fprintf(stderr, "Erreur lexicale ligne %d\n", line);
    exit(1);
}
