text = input("enter text: ")
word = len(text.split())
sentence = text.count('.') + text.count('!') + text.count('?')
character = int(0)
for i in text: character += i.isalpha()
L = character * 100 / word
S = sentence * 100 / word
Grade = round(0.0588 * L - 0.296 * S - 15.8)
if (Grade > 16):
    print("Grade 16+")
elif (Grade < 1):
    print("Before Grade 1")
else:
    print("Grade " + str(Grade))