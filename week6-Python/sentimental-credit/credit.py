import sys


def main():
    number = get_input()
    if luhnsAlgorithm(number):
        output(number)
    else:
        print("INVALID")


def get_input():
    while True:
        try:
            n = int(input("Number: "))
            if n > 0:
                return n
        except ValueError:
            print("Not an integer")


def luhnsAlgorithm(number):
    sum1 = num = digits = sum2 = 0
    n = number
    while n > 0:
        num = ((n // 10) % 10) * 2
        while num > 0:
            digits = num % 10
            sum1 += digits
            num //= 10
        n //= 100

    digits = 0
    n = number
    while n > 0:
        digits = n % 10
        sum2 += digits
        n //= 100

    if ((sum1 + sum2) % 10) == 0:
        return True
    else:
        return False


def output(number):
    n = number // 10000000000000
    if n == 34 or n == 37:
        print("AMEX")

    n = number // 100000000000000
    if n > 50 and n < 56:
        print("MASTERCARD")

    n = number // (10 ** 12)
    if n == 4 or (n // (10 ** 3)) == 4:
        print("VISA")

    if n not in [34, 37] and not (50 < n < 56) and not (n == 4 and (n // 1000) == 4):
        print("INVALID")


main()
