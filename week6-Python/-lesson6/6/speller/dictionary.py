# Words in dictionary
words = set()


def check(word):
    """Return true if word is in dictionary else false"""
    if word.lower() in words:
        return True
    else:
        return False


def load(dictionary):
    """Load dictionary into memory, returning true if successful else false"""
    file = open(dictionary, "r")
    for line in file:
        word = line.rstrip() #rstrip, the trailing new line is removed from the added word.
        words.add(word)
    file.close()
    return True


def size():
    """Returns number of words in dictionary if loaded else 0 if not yet loaded"""
    return len(words)


def unload():
    """Unloads dictionary from memory, returning true if successful else false"""
    #unload only needs to return True because Python handles memory management on its own.
    return True

# """-are used to define docstrings,
# which are documentation strings that describe what a function, module, or class does.