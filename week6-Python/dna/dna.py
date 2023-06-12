import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py <csv_file_name> <dna_file_name>")
        sys.exit(1)

    # Read database file into a variable
    database_file = sys.argv[1]
    with open(database_file) as file:
        reader = csv.DictReader(file)
        database = [row for row in reader]

    # Read DNA sequence file into a variable
    dna_file = sys.argv[2]
    with open(dna_file) as file:
        dna_sequence = file.read()

    # Find longest match of each STR in DNA sequence
    str_counts = {}
    for str_name in list(database[0].keys())[1:]:
        longest_run = longest_match(dna_sequence, str_name)
        str_counts[str_name] = longest_run

    # Check database for matching profiles
    for individual in database:
        if all(str_counts[str_name] == int(individual[str_name]) for str_name in str_counts.keys()):
            print(individual["name"])
            return
    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
