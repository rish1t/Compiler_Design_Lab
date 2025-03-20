%{
#include "q3.tab.h"
#include <stdlib.h>
%}

%%
[0-9]+         { yylval = atoi(yytext); return NUMBER; }
[ \t]          { /* Skip whitespace */ }
\n             { return '\n'; }
"("            { return '('; }
")"            { return ')'; }
"+"            { return '+'; }
"-"            { return '-'; }
"*"            { return '*'; }
"/"            { return '/'; }
.              { printf("Unexpected character: %s\n", yytext); }
%%

int yywrap(void) {
    return 1;
}