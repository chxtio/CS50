import csv
from sys import argv, exit
from cs50 import get_string

#from csv import reader, DictReader

if len(argv) != 3:
    print("missing command-line arguments")
    exit(0)

# Read csv file into a list
with open(argv[1], "r") as file:
    reader = list(csv.reader(file))
    reader[0].remove("name")
    strList = reader[0]

# Read DNA sequence from text file
with open(argv[2], "r") as sequence:
    dna = sequence.read()

# Compute longest run of consecutive repeats in DNA sequence
counts = []
notFound = True

for STR in strList:
    maxRepeat = 0

    # Search for STR matches within sequence
    for i in range(len(dna) - len(STR)):
        count = 0
        if dna[i: i + len(STR)] == STR:
            count += 1
            i += len(STR)
            while dna[i: i + len(STR)] == STR:
                count += 1
                i += len(STR)
            if count > maxRepeat:
                maxRepeat = count
    counts.append(maxRepeat)

# For each person, check if each STR count matches
with open(argv[1], "r") as people:
    reader = list(csv.reader(people))
    for line in reader:
        match = 0
        # Ignore first line of csv file
        if line[0] == "name":
            continue
        # Compare STR counts against sequence
        for i in range(len(line)):
            # Ignore name
            if i == 0:
                continue
            if int(line[i]) == int(counts[i - 1]):
                match += 1
        # Print out name of matching individuals (if any)
        if match == len(counts):
            print(line[0])
            notFound = False
if bool(notFound):
    print("No match")