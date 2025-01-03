SELECT DISTINCT(name) FROM people, stars, movies
    WHERE people.id = stars.person_id
    AND stars.movie_id = movies.id
    AND title IN
    (SELECT title FROM movies, stars, people
        WHERE movies.id = stars.movie_id
        AND people.id = stars.person_id
        AND people.id = (SELECT id FROM people WHERE name = 'Kevin Bacon' AND birth = 1958))
        AND name != 'Kevin Bacon';
