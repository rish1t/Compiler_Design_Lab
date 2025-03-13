%{
int chars = 0;
int words = 0;
int lines = 0;
int blanks = 0;
%}

%%
[a-zA-Z]+ { words++; chars += strlen(yytext); }
[ \t]+ { blanks += strlen(yytext); }
\n { lines++; }
. { chars++; }
%%

int main()
{
    yylex();
    printf("lines:%d words:%d chars:%d blanks:%d\n", lines, words, chars, blanks); 
}

int yywrap()
{
    return 1;
}