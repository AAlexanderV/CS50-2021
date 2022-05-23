from sys import argv
from crypt import crypt
import string

if len(argv) == 2 and argv[1].isalpha():
    key = []
    for i in argv[1]:
        key.append(int(ord(i.upper())-ord('A')))
    plaintext = input("Plaintext: ")
    ciphertext = []
    k = 0
    
    for i in range (len(plaintext)):
        if ord ("a") <= ord(plaintext[i]) <= ord ("z"): 
            ciphertext.append(chr((((ord(plaintext[i]) + key[k]) - ord ("a")) % 26) + ord ("a")))
            k = (k + 1) % len(key)
        elif ord ("A") <= ord(plaintext[i]) <= ord ("Z"): 
            ciphertext.append(chr((((ord(plaintext[i]) + key[k]) - ord ("A")) % 26) + ord ("A")))
            k = (k + 1) % len(key)
        else:
            ciphertext.append(plaintext[i])
    print(("".join(ciphertext)))
else:
    print("Usage: python vigenere.py k")