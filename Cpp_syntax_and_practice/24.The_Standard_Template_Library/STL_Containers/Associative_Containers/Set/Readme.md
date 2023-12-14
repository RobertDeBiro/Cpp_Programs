# `std::set`

    template<
        class Key,
        class Compare = std::less<Key>,
        class Allocator = std::allocator<Key>
    > class set;

- `std::set` is an associative container that contains a sorted set of unique objects of type `Key`
- sorting is done using the key comparison function `Compare`
  - `std::set` saves unique elements in sorted order
  - by default elements are sorted in **ascending** order - means that `std::less<>` is used
  - if we want to sort in **descending** order, we can use `std::greater<>`
- usually implemented as red-black trees

- time complexity:
  - search, removal, and insertion operations have logarithmic complexity

- references:
  - <https://en.cppreference.com/w/cpp/container/set>

--------------------------------------------------------------------------------

## Member functions

| Capacity    | Modifiers       | Lookup        | Observers    |
| :---        | :---            | :---          | :---         |
| 'empty'     | 'clear'         | 'count'       | 'key_comp'   |
| 'size'      | `insert`        | `find`        | 'value_comp' |
| 'max_size'  | `emplace`       | 'contains'    |              |
|             | 'emplace_hint'  | 'equal_range' |              |
|             | `erase`         | 'lower_bound' |              |
|             | 'swap'          | 'upper_bound' |              |
|             | 'extract'       |               |              |
|             | 'merge'         |               |              |
