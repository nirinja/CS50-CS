from cs50 import get_int

input = input("Greeting:")
input = input.lower()

if input[0] == "h":
    if "hello" in input:
        print("$0")
    else:
        print("$20")
else:
    print("$100")
