#include <cs50.h>
#include <stdio.h>

int main(void)
{

    long digits = get_long("Number: ");

    int sum = 0;
    int other = 0;
    int count = 0;

    long number = digits;

    while (number != 0)
    {
        other += number % 10;

        number /= 10;
        count++;

        if (number != 0)
        {
            sum += (number % 10) * 2 % 10;
            sum += (number % 10) * 2 / 10;
            number /= 10;
            count++;
        }
    }

    other += sum;

    if (other % 10 == 0)
    {
        if (count == 15)
        {
            if (digits / 10000000000000 == 34 || digits / 10000000000000 == 37)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (count == 16)
        {
            digits /= 100000000000000;
            if (digits / 10 == 4)
            {
                printf("VISA\n");
            }
            else if (50 < digits && 56 > digits)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (count == 13)
        {
            if (digits / 1000000000000 == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}