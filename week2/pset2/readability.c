#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

// Variables

int lettercount = 0;
int wordcount = 1;
int sentencecount = 0;

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{

    string text = get_string("Passage of text: ");

    // Function that counts each individual letter
    count_letters(text);

    // Function that counts the number of words
    count_words(text);

    // Function that counts the number of sentences
    count_sentences(text);

    // input L and S into the formula, have exceptions for 16+ and <1

    float L = (((float)lettercount / wordcount) * 100);
    float S = (((float)sentencecount / wordcount) * 100);
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 15)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}










// Counts all alphabetical characters

int count_letters(string text)
{
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            lettercount++;
        }
    }
    return lettercount;
}

// Counts all spaces (+1 for final word) to count words

int count_words(string text)
{
    for (int i = 0; i < strlen(text); i++)
    {
        if (isblank(text[i]))
        {
            wordcount++;
        }
    }
    return wordcount;
}

// Counts sentences with ? && . && !

int count_sentences(string text)
{
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '?')
        {
            sentencecount++;
        }
        else if (text[i] == '.')
        {
            sentencecount++;
        }
        else if (text[i] == '!')
        {
            sentencecount++;
        }
    }
    return sentencecount;
}

