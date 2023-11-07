/*
 * LearnCpp
 * Bit Manipulation
 * Bit manipulation with bitwise operators and bit masks
 */

#include <iostream>
#include <cstdint>
#include <bitset>

int main()
{
    std::cout << "*****************************************************\n";

    //********** Manipulate bit flag **********
    // Flag will be used to represent options available by bit masks

    // Bit masks with hexadecimal values
    constexpr std::uint8_t option_viewed{ 0x01 };      // 0000 0001
    constexpr std::uint8_t option_favorited{ 0x04 };   // 0000 0100
    constexpr std::uint8_t option_deleted{ 0x80 };     // 1000 0000
    
    // Setting the article as favorited
    std::uint8_t myArticleFlags {option_favorited}; 

    // Convert std::uint8_t to std::biset in order to display it as a binary, not char
    std::cout << "myArticle favorited = " << (std::bitset<8>)myArticleFlags << "\n";

    // Setting the article as viewed
    myArticleFlags |= option_viewed;
    std::cout << "myArticle favorited and viewed = " << (std::bitset<8>)myArticleFlags << "\n";

    // Check if article was deleted
    if(myArticleFlags & option_deleted)
    {
        // Do nothing
    }

    // Clear the article as a favorite
    myArticleFlags &= ~option_favorited;
    std::cout << "myArticle viewed = " << (std::bitset<8>)(myArticleFlags) << "\n";

    // Initialize bit flag typed with std::bitset<8>
    std::bitset<8> myArticleFlags_bitset {option_favorited};
    std::cout << "myArticle favorited = " << myArticleFlags_bitset << "\n";

    std::cout << "*****************************************************\n";
    return 0;
}
