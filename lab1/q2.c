#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fptr1, *fptr2;
    char filename[100], c;
    long file_size;

    printf("Enter the filename to open for reading: \n");
    scanf("%s", filename);
    fptr1 = fopen(filename, "r");

    if (fptr1 == NULL)
    {
        printf("Cannot open file %s \n", filename);
        exit(0);
    }

    fseek(fptr1, 0, SEEK_END);
    file_size = ftell(fptr1);
    rewind(fptr1);

    printf("Enter the filename to open for writing: \n");
    scanf("%s", filename);
    fptr2 = fopen(filename, "w+");

    if (fptr2 == NULL)
    {
        printf("Cannot open file %s \n", filename);
        fclose(fptr1);
        exit(0);
    }

    printf("\nSize : %ld\n", file_size);

    for (long i = file_size - 1; i >= 0; i--)
    {
        fseek(fptr1, i, SEEK_SET);
        c = fgetc(fptr1);
        fputc(c, fptr2);
    }

    printf("\nContents copied backwards to %s", filename);

    fclose(fptr1);
    fclose(fptr2);

    return 0;
}
