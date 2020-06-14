from cs50 import get_string


def main():
    text = get_string("Text: ")

    # Count number of letters, words, and sentences
    letters = count_letters(text)
    words = count_words(text)
    sent = count_sent(text)

    # Avg number of letters/100 words
    L = letters * 100 / words

    # Avg number of sentences/100 words
    S = sent * 100 / words

    # Compute the Coleman-Liau index
    index = round(0.0588 * L - 0.296 * S - 15.8)

    # Output the reading level
    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print("Grade", index)


# Count number of letters in input


def count_letters(txt):
    count = 0
    for char in txt:
        if char.isalpha():
            count += 1
    return count

# Count number of words in input


def count_words(txt):
    count = 0

    for char in txt:
        if char.isspace():
            count += 1
    # Add last word
    count += 1

    return count

# Count number of sentences in input


def count_sent(txt):
    count = 0

    for char in txt:
        if char == "." or char == "!" or char == "?":
            count += 1

    return count


main()
