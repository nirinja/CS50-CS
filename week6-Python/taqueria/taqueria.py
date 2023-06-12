import re

menu = {
    "Baja Taco": 4.00,
    "Burrito": 7.50,
    "Bowl": 8.50,
    "Nachos": 11.00,
    "Quesadilla": 8.50,
    "Super Burrito": 8.50,
    "Super Quesadilla": 9.50,
    "Taco": 3.00,
    "Tortilla Salad": 8.00
}


def titlecase(s):
    return re.sub(r"[A-Za-z]+('[A-Za-z]+)?",
                  lambda mo: mo.group(0).capitalize(),
                  s)


total = 0

while True:
    try:
        item = input("Item: ")
    except EOFError:
        break
    # Process the user input here
    item = titlecase(item)
    if item in menu:
        total += menu[item]
        print(f"Total: ${total:.2f}")
