#include <fstream> // std::ofstream
#include <iostream>

int main()
{
    std::cout << "*****************************************************\n";

    // Create a std::ofstream variable used for output data to a file
    //  - std::ofstream variable is initialized with the file
    //  - it can be existing file, or if file doesn't exist, program will create it
    //  - we are setting absolute path to the file
    //  - if we write only "Sample.txt" are file would be saved in directory where compiler is saved
    //    which is C:\msys64\mingw64\bin
    std::ofstream outf{ "C:\\Users\\Robert\\Desktop\\IT\\Programs\\Random_files\\txt\\Sample1.txt" };

    if(!outf)
    {
        std::cerr << "File could not be opened for writing!\n";
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
    outf.open("C:\\Users\\Robert\\Desktop\\IT\\Programs\\Random_files\\txt\\Sample1.txt", std::ios::app);

    outf << "This is line 3\n";
    outf.close();

    std::cout << "*****************************************************\n";
    return 0;
}
// When outf goes out of scope, the ofstream
// destructor will close the file
