#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct token {
    char lexeme[64];
    int row, col;
    char type[30];
};

static int row = 1, col = 1;
char specialsymbols[] = {'?', ';', ':', ',', '(', ')', '{', '}', '.'};
char *Keywords[] = {"for", "if", "else", "while", "do", "break", "continue", "return", "int", "double", "float", "char", 
                    "long", "short", "sizeof", "typedef", "switch", "case", "struct", "const", "void", "exit"};
char arithmeticsymbols[] = {'*','+','-','/', '%'};

int isKeyword(char *str) {
    for (int i = 0; i < sizeof(Keywords) / sizeof(char *); i++) {
        if (strcmp(str, Keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int charBelongsTo(int c, char *arr, int len) {
    for (int i = 0; i < len; i++) {
        if (c == arr[i])
            return 1;
    }
    return 0;
}

void fillToken(struct token *tkn, char c, int row, int col, char *type) {
    tkn->row = row;
    tkn->col = col;
    strcpy(tkn->type, type);
    tkn->lexeme[0] = c;
    tkn->lexeme[1] = '\0';
}

void newLine() {
    ++row;
    col = 1;
}

struct token getNextToken(FILE *fin) {
    int c, d;
    struct token tkn = {.row = -1};
    int gotToken = 0;

    while (!gotToken && (c = getc(fin)) != EOF) {

        if (c == '/') {
            d = getc(fin);
            if (d == '/') {  
                while ((c = getc(fin)) != EOF && c != '\n') {
                    ++col;
                }
                if (c == '\n') {
                    newLine();  
                }
                continue;
            } else if (d == '*') {  
                do {
                    if (c == '\n') {
                        newLine();  
                    }
                    while ((c = getc(fin)) != EOF && c != '*') {
                        ++col;
                    }
                    if (c == '*') {
                        d = getc(fin);
                    }
                } while (c != EOF && d != '/');
                continue;
            } else {
                fseek(fin, -1, SEEK_CUR);  
                --col;  
            }
        }

        if (c == '\n') {
            newLine();  
            continue;
        }

        if (charBelongsTo(c, specialsymbols, sizeof(specialsymbols) / sizeof(char))) {
            fillToken(&tkn, c, row, col, (char[]){c, '\0'});
            gotToken = 1;
            ++col;
        }

        else if (charBelongsTo(c, arithmeticsymbols, sizeof(arithmeticsymbols) / sizeof(char))) {
            d = getc(fin);
            if (d == '=' || (c == '+' || c == '-') && d == c) {
                fillToken(&tkn, c, row, col, (char[]){c, c == '=' ? '=' : '\0', '\0'});
                col += 2;
            } else {
                fillToken(&tkn, c, row, col, (char[]){c, '\0'});
                ++col;
                fseek(fin, -1, SEEK_CUR);
            }
            gotToken = 1;
        }

        else if (c == '=' || c == '<' || c == '>' || c == '!') {
            d = getc(fin);
            if (d == '=') {
                fillToken(&tkn, c, row, col, (char[]){c, '=', '\0'});
                col += 2;
            } else {
                fillToken(&tkn, c, row, col, (char[]){c, '\0'});
                ++col;
                fseek(fin, -1, SEEK_CUR);
            }
            gotToken = 1;
        }

        else if (isdigit(c)) {
            tkn.row = row;
            tkn.col = col++;
            tkn.lexeme[0] = c;
            int k = 1;
            while ((c = getc(fin)) != EOF && isdigit(c)) {
                tkn.lexeme[k++] = c;
                ++col;
            }
            tkn.lexeme[k] = '\0';
            strcpy(tkn.type, "Number");
            gotToken = 1;
            fseek(fin, -1, SEEK_CUR);
        }

        else if (isspace(c)) {
            if (c == '\n') {
                newLine();  
            } else {
                ++col;  
            }
            continue;
        }

        else if (isalpha(c) || c == '_') {
            tkn.row = row;
            tkn.col = col++;
            tkn.lexeme[0] = c;
            int k = 1;
            while ((c = getc(fin)) != EOF && isalnum(c)) {
                tkn.lexeme[k++] = c;
                ++col;
            }
            tkn.lexeme[k] = '\0';
            strcpy(tkn.type, isKeyword(tkn.lexeme) ? "Keyword" : "Identifier");
            gotToken = 1;
            fseek(fin, -1, SEEK_CUR);
        }

        else if (c == '"') {
            tkn.row = row;
            tkn.col = col;
            strcpy(tkn.type, "StringLiteral");
            int k = 1;
            tkn.lexeme[0] = '"';
            while ((c = getc(fin)) != EOF && c != '"') {
                tkn.lexeme[k++] = c;
                ++col;
            }
            tkn.lexeme[k] = '"';
            gotToken = 1;
        }

        else {
            ++col;
        }
    }
    return tkn;
}
