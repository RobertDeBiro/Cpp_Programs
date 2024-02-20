# Threads

---

## `thread`

```cpp
#include <thread>

class thread
```

- in every application there is a defualt thread - which is `main()` function - and inside it we create other threads
- a thread is also known as **lightweight process**
  - idea is to achieve parallelism by dividing a process into multiple threads
- if we create multiple threads sequentially in the code, there is no guarantee which one will start first
- threads either needs to be joined or detached, because main thread must not be terminated if there
  is joinable thread present

### Member functions

#### `detach()`

- used to detach the thread object from the associated thread of execution
- when a thread is detached, it means that the thread of execution is no longer tied to the `std::thread` object
- once detached, the thread can continue to execute independently, and the `std::thread` object becomes in a state
  where it no longer represents a thread of execution
  - this means that we can't join or detach it again
- when we detach a thread, we essentially tell the C++ runtime that we don't need to join with it later to obtain its return value or ensure its completion
  - this is useful in situations where we want the thread to run independently without blocking the main thread

---

## References

- <https://en.cppreference.com/w/cpp/thread/thread>
- <https://www.youtube.com/watch?v=wXBcwHwIt_I>
- <https://www.youtube.com/watch?v=TPVH_coGAQs&list=PLk6CEY9XxSIAeK-EAh3hB4fgNvYkYmghp>
- <https://www.youtube.com/watch?v=q3-5sDe6lzg&list=RDCMUCs6sf4iRhhE875T1QjG3wPQ&start_radio=1&rv=q3-5sDe6lzg&t=495>
- <https://stackoverflow.com/questions/37015775/what-is-different-between-join-and-detach-for-multi-threading-in-c>
