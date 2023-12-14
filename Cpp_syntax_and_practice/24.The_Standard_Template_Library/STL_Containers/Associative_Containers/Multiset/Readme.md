# `std::multiset`

    template<
        class Key,
        class Compare = std::less<Key>,
        class Allocator = std::allocator<Key>
    > class multiset;

- `std::multiset` is an associative container that contains a sorted set of objects of type `Key`
- `std::multiset` is the same as `std::set`, except multiple keys with equivalent values are allowed
- sorting is done using the key comparison function `Compare`
- usually implemented as red-black trees

- time complexity:
  - search, removal, and insertion operations have logarithmic complexity

- references:
  - <https://en.cppreference.com/w/cpp/container/multiset>

--------------------------------------------------------------------------------

## Member functions

| Capacity     | Modifiers       | Lookup        | Observers    |
| :---         | :---            | :---          | :---         |
| 'empty'      | 'clear'         | 'count'       | 'key_comp'   |
| 'size'       | 'insert'        | 'find'        | 'value_comp' |
| 'max_size'   | 'emplace'       | 'contains'    |              |
|              | 'emplace_hint'  | 'equal_range' |              |
|              | 'erase'         | 'lower_bound' |              |
|              | 'swap'          | 'upper_bound' |              |
|              | 'extract'       |               |              |
|              | 'merge'         |               |              |
