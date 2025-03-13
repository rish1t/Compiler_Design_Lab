/*
S → a | > | ( T )
T → S T'
T' → , S T' | ε
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int curr = 0;
char str[100];


void S();
void T();
void TPrime();

// result fucn

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
        return;
    }
    else if (str[curr] == '>')
    {
        curr++;
        return;
    }
    else if (str[curr] == '(')
    {
        curr++;
        T();
        if (str[curr] == ')')
        {
            curr++;
            return;
        }
        else
            invalid();
    }
    else
    {
        invalid();
    }
}

void T(){
    S();
    TPrime();
}

void TPrime(){
    if(str[curr] == ','){
        curr++;
        S();
        TPrime();
    }
}

