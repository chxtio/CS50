from cs50 import get_int

# Prompt user for valid height
while True:
    n = get_int("Height: ")

    if 1 <= n <= 8:
        break;

# Create a half-pyramid using hashes
for i in range(n):
    print(" " * (n - i - 1), end="")
    print("#" * (i + 1))

