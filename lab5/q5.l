%{
#include <stdio.h>
#include <stdlib.h>
int num;
%}

%%
[0-9]+ {
    num = atoi(yytext);
}
%%

int main() {
    yylex();
    printf("Number in HEX : #%x\n", num);
    return 0;
}

int yywrap() {
    return 1;
}
