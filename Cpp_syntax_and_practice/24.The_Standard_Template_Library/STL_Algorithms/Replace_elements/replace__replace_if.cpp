/*
 * replace( ForwardIt first, ForwardIt last, const T& old_value, const T& new_value ) -> void
 *
 * replace_if( ForwardIt first, ForwardIt last, UnaryPredicate p, const T& new_value ) -> void
 * 
 *  - included in <algorithm>
 * 
 * References:
 *  - https://en.cppreference.com/w/cpp/algorithm/replace
 */

#include <iostream>
#include <algorithm>

int main()
{
    std::cout << "*****************************************************\n";

    std::string str1("I-am-developer!");

    std::cout << "Original string: " << str1 << '\n';
    std::replace(str1.begin(), str1.end(), '-', ' ');
    std::cout << "Changed string: " << str1 << '\n';

    std::cout << "----------------------------\n";

    std::string str2{"Hello1World2!3"};
    std::cout << "Original string: " << str2 << '\n';
    auto cond{
        [](char c)
        {
            return (isdigit(c));
        }
    };
    std::replace_if(str2.begin(), str2.end(), cond, ' ');
    std::cout << "Changed string: " << str2 << '\n';

    std::cout << "*****************************************************\n";
    return 0;
}
