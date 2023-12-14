# `std::deque`

    template<
        class T,
        class Container = std::deque<T>
    > class deque;

- `std::deque` (**double-ended queue**) is an indexed sequence container that allows fast insertion
  and deletion at both its beginning and its end
- as opposed to `std::vector`, the elements of a `std::deque` are not stored contiguously:
  - typical implementations use a sequence of individually allocated fixed-size arrays,
    with additional bookkeeping, which means indexed access to deque must perform two pointer
    dereferences, compared to vector's indexed access which performs only one
- the storage of a deque is automatically expanded and contracted as needed
- pros comparing to `std::vector`:
  - expansion of a `std::deque` is cheaper than the expansion of a `std::vector` because
    it does not involve copying of the existing elements to a new memory location
- cons comparing to `std::vector`:
  - typically has large minimal memory cost

- time complexity:
  - Random access - constant `O(1)`
  - Insertion or removal of elements at the **end or beginning** - constant `O(1)`
  - Insertion or removal of elements - linear `O(n)`

- references:
  - <https://en.cppreference.com/w/cpp/container/deque>

--------------------------------------------------------------------------------

## Member functions

| Other     | Element access   | Capacity        | Modifiers       |
| :---      | :---             | :---            | :---            |
| 'assign'  | 'at'             | 'empty'         | 'clear'         |
|           | 'operator[]'     | 'size'          | 'insert'        |
|           | 'front'          | 'max_size'      | 'emplace'       |
|           | 'back'           | 'shrink_to_fit' | 'erase'         |
|           |                  |                 | `push_back`     |
|           |                  |                 | 'emplace_back'  |
|           |                  |                 | `pop_back`      |
|           |                  |                 | `push_front`    |
|           |                  |                 | 'emplace_front' |
|           |                  |                 | `pop_front`     |
|           |                  |                 | 'resize'        |
|           |                  |                 | 'swap'          |
