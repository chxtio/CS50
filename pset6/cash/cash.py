from cs50 import get_float

while True:
    change = get_float("Change owed: ")
    if change > 0:
        break

coins = 0
cents = int(change * 100)

# Add the number of quarters, dimes, and nickels to coins
for coin in [25, 10, 5]:
    coins += cents // coin
    cents %= coin
# Add pennies
coins += cents

print(coins)