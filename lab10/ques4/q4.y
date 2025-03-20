%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int yylex(void);
void yyerror(const char *s);
%}

%token NUMBER
%token PLUS MINUS MUL DIV POW NEG
%token NL

%%
input:
      /* empty */
    | input line
    ;

line:
      NL
    | exp NL { printf("Result: %d\n", $1); }
    ;

exp:
      NUMBER                        { $$ = $1; }
    | exp exp PLUS                { $$ = $1 + $2; }
    | exp exp MINUS               { $$ = $1 - $2; }
    | exp exp MUL                 { $$ = $1 * $2; }
    | exp exp DIV { 
            if ($2 == 0) { yyerror("Division by zero"); $$ = 0; }
            else { $$ = $1 / $2; } 
      }
    | exp exp POW                 { $$ = (int) pow($1, $2); }
    | exp NEG                     { $$ = -$1; }
    ;
    
%%

int main(void) {
    printf("Enter postfix expressions:\n");
    yyparse();
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}