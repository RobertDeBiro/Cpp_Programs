#include "../inc/GuitarSpec.h"

GuitarSpec::GuitarSpec(Builder builder, std::string model, Type type,
                       int numStrings, Wood backWood, Wood topWood)
    : this.builder = builder
    , this.model = model
    , this.type = type
    , this.numStrings = numStrings
    , this.backWood = backWood
    , this.topWood = topWood
{}

bool GuitarSpec::matches(GuitarSpec otherSpec)
{
    if (builder != otherSpec.builder)
        return false;
    if ((model != null) && (model.compare("") != 0) && (model.compare(otherSpec.model) != 0))
        return false;
    if (type != otherSpec.type)
        return false;
    if (numStrings != otherSpec.numStrings)
        return false;
    if (backWood != otherSpec.backWood)
        return false;
    if (topWood != otherSpec.topWood)
        return false;
    
    return true;
}
