%{
#include <stdio.h>
#include <string.h>
int positive_integers = 0;
int negative_integers = 0;
int positive_floats = 0;
int negative_floats = 0;
%}

%%
[1-9][0-9]*      { positive_integers++; }  
-[1-9][0-9]*     { negative_integers++; }  
[0-9]+\.[0-9]+   { positive_floats++; }    
-[0-9]+\.[0-9]+  { negative_floats++; }    
%%

int main() {
    yylex();
    printf("Positive Integers: %d\n", positive_integers);
    printf("Negative Integers: %d\n", negative_integers);
    printf("Positive Floats: %d\n", positive_floats);
    printf("Negative Floats: %d\n", negative_floats);
    return 0;
}

int yywrap() {
    return 1;
}
