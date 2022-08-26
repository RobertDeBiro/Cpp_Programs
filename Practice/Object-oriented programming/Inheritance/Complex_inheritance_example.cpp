// Summary and quiz

#include <iostream>
#include <string>
#include <array>
#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()

// Generate a random number between min and max (inclusive)
// Assumes std::srand() has already been called
// Assumes max - min <= RAND_MAX
int getRandomNumber(int min, int max)
{
  static constexpr double fraction{ 1.0 / (RAND_MAX + 1.0) }; // static used for efficiency, so we only calculate this value once
  // evenly distribute the random number across our range
  return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}

class Creature
{
protected:
    std::string m_name{};
    char m_symbol{};
    int m_health{};
    int m_damage{};
    int m_gold{};

public:
    Creature(const std::string& name, char symbol, int health, int damage, int gold)
        : m_name{ name }, m_symbol{ symbol }, m_health{ health }, m_damage{ damage }, m_gold{ gold }
    {
    }

    const std::string& getName() const { return m_name; }
    char getSymbol() const { return m_symbol; }
    int getHealth() const { return m_health; }
    int getDamagePerAttack() const { return m_damage; }
    int getGold() const { return m_gold; }

    void reduceHealth(const int reduce) { m_health -= reduce; }
    bool isDead() { return (m_health <= 0); }
    void addGold(int gold) { m_gold += gold; }
};

class Player : public Creature
{
private:
    int m_level{ 1 };

public:
    Player(std::string& name) : Creature(name, '@', 10, 1, 0)
    {
    }

    void levelUp()
    {
        ++m_level;
        ++m_damage;
    }
    int getLevel() const { return m_level; }
    bool hasWon() { return (m_level >= 20); }
};

class Monster : public Creature
{
public:
    enum class Type
    {
        dragon,
        orc,
        slime,
        max_types
    };

private:
    static const Creature getDefaultCreature(Type type)
    {
        static std::array<Creature, static_cast<std::size_t>(Type::max_types)> monsterData{
            { { "dragon", 'D', 20, 4, 100 },
            { "orc", 'o', 4, 2, 25 },
            { "slime", 's', 1, 1, 10 } }
        };

        return monsterData.at(static_cast<std::size_t>(type));
    }

public:
    Monster(Type monster) : Creature{ getDefaultCreature(monster) }
    {
    }

    static const Monster getRandomMonster()
    {
        int num{ getRandomNumber(0, static_cast<int>(Type::max_types) - 1) };
        return Monster{ static_cast<Type>(num) }; // we cannot assign int to enum! - therefore, using static_cast
    }
};


int main()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr))); // set initial seed value to system clock

	for (int i{ 0 }; i < 10; ++i)
	{
		Monster m{ Monster::getRandomMonster() };
		std::cout << "A " << m.getName() << " (" << m.getSymbol() << ") was created.\n";
	}

	return 0;
}
