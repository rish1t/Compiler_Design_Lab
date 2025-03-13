%{
#include <stdio.h>
#include <string.h>
#include <ctype.h> 
%}

%%
"//".*\n {  printf("%s", yytext); }
[A-Z] { 
    printf("%c", tolower(yytext[0])); 
}
.|\n { printf("%s", yytext); }
%%

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }

    yyin = file;

    yylex();

    fclose(file);

    return 0;
}

int yywrap() {
    return 1;
}
