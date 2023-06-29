#include <iostream>

void precautions(int beers_amount)
{
    switch (beers_amount)
    {
        case 1:
            std::cout << "Cheers!\n";
        case 2:
            std::cout << "Cheers, but be careful!\n";
            break;
        case 3:
            std::cout << "Are you sure you want more beers?\n";
        case 4:
            std::cout << "At your place I really wouldn't drink anymore!\n";
        default:
            std::cout << "Sorry, we ran out of beers!\n";
            break;
    }
}

int main()
{
    std::cout << "Please, enter your age: ";
    int age;
    std::cin >> age;

    if(age >= 21)
        std::cout << "You are old enough, you can grab a beer!\n";
    else
        std::cout << "Sorry, but you are not old enough to dring alcohol!\n";
        std::cout << "You can have a soda if you want.\n";
    
    std::cout << "-------------------------------------------------------\n";

    std::cout << "How many beers you want?: ";
    int beers_amount;
    std::cin >> beers_amount;
    precautions(beers_amount);
    
    return 0;
}