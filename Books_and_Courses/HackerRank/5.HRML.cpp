#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
using namespace std;


int main() {
    std::cout << "*****************************************************\n";
    
    /*
     * 1. input:
     *  - N - the number of lines in the HRML
     *  - Q - the number of queries
     */

    int n, q;
    cin >> n >> q;
    cin.ignore();

    string temp;
    vector<string> hrml;
    vector<string> quer;
    for(int i = 0;  i < n/2; i++)
    {
        getline(cin, temp);
        hrml.push_back(temp);
    }
    for(int i = 0;  i < q; i++)
    {
        getline(cin, temp);
        quer.push_back(temp);
    }

    map<string, string> m;
    vector<string> tag;



    std::cout << "*****************************************************\n";
    return 0;
}
