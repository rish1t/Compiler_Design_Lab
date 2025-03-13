%{
#include <stdio.h>
#include <ctype.h>
int vowels = 0;
int consonants = 0;
int yywrap() { return 1; }
%}

%%
[aeiouAEIOU] { vowels++; }
[bBcCdDfFgGhHjJkKlLmMnNpPqQrRsStTvVwWxXyYzZ] { consonants++; }
%%

int main() {
    yylex(); 
    printf("Vowels: %d\n", vowels);
    printf("Consonants: %d\n", consonants);
    return 0;
}
