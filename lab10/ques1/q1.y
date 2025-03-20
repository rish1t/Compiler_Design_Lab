%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
int yyerror(const char *);
%}

/* Define a union to store token values */
%union {
    char *sval;
}

%token TYPE SC CM NL
%token <sval> ID

%%
stmt: DC NL
    ;
DC: DT IDL SC { printf("Valid declaration statement!\n"); exit(0); }
    ;
DT: TYPE
    ;
IDL: ID
    | ID CM IDL 
    ;

%%
int yyerror(const char *msg) {
    printf("Invalid declaration statement!\n");
    exit(0);
}

int main() {
    printf("Enter the declaration statement:\n");
    yyparse();
    return 0;
}