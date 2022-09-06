#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //get name
    string name = get_string("what is your name? ");
    //show name
    printf("hello, %s\n", name);
}