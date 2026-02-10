#ifndef ITERATOR_H
#define ITERATOR_H

#include <memory>

// Forward declaration
class MenuItem;

/**
 * @brief Iterator interface for traversing menu collections
 *
 * Provides a uniform interface for iterating over different collection types
 * without exposing their underlying implementation.
 */
class Iterator {
public:
    virtual ~Iterator() = default;

    /**
     * @brief Check if there are more elements to iterate
     * @return true if there are more elements, false otherwise
     */
    virtual bool hasNext() const = 0;

    /**
     * @brief Get the next element in the iteration
     * @return Pointer to the next MenuItem, or nullptr if no more elements
     */
    virtual MenuItem* next() = 0;
};

#endif // ITERATOR_H
