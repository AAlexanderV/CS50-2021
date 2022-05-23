from sys import argv
from crypt import crypt
import string

# inicialization?
word = ["","","","",""]
counter = 0
end_of_check = 'Z'
iterations = 0

salt = str(argv[1][0]+argv[1][1])
print (salt)
    
def encrypt ():
    global counter
    global word
    global iterations
    global salt
    for i in str (string.ascii_lowercase + string.ascii_uppercase):
        word [counter] = i
        iterations += 1
        if counter == 0:
            print(word[0], ", № of iterations: ", iterations)
        if counter < 4:
            counter += 1
            encrypt ()
        h = crypt (("".join(word)), salt)
        if argv[1] == h:
            print ("Password: ", ("".join(word)))
            print("№ of iterations: ", iterations)
            exit()
        if ("".join(word)) == end_of_check:
            print ("Matches not found.")
    word [counter] = ""
    counter -=1

if (len (argv) == 2) and len (argv[1]) == 13:
    print ("Searching...")
    encrypt ()
else:
    print ("Usage: python crack.py HASH") 
    