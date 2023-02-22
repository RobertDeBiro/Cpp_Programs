## Syntax:  
    template<  
        class CharT,  
        class Traits = std::char_traits<CharT>,  
        class Allocator = std::allocator<CharT>  
    > class basic_string;  

    std::string = std::basic_string<char>

- references:
    - https://en.cppreference.com/w/cpp/string/basic_string

## Member functions
| Other     | Element access              | Capacity       | Operations   | Search              |
| :---      | :---                        | :---           | :---         | :---                |
| -assign   | -at                         | -empty         | -clear       | -find               |
|           | -operator[]                 | +size/length   | -insert      | -rfind              |
|           | -front                      | -max_size      | -erase       | -find_first_of      |
|           | -back                       | -reserve       | -push_back   | -find_first_not_of  |
|           | -data                       | -capacity      | -pop_back    | -find_last_of       |
|           | -c_str                      | -shrink_to_fit | +append      | -find_last_not_of   |
|           | -operator basic_string_view |                | -operator+=  |                     |
|           |                             |                | -compare     |                     |
|           |                             |                | +replace     |                     |
|           |                             |                | -substr      |                     |
|           |                             |                | -copy        |                     |
|           |                             |                | -resize      |                     |
|           |                             |                | -swap        |                     |
|           |                             |                | -copy        |                     |
