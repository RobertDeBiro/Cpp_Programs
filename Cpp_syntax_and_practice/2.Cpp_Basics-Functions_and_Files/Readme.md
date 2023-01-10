# One Definition Rule (ODR)

## Within a given file

- function, object, type, or template can only have one definition
  
## Within a given program

- a normal function or an object can only have one definition
    - the case only for functions and objects with external linkage
- a type, template function, and inline function can have multiple definitions so long as they are identical (therefore, they are exempt from this rule)
  
## Personal conclusion

- header guard prevents that the same header file is included more than once into .cpp file
    - if header file contains e.g. function definition and is introduced more than once into same .cpp file, we would violate ODR
    - with header guards we won't violate ODR because it will be introduced only once
    - but this is true and valid only when we are using just main.cpp
- if we are using several .cpp files, header guards won't help us avoiding ODR because same function definitions cannot be present multiple times in one program
    - the best solution for this is to avoid using any definition in header file
    - but, user-defined type definitions are usually used in header files
    - however, the difference is that user-defined type definitions can be present multiple times in one program (but not in one file), as long as they are the same
        - for user-defined type definitions guards are mandatory in order to avoid ODR violation
- therefore, using header guards in .h file is mandatory to satisfy all requirements previously mentioned
