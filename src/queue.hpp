/* Álvaro de Francisco Nievas (838819) and Guillermo Bajo Laborda (842748) */

#ifndef QUEUE_HPP
#define QUEUE_HPP

using namespace std;

template <typename T>
struct queue;

/* Returns an empty queue with no elements */
template <typename T>
void createEmpty(queue<T> &q);

/* Returns a queue resulting from adding elem to q as a priority element if
 prio is true, or as a non-priority element otherwise */
template <typename T>
void enqueue(queue<T> &q, const T &e);

/* Returns true if and only if q has no elements */
template <typename T>
bool isEmpty(const queue<T> &q);

/* Returns the first enqueued priority element in q. If there is no priority element,
 returns the first non-priority element enqueued.
 Partial: the operation is not defined if q is empty. */
template <typename T>
void front(queue<T> &q, T &e, bool &error);

/* If isEmpty(q), returns an empty queue. Otherwise, returns a queue resulting
 from removing the first element from q, meaning if there are priority elements
 in q, removes the first one enqueued; if not, removes the first non-priority
 element enqueued. */
template <typename T>
void dequeue(queue<T> &q);

/* Returns the number of elements in q */
template <typename T>
int length(const queue<T> &q);

/* Returns q as an empty queue and also frees previously used memory by q */
template <typename T>
void release(queue<T> &q);

// ITERATOR OPERATIONS

/* Prepares the iterator so that the next element to visit is the first element
 * of q, if it exists (situation where no elements have been visited yet) */
template <typename T>
void startIterator(queue<T> &q);

/* Returns false if all elements in q have been visited; returns true otherwise */
template <typename T>
bool hasNext(const queue<T> &q);

/* If there is an element in q pending to visit, returns the next element to
 * visit in e with error=false, and advances the iterator so the next element
 * can be visited. If there are no pending elements, returns error=true,
 * leaving e undefined. */
template <typename T>
void nextAndAdvance(queue<T> &q, T &e, bool &error);

// GENERIC QUEUE TAD DECLARATION

template <typename T>
struct queue
{
    friend void createEmpty<T>(queue<T> &q);
    friend void enqueue<T>(queue<T> &q, const T &e);
    friend bool isEmpty<T>(const queue<T> &q);
    friend void front<T>(queue<T> &q, T &e, bool &error);
    friend void dequeue<T>(queue<T> &q);
    friend int length<T>(const queue<T> &q);
    friend void release<T>(queue<T> &q);
    friend void startIterator<T>(queue<T> &q);
    friend bool hasNext<T>(const queue<T> &q);
    friend void nextAndAdvance<T>(queue<T> &q, T &e, bool &error);

private:
    struct Node
    {
        T data;
        Node *next;
    };
    Node *first;
    Node *last;
    int numElements;
    Node *iterator;
};

// GENERIC QUEUE TAD OPERATIONS
template <typename T>
void createEmpty(queue<T> &q)
{
    q.first = nullptr;
    q.last = nullptr;
    q.numElements = 0;
}

template <typename T>
void enqueue(queue<T> &q, const T &e)
{
    if (q.numElements == 0)
    {
        q.last = new typename queue<T>::Node;
        q.first = q.last;
    }
    else
    {
        q.last->next = new typename queue<T>::Node;
        q.last = q.last->next;
    }
    q.last->data = e;
    q.last->next = nullptr;
    q.numElements++;
}

template <typename T>
bool isEmpty(const queue<T> &q)
{
    return q.first == nullptr;
}

template <typename T>
void front(queue<T> &q, T &elem, bool &error)
{
    if (!isEmpty(q))
    {
        error = false;
        elem = q.first->data;
    }
    else
    {
        error = true;
    }
}

template <typename T>
void dequeue(queue<T> &q)
{
    typename queue<T>::Node *temp;
    if (!isEmpty(q))
    {
        temp = q.first;
        q.first = q.first->next;
        delete temp;
        q.numElements--;
        if (q.numElements == 0)
        {
            q.last = nullptr;
        }
    }
}

template <typename T>
int length(const queue<T> &q)
{
    return q.numElements;
}

template <typename T>
void release(queue<T> &q)
{
    typename queue<T>::Node *temp = q.first;
    while (temp != nullptr)
    {
        q.first = q.first->next;
        delete temp;
        temp = q.first;
    }
    q.last = nullptr;
    q.numElements = 0;
}

// ITERATOR OPERATIONS
template <typename T>
void startIterator(queue<T> &q)
{
    q.iterator = q.first;
}

template <typename T>
bool hasNext(const queue<T> &q)
{
    return q.iterator != nullptr;
}

template <typename T>
void nextAndAdvance(queue<T> &q, T &elem, bool &error)
{
    if (!hasNext(q))
    {
        error = true;
    }
    else
    {
        error = false;
        elem = q.iterator->data;
        q.iterator = q.iterator->next;
    }
}

#endif // end of queue.hpp
