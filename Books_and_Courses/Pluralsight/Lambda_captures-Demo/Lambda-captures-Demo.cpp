#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include "Resource.hpp"

using std::cout;
using std::vector;
using std::string;

int main()
{
    auto isOdd = [](int candidate) { return candidate % 2 != 0; };

    bool is3Odd = isOdd(3);
    bool is4Odd = isOdd(4);
    cout << is3Odd << '\n';
    cout << is4Odd << '\n';

    vector nums{ 2, 3, 4, -1, 1 };

    int odds = std::count_if(begin(nums), end(nums), isOdd);
    cout << "Number of odds: " << odds << '\n';

    int evens = std::count_if(begin(nums), end(nums), [](int candidate) { return candidate % 2 == 0; });
    cout << "Number of evens: " << evens << '\n';

    ////////////////////////////////////////////////

    //capturing by value and reference explicitly [x,y,&message]
    int x = 3;
    int y = 7;
    string message = "elements between ";
    message += std::to_string(x) + " and " + std::to_string(y) + " inclusive:";
    std::for_each(begin(nums), end(nums),
        [x, y, &message](int n)
        {
            if (n >= x && n <= y)
                message += " " + std::to_string(n);
        });

    cout << message << '\n';

    x = y = 0;
    std::for_each(begin(nums), end(nums),
        [&, x](int element) mutable {
            x += element;
            y += element;
            cout << "X = " << x << "; Y = " << y << '\n';
        });

    cout << '\n';
    cout << "x = " << x << "; y = " << y << '\n';

    ////////////////////////////////////////////////

    /*
     * Info about unique_ptr:
     *  - doesn't support copy semantics, so it cannot be captured by value
     *  - we can capture it by reference, but than we cannot use lambda after braces because
     *    unique_ptr will be deleted
     *  - we can use std::move, and it that way we can always use lambda because unique_ptr is now owned by lambda,
     *    but we cannot use unique_ptr if we are not in the lambda function
     */
    {
        // braces for scope
        auto pResource = std::make_unique<Resource>(", ");
        std::for_each(begin(nums), end(nums),
            [=, &message, p = std::move(pResource)](int n) // pr is new variable defined inside clause
        {
            if (n >= x && n <= y)
                message += p->GetName() + std::to_string(n);
            cout << message;
            cout << '\n';
        });

        cout << message << '\n';
    }

    return 0;
}
