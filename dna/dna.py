import csv
import sys


def main(argv):

    # TODO: Check for command-line usage
    if not len(argv) == 3:
        print("usage: python dna.py database.cav dna.txt")
        exit()
    # TODO: Read database file into a variable
    with open(argv[1], "r") as databasefile:
        reader = csv.reader(databasefile)
        for line in reader:
            break
        list = {}.fromkeys(line, 0)
        list.pop("name")
        #print(list)#

    # TODO: Read DNA sequence file into a variable
    with open(argv[2], 'r') as case:
        dna = case.readline()

    # TODO: Find longest match of each STR in DNA sequence
    listval = ['0']
    for dnacode in list:
        listval.append(str(longest_match(dna, dnacode)))

    # TODO: Check database for matching profiles
    with open(argv[1], "r") as databasefile:
        reader = csv.reader(databasefile)
        next(reader)
        for line in reader:
            j = int(1)
            k = int(0)
            find = bool(False)
            for i in range(len(list)):
                if line[j] == listval[j]:
                    k += 1
                j += 1
            if k == len(list):
                print(line[0])
                find = True
                break
        if not find:
            print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main(sys.argv)
# python dna.py databases/large.csv sequences/1.txt