from cs50 import get_string
from sys import argv

words = set()

def load(dictionary):
    """Load dictionary into memory, returning true if successful else false"""
    file = open(dictionary, "r")
    for line in file:
        words.add(line.rstrip("\n"))
        # words.append(line.rstrip("\n"))
    file.close()
    return True

def main():
    if len(argv) == 2:
        dictionary = argv[1]
        loaded = load (dictionary)
        if not loaded:
            print(f"Could not load {dictionary}.")
            exit(1)
        text = input("What message would you like to censor?\n")
        lst_text = text.split()
        censored = []
        for i in range (len(lst_text)):
            if lst_text[i].lower() in words:
                # for j in range(len(lst_text[i])):
                censored.append("*" * (len(lst_text[i])))
            else:
                censored.append(lst_text[i])
        print()
        print("Censored: ")
        print(" ".join(censored))
    else:
        print("Usage: python bleep.py dictionary")

if __name__ == "__main__":
    main()
    