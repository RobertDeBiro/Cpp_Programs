#include "../inc/Guitar.h"

Guitar::Guitar(std::string serialNumber, double price, GuitarSpec spec)
    : this.serialNumber = serialNumber
    , this.price = price
    , this.spec = spec
{}
