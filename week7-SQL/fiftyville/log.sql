SELECT * from crime_scene_reports
    where street = 'Humphrey Street'
    and (month = 7 or month = 8);

SELECT * from interviews
    where (month = 7 and  day > 27) or (month = 8 and day < 5);

SELECT
p.name,
air1.city,
pass.seat,
fly.origin_airport_id,
fly.destination_airport_id,
fly.day,
fly.month,
calls1.caller,
calls1.duration,
calls1.day AS call_day,
calls1.month AS call_month,
bake.day,
bake.hour,
bake.minute,
bake.activity,
atm.day,
atm.atm_location,
atm.amount

FROM people p
    JOIN interviews inter ON inter.name = p.name
    JOIN bank_accounts ba ON ba.person_id = p.id
    JOIN atm_transactions atm ON atm.account_number = ba.account_number
    JOIN passengers pass ON pass.passport_number = p.passport_number
    JOIN flights fly ON fly.id = pass.flight_id
    JOIN airports air1 ON air1.id = fly.origin_airport_id
    JOIN phone_calls calls1 ON calls1.caller = p.phone_number
    JOIN bakery_security_logs bake ON bake.license_plate = p.license_plate
where calls1.duration < 60 and calls1.month = 7 and calls1.day = 28
and (atm.month = 7 and atm.day = 28) or
(bake.day = 28 and bake.hour = 10)
;

SELECT name FROM people
WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE year = 2021 AND month = 07 AND day = 28 AND duration < 60) ORDER BY name;

------------------------------------------------------
-- Keep a log of any SQL queries you execute as you solve the mystery.
-- cat log.sql | sqlite3 fiftyville.db > output.txt