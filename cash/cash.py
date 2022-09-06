while True:
    try:
        moneyd = float(input("input: "))
    except:
        moneyd = float(input("input: "))
    if 0 < moneyd:
        break
money = int(round(moneyd * 100))
coin25 = money // 25
coin10 = (money % 25) // 10
coin5 = ((money % 25) % 10) // 5
coin1 = ((money % 25) % 10) % 5
print(f"{coin25 + coin10 + coin5 + coin1}")