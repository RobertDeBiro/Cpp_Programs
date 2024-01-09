#include <iostream>
#include <stdio.h>
#include <cmath>

void update(int *a, int *b) {
    int temp = *a + *b;
    *b = std::abs(*a - *b);
    *a = temp;
}

int main() {
    std::cout << "*****************************************************\n";
    int a, b;
    int *pa = &a, *pb = &b;
    
    scanf("%d %d", &a, &b);
    update(pa, pb);
    printf("%d\n%d\n", a, b);

    std::cout << "*****************************************************\n";
    return 0;
}