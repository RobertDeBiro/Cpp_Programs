#ifndef PHONEDISPLAY_HPP
#define PHONEDISPLAY_HPP

#include "IObserver.hpp"

class PhoneDisplay : public IObserver
{
public:
    void update() override;
};

#endif