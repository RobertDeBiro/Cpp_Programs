## thread
    #include <thread>

    class thread

 - in every application there is a defualt thread, which is mainj(), and in side it we create other threads
 - a thread is also known as lightweight process
    - idea is achieve parallelism by diciding a process into multiple threads
 - if we create multiple threads sequentially in the code, there is no guarantee which one will start first
 - threads either needs to be joined or detached, because main thread must not be terminated if there
   is joinable thread present

### References
 - https://en.cppreference.com/w/cpp/thread/thread
 - https://www.youtube.com/watch?v=wXBcwHwIt_I
 - https://www.youtube.com/watch?v=TPVH_coGAQs&list=PLk6CEY9XxSIAeK-EAh3hB4fgNvYkYmghp
<<<<<<< HEAD
 - https://www.youtube.com/watch?v=q3-5sDe6lzg&list=RDCMUCs6sf4iRhhE875T1QjG3wPQ&start_radio=1&rv=q3-5sDe6lzg&t=495
 - https://stackoverflow.com/questions/37015775/what-is-different-between-join-and-detach-for-multi-threading-in-c
=======
 - https://www.youtube.com/watch?v=q3-5sDe6lzg&list=RDCMUCs6sf4iRhhE875T1QjG3wPQ&start_radio=1&rv=q3-5sDe6lzg&t=495
>>>>>>> 6cb7e8d05798eb4100c6ca20d5b21d8834830159
