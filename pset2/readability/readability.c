#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int count_letters(string input);
int count_words(string input);
int count_sent(string input);

int main(void)
{
    string text = get_string("Text: ");

    int letters = count_letters(text), words = count_words(text), sent = count_sent(text);

    // Avg. number of letters/100 words
    float L = (float)(letters * 100) / words;

    // Avg. number of sentences/100 words
    float S = (float)(sent * 100) / words;

    // Compute the Coleman-Liau index
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    // Output the reading level
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

// Counts the number of letters in input
int count_letters(string input)
{
    int count = 0;

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (isalpha(input[i]))
        {
            count++;
        }
    }

    return count;
}

// Counts the number of words in input
int count_words(string input)
{
    int count = 0;

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (isspace(input[i]))
        {
            count++;
        }
    }

    //add last word
    count++;

    return count;
}

// Counts the number of sentences in input
int count_sent(string input)
{
    int count = 0;

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        char c = input[i];

        if (c == 33 || c == 46 || c == 63)
        {
            count++;
        }
    }

    return count;
}