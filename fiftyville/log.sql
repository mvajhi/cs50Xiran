-- Keep a log of any SQL queries you execute as you solve the mystery.
--go to location at time
SELECT description
FROM crime_scene_reports
WHERE street = "Humphrey Street"
    AND day = 28
    AND month = 7
    AND year = 2021;
--see interviews
SELECT *
FROM interviews
WHERE transcript like "%bakery%";
--see camera of bakery
SELECT *
FROM bakery_security_logs
WHERE year = 2021
    AND month = 7
    and day = 28
    and hour = 10;
--261|2021|7|28|10|18|exit|94KL13X
--262|2021|7|28|10|18|exit|6P58WS2
--exit who??
SELECT *
FROM people
WHERE license_plate = "94KL13X";
SELECT *
FROM people
WHERE license_plate = "6P58WS2";
--686048|Bruce|(367) 555-5533|5773159633|94KL13X
--243696|Barry|(301) 555-4174|7526138472|6P58WS2
--Bruce and Barry--
--see first fly in 29
SELECT *
FROM flights
WHERE year = 2021
    AND month = 7
    and day = 29;
--18|8|6|2021|7|29|16|0
--23|8|11|2021|7|29|12|15
--36|8|4|2021|7|29|8|20!!!!!!!!!!
--43|8|1|2021|7|29|9|30
--53|8|9|2021|7|29|15|20
--check airport
SELECT *
FROM airports
WHERE id IN(
        SELECT destination_airport_id
        FROM flights
        WHERE year = 2021
            AND month = 7
            and day = 29
    );
--1|ORD|O'Hare International Airport|Chicago
--4|LGA|LaGuardia Airport|New York City!!!!!!!!!!!!!!!!!!!!
--6|BOS|Logan International Airport|Boston
--9|HND|Tokyo International Airport|Tokyo
--11|SFO|San Francisco International Airport|San Francisco
--New York City--
--check ATM history on Leggett Street
SELECT *
FROM atm_transactions
WHERE year = 2021
    AND month = 7
    and day = 28
    and atm_location = "Leggett Street"
    AND transaction_type = "withdraw";
--check bank
SELECT *
FROM people
WHERE id IN(
        SELECT person_id
        FROM bank_accounts
        WHERE account_number IN (
                SELECT account_number
                FROM atm_transactions
                WHERE year = 2021
                    AND month = 7
                    and day = 28
                    and atm_location = "Leggett Street"
                    AND transaction_type = "withdraw"
            )
    );
--686048|Bruce|(367) 555-5533|5773159633|94KL13X
--Bruce main--
--check call defore
SELECT *
FROM phone_calls
WHERE year = 2021
    AND month = 7
    and day = 28
    and caller = "(367) 555-5533"
    and duration < 60;
--233|(367) 555-5533|(375) 555-8161|2021|7|28|45
SELECT *
FROM people
WHERE phone_number = "(375) 555-8161";
--864400|Robin|(375) 555-8161||4V16VO0
--Robin--