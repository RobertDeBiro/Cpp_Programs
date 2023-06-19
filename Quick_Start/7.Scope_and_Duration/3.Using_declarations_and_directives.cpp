#include <iostream>
#include <string>

int main()
{
    //* Using declarations
    using std::cout;
    cout << "Hello world!\n";

    // string s1{ "Hello world!\n"};

    //* Using directives
    using namespace std;
    string s2{ "Hello world!\n"};
    cout << s2;

    return 0;
}