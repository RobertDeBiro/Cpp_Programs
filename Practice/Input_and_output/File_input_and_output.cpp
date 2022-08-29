#include <iostream>
#include <fstream>
#include <cstdlib> // exit
#include <set>
#include <string>

namespace Files
{
    const char* inputFile{ "C:\\Users\\rar\\Desktop\\Posao\\Programming\\C++\\Programs\\VSCode\\Practice\\Input and output\\txt files\\EuropeCapitals.txt" };
    const char* outputFile{ "C:\\Users\\rar\\Desktop\\Posao\\Programming\\C++\\Programs\\VSCode\\Practice\\Input and output\\txt files\\EuropeCapitals-Sorted.txt" };
}

int main()
{
    // inputFile object will present file from which we will input the text
    std::ifstream inputFileObj;

    // Open an input file in order to use it inside the program
    inputFileObj.open(Files::inputFile);

    // Protection if something goes wrong while opening the file
    if(!inputFileObj.is_open())
    {
        std::cout << "There is no file called " << Files::inputFile << std::endl;
        exit(EXIT_FAILURE);
    }

    // Filter (delete duplicated events) and sort input file
    std::set<std::string> filterAndSort;
    std::string bufferWord;
    inputFileObj >> bufferWord;
    while(inputFileObj.good())
    {
        filterAndSort.insert(bufferWord);
        inputFileObj >> bufferWord;
    }

    // outputFile object will present file in which we will output the text
    std::ofstream outputFileObj;
    outputFileObj.open(Files::outputFile);

    // Write filtered and sort events into new file
    for(std::set<std::string>::iterator it = filterAndSort.begin(); it != filterAndSort.end(); it++)
    {
        outputFileObj << *it << std::endl;
    }

    inputFileObj.close();
    outputFileObj.close();

    return 0;
}
