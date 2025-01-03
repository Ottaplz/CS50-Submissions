from cs50 import get_float


def main():

    # get input from user
    cents = round(get_cents(), 2)

    # Measure amount of quarters in total
    quarters = calculate_quarters(cents)
    cents = round(cents - quarters * .25, 2)

    # Measure amount of dimes in total
    dimes = calculate_dimes(cents)
    cents = round(cents - dimes * .10, 2)

    # Measure amount of nickels in total
    nickels = calculate_nickels(cents)
    cents = round(cents - nickels * .05, 2)

    # Measure amount of pennies in total
    pennies = calculate_pennies(cents)
    cents = round(cents - pennies * .01, 2)

    # Count and print total coins
    coins = quarters + dimes + nickels + pennies
    print(f"{int(coins)}")

# While loop to get positive integer


def get_cents():
    while True:
        try:
            n = get_float("Change owed: ")
            if n > 0:
                return n
        except ValueError:
            print("Enter a positive value.")


def calculate_quarters(cents):
    n = (cents // .25)
    return n


def calculate_dimes(cents):
    n = (cents // .10)
    return n


def calculate_nickels(cents):
    n = (cents // .05)
    return n


def calculate_pennies(cents):
    n = (cents // .01)
    return n


main()