#include <iostream>
#include <vector>
#include <algorithm>

void printv(const std::vector<int>& v)
{
    for (const auto elem : v)
        std::cout << elem << '\n';
}

int main()
{
    //---------------------------------------------------------
    // Populating a vector
    //---------------------------------------------------------
    std::vector<int> v;
    for (int i = 0; i < 5; i++)
        v.push_back(i);
    std::cout << "***** Populating vector 1 *****\n";
    printv(v);

    for (int i = 0; i < 5; )
        v.push_back(i++);
    std::cout << "***** Populating vector 2 *****\n";
    printv(v);

    int i = 0;
    std::generate_n(std::back_inserter(v), 5, [&]() { return i++; });
    std::cout << "***** Populating vector 3 *****\n";
    printv(v);

    std::cout << '\n';

    //---------------------------------------------------------
    // Counting the number of 3's
    //---------------------------------------------------------
    int count1 = 0;
    for (unsigned int i = 0; i < v.size(); i++)
    {
        if (v[i] == 3)
            count1++;
    }
    std::cout << "***** Amount of 3's 1 *****\n" << count1 << '\n';

    int count2 = 0;
    for (auto it = begin(v); it != end(v); it++)
    {
        if (*it == 3)
            count2++;
    }
    std::cout << "***** Amount of 3's 2 *****\n" << count2 << '\n';

    int count3 = std::count(begin(v), end(v), 3);
    std::cout << "***** Amount of 3's 3 *****\n" << count3 << '\n';

    std::cout << '\n';

    //---------------------------------------------------------
    // Removing the 3's
    //---------------------------------------------------------
    auto v2 = v;
    for (unsigned int index = 0; index < v2.size(); index++)
    {
        if (v2[index] == 3)
            v2.erase(v2.begin() + index);
    }
    std::cout << "***** Removing 3's from vector 1 *****\n";
    printv(v2);

    
    // When we changed the content of the collection we invalidate the iterator of the collection,
    // hence this ends up with error
    //  - this error doesn't appear neither inside Code::Blocks, or VSCode
    //auto v3 = v;
    //for (auto it = begin(v3); it != end(v3); it++)
    //{
    //    if (*it == 3)
    //        v3.erase(it);
    //}

    //std::cout << "***** Removing 3's from vector 2 *****\n";
    //printv(v3);

    auto v4 = v;
    auto endv4 = std::remove_if(begin(v4), end(v4), [](int elem) { return (elem == 3); });
    std::cout << "***** Removing 3's from vector 3 - std::remove_if *****\n";
    std::cout << "Vector size after std::remove_if = " << v4.size() << '\n';
    printv(v4); // This prints 2, 3, 4 at the end and not 3, 3, 3 - Why???
    std::cout << "Return from std::remove_if is: " << *endv4 << '\n';

    v4.erase(endv4, end(v4)); // Deleting elements moved to the end (i.e. removed) by the std::remove_if
    std::cout << "***** Removing 3's from vector 4 - vector.erase() *****\n";
    std::cout << "Vector size after vector.erase() = " << v4.size() << '\n';
    printv(v4);

    return 0;
}
