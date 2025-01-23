
#include <stdio.h>
int main()
{
    FILE *fa, *fb;
    char ca, cb;
    fa = fopen("exq.c", "r");
    if (fa == NULL)
    {
        printf("Cannot open file \n");
        return 0;
    }
    fb = fopen("q1op.c", "w");
    ca = getc(fa);
    while (ca != EOF)
    {
        if (ca == ' ')
        {
            putc(ca, fb);
            while (ca == ' ')
                ca = getc(fa);
        }
        if (ca == '\t')
        {
            cb = ' ';
            putc(cb, fb);
        }
        else
            putc(ca, fb);
        ca = getc(fa);
    }
    fclose(fa);
    fclose(fb);
    return 0;
}