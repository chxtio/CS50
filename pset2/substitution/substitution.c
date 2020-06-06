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
        printf("Usage: ./substitution key\n");
        return 1;
    }

    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Check whether key contains exactly 26 alphabetic chars (ignore case)
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }

    // Verify whether key is comprised of distinct chars
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (argv[1][i] == argv[1][j])
            {
                printf("Key must contain 26 characters.\n");
                return 1;
            }
        }
    }

    // Character mapping for encrypting message
    string key = argv[1];

    string plaintext = get_string("plaintext: ");
    int n = strlen(plaintext);

    char ciphertext[n];

    printf("ciphertext: ");

    for (int i = 0; i < n; i++)
    {
        // Substitute alphabetical chars as specified by key mapping
        if (isalpha(plaintext[i]))
        {
            // Preserve uppercase chars
            if (isupper(plaintext[i]))
            {
                ciphertext[i] = toupper(key[(int)plaintext[i] - 65]);
            }
            // Preserve lowercase chars
            else
            {
                ciphertext[i] = tolower(key[(int)plaintext[i] - 97]);
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