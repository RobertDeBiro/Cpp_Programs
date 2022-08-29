#include <iostream>
#include <string>

enum class MonsterSpecies
{
    ogre,
    dragon,
    orc,
    spider,
    slime
};

struct Monster
{
    MonsterSpecies monsterSpecies{};
    std::string name{};
    double health{};
};

void printMonster(Monster monster)
{
    if(monster.monsterSpecies == MonsterSpecies::ogre)
        std::cout << "This Ogre is named " << monster.name << " and has " << monster.health << ".\n";
    else if(monster.monsterSpecies == MonsterSpecies::dragon)
        std::cout << "This Dragon is named " << monster.name << " and has " << monster.health << ".\n";
    else if(monster.monsterSpecies == MonsterSpecies::orc)
        std::cout << "This Orc is named " << monster.name << " and has " << monster.health << ".\n";
    else if(monster.monsterSpecies == MonsterSpecies::spider)
        std::cout << "This Spider is named " << monster.name << " and has " << monster.health << ".\n";
    else if(monster.monsterSpecies == MonsterSpecies::slime)
        std::cout << "This Slime is named " << monster.name << " and has " << monster.health << ".\n";
    else
        std::cout << "Monster doesn't exist!" << '\n';
}

int main()
{
    Monster ogre{ MonsterSpecies::ogre, "Torg", 145 };
    Monster slime{ MonsterSpecies::slime, "Blurp", 23 };

    printMonster(ogre);
    printMonster(slime);

    return 0;
}
