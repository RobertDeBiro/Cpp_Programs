#include <iostream>
#include <string>

int main()
{
    std::cout << "*****************************************************\n";

    //********** Initializations **********
    // Uninitialized string
    //  - uninitialized string will be empty string
    std::string un_str;
    std::cout << "Uninitialized string: " << un_str << '\n';

    // String initialized with empty string is the same as being uninitialized
    std::string empty_str{ "" };
    std::cout << "String initialized with empty string: " << empty_str << '\n';

    // String can be initialized with "const char*" literal
    //  - initialize with uniform initialization
    //    (valid, even though uniform syntax disallows narrowing conversion)
    std::string cch_ui_str{ "I saw a red car yesterday." };
    std::cout << cch_ui_str << '\n';

    //  - initialize with copy initialization
    std::string cch_ci_str = "Some random string";
    std::cout << cch_ci_str << '\n';

    // Initialize by using std::string class constructor
    //  - initialize with 10 copies of the character 'I'
    std::string str_constructor(10, 'I');
    std::cout << str_constructor << '\n';

    std::cout << "-----------------------------\n";


    //********** Assignment **********
    // String is dynamically resized when assigning new value to it
    std::string str_ass = "I saw a blue car yesterday.";
    std::cout << str_ass << '\n';
    str_ass = "I saw blue, red, green and yellow cars yesterday.";
    std::cout << str_ass << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}
