#include <fstream>
#include <iostream>
#include <string>

int main()
{
    std::cout << "*****************************************************\n";

    //********* Initialize basic file I/O 'fstream' class object for reading and writing *********
    // - created 'fstream' object must be able to both read from file and write to file
    // - in order to achieve that we need to send to 'fstream' constructor an "ios file mode" as
    //   optional second parameter
    // - we can send multiple ios file modes by using bitwise OR operator '|'
    // - sending two ios file modes:
    //    1. std::ios::in - opens the file in read mode
    //    2. std::ios::out - opens the file in write mode
    std::fstream iofile
    {
        "C:\\Users\\Robert\\Desktop\\IT\\Programming_languages\\Data_files\\txt\\Sample1.txt",
        std::ios::in | std::ios::out
    };

    // If 'iofile' cannot be open, print an error
    if (!iofile)
    {
        // Print an error using 'std::cerr'
        std::cerr << "Uh oh, Sample1.txt could not be opened!\n";
        return 1;
    }

    std::cout << "Current 'get pointer' position = " << iofile.tellg() << '\n';

    char chChar{}; // we're going to do this character by character

    // Get character by character from the file, while there's still data to process
    //! For some reason following part doesn't work as expected
    //! - file pointer is not in expected position
    while (iofile.get(chChar))
    {
        std::cout << "tellg() position = " << iofile.tellg() << " for letter " << chChar << '\n';
        
        switch (chChar)
        {
            // If we find a vowel
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
            case 'A':
            case 'E':
            case 'I':
            case 'O':
            case 'U':

                std::cout << "Current 'get pointer' position = " << iofile.tellg() << '\n';

                // Back up one character
                iofile.seekg(-1, std::ios::cur);

                // Because we did a "seek", we can now safely do a "write", so
                // let's write a '#' over the vowel
                iofile << '#';

                // Now we want to go back to "read" mode so the next call
                // to 'get()' will perform correctly. We'll 'seekg()' to the current
                // location because we don't want to move the file pointer.
                iofile.seekg(iofile.tellg(), std::ios::beg);

                break;
        }
    }

    std::cout << "*****************************************************\n";
    return 0;
}