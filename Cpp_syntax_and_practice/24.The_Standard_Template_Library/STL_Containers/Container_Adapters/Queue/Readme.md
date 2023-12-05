## SYNTAX
    template<
        class T,
        class Container = std::deque<T>
    > class queue;

 - *std::queue* class is a container adapter that gives the programmer the functionality of 
   a queue - specifically, a FIFO (first-in, first-out) data structure
 - the class template acts as a wrapper to the underlying container
    - in other words, *std::queue* is implemented as some other container
    - by default it is implemented internally as *std::deque*

 - references:
    - https://en.cppreference.com/w/cpp/container/queue
--------------------------------------------------------------------------------

## Member functions
| Element access   | Capacity   | Modifiers  |
| :---             | :---       | :---       |
| +front           | +empty     | +push      |
| -back            | -size      | -emplace   |
|                  |            | +pop       |
|                  |            | -swap      |
