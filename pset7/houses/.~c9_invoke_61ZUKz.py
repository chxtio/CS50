import csv
from sys import argv, exit
from cs50 import SQL

def main():
    loadData()

def loadData():
    if len(argv) != 2:
        print('missing command line argument')
        exit(1)
    importData(argv[1])

def importData(fileName):
    # Connect to database
    db = SQL('sqlite:///students.db')
    with open(fileName, 'r') as f:
        reader = csv.DictReader(f)
        ID = 0
        for row in reader:
            name = row['name'].split(' ')
            if len(name) == 3:
                first, middle, last = name
            else:
                first, last = name
                middle = None
            db.execute('INSERT INTO students (id, first, middle, last, house, birth) values(?, ?, ?, ?, ?, ?)', ID, first, middle, last, row['house'], row['birth'])
            ID += 1

main()
