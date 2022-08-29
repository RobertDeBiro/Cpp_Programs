// LearnCpp - Bit manipulation with bitwise operators and bit masks

#include <iostream>
#include <cstdint>
#include <bitset>

int main()
{
    // Bit masks
    constexpr std::uint8_t option_viewed{ 0x01 };      // 0000 0001
    constexpr std::uint8_t option_favorited{ 0x04 };   // 0000 0100
    constexpr std::uint8_t option_deleted{ 0x80 };     // 1000 0000

    // myArticleFlags variable presents bit flag
    //  - bit flag is object that holds several individual bits i.e. holds several specifications (parameters),
    //    each presented by a single bit
    //  - thise specifications (parameters) are defined bit masks

    // Setting the article as favorited
    //  - here we created bit flag as std::uint8_t, but std::bitset<n> can be also used
    std::uint8_t myArticleFlags {option_favorited};
    std::cout << "myArticle favorited = " << (std::bitset<8>)myArticleFlags << "\n"; // convert std::uint8_t so std::biset in order to display it as a binary, not char

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

    return 0;
}
