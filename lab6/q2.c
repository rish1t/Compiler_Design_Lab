/*
S→UVW
U →(S) | aSb | d
V → aV | 𝜖
W → cW | 𝜖
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int curr = 0;
char str[100];

// declarations
void S();
void U();
void V();
void W();

// result functions
void invalid()
{
    printf("-----------------ERROR!----------------\n");
    exit(0);
}

void valid()
{
    printf("----------------SUCCESS!---------------\n");
    exit(0);
}

// functions for grammar rules
void S()
{
    U();
    V();
    W();
}

void U()
{
    if (str[curr] == '(')
    {
        curr++;
        S();
        if (str[curr] == ')')
        {
            curr++;
            return;
        }
        else
            invalid();
    }
    else if (str[curr] == 'a')
    {
        curr++;
        S();
        if (str[curr] == 'b')
        {
            curr++;
            return;
        }
        else
            invalid();
    }
    else if (str[curr] == 'd')
    {
        curr++;
        return;
    }
    else
    {
        invalid();
    }
}

void V()
{
    if (str[curr] == 'a')
    {
        curr++;
        V();
    }
}

void W()
{
    if (str[curr] == 'c')
    {
        curr++;
        W();
    }
}

int main()
{
    printf("Enter String: ");
    scanf("%s", str);
    S();
    if (str[curr] == '$')
        valid();
    else
    {
        printf("%c\n", str[curr]);
        invalid();
    }
}
