#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

// We can define symbolic constants inside header file without violating the ODR because
// symbolic constants have internal linkage by default
constexpr double gravity{ 9.8 };

#endif