#ifndef GUITAR_H
#define GUITAR_H

#include "GuitarSpec.h"

enum class Type
{
    ACOUSTIC,
    ELECTRIC
};

enum class Builder
{
    FENDER,
    MARTIN,
    GIBSON,
    COLLINGS,
    OLSON,
    RYAN,
    PRS,
    ANY
};

enum class Wood
{
    INDIAN_ROSEWOOD,
    BRAZILIAN_ROSEWOOD,
    MAHOGANY,
    MAPLE,
    COCOBOLO,
    CEDAR,
    ADIRONDACK,
    ALDER,
    SITKA
};


class Guitar
{
    std::string serialNumber;
    double price;
    GuitarSpec spec;

public:
    Guitar(std::string serialNumber, double price, GuitarSpec spec);

    std::string getSerialNumber(){ return serialNumber; }
    double getPrice(){ return price; }
    void setPrice(double newPrice){ price = newPrice; }
    GuitarSpec getSpec(){ return spec; }
};

#endif // GUITAR_H
