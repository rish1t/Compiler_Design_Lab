%{
#include "q4.tab.h"
#include <stdlib.h>
%}

%%
[0-9]+        { yylval = atoi(yytext); return NUMBER; }
[ \t]         { /* Skip whitespace */ }
"\n"          { return NL; }
"+"           { return PLUS; }
"-"           { return MINUS; }
"*"           { return MUL; }
"/"           { return DIV; }
"^"           { return POW; }
"n"           { return NEG; }
.             { printf("Unexpected character: %s\n", yytext); }
%%

int yywrap(void) {
    return 1;
}