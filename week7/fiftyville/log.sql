-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Running .schema to get on overview of all tables and their relationships
-- Check all info from crime_scene_reports that oocured on July 28 2021
 SELECT * FROM crime_scene_reports
    WHERE year = 2021
    AND month = 07
    AND day = 28;
-- Have idenitified the crime report for the stolen duck, crime_scene_reports.id = 295.
-- Crime took place at 10:15am. 3 witnesses for the crime, next query will be regarding the interviews with witnesses.
SELECT * FROM interviews
    WHERE year = 2021
    AND month = 7
    AND day = 28
    AND transcript LIKE '%bakery%';
    -- Multiple leads to follow based on interview transcripts, bakery security footage, ATM withdrawal, phone call, and flight purchase
    -- First query will be regarding the car that left the parking lot within 10 minutes of the crime
    SELECT * FROM bakery_security_logs
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND hour = 10
        AND minute > 14
        AND minute < 26;
    -- 8 different cars exited the parking lot in the given time frame.
    -- Query for the ATM on Leggett Street, someone Eugene recognised before the crime took place.
    SELECT * FROM atm_transactions
        WHERE year = 2021
        AND month = 7
        AND day = 28
        AND atm_location = 'Leggett Street'
        AND transaction_type = 'withdraw';
    -- 8 different withdrawals occured at the ATM on Leggett Street during the day.
    -- Run a query that returns a person based on the 8 license plate numbers and 8 bank account numbers to see if there is a match
    SELECT * FROM people
    JOIN bank_accounts ON people.id = bank_accounts.person_id
        WHERE id IN (SELECT person_id FROM bank_accounts
            WHERE account_number IN (SELECT account_number FROM atm_transactions
                WHERE year = 2021 AND month = 7 AND day = 28
                AND atm_location = 'Leggett Street'AND transaction_type = 'withdraw'))

        AND license_plate IN (SELECT license_plate FROM bakery_security_logs
            WHERE year = 2021 AND month = 7 AND day = 28
            AND hour = 10 AND minute > 14 AND minute < 26);
-- Cross reference of license plate and atm transaction returned 4 suspects, Bruce, Diana, Iman, and Luca.
-- Using the information of all of the above suspects search for phone records of that day with their phone numbers.
    SELECT * FROM phone_calls
        WHERE caller IN
            (SELECT phone_number FROM people
            JOIN bank_accounts ON people.id = bank_accounts.person_id
            WHERE id IN (SELECT person_id FROM bank_accounts
                WHERE account_number IN (SELECT account_number FROM atm_transactions
                    WHERE year = 2021 AND month = 7 AND day = 28
                    AND atm_location = 'Leggett Street'AND transaction_type = 'withdraw'))

            AND license_plate IN (SELECT license_plate FROM bakery_security_logs
                WHERE year = 2021 AND month = 7 AND day = 28
                AND hour = 10 AND minute > 14 AND minute < 26))
    AND year = 2021
    AND month = 7
    AND day = 28;
-- This gives 2 potential options left for suspects, both made outgoing calls less than 1 minute long.
-- Running the next query on the to obtain the personal profile of both suspects that had outgoing calls.
SELECT * FROM people WHERE phone_number IN
        (SELECT caller FROM phone_calls
            WHERE caller IN
                (SELECT phone_number FROM people
                JOIN bank_accounts ON people.id = bank_accounts.person_id
                WHERE id IN (SELECT person_id FROM bank_accounts
                    WHERE account_number IN (SELECT account_number FROM atm_transactions
                        WHERE year = 2021 AND month = 7 AND day = 28
                        AND atm_location = 'Leggett Street'AND transaction_type = 'withdraw'))

                AND license_plate IN (SELECT license_plate FROM bakery_security_logs
                    WHERE year = 2021 AND month = 7 AND day = 28
                    AND hour = 10 AND minute > 14 AND minute < 26))
        AND year = 2021
        AND month = 7
        AND day = 28);
-- This leaves Bruce and Diana as the only suspects left, both of them having 1 call under 1 minute each.
-- This leaves 2 potential accomplices as well.
-- Will now query to obtain flight information for the next day to isolate the earliest flight.
SELECT * FROM flights
    WHERE year = 2021
    AND month = 7
    AND day = 29
        ORDER BY hour;
-- This gives one flight as the option for the theif to have left with the duck, at 8:20am.
-- Can now query to identify the city the thief fled to
SELECT * FROM airports
    WHERE id = (SELECT destination_airport_id FROM flights
                WHERE year = 2021 AND month = 7 AND day = 29 AND hour = 8 AND minute = 20);
-- The query shows that the thief escaped to LaGuardia Airport in NYC.
-- With this information can now check the passenger details on the flight and cross reference with the previous phone call query.
SELECT name FROM people
    JOIN passengers ON people.passport_number = passengers.passport_number
    JOIN flights ON passengers.flight_id = flights.id
        WHERE flight_id IN
        (SELECT id FROM flights
            WHERE year = 2021 AND month = 7 AND day = 29 AND hour = 8 AND minute = 20)

        AND phone_number IN (SELECT phone_number FROM people WHERE phone_number IN
            (SELECT caller FROM phone_calls
                WHERE caller IN
                    (SELECT phone_number FROM people
                    JOIN bank_accounts ON people.id = bank_accounts.person_id
                        WHERE id IN (SELECT person_id FROM bank_accounts
                            WHERE account_number IN (SELECT account_number FROM atm_transactions
                                WHERE year = 2021 AND month = 7 AND day = 28
                                AND atm_location = 'Leggett Street'AND transaction_type = 'withdraw'))

                    AND license_plate IN (SELECT license_plate FROM bakery_security_logs
                        WHERE year = 2021 AND month = 7 AND day = 28
                        AND hour = 10 AND minute > 14 AND minute < 26))
            AND year = 2021
            AND month = 7
            AND day = 28));
-- This final query identifies Bruce as a positive match as the thief of the cs50 duck!
-- The only thing left to do is identify the accomplice by their phone call with Bruce after the crime
SELECT * FROM people WHERE phone_number IN
        (SELECT receiver FROM phone_calls
            WHERE caller IN
                (SELECT phone_number FROM people
                    JOIN bank_accounts ON people.id = bank_accounts.person_id
                    WHERE id IN (SELECT person_id FROM bank_accounts
                        WHERE account_number IN (SELECT account_number FROM atm_transactions
                            WHERE year = 2021 AND month = 7 AND day = 28
                            AND atm_location = 'Leggett Street'AND transaction_type = 'withdraw'))

                    AND license_plate IN (SELECT license_plate FROM bakery_security_logs
                        WHERE year = 2021 AND month = 7 AND day = 28
                        AND hour = 10 AND minute > 14 AND minute < 26)
                        AND name = 'Bruce')
        AND duration < 61
        AND year = 2021
        AND month = 7
        AND day = 28);
-- This final query gives us our last answer, which is Robin, Bruce's accomplice to  stealing the cs50 duck.

