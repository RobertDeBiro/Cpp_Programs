#include <vector>
#include <iostream>
using namespace std;


int main() {
    std::cout << "*****************************************************\n";

    cout << "Insert wanted container size: ";
    int vectSize;
    cin >> vectSize;

    vector<int> vect;
    vect.reserve(vectSize);
    
    cout << "Insert elements: ";
    int elem;
    for(int i = 0; i < vectSize; i++)
    {
        cin >> elem;
        vect.push_back(elem);
    }
    
    cout << "Container: ";
    for(const auto& elem : vect)
        cout << elem << ' ';
    cout << '\n';
    
    // Const iterator restricts us from changing the value to which iterator points
    //  - so called "read-only iterator"
    vector<int>::const_reverse_iterator it;

    cout << "Reversed container: ";
    for(it = vect.crbegin(); it != vect.crend(); it++)
        cout << *it << ' ';
    std::cout << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}
