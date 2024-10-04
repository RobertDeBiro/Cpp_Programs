#include <iostream>
#include <string>
#include <functional>  // for std::hash

int main()
{
    std::hash<int> hash_int;
    std::hash<std::string> hash_string;

    int myInt = 42;
    std::string myStr = "Hello, World!";

    //* Hash of Integer (42)
    /**
     * The hash value for the integer 42 is simply 42 because, by default, the hash function for integers is designed
     * to return the same value as the integer itself.
     * This is useful since the integer value is already a unique identifier in the context of hashing.
    **/
    std::cout << "Hash of int: " << hash_int(myInt) << std::endl;

    //* Hash of String ("Hello, World!")
    /**
     * The hash value 18371290486108036847 for the string "Hello, World!" is a much larger number, and it is a result
     * of the hashing algorithm used by 'std::hash' for strings.
     * This value is generated through a more complex calculation involving the characters in the string.
     * The purpose of hashing a string is to create a unique representation of its contents that can be used for fast comparisons and lookups,
     * especially in hash-based data structures like 'std::unordered_map'.
     * 
     */
    std::cout << "Hash of string: " << hash_string(myStr) << std::endl;

    return 0;
}
