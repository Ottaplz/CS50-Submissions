def main():
    height = get_height()
    draw(height)


def draw(height):
    # loop by total height of pyramid
    for i in range(height):
        if i != 0:
            print()
        # loop for spaces to extend pyramid to right side
        for x in range(height - i - 1):
            print(" ", end="")
        # loop to print hashes based on height
        for j in range(i + 1):
            print("#", end="")
        # spaces in between pyramids
            print("  ", end="")
        # loop to make second pyramid
        for z in range(i + 1):
            print("#", end="")

    print()


def get_height():
    # While loop to recieve integer between 1-8
    while True:
        try:
            n = int(input("What is the size of the pyramid? "))
            if n > 0 and n < 9:
                return n
        except ValueError:
            print("Enter a number between 1-8")


main()
