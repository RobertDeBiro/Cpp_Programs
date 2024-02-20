# Different ways to create threads in C++11

 1. Function Pointers
 2. Lambda functions
 3. Functors
 4. Non-static member functions
 5. Static member functions

---

## Functors

- in programming, a **functor** is a concept borrowed from functional programming and is
  often used in languages that support higher-order functions or function objects
- a functor is simply an ***object that can be called as if it were a function***
- in C++, functors are typically implemented as classes that define the `operator()` member function
  - this allows instances of the functor class to be invoked using the function call syntax, just like regular functions
- functors are often used to encapsulate behavior that can be passed as a parameter to algorithms or used in other
  contexts where a function is expected.

---

## References

- <https://www.youtube.com/watch?v=hCvc9y39RDw&list=PLk6CEY9XxSIAeK-EAh3hB4fgNvYkYmghp&index=2>
