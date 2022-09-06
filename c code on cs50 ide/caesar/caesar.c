#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>



int main(int argc, string argv[])
{
    //check input
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        for (int i = 0; argv[1][i] != '\0'; i++)
        {
            if (argv[1][i] < '0' || argv[1][i] > '9')
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
    }
    //input
    string text = get_string("enter text: ");
    int key = atoi(argv[argc - 1]);
    //codeing
    for (int i = 0; text[i] != '\0'; i++)
    {
        if ('a' <= text[i] && text[i] <= 'z')
        {
            text[i] = (text[i] + key - 97) % 26 + 97;
        }
        else if ('A' <= text[i] && text[i] <= 'Z')
        {
            text[i] = (text[i] + key - 65) % 26 + 65;
        }
    }
    //output
    printf("ciphertext: %s\n", text);
}