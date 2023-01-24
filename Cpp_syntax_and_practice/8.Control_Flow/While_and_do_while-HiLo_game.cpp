// LearncCpp
// Control Flow and Error Handling
// Summary and quiz

#include <iostream>
#include <random>
#include <ctime>

int obtain_random_number()
{
    std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
    std::uniform_int_distribution<> number_scope{ 1, 100 };
    int random_number{ number_scope(mersenne) };
    return random_number;
}

int choose_the_number()
{
    int choosed_number{};
    while(1)
    {
        std::cin >> choosed_number;
        if(std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "You did not typed the integer number. Please, try again!\n";
        }
        else
        {
            std::cin.ignore(32767, '\n');
            return choosed_number;
        }
    }
}

void play_hi_lo()
{
    std::cout << "\n--------------- STARTING A GAME ---------------\n\n"
              << "I'm thinking of a number between 1 and 100.\n"
              << "You have 7 tries to guess what it is.\n";
    int random_number{ obtain_random_number() };
    int counter{ 1 };
    int choosed_number{};

    while (true)
    {
        std::cout << "Guess #" << counter << ": ";
        choosed_number = choose_the_number();

        if (choosed_number > random_number)
            std::cout << "Your guess is too high.\n";
        else if (choosed_number < random_number)
            std::cout << "Your guess is too low.\n";
        else
        {
            std::cout << "\n*************** CORRECT! YOU WIN! ***************\n\n";
            break;
        }

        if (counter == 7)
        {
            std::cout << "Sorry, you lose. The correct number was " << random_number << ".\n";
            break;
        }

        counter++;
    }
}

char user_interface()
{
    char play_again;
    do
    {
        std::cout << "Would you like to play again (y/n)? ";
        std::cin >> play_again;
    } while ((play_again != 'y') && (play_again != 'n'));

    return play_again;
}

int main()
{
    char play_next_game;
    do
    {
        play_hi_lo();
        play_next_game = user_interface();
    } while (play_next_game == 'y');

    std::cout << "Thank you for playing.";

    return 0;
}
