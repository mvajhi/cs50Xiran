#include <stdio.h>
#include <cs50.h>
#include <math.h>

int number_character(string paragraph);
int number_word(string paragraph);
int number_sentence(string paragraph);
int calculat_grade(int number_characters, int number_words, int number_sentences);

int main(void)
{
    string paragraph = get_string("enter paragraph: ");

    int number_characters = number_character(paragraph);
    int number_words = number_word(paragraph);
    int number_sentences = number_sentence(paragraph);
    int grade = calculat_grade(number_characters, number_words, number_sentences);

    //printf("characters:%i\nwords:%i\nsentence:%i\n", number_characters, number_words, number_sentences);

    if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", (int)round(grade));
    }
    printf("ch %i\nword %i\nsen %i\n", number_characters, number_words, number_sentences);
}


//count character
int number_character(string paragraph)
{
    //counter
    int j = 0;

    for (int i = 0; paragraph [i] != '\0'; i++)
    {
        char pi = paragraph [i];
        if (('a' <= paragraph [i] && paragraph [i] <= 'z') || ('A' <= paragraph [i] && paragraph [i] <= 'Z'))
        {
            j++;
        }
    }

    return j;
}

//count word
int number_word(string paragraph)
{
    //counter
    int j = 1;

    for (int i = 0; paragraph [i] != '\0'; i++)
    {
        if (paragraph [i] == ' ')
        {
            j++;
        }
    }

    return j;

}

//count sentence
int number_sentence(string paragraph)
{
    //counter
    int j = 0;

    for (int i = 0; paragraph [i] != '\0'; i++)
    {
        if (paragraph [i] == '!' || paragraph [i] == '?' || paragraph [i] == '.')
        {
            j++;
        }
    }

    return j;
}

//calculat grad
int calculat_grade(int number_characters, int number_words, int number_sentences)
{
    //c/w
    float L = (100 / (float) number_words) * (float) number_characters;
    //s/w
    float S = (100 / (float) number_words) * (float) number_sentences;
    int grade = round(0.0588 * L - 0.296 * S - 15.8);

    return grade;
}
