## SYNTAX:
    template<
        class T,
        class Allocator = std::allocator<T>
    > class forward_list;
 
 - std::forward_list is a sequence container that supports fast
   insertion and removal of elements from anywhere in the container
 - fast random access is not supported (element is accessed with O(n))
 - it is implemented as a singly-linked list
    - so, it is similar as std::list, with the difference that we are able to put
      element only in fornt of the existing element

 - time complexity:
    - Random access - complex O(n)
    - Insertion or removal of elements - constant O(1)

 - references:
    - https://en.cppreference.com/w/cpp/container/forward_list

 - TODO: 3:23
--------------------------------------------------------------------------------

## Member functions
| Other     | Element access   | Capacity    | Modifiers       | Operations         |
| :---      | :---             | :---        | :---            | :---               |
| -assign   | -front           | -empty      | -clear          | +merge             |
|           |                  | -max_size   | -insert_after   | -splice_after      |
|           |                  |             | -emplace_after  | -remove, remove_if |
|           |                  |             | -erase_after    | -reverse           |
|           |                  |             | -push_front     | -unique            |
|           |                  |             | -emplace_front  | -sort              |
|           |                  |             | -pop_front      |                    |
|           |                  |             | -resize         |                    |
|           |                  |             | -swap           |                    |
