#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    // Verify whether user provides exactly one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Validate key
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    printf("Success\n");

    // Number of positions for which char will be rotated
    int k = atoi(argv[1]);
    printf("%i\n", k);

    string plaintext = get_string("plaintext: ");
    int n = strlen(plaintext);

    char ciphertext[n];

    printf("ciphertext: ");

    for (int i = 0; i < n; i++)
    {
        // Rotate alphabetical chars by specified amount in key, preserving case
        if (isalpha(plaintext[i]))
        {
            int rotation = k % 26;

            // Preserve uppercase chars
            if (isupper(plaintext[i]))
            {
                if (plaintext[i] + rotation > 90)
                {
                    ciphertext[i] = 65 + rotation - (90 - plaintext[i]) - 1;
                }
                else
                {
                    ciphertext[i] = plaintext[i] + rotation;
                }
            }

            // Preserve lowercase chars
            else
            {
                if (plaintext[i] + rotation > 122)
                {
                    ciphertext[i] = 97 + rotation - (122 - plaintext[i]) - 1;
                }
                else
                {
                    ciphertext[i] = plaintext[i] + rotation;
                }
            }
            printf("%c", ciphertext[i]);
        }
        else
        {
            // Preserve original char
            ciphertext[i] = plaintext[i];
            printf("%c", ciphertext[i]);
        }
    }
    printf("\n");
}