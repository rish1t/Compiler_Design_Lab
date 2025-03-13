%{
#include<stdio.h>
int yywrap() { return 1; }
%}

%%
[a-zA-Z_][a-zA-Z0-9_]*   printf("Identifier: %s\n", yytext);
%%  


int main()
{
    char stat[20];
    printf("Enter a valid C statement: ");
    yylex();
    scanf("%s", stat);
    return 0;
}
