/**
 * * Boolean
 *      - integral type 1 byte big
 *      - to declare it we use the keyword bool
 *      - can contain only two values: true and false
 *      - the logical NOT operator (!) can be used to flip a Boolean value from true to false,
 *        or false to true
 *      - functions that check whether something is true or not are typically named starting with the word
 *        is (e.g. isBigger) or has (e.g. hasEnoughPoints)
 **/
/**
 * * Printing boolean variables
 *      - boolean variables are printed as 1 or 0
 *      - for printing true or false rather then 1 or 0 we can use std::boolalpha
 *          - std::noboolalpha used to turn it back off
 **/

#include <iostream>

int main()
{
    bool b1 = true;
    bool b2 = !b1;

    // Boolean variables are printed as 1 or 0
    std::cout << "b1 = " << b1 << '\n';
    std::cout << "b2 = " << b2 << '\n';

    std::cout << "--------------------------------\n";






    //////////////////////////////////////////////////////////////

    /*
     * Integer to boolean
     */
    bool b3 = 5;
    bool b4 = 0;
    std::cout << "b3 = " << b3 << '\n';
    std::cout << "b4 = " << b4 << '\n';

    std::cout << "----------------------------------\n";

    //////////////////////////////////////////////////////////////





    /*
     * Input boolean via std::cin
     */
    bool b5;
    std::cout << "Insert boolean: ";
    std::cin >> b5;
    std::cout << "b5 = " << b5 << '\n';

    return 0;
}