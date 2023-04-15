#include <fstream> // std::ifstream
#include <iostream>
#include <string>

int main()
{
    std::cout << "*****************************************************\n";

    // Create a std::ifstream variable used for input data from a file
    std::ifstream inf{ "C:\\Users\\Robert\\Desktop\\IT\\Programs\\Random_files\\txt\\Sample1.txt" };

    if(!inf)
    {
        std::cerr << "File could not be opened for reading!\n";
        return 1;
    }

    // Read from the file until there's still stuff left to read - whitespace splitting
    //  - when whitespace is encountered, extraction operator stops retrieving from file
    //    and goes to the next line for next iteration of retrieving
    while(inf)
    {
        // read stuff from the file into a string and print it
        std::string strInput;
        inf >> strInput;
        std::cout << strInput << '\n';
    }

    std::cout << "-------------------------------------------\n";

    // We came to the end of the file, so inf has the value of EOF
    //  - run inf.clear() to reset it
    //  - run inf.seekg(0) to go to the beginning
    //     - seekg stands for seek and get
    inf.clear();
    inf.seekg(0);

    // Read from the file until there's still stuff left to read - newline splitting
    while(inf)
    {
        // read stuff from the file into a string and print it
        std::string strInput;
        std::getline(inf, strInput);
        std::cout << strInput << '\n';
    }

    std::cout << "*****************************************************\n";
    return 0;
}
// When inf goes out of scope, the ifstream
// destructor will close the file