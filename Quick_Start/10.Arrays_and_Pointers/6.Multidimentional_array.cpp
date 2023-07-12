#include <iostream>

int main() {
    const int rows = 3;
    const int cols = 4;

    //* Multidimensional array - array of arrays
    //  - 2D array
    //  - leftmost length specification can be ommited
    int grid[rows][cols] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    //* Print 2D array
    //  - the best way to print 2D array is by using 2 for loops
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
