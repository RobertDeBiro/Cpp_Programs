/*
 * LearnCpp
 * Basic Object-oriented Programming
 * Summary and quiz
 */

#include <string>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <array>

class Monster
{
public:
    //* User-defined data type nested inside class
    //  - user-defined data type is defined inside a class always before member variables and
    //    functions are defined
    enum class Type
    {
        dragon,
        goblin,
        ogre,
        orc,
        skeleton,
        troll,
        vampire,
        zombie,
        max_monster_types
    };

private:
    Type m_type{};
    std::string m_name{};
    std::string m_roar{};
    int m_hitPoints{};

public:
    Monster(Type type, std::string name, std::string roar, int hitPoints) :
        m_type{ type }, m_name{ name }, m_roar{ roar }, m_hitPoints{ hitPoints }
    {
    }

    void print()
    {
        std::cout << m_name << " the " << getTypeString()
            << " has " << m_hitPoints << " and says " << m_roar << '\n';
    }

    std::string getTypeString() const
    {
        switch(m_type)
        {
            case Type::dragon:      return "dragon";
            case Type::goblin:      return "goblin";
            case Type::ogre:        return "ogre";
            case Type::orc:         return "orc";
            case Type::skeleton:    return "skeleton";
            case Type::troll:       return "troll";
            case Type::vampire:     return "vampire";
            case Type::zombie:      return "zombie";
            default:                return "???";
        }
    }
};

class MonsterGenerator
{
public:
    //* Generate a random number between min and max (inclusive)
	//  - assumes std::srand() has already been called
	//  - assumes max - min <= RAND_MAX
	static int getRandomNumber(int min, int max)
	{
        // static used for efficiency, so we only calculate this value once
		static constexpr double fraction { 1.0 / (RAND_MAX + 1.0) };

		// evenly distribute the random number across our range
		return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
	}

    //* Static member function
    // When we have member function that behaves the same for every particular object, i.e.
    // that doesn't depend on object calling the function, it is the best to make that function
    // static in order to show that it doesn't depend on particular object
    static Monster generateMonster()
    {
        auto type{ static_cast<Monster::Type>(getRandomNumber(0, static_cast<int>(Monster::Type::max_monster_types) - 1)) };
		int hitPoints{ getRandomNumber(1, 100) };

		// using 'constexpr' because then we can initialize these variables inside class definition
		static constexpr std::array s_names{ "Blarg", "Moog", "Pksh", "Tyrn", "Mort", "Hans" };
		static constexpr std::array s_roars{ "*ROAR*", "*peep*", "*squeal*", "*whine*", "*hum*", "*burp*" };

		// Without the cast, compilers with a high warning level complain about
		// an implicit cast from a signed to an unsigned integer.
		auto name{ s_names[getRandomNumber(0, static_cast<int>(s_names.size()-1))] };
		auto roar{ s_roars[getRandomNumber(0, static_cast<int>(s_roars.size()-1))] };

		return { type, name, roar, hitPoints };
    }
};

int main()
{
    std::cout << "*****************************************************\n";

	std::srand(static_cast<unsigned int>(std::time(nullptr))); // set initial seed value to system clock

	Monster m{ MonsterGenerator::generateMonster() };
	m.print();

    std::cout << "*****************************************************\n";
	return 0;
}
