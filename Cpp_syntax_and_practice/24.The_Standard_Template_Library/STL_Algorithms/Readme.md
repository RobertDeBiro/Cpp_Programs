# STL Algorithms

- because searching, counting, and sorting are such common operations to do, the C++ standard library comes with a bunch functions to do these things in just a few lines of code

### STL Algorithms Benefits
 - **pre-tested**
 - **efficient**
 - work on a variety of **different container types**
 - many support **parallelization** (the ability to devote multiple CPU threads to the same task in order to complete it faster)

### STL Algorithms Categories
1. Inspectors
    - used to view (but not modify) data in a container
    - examples include:
        - searching - std::find
        - counting - std::count
2. Mutators
    - used to modify data in a container
    - examples include:
        - sorting – std::sort
        - shuffling – std::shuffle
3. Facilitators
    - used to generate a result based on values of the data members
    - examples include objects that sum or multiply values, or objects that determine what order pairs of elements should be sorted in:
        - std::accumulate - sums up the range of elements and given value init
        - std::reduce (similar to std::accumulate)

References:
 - https://en.cppreference.com/w/cpp/algorithm
