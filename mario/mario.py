while True:
    try:
        x = int(input("input: "))
    except:
        x = int(input("input: "))
    if 0 < x < 9:
        x = int(x)
        break

for i in range(x):
    print(" " * (x - i - 1) + "#" * (i + 1) + "  " + "#" * (i + 1))
