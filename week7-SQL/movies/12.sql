-- In 12.sql, write a SQL query to list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred.
-- Your query should output a table with a single column for the title of each movie.
-- You may assume that there is only one person in the database with the name Johnny Depp.
-- You may assume that there is only one person in the database with the name Helena Bonham Carter.
SELECT
    m.title
FROM
    movies m
    JOIN stars s1 ON s1.movie_id = m.id
    JOIN people p1 ON p1.id = s1.person_id
    AND p1.name = 'Johnny Depp'
    JOIN stars s2 ON s2.movie_id = m.id
    JOIN people p2 ON p2.id = s2.person_id
    AND p2.name = 'Helena Bonham Carter';