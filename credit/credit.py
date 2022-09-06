from lib2to3.pgen2.token import LESSEQUAL
from operator import le


credit = input("input credit: ")
credit_len = len(credit)
credit_1first = int(credit[0])
credit_2first = int(credit[0] + credit[1])
sumnum = int(0)
buffer = int()
buffer2 = str()
for i in range(credit_len):
    #odd
    if i % 2 == 0:
        buffer = int(credit[credit_len - i - 1])
    #even
    else:
        buffer = int(credit[credit_len - i - 1]) * 2
        if buffer > 9:
            buffer2 = str(buffer)
            buffer = int(buffer2[0]) + int(buffer2[1])
    sumnum += buffer
sumnumfirst = sumnum % 10
if sumnumfirst != 0:
    print("INVALID")
    raise SystemExit

if (credit_2first == 34 or credit_2first == 37) and credit_len == 15:
    print("AMEX")
elif (credit_len == 13 or credit_len == 16) and credit_1first == 4:
    print("VISA")
elif 51 <= credit_2first <= 55 and credit_len == 16:
    print("MASTERCARD")
else:
    print("INVALID")