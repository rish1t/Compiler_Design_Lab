#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_TOKENS 1024
#define MAX_SYMBOLS 256

// Structure for tokens (as provided)
struct token {
    char lexeme[64];
    int row, col;
    char type[30];
};

// Structure for symbol table entries
struct symbol {
    int index;
    char name[64];
    char type[30];
    int size;
};

int row = 1, col = 1;

// getNextToken function (as provided)
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
            const char *keywords[] = {"for", "if", "else", "while", "do", "break", "continue",
                                        "return", "int", "double", "float", "char", "long", "short",
                                        "sizeof", "typedef", "switch", "case", "struct", "const",
                                        "void", "exit"};
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

int getSizeForType(const char *type) {
    if (strcmp(type, "int") == 0)
        return 4;
    else if (strcmp(type, "char") == 0)
        return 1;
    else if (strcmp(type, "float") == 0)
        return 4;
    else if (strcmp(type, "double") == 0)
        return 8;
    else if (strcmp(type, "long") == 0)
        return 8; 
    else if (strcmp(type, "short") == 0)
        return 2;
    else
        return 0;
}

int main() {
    FILE *fin = fopen("digit.c", "r");
    if (!fin) {
        printf("Error opening file.\n");
        return 1;
    }

    struct symbol symTable[MAX_SYMBOLS];
    int symCount = 1;

    int inDeclaration = 0;
    char currentType[30] = "";

    struct token t;
    while ((t = getNextToken(fin)).row != -1) {

        // printf("<%s, %d, %d, %s>\n", t.type, t.row, t.col, t.lexeme);

        // If a type keyword (for data declaration) is found, start a declaration
        if (strcmp(t.type, "Keyword") == 0 &&
            (strcmp(t.lexeme, "int") == 0 || strcmp(t.lexeme, "char") == 0 ||
             strcmp(t.lexeme, "float") == 0 || strcmp(t.lexeme, "double") == 0 ||
             strcmp(t.lexeme, "long") == 0 || strcmp(t.lexeme, "short") == 0)) {
            inDeclaration = 1;
            strcpy(currentType, t.lexeme);
            continue;
        }

        // If we are inside a declaration, look for identifiers
        if (inDeclaration) {
            if (strcmp(t.type, "Identifier") == 0) {
                // Check if this identifier is already in the symbol table.
                int exists = 0;
                for (int i = 0; i < symCount; i++) {
                    if (strcmp(symTable[i].name, t.lexeme) == 0) {
                        exists = 1;
                        break;
                    }
                }
                if (!exists && symCount < MAX_SYMBOLS) {
                    symTable[symCount].index = symCount;
                    strcpy(symTable[symCount].name, t.lexeme);
                    strcpy(symTable[symCount].type, currentType);
                    symTable[symCount].size = getSizeForType(currentType);
                    symCount++;
                }
            }
            // If we hit a semicolon, end the current declaration
            if (strcmp(t.lexeme, ";") == 0) {
                inDeclaration = 0;
                currentType[0] = '\0';
            }
        }
    }

    fclose(fin);

    // Print the symbol table
    printf("\nSymbol Table:\n");
    printf("Index\tName\tType\tSize\n");
    printf("-----\t----\t----\t----\n");
    for (int i = 0; i < symCount; i++) {
        printf("%d\t%s\t%s\t%d\n", symTable[i].index, symTable[i].name,
               symTable[i].type, symTable[i].size);
    }
    return 0;
}
