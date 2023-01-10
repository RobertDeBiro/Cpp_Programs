#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include <string>

class Resource
{
private:
    std::string name;
public:
    Resource(std::string n);
    Resource(const Resource& r); // copy constructor
    Resource& operator=(const Resource& r); // copy assignment operator
    ~Resource(void);
    std::string GetName() const { return name; }
};

#endif
