#ifndef GUITARSPEC_H
#define GUITARSPEC_H

class GuitarSpec
{
    Builder builder;
    std::string model;
    Type type;
    Wood backWood;
    Wood topWood;
    int numStrings;

public:
    GuitarSpec(Builder, std::string, Type, int, Wood, Wood);

    Builder getBuilder(){ return builder; }
    std::string getModel(){ return model; }
    Type getType(){ return type; }
    Wood getBackWood(){ return backWood; }
    Wood getTopWood(){ return topWood; }
    int getNumStrings(){ return numStrings; }

    bool matches(GuitarSpec otherSpec);
};

#endif // GUITARSPEC_H