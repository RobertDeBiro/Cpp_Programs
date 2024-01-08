#include <iostream>
#include <iomanip>

int main()
{
    std::cout << "*****************************************************\n";

    // Format "Normal"
    //  - 'setprecision' count numbers from the beginning
    //  - if precision is less than the number of significant digits, the number will be rounded
    std::cout << "Format: Normal\n";
    std::cout << std::setprecision(2) << 123.456 << '\n';
    std::cout << std::setprecision(3) << 123.456 << '\n';
    std::cout << std::setprecision(4) << 123.456 << '\n';
    std::cout << std::setprecision(5) << 123.456 << '\n';
    std::cout << std::setprecision(6) << 123.456 << '\n';
    std::cout << std::setprecision(7) << 123.456 << '\n';
    std::cout << std::setprecision(8) << 123.456 << '\n';

    std::cout << "----------------------------------\n";

    // Format "Normal", with 'std::showpoint' manipulator
    //  - 'std::showpoint' adds trailing zeros (format normal by default don't show them)
    std::cout << "Format: Normal, with showpoint";
    std::cout << std::showpoint << '\n';
    std::cout << std::setprecision(2) << 123.456 << '\n';
    std::cout << std::setprecision(3) << 123.456 << '\n';
    std::cout << std::setprecision(4) << 123.456 << '\n';
    std::cout << std::setprecision(5) << 123.456 << '\n';
    std::cout << std::setprecision(6) << 123.456 << '\n';
    std::cout << std::setprecision(7) << 123.456 << '\n';
    std::cout << std::setprecision(8) << 123.456 << '\n';

    std::cout << "----------------------------------\n";

    // Format "Fixed"
    //  - "fixed" - non-decimal part is fixed and cannot be manipulated by 'setprecision()'
    //  - 'setprecision' count numbers from the first decimal place
    //  - if precision is less than the number of significant digits, the number will be rounded
    //  - adds trailing zeros
    std::cout << "Format: Fixed\n";
    std::cout << std::fixed;
    std::cout << std::setprecision(2) << 123.456 << '\n';
    std::cout << std::setprecision(3) << 123.456 << '\n';
    std::cout << std::setprecision(4) << 123.456 << '\n';
    std::cout << std::setprecision(5) << 123.456 << '\n';
    std::cout << std::setprecision(6) << 123.456 << '\n';
    std::cout << std::setprecision(7) << 123.456 << '\n';
    std::cout << std::setprecision(8) << 123.456 << '\n';

    std::cout << "----------------------------------\n";

    // Format "Scientific"
    //  - prints numbers in scientific notation
    //  - in scientific notation there is always only one number before first decimal place
    //  - 'setprecision' count numbers from the first decimal place
    //  - if precision is less than the number of significant digits, the number will be rounded
    //  - adds trailing zeros
    std::cout << "Format: Scientific\n";
    std::cout << std::scientific;
    std::cout << std::setprecision(1) << 123.456 << '\n';
    std::cout << std::setprecision(2) << 123.456 << '\n';
    std::cout << std::setprecision(3) << 123.456 << '\n';
    std::cout << std::setprecision(4) << 123.456 << '\n';
    std::cout << std::setprecision(5) << 123.456 << '\n';
    std::cout << std::setprecision(6) << 123.456 << '\n';
    std::cout << std::setprecision(7) << 123.456 << '\n';
    std::cout << std::setprecision(8) << 123.456 << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}