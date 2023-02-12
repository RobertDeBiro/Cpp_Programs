#include <iostream>

int main()
{
    std::cout << "*****************************************************\n";

    // showpos
    std::cout.setf(std::ios::showpos);
    std::cout << 27 << '\n';
    std::cout.unsetf(std::ios::showpos);
    std::cout << 27 << '\n';

    std::cout << std::showpos;
    std::cout << 27 << '\n';
    std::cout << std::noshowpos;
    std::cout << 27 << '\n';

    std::cout << "-------------------------\n";

    // uppercase
    std::cout.setf(std::ios::uppercase);
    std::cout << 1234567.89f << '\n';
    std::cout.unsetf(std::ios::uppercase);
    std::cout << 1234567.89f << '\n';

    std::cout << std::uppercase;
    std::cout << 1234567.89f << '\n';
    std::cout << std::nouppercase;
    std::cout << 1234567.89f << '\n';

    std::cout << "-------------------------\n";

    // hex
    std::cout.setf(std::ios::hex, std::ios::basefield);
    std::cout << 27 << '\n';
    std::cout.unsetf(std::ios::hex); // when using unset it is not needed to add format group
    std::cout << 27 << '\n';

    std::cout << std::hex;
    std::cout << 27 << '\n';
    std::cout << std::dec;
    std::cout << 27 << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}