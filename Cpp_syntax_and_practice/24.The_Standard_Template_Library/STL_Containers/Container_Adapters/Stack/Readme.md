## SYNTAX
    template<
        class T,
        class Container = std::deque<T>
    > class stack;

 - *std::stack* class is a container adapter that gives the programmer the functionality of 
   a stack - specifically, a LIFO (last-in, first-out) data structure
 - the class template acts as a wrapper to the underlying container
    - in other words, *std::stack* is implemented as some other container
    - by default it is implemented internally as *std::deque* (we can see that also in SYNTAX)

 - references:
    - https://en.cppreference.com/w/cpp/container/stack
--------------------------------------------------------------------------------

## Member functions
| Element access   | Capacity   | Modifiers  |
| :---             | :---       | :---       |
| +top             | +empty     | +push      |
|                  | -size      | -emplace   |
|                  |            | +pop       |
|                  |            | -swap      |
