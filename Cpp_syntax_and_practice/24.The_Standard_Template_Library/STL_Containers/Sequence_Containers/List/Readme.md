# `std::list`

    template<
        class T,
        class Allocator = std::allocator<T>
    > class list;

- `std::list` is a sequence container that supports constant time 
   insertion and removal of elements from **anywhere in the container**
- fast random access is not supported (element is accessed with `O(n)`)
- it is implemented as a **doubly-linked list**
- it is not possible to use some STL algorithms on list objects
  - therefore `std::list` implements its own operations, such as `reverse` and `sort`

- time complexity:
  - Random access - complex `O(n)`
  - Insertion or removal of elements - constant `O(1)`

- references:
  - <https://en.cppreference.com/w/cpp/container/list>

--------------------------------------------------------------------------------

## Member functions

| Other     | Element access  | Capacity    | Modifiers       | Operations          |
| :---      | :---            | :---        | :---            | :---                |
| 'assign'  | 'front'         | 'empty'     | 'clear'         | `merge`             |
|           | 'back'          | 'size'      | 'insert'        | `splice`            |
|           |                 | 'max_size'  | 'emplace'       | 'remove, remove_if' |
|           |                 |             | 'erase'         | 'reverse'           |
|           |                 |             | 'push_back'     | `unique`            |
|           |                 |             | 'emplace_back'  | `sort`              |
|           |                 |             | 'pop_back'      |                     |
|           |                 |             | 'push_front'    |                     |
|           |                 |             | 'emplace_front' |                     |
|           |                 |             | 'pop_front'     |                     |
|           |                 |             | 'resize'        |                     |
|           |                 |             | 'swap'          |                     |
