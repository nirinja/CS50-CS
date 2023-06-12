import sqlite3
import csv

# Connect to the database
conn = sqlite3.connect('roster.db')
c = conn.cursor()

# Insert data into students table
with open('students.csv', newline='') as csvfile:
    reader = csv.reader(csvfile)
    for row in reader:
        c.execute("INSERT INTO students (id, name) VALUES (?, ?)", (row[0], row[1]))

# Commit changes and close connection
conn.commit()
conn.close()