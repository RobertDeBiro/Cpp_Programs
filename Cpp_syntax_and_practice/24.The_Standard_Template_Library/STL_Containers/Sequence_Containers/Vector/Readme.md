# `std::vector`

    template<
        class T,
        class Allocator = std::allocator<T>
    > class vector;

- `std::vector` is a sequence container, also known as Dynamic Array or Array List
- `std::vector` is actually a mix of `std::array` and `std::list`
  - it can access element just like normal array, with complexity `O(1)`
  - it can dynamically increase and decrease, just like list

- time complexity:
  - Random access - constant `O(1)`
  - Insertion or removal of elements at the end - amortized constant `O(1)`
  - Insertion or removal of elements - linear in the distance to the end of the vector `O(n)`

- references:
  - <https://en.cppreference.com/w/cpp/container/vector>

--------------------------------------------------------------------------------

## Member functions

| Other     | Element access   | Capacity        | Modifiers       |
| :---      | :---             | :---            | :---            |
| `assign`  | `at`             | 'empty'         | 'clear'         |
|           | `operator[]`     | `size`          | `insert`        |
|           | 'front'          | 'max_size'      | `emplace`       |
|           | 'back'           | `reserve`       | `erase`         |
|           | 'data'           | `capacity`      | `push_back`     |
|           |                  | `shrink_to_fit` | 'emplace_back'  |
|           |                  |                 | `pop_back`      |
|           |                  |                 | `resize`        |
|           |                  |                 | 'swap'          |
