#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>

enum {
    T_PROGRAM, T_VAR, T_INTEGER, T_CHAR, T_BEGIN, T_END, T_IF, T_THEN, T_ELSE,
    T_WHILE, T_DO, T_READ, T_READLN, T_WRITE, T_WRITELN, T_NOT,
    T_ID, T_NB, T_OPREL, T_OPADD, T_OPMUL,
    T_PV, T_PT, T_VIR, T_DP, T_AFF, T_PO, T_PF, T_EOF
};

void lexer_init(FILE *fp);
int next_token(void);
int get_line(void);
const char *token_name(int t);

#endif
