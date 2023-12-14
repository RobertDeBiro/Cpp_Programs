# `std::map`

    template<
        class Key,
        class T,
        class Compare = std::less<Key>,
        class Allocator = std::allocator<std::pair<const Key, T>
    > class map;

- `std::map` is an associative container that contains a sorted list of **key-value** pairs with unique keys
- sorting is done using the key comparison function `Compare`
  - by default `std::map` sorts elements with increasing values
  - we can change that, e.g. to sort it by decreasing values
- `std::map` is generally used in **Dictionary type problems**
- usually implemented as red-black trees

- time complexity:
  - search, removal, and insertion operations have logarithmic complexity

- references:
  - <https://en.cppreference.com/w/cpp/container/map>

--------------------------------------------------------------------------------

## Member functions

| Element access   | Capacity     | Modifiers          | Lookup        | Observers    |
| :---             | :---         | :---               | :---          | :---         |
| `at`             | 'empty'      | 'clear             | 'count'       | 'key_comp'   |
| `operator[]`     | `size`       | `insert`           | 'find'        | 'value_comp' |
|                  | 'max_size'   | 'insert_or_assign' | 'contains'    |              |
|                  |              | 'emplace'          | 'equal_range' |              |
|                  |              | `erase`            | 'lower_bound' |              |
|                  |              | 'swap'             | 'upper_bound' |              |
|                  |              | 'extract'          |               |              |
|                  |              | 'merge'            |               |              |
