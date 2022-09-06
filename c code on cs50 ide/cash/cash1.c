#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int cash = -1;
    int counter = 0;
    //check right enter
    while (cash < 0)
    {
        cash = get_int("cash: ");
    }
    //25
    while (cash >= 25)
    {
        cash = cash - 25;
        counter++;
    }
    //10
    while (cash >= 10)
    {
        cash = cash - 10;
        counter++;
    }
    //5
    while (cash >= 5)
    {
        cash = cash - 5;
        counter++;
    }
    //1
    while (cash >= 1)
    {
        cash = cash - 1;
        counter++;
    }
    printf("%i\n", counter);
}

