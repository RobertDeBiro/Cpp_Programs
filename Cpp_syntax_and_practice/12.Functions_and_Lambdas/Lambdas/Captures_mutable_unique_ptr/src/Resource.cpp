#include <iostream>
#include "../inc/Resource.hpp"

using std::cout;
using std::endl;
using std::string;

Resource::Resource(string n) : name(n)
{
    cout << "constructing " << name << endl;
}

Resource::Resource(const Resource& r) : name(r.name)
{
    cout << "copy constructing " << name << endl;
}

Resource& Resource::operator=(const Resource& r)
{
    //If this class managed Resource lifetime, clean up existing one
    //before setting new values.
    //No need here because string takes care of it.
    name = r.GetName();
    cout << "copy assigning " << name << endl;
    return *this;
}

Resource::~Resource(void)
{
    //If this class managed Resource lifetime, clean up existing one.
    //No need here because string takes care of it
    cout << "destructing " << name << endl;
}


