/*
 * std::priority_queue
 *  - SYNTAX:
 *      template<
 *          class T,
 *          class Container = std::vector<T>,
 *          class Compare = std::less<typename Container::value_type>
 *      > class priority_queue;
 * 
 *  - std::priority_queue class is a container adapter that that provides constant time lookup
 *    of the largest (by default) element, at the expense of logarithmic insertion and extraction
 *  - the class template acts as a wrapper to the underlying container
 *     - in other words, std::priority_queue is implemented as some other container
 *     - by default it is implemented internally as std::vector
 *
 *  Element access          Capacity            Modifiers
 *  + top                   + empty             + push
 *                          - size              - emplace
 *                                              + pop
 *                                              - swap
 * TODO 5:40/11:14
 */

#include <iostream>
#include <queue>
#include <vector>

