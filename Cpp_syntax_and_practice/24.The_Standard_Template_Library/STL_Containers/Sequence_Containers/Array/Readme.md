
# `std::array`

    template<
        class T, 
        std::size_t N
    > struct array;

- `std::array` is a sequence container that encapsulates fixed size array
- this container is an aggregate type with the same semantics as a struct  
  holding a C-style array `T[N]` as its only non-static data member
- unlike a C-style array, it doesn't decay to `T*` automatically

- time complexity:
  - Random access - constant `O(1)`

- references:
  - <https://en.cppreference.com/w/cpp/container/array>

--------------------------------------------------------------------------------

## Member functions

| Element access    | Capacity      | Operations     |
| :---              | :---          | :---           |
| `at`              | `empty`       | `fill`         |
| `operator[]`      | `size`        | `swap`         |
| `front`           | `max_size`    |                |
| `back`            |               |                |
| `data`            |               |                |
