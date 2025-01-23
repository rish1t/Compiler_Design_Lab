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

void to_upper(char *buf){
    for(int i=0; i<50;i++){
        if(buf[i] == '\0'){
            break;
        }
        if(buf[i] >= 'a' &&  buf[i] <= 'z'){
            buf[i] -= 32;
        }
    }
    printf("%s\n", buf);
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
            if (i >= sizeof(buf) - 1) {
                buf[i] = '\0';
                printf("Word too long, ignoring: %s\n", buf);
                i = 0;  
            }
        } else {
            
            if (i > 0) {
                buf[i] = '\0';
                if (is_keyword(buf)) {
                    to_upper(buf);
                }
                i = 0;
            }
        }
        
        ca = getc(fa);
    }


    fclose(fa);
    return 0;
}
