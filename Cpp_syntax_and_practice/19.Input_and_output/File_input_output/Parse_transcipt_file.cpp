#include <iostream>
#include <fstream>
#include <cstdlib> // exit
#include <set>
#include <string>

namespace Files
{
    // const char* inputFile{ "C:\\Users\\rar\\Desktop\\Posao\\Programs\\Random_files\\txt\\Transcript-Msys2.txt" };
    // const char* outputFile{ "C:\\Users\\rar\\Desktop\\Posao\\Programs\\Random_files\\txt\\Transcript_parsed-Msys2.txt" };
    const char* inputFile{ "C:\\Users\\rar\\Desktop\\Posao\\Programs\\Random_files\\txt\\Transcript-VSCode.txt" };
    const char* outputFile{ "C:\\Users\\rar\\Desktop\\Posao\\Programs\\Random_files\\txt\\Transcript_parsed-VSCode.txt" };
}

int main()
{
    std::cout << "*****************************************************\n";

    std::ifstream inputFileObj;
    inputFileObj.open(Files::inputFile);
    if(!inputFileObj.is_open())
    {
        std::cout << "There is no file called " << Files::inputFile << std::endl;
        exit(EXIT_FAILURE);
    }

    std::ofstream outputFileObj;
    outputFileObj.open(Files::outputFile);
    if(!outputFileObj.is_open())
    {
        std::cout << "There is no file called " << Files::outputFile << std::endl;
        exit(EXIT_FAILURE);
    }

    char chChar{};
    bool flag_remove_space{ false };
    while (inputFileObj.get(chChar))
    {
        if(flag_remove_space)
        {
            flag_remove_space = false;
            continue;
        }
        outputFileObj.put(chChar);
        if(chChar == '.')
        {
            outputFileObj.put('\n');
            flag_remove_space = true;
        }
    }

    std::cout << "*****************************************************\n";
    return 0;
}
