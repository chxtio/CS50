import sys
from cs50 import SQL

def main():
    # Check command line arguments
    if len(sys.argv) != 2:
        print('usage: roster.py name_of_house')
        sys.exit(1)
    house = sys.argv[1]

    # Connect to database
    db = SQL('sqlite:///students.db')

    # Query database for all students in house
    roster = db.execute('SELECT first, middle, last, birth FROM students WHERE house = (?) ORDER BY last, first', house)

    # Print out students' full name and birth year
    for student in roster:
        if student['middle'] == None:
            print('{} {}, born {}'.format(student['first'], student['last'], student['birth']))
        else:
            print('{} {} {}, born {}'.format(student['first'], student['middle'], student['last'], student['birth']))

if __name__ == "__main__":
    main()