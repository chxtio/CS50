import csv
import sys
from cs50 import SQL

def main():
    loadData()

def loadData():
    # Check command line arguments
    if len(sys.argv) != 2:
        print('usage: import.py file.csv')
        sys.exit(1)
    filename = sys.argv[1]

    # Connect to database
    db = SQL('sqlite:///students.db')

    # Import data from csv into database
    with open(filename, 'r') as characters:
        reader = csv.DictReader(characters)
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

if __name__ == "__main__":
    main()