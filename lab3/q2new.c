#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_TOKENS 1024

struct token {
    char lexeme[64];
    int row, col;
    char type[30];
};

int row = 1, col = 1;

struct token getNextToken(FILE *fin) {
    struct token t;
    t.row = -1;
    char c;
    while ((c = getc(fin)) != EOF) {
        if (c == '\n') { row++; col = 1; continue; }
        if (isspace(c)) { col++; continue; }
        if (c == '/') {
            int next = getc(fin);
            if (next == '/') {
                while ((c = getc(fin)) != EOF && c != '\n') col++;
                if (c == '\n') { row++; col = 1; }
                continue;
            } else if (next == '*') {
                int prev = 0;
                while ((c = getc(fin)) != EOF) {
                    col++;
                    if (c == '\n') { row++; col = 1; }
                    if (prev == '*' && c == '/') break;
                    prev = c;
                }
                continue;
            } else {
                ungetc(next, fin);
                t.row = row; t.col = col;
                t.lexeme[0] = '/'; t.lexeme[1] = '\0';
                strcpy(t.type, "Operator");
                col++;
                return t;
            }
        }
        char specialSymbols[] = {'#', '?', ';', ':', ',', '(', ')', '{', '}', '.'};
        int isSpecial = 0;
        for (int i = 0; i < sizeof(specialSymbols)/sizeof(char); i++) {
            if (c == specialSymbols[i]) { isSpecial = 1; break; }
        }
        if (isSpecial) {
            t.row = row; t.col = col;
            t.lexeme[0] = c; t.lexeme[1] = '\0';
            strcpy(t.type, "Special");
            col++;
            return t;
        }

        if (c == '-' || c == '+' || c == '*' || c == '%') {
            int startCol = col, startRow = row;
            char op[3] = {c, '\0', '\0'};
            int next = getc(fin);
            if (next == '=' || ((c == '+' || c == '-') && next == c)) {
                op[1] = next; op[2] = '\0';
                col += 2;
            } else {
                ungetc(next, fin);
                col++;
            }
            t.row = startRow; t.col = startCol;
            strcpy(t.lexeme, op);
            strcpy(t.type, "Operator");
            return t;
        }
        if (c == '=' || c == '<' || c == '>' || c == '!') {
            int startCol = col, startRow = row;
            char op[3] = {c, '\0', '\0'};
            int next = getc(fin);
            if (next == '=') {
                op[1] = '='; op[2] = '\0';
                col += 2;
            } else {
                ungetc(next, fin);
                col++;
            }
            t.row = startRow; t.col = startCol;
            strcpy(t.lexeme, op);
            strcpy(t.type, "Operator");
            return t;
        }
        if (isdigit(c)) {
            int startCol = col, startRow = row;
            char num[64];
            int i = 0;
            num[i++] = c;
            col++;
            while ((c = getc(fin)) != EOF && isdigit(c)) {
                num[i++] = c;
                col++;
            }
            num[i] = '\0';
            if (c != EOF) { ungetc(c, fin); col--; }
            t.row = startRow; t.col = startCol;
            strcpy(t.lexeme, num);
            strcpy(t.type, "Number");
            return t;
        }
        if (isalpha(c) || c == '_') {
            int startCol = col, startRow = row;
            char ident[64];
            int i = 0;
            ident[i++] = c;
            col++;
            while ((c = getc(fin)) != EOF && (isalnum(c) || c == '_')) {
                ident[i++] = c;
                col++;
            }
            ident[i] = '\0';
            if (c != EOF) { ungetc(c, fin); col--; }
            t.row = startRow; t.col = startCol;
            strcpy(t.lexeme, ident);
            const char *keywords[] = {"for", "if", "else", "while", "do", "break", "continue", "return", "int", "double", "float", "char", "long", "short", "sizeof", "typedef", "switch", "case", "struct", "const", "void", "exit"};
            int isKeyword = 0;
            for (int j = 0; j < sizeof(keywords)/sizeof(keywords[0]); j++) {
                if (strcmp(ident, keywords[j]) == 0) { isKeyword = 1; break; }
            }
            if (isKeyword) strcpy(t.type, "Keyword");
            else strcpy(t.type, "Identifier");
            return t;
        }
        if (c == '"') {
            int startCol = col, startRow = row;
            char strLit[64];
            int i = 0;
            strLit[i++] = c;
            col++;
            while ((c = getc(fin)) != EOF && c != '"') {
                strLit[i++] = c;
                col++;
            }
            if (c == '"') { strLit[i++] = c; col++; }
            strLit[i] = '\0';
            t.row = startRow; t.col = startCol;
            strcpy(t.lexeme, strLit);
            strcpy(t.type, "StringLiteral");
            return t;
        }
        col++;
    }
    t.row = -1;
    return t;
}

int main() {
    FILE *fin = fopen("digit.c", "r");
    if (!fin) { printf("Error opening file.\n"); return 1; }
    struct token tokens[MAX_TOKENS];
    int count = 0;
    struct token t;
    while ((t = getNextToken(fin)).row != -1 && count < MAX_TOKENS)
        tokens[count++] = t;
    for (int i = 0; i < count; i++)
        printf("%d. <%s, %d, %d, %s>\n", i + 1, tokens[i].type, tokens[i].row, tokens[i].col, tokens[i].lexeme);
    fclose(fin);
    return 0;
}
