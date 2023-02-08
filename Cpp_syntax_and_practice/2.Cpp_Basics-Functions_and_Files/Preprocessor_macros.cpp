#include <iostream>
#include <iomanip>

int main(int argc, char* argv[]) {
    std::cout << "*****************************************************\n";

    //  Compile with g++ -std=c++11 or g++ -std=c++14 to
    //  have different output.
    //  more info:
    //   - https://renenyffenegger.ch/notes/development/languages/C-C-plus-plus/preprocessor/macros/predefined/__cplusplus
    //   - https://stackoverflow.com/a/7132549/180275
    std::cout << "Preprocessor macro: ";
    std::cout << std::setw(6) << argv[0] << ": " <<  __cplusplus << std::endl;

    std::cout << "*****************************************************\n";
}