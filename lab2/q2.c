
#include <stdio.h>
#include <stdlib.h>
int main()
{
    FILE *fa, *fb;
    char ca, cb;
    int flag = 1;
    fa = fopen("exq.c", "r");
    if (fa == NULL)
    {
        printf("Cannot open file \n");
        return 0;
    }
    fb = fopen("q2op.c", "w");
    ca = getc(fa);
    while (ca != EOF)
    {
        if (ca == '#' && flag)
        {
            while (ca != '\n')
            {
                ca = getc(fa);
            }
        }
        if (ca == '{')
        {
            flag = 0;
            putc(ca, fb);
            ca = getc(fa);
        }
        else
        {
            putc(ca, fb);
            ca = getc(fa);
        }
    }
    fclose(fa);
    fclose(fb);
    return 0;
}