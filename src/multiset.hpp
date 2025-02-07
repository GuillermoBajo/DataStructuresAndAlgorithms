/* Álvaro de Francisco Nievas (838819) and Guillermo Bajo Laborda (842748) */

#ifndef MULTISET_HPP
#define MULTISET_HPP

#include "stack.hpp"

using namespace std;

template <typename T>
struct multiset;

// PUBLIC OPERATIONS
template <typename T>
void empty(multiset<T> &m);
template <typename T>
void add(multiset<T> &m, T &e);
template <typename T>
bool remove(multiset<T> &m, T &e);
template <typename T>
int multiplicity(multiset<T> &m, T &e);
template <typename T>
int size(const multiset<T> &m);
template <typename T>
void free(multiset<T> &m);

// ITERATOR OPERATIONS: traverses from smallest to largest
template <typename T>
void startIterator(multiset<T> &m);
template <typename T>
bool hasNext(multiset<T> &m);
template <typename T>
void next(multiset<T> &m, T &e, int &multiplicity, bool &error);

// PRIVATE OPERATIONS
template <typename T>
void insert(typename multiset<T>::Node *&a, T &e, bool &added);
template <typename T>
void erase(typename multiset<T>::Node *&a, T &e, bool &removed);
template <typename T>
void eraseMax(typename multiset<T>::Node *&a, T &e);
template <typename T>
void exists(typename multiset<T>::Node *&a, T &e, int &result, bool &found);
template <typename T>
void freeRec(typename multiset<T>::Node *&a);

// DECLARATION OF THE GENERIC DATA TYPE multiset

template <typename T>
struct multiset
{

    friend void empty<T>(multiset<T> &m);
    friend void add<T>(multiset<T> &m, T &e);
    friend bool remove<T>(multiset<T> &m, T &e);
    friend int multiplicity<T>(multiset<T> &m, T &e);
    friend int size<T>(const multiset<T> &m);
    friend void free<T>(multiset<T> &m);
    friend void startIterator<T>(multiset<T> &m);
    friend bool hasNext<T>(multiset<T> &m);
    friend void next<T>(multiset<T> &m, T &e, int &multiplicity, bool &error);

private:
    struct Node
    {
        T data;
        int multiplicity = 0;
        Node *left;
        Node *right;
    };

    friend void insert<T>(typename multiset<T>::Node *&a, T &e, bool &added);
    friend void erase<T>(typename multiset<T>::Node *&a, T &e, bool &removed);
    friend void eraseMax<T>(typename multiset<T>::Node *&a, T &e);
    friend void exists<T>(typename multiset<T>::Node *&a, T &e, int &result, bool &found);
    friend void freeRec<T>(typename multiset<T>::Node *&a);

    int size;
    Node *root;
    Stack<Node *> iterator;
};

// IMPLEMENTATION OF THE GENERIC DATA TYPE OPERATIONS

// Returns an empty multiset with no elements
template <typename T>
void empty(multiset<T> &m)
{
    m.size = 0;
    m.root = nullptr;
}

// add: multiset m, element e -> multiset
// Returns the multiset resulting from adding an instance of element e to m
template <typename T>
void add(multiset<T> &m, T &e)
{
    bool added;
    insert(m.root, e, added);
    if (added)
    {
        m.size++;
    }
}

// Returns the multiset resulting from removing an instance of element e from m;
// if there is no element e in m, it returns the multiset equal to m
template <typename T>
bool remove(multiset<T> &m, T &e)
{
    bool removed;
    erase(m.root, e, removed);
    if (removed)
    {
        m.size--;
    }
}

// Returns the number of instances of element e in m (0 if there are none)
template <typename T>
int multiplicity(multiset<T> &m, T &e)
{
    bool success;
    int result;
    exists(m.root, e, result, success);

    if (success)
    {
        return result;
    }
    else
    {
        return 0;
    }
}

// Returns the total number of elements in m, counting duplicates
template <typename T>
int size(const multiset<T> &m)
{
    return m.size;
}

// Frees all memory used by the multiset and leaves the multiset empty
template <typename T>
void free(multiset<T> &m)
{
    free(m.iterator);
    freeRec(m.root);
    m.size = 0;
}

// ITERATOR OPERATIONS: traverses from smallest to largest

// Prepares the iterator so that the NEXT ELEMENT TO VISIT is the smallest in the
// multiset m (according to the "min" operation of the formal element), if it exists
// (i.e., when no elements have been visited yet).
template <typename T>
void startIterator(multiset<T> &m)
{
    createEmpty(m.iterator);
    typename multiset<T>::Node *aux;

    free(m.iterator); // Remove leftovers from previous (non-exhaustive) traversals and start with an empty stack
    aux = m.root;     // Root of the tree
    while (aux != nullptr)
    {
        push(m.iterator, aux); // Push pointer to tree node onto the iterator stack
        aux = aux->left;
    }
}

// Returns false if all elements have been visited in m, returns true otherwise
template <typename T>
bool hasNext(multiset<T> &m)
{
    return (!isEmpty(m.iterator));
}

// Returns the next element and its multiplicity, and advances the iterator.
template <typename T>
void next(multiset<T> &m, T &e, int &multiplicity, bool &error)
{
    typename multiset<T>::Node *aux;

    if (hasNext(m))
    {
        error = false;
        top(m.iterator, aux, error);
        e = aux->data;
        multiplicity = aux->multiplicity;
        // Move forward
        pop(m.iterator);
        aux = aux->right;
        while (aux != nullptr)
        {
            push(m.iterator, aux);
            aux = aux->left;
        }
    }
    else
    {
        error = true;
    }
}

// INTERNAL AUXILIARY FUNCTIONS, DO NOT USE THEM OUTSIDE THIS MODULE

template <typename T>
void insert(typename multiset<T>::Node *&a, T &e, bool &added)
{
    if (a == nullptr)
    {
        a = new typename multiset<T>::Node;
        a->data = e;
        a->multiplicity++;
        a->left = nullptr;
        a->right = nullptr;
        added = true;
    }
    else
    {
        if (e < a->data)
        {
            insert(a->left, e, added);
        }
        else if (e > a->data)
        {
            insert(a->right, e, added);
        }
        else
        {
            a->multiplicity++;
            added = true;
        }
    }
}

template <typename T>
void erase(typename multiset<T>::Node *&a, T &e, bool &removed)
{
    typename multiset<T>::Node *aux;
    if (a != nullptr)
    {
        if (e < a->data)
        {
            erase(a->left, e, removed);
        }
        else if (e > a->data)
        {
            erase(a->right, e, removed);
        }
        else if (e == a->data)
        {
            if (a->multiplicity > 1)
            {
                a->multiplicity--;
            }
            else
            {
                if (a->left == nullptr)
                {
                    aux = a;
                    a = a->right;
                    delete aux;
                }
                else
                { // both children are not empty
                    eraseMax(a->left, a->data);
                }
            }
            removed = true;
        }
    }
    else
    {
        removed = false;
    }
}

template <typename T>
void eraseMax(typename multiset<T>::Node *&a, T &e)
{
    typename multiset<T>::Node *aux;
    if (a->right == nullptr)
    {
        e = a->data;
        aux = a;
        a = a->left;
        delete aux;
    }
    else
    {
        eraseMax(a->right, e);
    }
}

template <typename T>
void exists(typename multiset<T>::Node *&a, T &e, int &result, bool &found)
{
    if (a == nullptr)
    {
        found = false;
    }
    else
    {
        if (e < a->data)
        {
            exists(a->left, e, result, found);
        }
        else if (e > a->data)
        {
            exists(a->right, e, result, found);
        }
        else if (e == a->data)
        {
            found = true;
            result = a->multiplicity;
        }
    }
}

// Frees all the memory used by the tree a, in which the data of the multiset is stored,
// and leaves a as an empty tree
template <typename T>
void freeRec(typename multiset<T>::Node *a)
{
    if (a != nullptr)
    {
        freeRec(a->left);
        freeRec(a->right);
        delete a;
        a = nullptr;
    }
}

#endif
