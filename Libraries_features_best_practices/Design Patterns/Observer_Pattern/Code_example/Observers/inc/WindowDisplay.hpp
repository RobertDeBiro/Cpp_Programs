#ifndef WINDOWSDISPLAY_HPP
#define WINDOWSDISPLAY_HPP

#include "IObserver.hpp"

class WindowDisplay : public IObserver
{
public:
    void update() override;
};

#endif