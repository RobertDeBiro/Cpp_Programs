#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    cout << "*****************************************************\n";

	string a, b;
    cin >> a >> b;

    cout << a.size() << " " << b.size() << '\n';
    cout << a + b << '\n';
    swap(a[0], b[0]);
    cout << a << ' ' << b << '\n';
  
    cout << "*****************************************************\n";
    return 0;
}