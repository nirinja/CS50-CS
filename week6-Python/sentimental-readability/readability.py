import sys


def main():
    text = input("Text: ")
    words = 1
    sentences = letters = 0

    for char in text:
        if char.isalpha():
            letters += 1
        if (char == "." or char == "!" or char == "?") and text.index(char) != 0 and text[text.index(char) - 1].isalpha():
            sentences += 1
        if char.isspace():
            words += 1

    L = letters / words * 100.00
    S = sentences / words * 100.00
    index = 0.0588 * L - 0.296 * S - 15.8
    index = round(index)

    if index >= 16:
        print("Grade 16+")
    if index < 1:
        print("Before Grade 1")
    if index < 16 and index > 0:
        print(f"Grade {index}")


main()
