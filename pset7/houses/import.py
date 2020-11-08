import csv
import sys
#from cs50 import SQL
import sqlite3

def getCSV():
    if len(sys.argv) != 2:
        print('usage: import.py file.csv')
        sys.exit(1)

    return sys.argv[1]

def parseLines(ID, line):
    name = line['name'].split(' ')
    if len(name) == 3:
        first, middle, last = name
    else:
        first, last = name
        middle = None
    student_info = [ID, first, middle, last]
    student_info.append(line['house'])
    student_info.append(line['birth'])

    return student_info

def importData(filename):
    # Connect to database
    #db = SQL('sqlite:///students.db')
    con = sqlite3.connect('students.db')
    db = con.cursor()

    # Import data from csv into database
    with open(filename, 'r') as characters:
        reader = csv.DictReader(characters)
        ID = 0
        for row in reader:
            student = parseLines(ID, row)
            db.execute('INSERT INTO students (id, first, middle, last, house, birth) values(?, ?, ?, ?, ?, ?)', student)
            ID += 1

    con.commit()
    con.close()

def main():
    filename = getCSV()
    importData(filename)

if __name__ == "__main__":
    main()