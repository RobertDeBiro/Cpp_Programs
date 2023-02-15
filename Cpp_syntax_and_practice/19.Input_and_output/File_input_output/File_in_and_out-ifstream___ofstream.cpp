#include <iostream>
#include <fstream>
#include <cstdlib> // exit
#include <set>
#include <string>

namespace Files
{
    const char* inputFile{ "C:\\Users\\rar\\Desktop\\Posao\\Programs\\Random_files\\txt\\EuropeCapitals.txt" };
    const char* outputFile{ "C:\\Users\\rar\\Desktop\\Posao\\Programs\\Random_files\\txt\\EuropeCapitals-Sorted.txt" };
}

int main()
{
    std::cout << "*****************************************************\n";

    // inputFile object will represent file from which we will input the text
    std::ifstream inputFileObj;

    // Open an input file in order to use it inside the program
    //  - if we don't initialize the ifstream object with the file when creating the object,
    //    then we can assign a file to it by using open() member function
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
    while(inputFileObj.good()) // The same as while(inputFileObj)
    {
        filterAndSort.insert(bufferWord);
        inputFileObj >> bufferWord;
    }

    // outputFile object will represent file in which we will output the text
    std::ofstream outputFileObj;
    outputFileObj.open(Files::outputFile);

    // Write filtered and sort events into new file
    for(std::set<std::string>::iterator it = filterAndSort.begin(); it != filterAndSort.end(); it++)
    {
        outputFileObj << *it << std::endl;
    }

    inputFileObj.close();
    outputFileObj.close();

    std::cout << "*****************************************************\n";
    return 0;
}
