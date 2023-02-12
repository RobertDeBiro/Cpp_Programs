#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    std::cout << "*****************************************************\n";

    /*
        a[i1, i2, ..., in]
            a[i1] = int a[j1, j2, ..., jk1]
            a[i2] = int a[j1, j2, ..., jk2]
            a[in] = int a[j1, j2, ..., jkn]
        
        1. input:
            n = the number of variable-lenght arrays
            q = the number od queries
        2. input:
            array_length_1 + variable-length_array_1
            array_length_2 + variable-length_array_2
            ...
            query_1 i j
            query_2 i j
        
        output: a[i] => a[j]
    */
    
    // Create vector that will contain variable-length arrays (vectors)
    vector<vector<int>> vect;
    
    // Insert amount of variable-length arrays that will be placed into vector
    vector<vector<int>>::size_type n;
    cin >> n;
    vect.reserve(n);
    
    // Insert amount of queries
    int q;
    cin >> q;
    
    // Fill vector with variable-length arrays
    vector<int>::size_type arr_size;
    for(int i = 1; i <= static_cast<int>(n); i++)
    {
        // Create variable-length arrays (vectors)
        cin >> arr_size;
        vector<int> arr(arr_size);
        
        // Insert elements for every variable-length array
        for(int j = 0; j < static_cast<int>(arr_size); j++)
        {
            int elem;
            cin >> elem;
            arr[j] = elem;
        }
        vect.push_back(arr);
    }
    
    // Declare query pairs
    int i, j;
    for(int count = 1; count <= q; count++)
    {
        // Insert query pairs
        cin >> i;
        cin >> j;

        // Print wanted element
        cout << vect[i][j] << '\n';
    }

    std::cout << "*****************************************************\n";
    return 0;
}