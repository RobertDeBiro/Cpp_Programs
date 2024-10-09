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

## Atomic and regular mutex comparison

### Benefits of Atomic Operations Compared to Regular Mutex

1.Performance (Speed):

Atomic operations are typically much faster than mutexes because they operate at a hardware level and don't require the overhead of locking and unlocking a shared resource. This is especially beneficial for small, low-contention data structures or single variables.
Mutexes, on the other hand, involve more overhead because they require interaction with the operating system to lock and unlock. This involves kernel-mode switching, which can slow down performance, especially in multithreaded applications with frequent contention for resources.

2.Fine-grained Control:

Atomic operations give fine-grained control over specific values or variables without the need to block other threads entirely. For example, atomic compare-and-swap (CAS) or atomic increment only locks the data being modified, avoiding thread contention for an entire block of code.
Mutexes lock larger critical sections of code, preventing other threads from accessing even unrelated data within the section. This can lead to longer wait times for other threads.

3.Deadlock-Free:

Atomic operations are not prone to deadlocks, as they don't involve locking and unlocking mechanisms. Operations like atomic compare-and-swap are executed as a single, indivisible step.
Mutexes can lead to deadlocks if multiple threads attempt to acquire locks in the wrong order or if a thread holds a lock and waits for another resource indefinitely.

### Benefits of Regular Mutexes

1.Complexity Management:

Mutexes provide an easier way to manage complex critical sections of code where multiple resources may need to be locked simultaneously. For example, when manipulating larger data structures (e.g., lists or queues), mutexes can be used to ensure consistency across multiple operations.
Atomic operations, in contrast, are best suited for single or very small data points. Using atomics for more complex logic can lead to code that's harder to maintain and more error-prone.

2.Locking Larger Critical Sections:

Mutexes allow for locking larger sections of code, where multiple variables or operations must be treated as a single atomic transaction. This is useful when it's essential to synchronize more than just one variable or operation at a time.
Atomic operations can only ensure atomicity at the level of individual memory accesses (e.g., an integer or a pointer), which might not be enough for more complex operations that involve multiple variables or data structures.

3.Fairness and Flexibility:

Mutexes can offer fairness guarantees through priority mechanisms (such as fair locking algorithms), ensuring that no thread is indefinitely blocked while waiting for a lock.
Atomic operations, on the other hand, do not provide this level of fairness, which might result in starvation for some threads under certain conditions, especially in highly concurrent environments.

### Use Cases

Atomic Operations: Best for simple, low-contention tasks like updating counters, flags, or small variables where performance is critical.
Mutexes: Better for complex critical sections where multiple variables or operations need to be synchronized, or where fairness and lock contention management are necessary.

---

## Member functions

### `load()`

- obtains the value of atomic variable

---

## References

- <https://en.cppreference.com/w/cpp/atomic/atomic>
- <https://www.youtube.com/watch?v=oE_D3IgBJi8>
