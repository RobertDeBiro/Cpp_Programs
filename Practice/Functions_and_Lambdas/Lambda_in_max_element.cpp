#include <iostream>
#include <array>
#include <algorithm> // std::max_element

struct Student
{
  std::string name{};
  int points{};
};

int main()
{
  std::array<Student, 8> stArr{
    { { "Albert", 3 },
      { "Ben", 5 },
      { "Christine", 2 },
      { "Dan", 8 }, // Dan has the most points (8)
      { "Enchilada", 4 },
      { "Francis", 1 },
      { "Greg", 3 },
      { "Hagrid", 5 } }
  };

  // Storing lambda in lambdaMax variable
  // - returning true if second element is bigger than first one
  auto lambdaMax{
    [](const auto& a, const auto& b)
    {
      return (a.points < b.points);
    }
  };

  std::array<Student, 8>::iterator bestStudent{ std::max_element(stArr.begin(), stArr.end(), lambdaMax) };

  std::cout << bestStudent->name << " is the best student.\n";

  return 0;
}
