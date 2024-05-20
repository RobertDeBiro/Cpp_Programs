#include <fstream>
#include <iostream>

namespace Files
{
    //* Windows paths
    // const std::string filename{ "C:\\Users\\Robert\\Desktop\\IT\\Programming_languages\\Data_files\\txt\\Sample1.txt" };

    //* Linux paths
    const std::string filename{ "/home/robert/IT/Files_for_testing/Sample" };
}

int main()
{
    std::cout << "*****************************************************\n";

    // Create a 'std::ofstream' variable used for output data to a file
    //  - 'std::ofstream' variable is initialized with the file
    //  - it can be existing file, or if file doesn't exist, program will create it
    //  - we are setting absolute path to the file
    //  - if we write only <file_name> (not full path) our file would be saved in directory
    //    where compiler is saved, which is "C:\msys64\mingw64\bin"
    std::ofstream outf{ Files::filename };

    if (!outf)
    {
        std::cerr << "There is no file called " << Files::filename << std::endl;
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

    // Open file and append data to it by using 'std::ios::app' ios file mode
    outf.open(Files::filename, std::ios::app);

    outf << "This is line 3\n";
    outf.close();

    std::cout << "*****************************************************\n";
    return 0;
}
// When 'outf' goes out of scope, the 'ofstream' destructor will close the file
