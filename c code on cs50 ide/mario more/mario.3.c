#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //get h
    int h = 0;
    while (h < 1 || h > 8)
    {
        h = get_int("enter h: ");
    }
    //print heram
    int i = 0;
    for (int x = 0; x < h; x++)
    {
        //fasele
        for (int j = 2; j <= h - i; j++)
        {
            printf(" ");
        }
        //hashtag
        for (i = 0; i <= x; i++)
        {
            printf("#");
        }
        printf("\n");
    }
}
