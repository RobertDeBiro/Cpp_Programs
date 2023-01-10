#include <iostream>
#include <algorithm>
#include <tuple> // std::tuple, std::tie
#include <random>
#include <ctime>
#include <vector>
#include <cmath> // pow, abs

using vectorType = std::vector<int>;
using vectorSizeType = vectorType::size_type;

std::tuple<int, int> initialUserInput()
{
  std::cout << "Start where? ";
  int x;
  std::cin >> x;

  std::cout << "How many? ";
  int y;
  std::cin >> y;

  std::tuple<int, int> inituser{ x, y };
  return inituser;
}

int obtain_random_number()
{
    std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
    std::uniform_int_distribution<> number_scope{ 2, 4 };
    int random_number{ number_scope(mersenne) };
    return random_number;
}

void fillUpUserList(vectorType& userList, int squareRoot)
{
  for(auto element{ userList.begin() }; element != userList.end(); ++element, ++squareRoot)
      *element = squareRoot;
}

void printList(vectorType list)
{
  for(const auto & element : list)
    std::cout << element << " ";
  std::cout << '\n';
}

void playGame(vectorType& multipliedList, const int multiplier)
{
  std::cout << "I generated " << multipliedList.size() << " square numbers."
                " Do you know what each number is after multiplying it by " << multiplier << "?\n";

  int guessNumber{};
  do{
    std::cin >> guessNumber;
    vectorType::iterator it{ std::find(multipliedList.begin(), multipliedList.end(), guessNumber) }; // we could use also auto as data type
    if (it != multipliedList.end())
    {
      multipliedList.erase(it);
      if(multipliedList.size())
        std::cout << "Nice! " << multipliedList.size() << " numbers left.\n";
      else
        std::cout << "Nice! You found all numbers, good job!\n";
    }
    else
    {
      int index{};
      for(const auto& element : multipliedList)
      {
        if(abs(guessNumber - element) <= 4)
          break;
        ++index;
      }
      auto vectorIndex{ static_cast<vectorSizeType>(index) };
      if(vectorIndex != multipliedList.size())
        std::cout << guessNumber << " is wrong! Try " << multipliedList[vectorIndex] << " next time.\n";
      else
        std::cout << guessNumber << " is wrong!\n";
      break;
    }
  } while(multipliedList.size());
}

int main()
{
  /*
   * Initial user input
   */
  int squareRoot, numbersAmount;
  std::tie(squareRoot, numbersAmount) = initialUserInput();

  /*
   * Generate root user list
   */
  vectorType userList(static_cast<vectorSizeType>(numbersAmount)); // Create empty user root list
  fillUpUserList(userList, squareRoot); // Fill up user root list
  std::cout << "Print user root list:\n";
  printList(userList);

  /*
   * Generate squared list
   */
  std::for_each(userList.begin(), userList.end(), [](int& x) { x = pow(x, 2); }); // Square user root list
  std::cout << "Print squared user root list:\n";
  printList(userList);

  /*
   * Generate multiplied list
   */
  int multiplier{ obtain_random_number() };
  vectorType multipliedList{ userList };
  std::for_each(multipliedList.begin(), multipliedList.end(), ([multiplier](int& y) { y *= multiplier; })); // Multiply squared user list with multiplier
  std::cout << "Print multiplied list:\n";
  printList(multipliedList);

  /*
   * Play a game
   */
  playGame(multipliedList, multiplier);

  return 0;
}
