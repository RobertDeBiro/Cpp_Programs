# `std::priority_queue`

    template<
        class T,
        class Container = std::vector<T>,
        class Compare = std::less<typename Container::value_type>
    > class priority_queue;

- `std::priority_queue` class is a container adapter that provides **constant time lookup**
  of the largest (by default) OR smallest element
  - cost of insertion and extraction is logarithmic
- the class template acts as a wrapper to the underlying container
  - in other words, `std::priority_queue` is implemented as some other container
  - by default it is implemented internally as `std::vector`
- internally is implemented like a heap using functions:
  - `std::make_heap`
  - `std::push_heap`
  - `std::pop_heap`

- time complexity:
  - Retrieve largest or smallest element - constant `O(1)`

- references:
  - <https://en.cppreference.com/w/cpp/container/priority_queue>
  - <https://www.youtube.com/watch?v=JSqznrzWGvc>

--------------------------------------------------------------------------------

## Member functions

| Element access   | Capacity   | Modifiers   |
| :---             | :---       | :---        |
| `top`            | `empty`    | `push`      |
|                  | 'size'     | 'emplace'   |
|                  |            | `pop`       |
|                  |            | 'swap'      |
