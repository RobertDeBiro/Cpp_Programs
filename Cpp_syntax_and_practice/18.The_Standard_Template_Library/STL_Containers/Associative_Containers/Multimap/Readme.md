## SYNTAX:
    template<
        class Key,
        class T,
        class Compare = std::less<Key>,
        class Allocator = std::allocator<std::pair<const Key, T>
    > class multimap;

 - std::multimap is an associative container that contains a sorted list of key-value pairs
 - sorting is done using the key comparison function Compare
 - std::map is generally used in Dictionary type problems
 - usually implemented as red-black trees

 - time complexity:
    - search, removal, and insertion operations have logarithmic complexity

 - references:
    - https://en.cppreference.com/w/cpp/container/multimap

 - TODO: 12:04
--------------------------------------------------------------------------------

## Member functions
| Capacity       | Modifiers         | Lookup       | Observers   |
| :---           | :---              | :---         | :---        |
| -empty         | -clear            | +count       | -key_comp   |
| -size          | -insert           | +find        | -value_comp |
| -max_size      | -emplace          | -contains    |             |
|                | -emplace_hint     | +equal_range |             |
|                | -erase            | -lower_bound |             |
|                | -swap             | -upper_bound |             |
|                | -extract          |              |             |
|                | -merge            |              |             |
