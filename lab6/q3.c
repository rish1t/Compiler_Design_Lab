/*
S → aAcBe
A → bA'
A' → bA' | ε
B → d
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int curr = 0;
char str[100];

void S();
void A();
void APrime();
void B();

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

// fucntions

void S()
{
    if (str[curr] == 'a')
    {
        curr++;
        A();
        if (str[curr] == 'c')
        {
            curr++;
            B();
            if (str[curr] == 'e')
            {
                curr++;
                return;
            }
            else
            {
                invalid();
            }
        }
        else
        {
            invalid();
        }
    }
    else
    {
        invalid();
    }
}

void A()
{
    if (str[curr] == 'b')
    {
        curr++;
        APrime();
    }
    else
    {
        invalid();
    }
}

void APrime()
{
    if (str[curr] == 'b')
    {
        curr++;
        APrime();
    }
}

void B(){
    if(str[curr] == 'd')
    {
        curr++;
        return;
    }
    else
    {
        invalid();
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
        printf("%c\n", str[curr]);
        invalid();
}