#include <stdio.h>
#include <string.h>

const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if", "inline",
    "int", "long", "register", "restrict", "return", "short", "signed", "sizeof",
    "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile",
    "while", "_Bool", "_Complex", "_Imaginary"
};

#define NUM_KEYWORDS (sizeof(keywords) / sizeof(keywords[0]))

int is_keyword(const char *word) {
    for (int i = 0; i < NUM_KEYWORDS; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    FILE *fa;
    char ca, buf[50];
    int i = 0;
    
    fa = fopen("exq.c", "r");
    if (fa == NULL) {
        printf("Cannot open file \n");
        return 0;
    }
    
    ca = getc(fa);
    while (ca != EOF) {
        if ((ca >= 'a' && ca <= 'z') || (ca >= 'A' && ca <= 'Z') || (ca == '_')) {
            buf[i++] = ca;
        } else {
            if (i > 0) {
                buf[i] = '\0';
                if (is_keyword(buf)) {
                    continue;
                } else {
                    ca = getc(fa);
                    if(ca == '('){
                        
                    }
                }
                i = 0;
            }
        }
        
        ca = getc(fa);
    }


    fclose(fa);
    return 0;
}
