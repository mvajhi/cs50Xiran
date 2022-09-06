#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


int main (void)
{
    while (true)
    {
    string x = get_string("enter: ");
    if (atoi(x) == 235)
    {
        break;
    }
    int sum = 0;
    for (int i = 0; i < strlen(x); i++)
    {
        sum += (toupper(x[i]) - 'A');
    }
    printf("sum = %i\n", sum);
    }

}