#include <fstream>
#include <iostream>
#include <string>

int main()
{
    std::cout << "*****************************************************\n";

    // Note we have to specify both in and out because we're using fstream
    std::fstream iofile
    {
        "C:\\Users\\rar\\Desktop\\Posao\\Programs\\Random_files\\txt\\Sample1.txt",
        std::ios::in | std::ios::out
    };

    // If we couldn't open iofile, print an error
    if (!iofile)
    {
        // Print an error and exit
        std::cerr << "Uh oh, Sample1.txt could not be opened!\n";
        return 1;
    }

    char chChar{}; // we're going to do this character by character

    // While there's still data to process
    while (iofile.get(chChar))
    {
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

                // Back up one character
                iofile.seekg(-1, std::ios::cur);

                // Because we did a seek, we can now safely do a write, so
                // let's write a # over the vowel
                iofile << '#';

                // Now we want to go back to read mode so the next call
                // to get() will perform correctly. We'll seekg() to the current
                // location because we don't want to move the file pointer.
                iofile.seekg(iofile.tellg(), std::ios::beg);

                break;
        }
    }

    std::cout << "*****************************************************\n";
    return 0;
}