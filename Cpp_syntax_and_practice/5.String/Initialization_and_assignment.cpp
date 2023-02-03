#include <iostream>
#include <string>

int main()
{
    /*
     * Initializations
     */
    // Initialize string variable with empty string
    std::string str1;
    std::cout << "String initialized with empty string: " << str1 << '\n';

    // Initialize with const char* literal using uniform initialization
    std::string str2{ "I saw a red car yesterday." };
    std::cout << str2 << '\n';

    // Initialize with const char* literal using copy initialization
    std::string str3 = "Some random string";
    std::cout << str3 << '\n';

    // Initialize with 10 copies of the character 'I'
    std::string str4(10, 'I');
    std::cout << str4 << '\n';

    /*
     * Assignment
     */
    // String is dynamically resized when assigning new value to it
    str2 = "I saw a blue car yesterday.";
    std::cout << str2 << '\n';

    str2 = "I saw blue, red, green and yellow cars yesterday.";
    std::cout << str2 << '\n';

    return 0;
}
