change = float (input("Change: "))
counter = 0
while change >= 0.25:
    change = round ((change - 0.25),2)
    counter += 1
while change >= 0.1:
    change = round ((change - 0.1),2)
    counter += 1
while change >= 0.05:
    change = round ((change - 0.05),2)
    counter += 1
while change >= 0.01:
    change = round ((change - 0.01),2)
    counter += 1

print("", counter)