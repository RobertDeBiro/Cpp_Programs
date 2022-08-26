// File_input - Input from a file

#include <fstream> // std::ifstream
#include <iostream>
#include <string>

int main()
{
    // Create a std::ifstream variable used for input data from a file
    std::ifstream inf{ "C:\\Users\\rar\\Desktop\\Posao\\Programming\\C++\\Programs\\VSCode\\Practice\\Input and output\\txt files\\Sample.txt" };

    // If we couldn't open the output file stream for reading
    if (!inf)
    {
        // Print an error and exit
        std::cerr << "Uh oh, Sample.txtcould not be opened for reading!\n";
        return 1;
    }

    // Read from the file until there's still stuff left to read - whitespace splitting
    //  - when whitespace is encountered, extraction operator stops retrieving from file
    //    and goes to the next line for next iteration of retrieving
    while (inf)
    {
        // read stuff from the file into a string and print it
        std::string strInput;
        inf >> strInput;
        std::cout << strInput << '\n';
    }

    // We came to the end of the file, so inf has the value of EOF
    //  - run inf.clear() to reset it
    //  - run inf.seekg(0) to go to the beginning
    //     - seekg stands for seek and get
    inf.clear();
    inf.seekg(0);

    // Read from the file until there's still stuff left to read - newline splitting
    while (inf)
    {
        // read stuff from the file into a string and print it
        std::string strInput;
        std::getline(inf, strInput);
        std::cout << strInput << '\n';
    }

    return 0;

    // When inf goes out of scope, the ifstream
    // destructor will close the file
}