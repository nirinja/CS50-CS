import csv
import requests


def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )

    # returns the content of the response as bytes.
    decoded_content = download.content.decode("utf-8")

    # splits the string into a list of lines
    file = decoded_content.splitlines()

    # creates a new CSV reader object from the list of lines, which treats the first row as column headers and returns each subsequent row as a dictionary where the keys are the column headers and the values are the corresponding values for that row.
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


# TODO: Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):
    fortnight = {}
    for row in reader:
        state = row['state']
        cases = int(row['cases'])
        # Shift the list to the left and add new cases to the right end
        fortnight[state] = fortnight[state][1:] + [cases]
    return fortnight


# TODO: Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):
    for state in states:
        # Get the list of daily new cases for the past 7 days
        past_week = new_cases[state][-7:]
        average = sum(past_week) / len(past_week)

        pastpast_week = new_cases[state][0:7]
        averagepast =  sum(pastpast_week) / len(pastpast_week)
        inc = ((averagepast-average) / average ) * 100
        name_inc = "increase"
        if inc < 0:
            name_inc = "decrease"
        # Print the result
        print(f"{state}  had a 7-day average of {average:.0f} and and a {name_inc} of {inc:.2f}% ")


main()
