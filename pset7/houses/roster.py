import sys
#from cs50 import SQL
import sqlite3

def main():
    # Check command line arguments
    if len(sys.argv) != 2:
        print('usage: roster.py name_of_house')
        sys.exit(1)
    house = sys.argv[1]

    # Connect to database
    #db = SQL('sqlite:///students.db')
    con = sqlite3.connect('students.db')
    db = con.cursor()

    # Query database for all students in house
    db.execute('SELECT first, middle, last, birth FROM students WHERE house = (?) ORDER BY last, first', (house,))
    roster = db.fetchall()

    # Print out students' full name and birth year
    for student in roster:
        if student[1] == None:
            print('{} {}, born {}'.format(student[0], student[2], student[3]))
        else:
            print('{} {} {}, born {}'.format(student[0], student[1], student[2], student[3]))

    con.close()

if __name__ == "__main__":
    main()
