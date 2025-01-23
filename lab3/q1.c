#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void idarith(char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%') {
        printf("\nArithmetic operator: %c", c);
    }
}

void idrel(char c, FILE *fp) {
    char buf[3] = {0};
    int i = 0;
    if (c == '=' || c == '<' || c == '>' || c == '!') {
        buf[i++] = c;
        c = fgetc(fp);
        if (c == '=') {
            buf[i++] = c;
        }
        printf("\nRelational operator: %s", buf);
    }
}

void idlog(char c, FILE *fp) {
    char buf[3] = {0};
    int i = 0;
    if (c == '&' || c == '|') {
        buf[i++] = c;
        c = fgetc(fp);
        if (c == buf[i - 1]) {
            buf[i++] = c;
        }
        printf("\nLogical operator: %s", buf);
    }
}

void idkey(char *word) {
    char *keywords[] = {"int", "float", "double", "char", "if", "else", "while", "for", "return", "void"};
    for (int i = 0; i < 10; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            printf("\nKeyword: %s", word);
            return;
        }
    }
}

void idnum(char *word) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (!isdigit(word[i])) {
            return;  
        }
    }
    printf("\nNumerical constant: %s", word);
}

void idstr(char *word) {
    if (word[0] == '"' && word[strlen(word) - 1] == '"') {
        printf("\nString literal: %s", word);
    }
}

void idIdentifiers(char *word) {
    if (isalpha(word[0]) || word[0] == '_') {
        for (int i = 1; word[i] != '\0'; i++) {
            if (!isalnum(word[i]) && word[i] != '_') {
                return;  
            }
        }
        printf("\nIdentifier: %s", word);
    }
}

void idspecial(char c) {
    if (c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']' || c == ',' || c == ';' || c == '.' || c == ':') {
        printf("\nSpecial symbol: %c", c);
    }
}

int main() {
    char c, buf[100];
    FILE *fp = fopen("digit.c", "r");
    
    if (fp == NULL) {
        printf("Cannot open file \n");
        exit(0);
    }

    while ((c = fgetc(fp)) != EOF) {
        int i = 0;
        buf[0] = '\0';

        idarith(c);

        if (c == '=' || c == '<' || c == '>' || c == '!') {
            idrel(c, fp);
        }

        if (c == '&' || c == '|') {
            idlog(c, fp);
        }

        idspecial(c);

        if (c == '"') {
            buf[i++] = c;
            while ((c = fgetc(fp)) != '"' && c != EOF) {
                buf[i++] = c;
            }
            if (c == '"') {
                buf[i++] = c;
            }
            buf[i] = '\0';
            idstr(buf);
        }

        if (isalpha(c) || c == '_') {
            buf[i++] = c;
            while (isalnum(c = fgetc(fp)) || c == '_') {
                buf[i++] = c;
            }
            buf[i] = '\0';
            idkey(buf);
            idIdentifiers(buf);
        }

        if (isdigit(c)) {
            buf[i++] = c;
            while (isdigit(c = fgetc(fp))) {
                buf[i++] = c;
            }
            buf[i] = '\0';
            idnum(buf);
        }
    }

    fclose(fp);
    return 0;
}
