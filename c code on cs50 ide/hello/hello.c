#include <stdio.h>

int main(void)
{
    //get name
    printf("what is your name? ");
    char name[10];
    scanf("%s", name);
    //show name
    printf("hello, %s\n", name);
    return 0;
}