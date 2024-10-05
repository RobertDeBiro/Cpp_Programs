#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>

#include "Guitar.h"

class Inventory
{
    std::vector<Guitar> guitars;

public:
    void addGuitar(std::string, double, Builder, String, Type, Wood, Wood);
};

#endif // INVENTORY_H
