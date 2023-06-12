CREATE TABLE students (
id INTEGER PRIMARY KEY,
name TEXT NOT NULL
);

CREATE TABLE houses (
id INTEGER PRIMARY KEY,
name TEXT NOT NULL,
head_of_house TEXT NOT NULL
);

CREATE TABLE house_assignments (
student_id INTEGER NOT NULL,
house_id INTEGER NOT NULL,
PRIMARY KEY(student_id),
FOREIGN KEY(student_id) REFERENCES students(id),
FOREIGN KEY(house_id) REFERENCES houses(id)
);