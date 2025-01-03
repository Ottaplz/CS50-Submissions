def main():

    # Get a string of text
    text = input("Text: ")

    # Count total letters
    lettercount = count_letters(text)

    # Count total words
    wordcount = count_words(text)

    # Count total sentences
    sentencecount = count_sentences(text)

    # Input results in CL formula to determine grade level
    L = (lettercount / wordcount) * 100
    S = (sentencecount / wordcount) * 100
    index = round(0.0588 * L - 0.296 * S - 15.8)

    # Print out grade level
    print_index(index)

# Count total letters in the text


def count_letters(text):
    letters = 0
    for n in text:
        if n.isalpha() == True:
            letters += 1
    return letters

# Count total words in the text + 1


def count_words(text):
    spaces = 1
    for n in text:
        if n.isspace() == True:
            spaces += 1
    return spaces

# Count total sentences in the text


def count_sentences(text):
    sentences = 0
    for n in text:
        if n == ".":
            sentences += 1
        elif n == "?":
            sentences += 1
        elif n == "!":
            sentences += 1

    return sentences

# Print Grade level based on formula result


def print_index(index):
    if index < 1:
        print("Before Grade 1")
    elif index > 15:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


main()