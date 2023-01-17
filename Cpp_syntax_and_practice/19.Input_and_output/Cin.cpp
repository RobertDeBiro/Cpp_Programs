#include <iostream>
#include <iomanip> // std::setw
#include <limits> // std::numeric_limits

void badInput();
void setWidth();
void cin_get();
void cin_getline();

int main()
{
    std::cout << "*****************************************************\n";

    badInput();
    setWidth();
    cin_get();
    cin_getline();

    std::cout << "*****************************************************\n";
    return 0;
}

void badInput()
{
    int number{};
    do
    {
        std::cout << "Enter a number between 1 and 9: ";
        std::cin >> number;

        // If the user entered something invalid, e.g. letter, std::cin.fail() returns true
        if (std::cin.fail())
        {
            std::cin.clear(); // reset any error flags
        }
        // Ignore every character in the buffer until encountering newline (\n)
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while(number < 1 || number > 9);

    std::cout << "Number " << number << " is in proper scope!\n";
    std::cout << "------------------------------\n";
}

void setWidth()
{
    // When typing "MoreThenTenChars", everything is fine,
    // even though it shouldn't be since 16 characters are generated
    //  - but I noticed that if 18 or more chars are generated, than program starts behave strangly,
    //    or segmentation fault exception occurs ?!?!
    char buf1[10];
    std::cout << "Type in more then 10 characters (without space): \n";
    std::cin >> buf1;
    std::cout << buf1;

    std::cout << "\n\n";

    // Retrieve 10 characters placed inside std::cin buffer, and put them into a variable
    char buf2[10];
    std::cout << "Type in more then 10 characters (without space): \n";
    std::cin >> std::setw(10) >> buf2; // setw = set width
    std::cout << buf2;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\n------------------------------\n";
}

void cin_get()
{
    // When typing "Hello, my name is Robert de Biro!", everything will be saved inside input buffer
    // except whitespace characters, since the extraction operator (>>) skips whitespace
    // (blanks, tabs, and newlines) 
    //  - hence, "Hello,mynameisRobertdeBiro" will be printed to the screen 
    char ch;
    std::cout << "Please, type some sentence (whitespaces won't be saved):\n";
    while (std::cin >> ch && ch != '!')
        std::cout << ch;
    
    std::cout << "\n\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Remove "!" and newline characters that left from previous input

    // Save whitespaces also
    std::cout << "Please, type some sentence (whitespaces will be saved):\n";
    while (std::cin.get(ch) && ch != '!')
        std::cout << ch;
    
    std::cout << "\n\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Restrict number of characters saved in input buffer
    //  - the same feature as std::setw, except std::cin.get() includes also whitespaces
    //  - input: Hello, my name is Robert
    //  - output: Hello, my 
    char strBuf[11];
    std::cout << "Please, type Hello!:\n";
    std::cin.get(strBuf, 11);
    std::cout << strBuf << '\n';
    // Retrieve how many characters were extracted by the last usage of std::cin
    std::cout << std::cin.gcount() << " characters were read" << '\n';

    // Read up to 10 more charachters
    // - only newline will be read (newline from previous input), hence nothing will be printed
    std::cout << "Please, type some word (chars amount restricted):\n";
    std::cin.get(strBuf, 11);
    std::cout << strBuf << '\n';
    std::cout << std::cin.gcount() << " characters were read" << '\n';

    // Since std::cin.get collected in strBuf only newline, error appeared (but not showed)
    // and needs to be cleared
    std::cin.clear();

    std::cout << "\n------------------------------\n";
}

void cin_getline()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Restrict number of characters saved in input buffer
    //  - newline also saved inside strBuf
    //  - in this way we are avoiding the issue appeared in cin_get() function 
    char strBuf[11];
    std::cout << "Please, type some word (chars amount restricted):\n";
    std::cin.getline(strBuf, 11);
    std::cout << strBuf << '\n';
    std::cout << std::cin.gcount() << " characters were read" << '\n';

    std::cout << '\n';

    // Read up to 10 more characters
    std::cout << "Please, type some word (chars amount restricted):\n";
    std::cin.getline(strBuf, 11);
    std::cout << strBuf << '\n';
    std::cout << std::cin.gcount() << " characters were read" << '\n';

    std::cout << "------------------------------\n";
}