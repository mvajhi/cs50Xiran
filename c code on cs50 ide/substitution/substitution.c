#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>


int main(int argc, string argv[])
{
    //check input slot
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else
    {
        //input counter
        int j = 0;
        for (int i = 0; argv[1][i] != '\0'; i++)
        {
            if (('a' <= argv[1][i] && argv[1][i] <= 'z') || ('A' <= argv[1][i] && argv[1][i] <= 'Z'))
            {
                argv[1][i] = toupper(argv[1][i]);
                //check input not duplicate
                for (int k = 0; argv[1][k] != '\0'; k++)
                {
                    if (argv[1][k] == argv[1][i] && i != k)
                    {
                        printf("Usage: ./substitution key\n");
                        return 1;
                    }
                }
                //input counter
                j++;
            }
            else
            {
                printf("Usage: ./substitution key\n");
                return 1;
            }
        }
        //check input characters enough
        if (j != 26)
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
    }
    //input
    string text = get_string("enter text: ");
    //uncodeing
    for (int i = 0; text[i] != '\0'; i++)
    {
        if ('a' <= text[i] && text[i] <= 'z')
        {
            text[i] = argv[1][(text[i] - 97) % 26] + 32;
        }
        else if ('A' <= text[i] && text[i] <= 'Z')
        {
            text[i] = argv[1][(text[i] - 65) % 26];
        }
    }
    //output
    printf("ciphertext: %s\n", text);
}