#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float dollars;

    do
    {
        dollars = get_float("Change owed: ");
    }
    while (dollars < 0);

    int cents = round(dollars * 100); //convert dollars to cents rounded to nearest penny

    int minCoins = 0;
    minCoins += cents / 25; //Add quarters
    cents = cents % 25; //leftover change

    minCoins += cents / 10; //Add dimes
    cents = cents % 10; //leftover change

    minCoins += cents / 5; //Add nickels
    cents = cents % 5; //leftover change

    minCoins += cents; //Add pennies

    printf("%i\n", minCoins);
}