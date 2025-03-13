%{
#include <stdio.h>

int scanf_count = 0;
int printf_count = 0;
%}

%%

"scanf"    { 
    printf("READ");
    scanf_count++; 
}

"printf"   { 
    printf("WRITE");
    printf_count++; 
}

.|\n { 
    putchar(yytext[0]); 
}

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

    printf("\nTotal number of scanf: %d\n", scanf_count);
    printf("Total number of printf: %d\n", printf_count);

    fclose(file);

    return 0;
}

int yywrap() {
    return 1;
}
