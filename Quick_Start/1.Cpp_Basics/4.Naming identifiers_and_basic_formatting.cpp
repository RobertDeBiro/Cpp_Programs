#include <iostream>

int main()
{
    //* Identifier
    /**
     *  - Rules:
     *      - name of variable, function, type or other kind of item
     *      - rules when naming identifiers:
     *          1. The identifier cannot be a keyword
     *              - C++ reserves a set of 97 words (as of C++23) for its own use
     *              - cppreference: https://en.cppreference.com/w/cpp/keyword
     *          2. The identifier can only be composed:
     *              - letters (lower or upper case)
     *              - numbers
     *              - underscore character
     *          3. The identifier must begin with a letter or an underscore
     *          4. C++ is case sensitive
     *  - Naming best practices:
     *      - variables
     *          – name should begin with a lowercase letter
     *          - if the variable name is one word, the whole thing should be written in lowercase letters
     *      - function – name should begin also with lowercase letter
     *      - user-defined types (structs, classes, enumerations) – name should begin with uppercase letter
     *      - if the variable or function name is multi-word, there are two common conventions for
     *        name separations:
     *          1. snake_case - words separated by underscores
     *          2. cammelCase - every new word starts with capital letter
     *      - we should avoid naming our identifiers starting with an underscore,
     *        as these names are typically reserved for OS, library, and/or compile use
     **/
    // 1. Rule
    ////char char = 'a';        //! SYNTAX ERROR: Identifier cannot be a keyword

    // 2. Rule
    char letterS;           // Identifier containing letters
    int number1;            // Identifier containing letters and number
    float number_2;         // Identifier containing letters, number, and underscore

    // 3. Rule
    ////char 3number;           //! SYNTAX ERROR: Identifier must begin with a letter or an underscore

    // 4. Rule
    int Number1;            // Number1 is not the same as number1
    //float number1;         //! SYNTAX ERROR: We cannot have the same identifiers in one function

    //* Naming best practices
    int Value;              // Valid, but bad practice
    int VALUE;              // Valid, but bad practice

    int my_variable_name;   // Good practice (snake_case)
    int myVariableName;     // Good practice (CamelCase)
    ////int my variable name;   //! invalid (whitespace not allowed)
    int MyVariableName;     // Valid, but bad practice (should start with lower case letter)

    ////////////////////////////////////////////////////////////////////////////////////

    //* Whitespace
    /**
     *  - whitespace refers to spaces, tabs, and newlines
     *  - C++ is a whitespace-independent language – C++ compiler generally ignores whitespace
     *  - newlines are not allowed in the quoted text
     *      - if we want to put the quoted text in newline we should close the quotes and open the new one
     *        in new line and compiler will ultimately concatenate quoted texts
     **/
    int          elem1;     // We can put any spaces between data type and identifier
    char                    // We can even put a newline between data type and identifier
    c1;

    ////std::cout << "Hello
    ////              World!" << std::endl;     //! SYNTAX ERROR: Newlines are not allowed in the quoted text
    std::cout << "Hello "
              << "World!" << std::endl;     // Valid: compiler will concatenate quoted text

    //* Basic formatting
    /**
     * - intendation should be 4 spaces long
     * - our lines should be no longer than 80 characters in length 
     **/

    return 0;
}
