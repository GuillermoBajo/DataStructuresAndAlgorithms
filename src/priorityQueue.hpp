/* Álvaro de Francisco Nievas (838819) and Guillermo Bajo Laborda (842748) */

#ifndef PRIORITYQUEUE_HPP
#define PRIORITYQUEUE_HPP

#include "queue.hpp"

template <typename T>
struct priorityQueue;

/* Returns an empty queue with no elements */
template <typename T>
void initialize(priorityQueue<T> &q);

/* Returns a queue resulting from adding element e to q as a priority element if
prio is true, or as a non-priority element otherwise */
template <typename T>
void enqueuePriority(priorityQueue<T> &q, const T &e, bool isPrio);

/* Returns true if and only if q has no elements */
template <typename T>
bool isEmptyPriorityQueue(const priorityQueue<T> &q);

/* Returns the first enqueued priority element from q. If there is no priority element,
returns the first non-priority element enqueued. Partial: operation is not defined if q is empty */
template <typename T>
void firstPriority(priorityQueue<T> &q, T &e, bool &error);

/* If isEmpty(q), returns the empty queue. Otherwise, returns a queue equal to the
resulting one from removing the first element from q. If q contains priority elements,
removes the first enqueued priority element; otherwise, removes the first enqueued
non-priority element. */
template <typename T>
void dequeuePriority(priorityQueue<T> &q);

/* Returns the number of elements in q */
template <typename T>
int lengthPriorityQueue(const priorityQueue<T> &q);

/* If prio is true, returns the number of priority elements in q; otherwise, returns
the number of non-priority elements in q. */
template <typename T>
int lengthClass(const priorityQueue<T> &q, bool isPrio);

// ITERATOR OPERATIONS

/* Prepares the iterator to make the next element to visit the first element in the
queue q (as defined by the first(q) operation above), if it exists (i.e., situation
where no elements have been visited yet). */
template <typename T>
void initializeIteratorPriorityQueue(priorityQueue<T> &q);

/* Returns false if all elements of q have been visited; returns true otherwise. */
template <typename T>
bool hasNextPriorityQueue(const priorityQueue<T> &q);

/* Returns the next priority element from q that was enqueued, if there is one;
otherwise, if there are no more priority elements in q to visit, returns the next
non-priority element from q that was enqueued, if it exists. Partial: operation is not
defined if hasNext(q) returns false. */
template <typename T>
void nextAndAdvancePriorityQueue(priorityQueue<T> &q, T &e, bool &error);

// GENERIC DECLARATION OF PRIORITYQUEUE TAD
template <typename T>
struct priorityQueue
{
    friend void initialize<T>(priorityQueue<T> &q);
    friend void enqueuePriority<T>(priorityQueue<T> &q, const T &e, bool isPrio);
    friend bool isEmptyPriorityQueue<T>(const priorityQueue<T> &q);
    friend void firstPriority<T>(priorityQueue<T> &q, T &e, bool &error);
    friend void dequeuePriority<T>(priorityQueue<T> &q);
    friend int lengthPriorityQueue<T>(const priorityQueue<T> &q);
    friend int lengthClass<T>(const priorityQueue<T> &q, bool isPrio);
    friend void initializeIteratorPriorityQueue<T>(priorityQueue<T> &q);
    friend bool hasNextPriorityQueue<T>(const priorityQueue<T> &q);
    friend void nextAndAdvancePriorityQueue<T>(priorityQueue<T> &q, T &e, bool &error);

private:
    queue<T> priorityQueueElements;
    queue<T> nonPriorityQueueElements;
};

// IMPLEMENTATION OF GENERIC PRIORITYQUEUE TAD OPERATIONS
template <typename T>
void initialize(priorityQueue<T> &q)
{
    createEmpty(q.priorityQueueElements);
    createEmpty(q.nonPriorityQueueElements);
}

template <typename T>
void enqueuePriority(priorityQueue<T> &q, const T &e, bool isPrio)
{
    if (isPrio)
    {
        enqueue(q.priorityQueueElements, e);
    }
    else
    {
        enqueue(q.nonPriorityQueueElements, e);
    }
}

template <typename T>
bool isEmptyPriorityQueue(const priorityQueue<T> &q)
{
    return (isEmpty(q.nonPriorityQueueElements) && isEmpty(q.priorityQueueElements));
}

template <typename T>
void firstPriority(priorityQueue<T> &q, T &e, bool &error)
{
    if (!isEmptyPriorityQueue(q))
    {
        if (!isEmpty(q.priorityQueueElements))
        {
            T priorityElem;
            bool priorityError;
            first(q.priorityQueueElements, priorityElem, priorityError);
            e = priorityElem;
            error = priorityError;
        }
        else
        {
            T nonPriorityElem;
            bool nonPriorityError;
            first(q.nonPriorityQueueElements, nonPriorityElem, nonPriorityError);
            e = nonPriorityElem;
            error = nonPriorityError;
        }
    }
    else
    {
        error = true;
    }
}

template <typename T>
void dequeuePriority(priorityQueue<T> &q)
{
    if (!isEmptyPriorityQueue(q))
    {
        if (!isEmpty(q.priorityQueueElements))
        {
            dequeue(q.priorityQueueElements);
        }
        else
        {
            dequeue(q.nonPriorityQueueElements);
        }
    }
}

template <typename T>
int lengthPriorityQueue(const priorityQueue<T> &q)
{
    return length(q.priorityQueueElements) + length(q.nonPriorityQueueElements);
}

template <typename T>
int lengthClass(const priorityQueue<T> &q, bool isPrio)
{
    if (isPrio)
    {
        return length(q.priorityQueueElements);
    }
    else
    {
        return length(q.nonPriorityQueueElements);
    }
}

// ITERATOR OPERATIONS
template <typename T>
void initializeIteratorPriorityQueue(priorityQueue<T> &q)
{
    initializeIterator(q.priorityQueueElements);
    initializeIterator(q.nonPriorityQueueElements);
}

template <typename T>
bool hasNextPriorityQueue(const priorityQueue<T> &q)
{
    return (hasNext(q.priorityQueueElements) || hasNext(q.nonPriorityQueueElements));
}

template <typename T>
void nextAndAdvancePriorityQueue(priorityQueue<T> &q, T &e, bool &error)
{
    nextAndAdvance(q.priorityQueueElements, e, error);

    if (error)
    {
        nextAndAdvance(q.nonPriorityQueueElements, e, error);
    }
}

#endif // end of priorityQueue.hpp
