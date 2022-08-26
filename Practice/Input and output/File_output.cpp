// File_output - Output to a file

#include <fstream> // std::ofstream
#include <iostream>

int main()
{
    // Create a std::ofstream variable used for output data to a file
    //  - std::ofstream variable is initialized with the file
    //  - it can be existing file, or if file doesn't exist, program will create it
    //  - we are setting absolute path to the file
    //  - if we write only "Sample.txt" are file would be saved in directory where compiler is saved
    //    which is C:\msys64\mingw64\bin
    std::ofstream outf{ "C:\\Users\\rar\\Desktop\\Posao\\Programming\\C++\\Programs\\VSCode\\Practice\\Input and output\\txt files\\Sample.txt" };

    // If we couldn't open the output file stream for writing
    if (!outf)
    {
        // Print an error and exit
        std::cerr << "Uh oh, Sample.txt could not be opened for writing!\n";
        return 1;
    }

    // We'll write two lines into this file
    outf << "This is line 1\n";
    outf << "This is line 2\n";

    // Put character by character into file
    outf.put('a');
    outf.put('b');
    outf.put('c');
    outf.put('\n');

    outf.close(); // explicitly close the file

    // Open Sample file and append data to it
    outf.open("C:\\Users\\rar\\Desktop\\Posao\\Programming\\C++\\Programs\\VSCode\\Practice\\Input and output\\txt files\\Sample.txt", std::ios::app);

    outf << "This is line 3\n";
    outf.close();

    return 0;

    // When outf goes out of scope, the ofstream
    // destructor will close the file
}