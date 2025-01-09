#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fptr1, *fptr2, *fptr3;
    char filename[100], c1, c2;

    // Open first file for reading
    printf("Enter the filename to open for reading: \n");
    scanf("%s", filename);
    fptr1 = fopen(filename, "r");
    if (fptr1 == NULL)
    {
        printf("Cannot open file %s \n", filename);
        exit(0);
    }

    // Open second file for reading
    printf("Enter the second filename to open for reading: \n");
    scanf("%s", filename);
    fptr2 = fopen(filename, "r");
    if (fptr2 == NULL)
    {
        printf("Cannot open file %s \n", filename);
        fclose(fptr1);
        exit(0);
    }

    // Open output file for writing
    printf("Enter the filename to open for writing: \n");
    scanf("%s", filename);
    fptr3 = fopen(filename, "w");
    if (fptr3 == NULL)
    {
        printf("Cannot open file %s \n", filename);
        fclose(fptr1);
        fclose(fptr2);
        exit(0);
    }

    while (1)
    {
        c1 = fgetc(fptr1);
        while (c1 != '\n' && c1 != EOF)
        {
            fputc(c1, fptr3);
            c1 = fgetc(fptr1);
        }
        fputc('\n', fptr3); 

        c2 = fgetc(fptr2);
        while (c2 != '\n' && c2 != EOF)
        {
            fputc(c2, fptr3);
            c2 = fgetc(fptr2);
        }
        fputc('\n', fptr3);
        if(c1 == EOF || c2 == EOF){
            break;
        }
    }

    // Close all files
    fclose(fptr1);
    fclose(fptr2);
    fclose(fptr3);

    return 0;
}