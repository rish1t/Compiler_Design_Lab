%{
#include <stdio.h>
#include <stdlib.h>
int yylex(void);
void yyerror(const char *s);
%}

%token NUMBER

%left '+' '-'
%left '*' '/'

%%
input:
      /* empty */
    | input line
    ;

line:
      '\n'
    | expression '\n' { printf("Result: %d\n", $1); }
    ;

expression:
      expression '+' expression { $$ = $1 + $3; }
    | expression '-' expression { $$ = $1 - $3; }
    | expression '*' expression { $$ = $1 * $3; }
    | expression '/' expression { 
          if ($3 == 0) { yyerror("Division by zero"); $$ = 0; }
          else { $$ = $1 / $3; } 
      }
    | '(' expression ')'         { $$ = $2; }
    | NUMBER                     { $$ = $1; }
    ;
    
%%

int main(void) {
    printf("Enter an arithmetic expression:\n");
    yyparse();
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}