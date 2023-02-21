#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

vector<int> parseInts(string str) {
	stringstream ss;
    ss << str;
    char comma;
    int num;
    vector<int> nums;

    while(!ss.eof())
    {
        ss >> num;
        nums.push_back(num);
        if(!ss.eof())
            ss >> comma;
    }
    return nums;
}

int main() {
    cout << "*****************************************************\n";

    string str;
    cin >> str;
    vector<int> integers = parseInts(str);
    for(int i = 0; i < integers.size(); i++) {
        cout << integers[i] << "\n";
    }
    
    cout << "*****************************************************\n";
    return 0;
}