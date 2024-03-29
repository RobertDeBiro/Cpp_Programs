#include <iostream>
#include <cstdio>

int max_of_four(int a, int b, int c, int d)
{
    int max = a;
    int arr[3]{ b, c, d };
    
    for(int* i = std::begin(arr); i != std::end(arr); i++)
    {
        if (*i > max)
            max = *i;
    }
    
    return max;
}

int main() {
    std::cout << "*****************************************************\n";

    int a, b, c, d;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    int ans = max_of_four(a, b, c, d);
    printf("%d\n", ans);
    
    std::cout << "*****************************************************\n";
    return 0;
}