# Atomic variables

```cpp
#include <atomic>

struct atomic
```

- `std::atomic` is a template class provided by the C++ Standard Library that allows for atomic operations on certain types
- atomic operations are operations that are guaranteed to be indivisible and non-interruptible,
  even in the presence of concurrent execution by multiple threads
- they are essential for writing correct concurrent and multithreaded code
- using `std::atomic` variable is similar to using variable together with `mutex` variable
  - the difference between this approach and mutex approach is that mutex blocks thread execution
  - blocking thread execution can be dangerous because, if not implemented properly, can cause **deadlock**

---

## Key points about `std::atomic`

1.**Atomic Types**

- `std::atomic` can be used with a variety of types, including:
  - integral types (`int`, `long`, `short`...)
  - floating-point types (`float`, `double`)
  - user-defined types (if they are trivially copyable)

2.**Atomic Operations**

- `std::atomic` provides various atomic operations that can be performed on the underlying value, such as:
  - load
  - store
  - exchange
  - compare-and-exchange (CAS)
  - fetch-and-add
  - fetch-and-subtract
- these operations are designed to be thread-safe and ensure atomicity

3.**Memory Ordering**

- `std::atomic` operations can be specified with memory orderings to control the visibility
  and ordering of memory operations between threads
- memory orderings determine how the memory accesses performed by one thread are ordered
  with respect to the memory accesses performed by other threads

4.**Lock-Free Operations**

- `std::atomic` operations can be implemented in a lock-free manner, meaning they do not require
  explicit locks or mutexes to ensure thread safety
- instead, they typically use low-level hardware primitives like compare-and-swap (CAS) instructions provided by modern CPUs

5.**Portable Concurrency**

- `std::atomic` provides a portable and standardized way to write concurrent code that works across different platforms and architectures
- it abstracts away the platform-specific details of atomic operations and memory ordering,
  allowing developers to write thread-safe code without worrying about platform-specific quirks

---

## Member functions

### `load()`

- obtains the value of atomic variable

---

## References

- <https://en.cppreference.com/w/cpp/atomic/atomic>
- <https://www.youtube.com/watch?v=oE_D3IgBJi8>
