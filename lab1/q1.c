#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fptr1;
    int ccount = 0, lcount = 0;
    char filename[100], c;

    printf("Enter the filename to open for reading: \n");
    scanf("%s", filename);

    fptr1 = fopen(filename, "r");

    if (fptr1 == NULL)
    {
        printf("Cannot open file %s \n", filename);
        exit(0);
    }

    c = fgetc(fptr1);
    while (c != EOF)
    {
        ccount++;
        if (c == '\n')
        {
            lcount++;
        }
        c = fgetc(fptr1);  // Move to the next chraacter
    }
	lcount++;

    printf("Characters : %d\nLines : %d\n", ccount, lcount);
	fclose(fptr1);

    return 0;
}
