import sys
import random
from pyfiglet import Figlet

figlet = Figlet()

fonts = figlet.getFonts()
fname = random.choice(fonts)

if len(sys.argv) == 1:
    pass
elif len(sys.argv) == 3 and sys.argv[1] in ["-f", "--font"] and sys.argv[2] in fonts:
    fname = sys.argv[2]
else:
    sys.exit("Invalid usage")

figlet.setFont(font=fname)

# Get input from user
text = input("input: ")

# Output text in selected font
print("output: ")
print(figlet.renderText(text))
