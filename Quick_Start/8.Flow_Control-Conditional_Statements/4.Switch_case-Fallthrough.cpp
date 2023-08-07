//* Switch-case fallthrough
/**
 *  - switch-case executions continues until one of the following termination conditions is true:
 *		1. The end of the switch block is reached
 *		2. A return statement occurs
 *		3. A break statement occurs
 *		4. A goto statement occurs
 *		5. Something else interupt the normal flow
 **/

#include <iostream>

int getOrdinalNumber(char letter)
{
    switch (letter) {
        case 'A':
        case 'a':
            return 1;
        case 'B':
        case 'b':
            return 2;
        case 'C':
        case 'c':
            return 3;
        case 'D':
        case 'd':
            return 4;
        case 'E':
        case 'e':
            return 5;
        case 'F':
        case 'f':
            return 6;
        case 'G':
        case 'g':
            return 7;
        case 'H':
        case 'h':
            return 8;
        case 'I':
        case 'i':
            return 9;
        case 'J':
        case 'j':
            return 10;
        case 'K':
        case 'k':
            return 11;
        case 'L':
        case 'l':
            return 12;
        case 'M':
        case 'm':
            return 13;
        case 'N':
        case 'n':
            return 14;
        case 'O':
        case 'o':
            return 15;
        case 'P':
        case 'p':
            return 16;
        case 'Q':
        case 'q':
            return 17;
        case 'R':
        case 'r':
            return 18;
        case 'S':
        case 's':
            return 19;
        case 'T':
        case 't':
            return 20;
        case 'U':
        case 'u':
            return 21;
        case 'V':
        case 'v':
            return 22;
        case 'W':
        case 'w':
            return 23;
        case 'X':
        case 'x':
            return 24;
        case 'Y':
        case 'y':
            return 25;
        case 'Z':
        case 'z':
            return 26;
            
        default:
            return -1;  // Return -1 for invalid input
    }
}

int main()
{
    char letter;
    std::cout << "Enter a letter: ";
    std::cin >> letter;

    int ordinalNumber = getOrdinalNumber(letter);
    if (ordinalNumber != -1)
    {
        std::cout << "Ordinal number of " << letter << " is " << ordinalNumber << std::endl;
    }
    else
    {
        std::cout << "Invalid input. Please enter a letter from the English alphabet." << std::endl;
    }

    return 0;
}
