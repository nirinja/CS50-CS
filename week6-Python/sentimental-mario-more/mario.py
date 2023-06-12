import sys


def main():
    h = get_height()
    while h == 9:
        h = get_height()
    for i in range(1, h+1):
        print((h - i) * " ", end="")
        print(i * "#", end="")
        print("  ", end="")
        print(i * "#")


def get_height():
    while True:
        try:
            n = int(input("Height: "))
            if n > 0:
                return n
        except ValueError:
            print("Not an integer")


main()
