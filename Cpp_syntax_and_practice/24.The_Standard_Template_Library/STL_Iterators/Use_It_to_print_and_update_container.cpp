/*
 * C++ Primer
 * Exercise Section 3.4.1
 *  - Exercise 3.22

 * Input example:
Let me tell you a little story.
Once upon a time there was a man, and there was a woman.
And they had kids.

And now here we are today.
The end!
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

void printText(const vector<string>& varVect)
{
    for(auto it = varVect.begin(); it != varVect.end(); it++)
        std::cout << *it << '\n' ;
}

void printFirstParagraph(const vector<string>& varVect)
{
    for(auto it = varVect.begin(); it != varVect.end() && !it->empty(); it++)
        std::cout << *it << '\n' ;
}

void updateAndPrintFirstParagraph(vector<string>& varVect)
{
    for(auto it1 = varVect.begin(); it1 != varVect.end() && !it1->empty(); it1++)
    {
        for(auto it2 = it1->begin(); it2 != it1->end(); it2++)
        {
            *it2 = toupper(*it2);
        }
        std::cout << *it1 << '\n' ;
    }
}

int main()
{
    std::cout << "*****************************************************\n";

    vector<string> text;

    std::cout << "Enter some text containing 2 paragraphs:\n";
    int paragraph_counter;
    string line;
    while(paragraph_counter < 2)
    {
        getline(cin, line);
        if(line.empty())
            paragraph_counter++;
        text.push_back(line);
    }

    std::cout << "---------------------------------------------\n";
    std::cout << "Print full text:\n";
    printText(text);
    std::cout << "---------------------------------------------\n";

    std::cout << "Print only first paragraph:\n";
    printFirstParagraph(text);
    std::cout << "---------------------------------------------\n";

    std::cout << "Update and print first paragraph:\n";
    updateAndPrintFirstParagraph(text);
    std::cout << "---------------------------------------------\n";

    std::cout << "*****************************************************\n";
    return 0;
}