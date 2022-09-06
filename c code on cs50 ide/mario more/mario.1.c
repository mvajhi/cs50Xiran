#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //get h
    int h = get_int("enter h: ");
    //print heram
    int i = 0;
    for(int x = 0;x < h; x++)
    {
        while(i < x)
        {
            printf("#");
            i++;
        }
        printf("\n");
    }
}
