#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "parser.h"

static int tok;

static void erreur(const char *attendu) {
    fprintf(stderr, "Erreur syntaxique ligne %d : attendu %s, trouve '%s'\n",
            get_line(), attendu, token_name(tok));
    exit(1);
}

static void avancer_tok(void) {
    tok = next_token();
}

static void consommer(int t) {
    if (tok != t) {
        erreur(token_name(t));
    }
    avancer_tok();
}

static void facteur(void);
static void terme(void);
static void exp_simple(void);
static void expression(void);
static void instruction(void);

static void facteur(void) {
    if (tok == T_ID || tok == T_NB) {
        avancer_tok();
    } else if (tok == T_PO) {
        avancer_tok();
        exp_simple();
        consommer(T_PF);
    } else if (tok == T_NOT) {
        avancer_tok();
        facteur();
    } else {
        erreur("facteur");
    }
}

static void terme(void) {
    facteur();
    while (tok == T_OPMUL) {
        avancer_tok();
        facteur();
    }
}


static void exp_simple(void) {
    terme();
    while (tok == T_OPADD) {
        avancer_tok();
        terme();
    }
}
static void expression(void) {

    exp_simple();
    if (tok == T_OPREL) {

        avancer_tok();

        exp_simple();
    }

}

static void liste_id(void) {
    consommer(T_ID);
    while (tok == T_VIR) {
        avancer_tok();
        consommer(T_ID);
    }

}

static void type(void) {
    if (tok == T_INTEGER || tok == T_CHAR) {
        avancer_tok();
    } else {

        erreur("type");
    }
}

static void dcl(void) {
    while (tok == T_VAR) {
        avancer_tok();
        liste_id();

        consommer(T_DP);
        type();
        consommer(T_PV);
    }
}

static void instruction(void) {
    switch (tok) {
    case T_ID:
        avancer_tok();
        consommer(T_AFF);
        exp_simple();
        break;
    case T_IF:
        avancer_tok();
        expression();
        consommer(T_THEN);
        instruction();
        consommer(T_ELSE);
        instruction();
        break;
    case T_WHILE:
        avancer_tok();

        expression();
        consommer(T_DO);
        instruction();
        break;
    case T_READ:
    case T_READLN:
    case T_WRITE:
    case T_WRITELN:
        avancer_tok();
        consommer(T_PO);
        consommer(T_ID);
        consommer(T_PF);
        break;
    default:
        erreur("instruction");
    }
}

static void inst_composee(void) {
    consommer(T_BEGIN);
    if (tok != T_END) {
        instruction();
        while (tok == T_PV) {
            avancer_tok();
            instruction();
        }
    }
    consommer(T_END);
}

void parse(void) {
    avancer_tok();
    consommer(T_PROGRAM);
    consommer(T_ID);
    consommer(T_PV);
    dcl();
    inst_composee();
    consommer(T_PT);
    if (tok != T_EOF) {
        erreur("EOF");
    }
    printf("Analyse syntaxique reussie.\n");
}
