#ifndef STACK_HPP
#define STACK_HPP

using namespace std;

/* BEGINNING OF THE PUBLIC PART or INTERFACE */

/* The values of the generic Stack ADT represent sequences of elements with LIFO (last in, first out) access,
   i.e., the last element added will be the first one removed.
   The last element added to the stack is referred to as the top of the stack.
   All operations will have constant cost, except the duplicate, ==, and release operations, which will have O(N) cost, where N is the number of elements in the stack.
   Likewise, the memory cost of this implementation will be O(N).
   
   The formal parameter T is required to support the usual operators for:
   equality comparison ==, and the usual copy operator =, which
   will be used respectively in the == stack operations and the stack duplicate operations.
      bool operator==(const T& t1, const T& t2);
      T& operator=(const T& origin)
 */
template<typename T> struct Stack;

/* Returns an empty Stack with no elements in `s`. */
template<typename T> void createEmpty(Stack<T>& s);

/* Pushes `e` onto `s` as the new top of the Stack. */
template<typename T> void push(Stack<T>& s, const T& e);

/* If `s` is not empty, removes the element at the top of `s` (the last element that was pushed).
   If `s` is empty, leaves it unchanged.
*/
template<typename T> void pop(Stack<T>& s);

/* If `s` is not empty, retrieves in `e` the last element pushed onto `s` (i.e., its top), and sets `error=false`.
   If `s` is empty, sets `error=true`.
*/
template<typename T> void top(const Stack<T>& s, T& e, bool& error);

/* Returns true if and only if `s` has no elements. */
template<typename T> bool isEmpty(const Stack<T>& s);

/* Returns the number of elements in `s`. */
template<typename T> int height(const Stack<T>& s);

/* Performs a deep copy of `srcStack` into `destStack`, duplicating the memory representation.
   Each element in the stack is copied using the copy operator = of the type T data.
*/
template<typename T> void duplicate(const Stack<T>& srcStack, Stack<T>& destStack);

/* Returns true if and only if `s1` and `s2` have the same elements in the same order.
   Each element in the stack is compared using the == operator of the type T data.
*/
template<typename T> bool operator==(const Stack<T>& s1, const Stack<T>& s2);

/* Releases all dynamic memory used by `s` and returns an empty Stack in `s`. */
template<typename T> void release(Stack<T>& s);

/* The following three operations form an internal iterator for the Stack: */

/* Prepares the iterator to visit the first element of `s`, if any (situation of no element visited). */
template<typename T> void initializeIterator(Stack<T>& s);

/* Returns false if all elements of `s` have been visited; returns true otherwise. */
template<typename T> bool hasNext(const Stack<T>& s);

/* If there is a pending element to visit in `s`, retrieves the next element in `e` and sets `error=false`,
   then advances the iterator to the next element.
   If no elements are left to visit, sets `error=true`.
*/
template<typename T> void next(Stack<T>& s, T& e, bool& error);

/* END OF THE PUBLIC PART or INTERFACE */

template<typename T>
struct Stack {
    friend void createEmpty<T>(Stack<T>& s);
    friend void push<T>(Stack<T>& s, const T& e);
    friend void pop<T>(Stack<T>& s);
    friend void top<T>(const Stack<T>& s, T& e, bool& error);
    friend bool isEmpty<T>(const Stack<T>& s);
    friend int height<T>(const Stack<T>& s);
    friend void duplicate<T>(const Stack<T>& srcStack, Stack<T>& destStack);
    friend bool operator==<T>(const Stack<T>& s1, const Stack<T>& s2);
    friend void release<T>(Stack<T>& s);
    friend void initializeIterator<T>(Stack<T>& s);
    friend bool hasNext<T>(const Stack<T>& s);
    friend void next<T>(Stack<T>& s, T& e, bool& error);

private:
    /* In this implementation, the stack is represented in dynamic memory as a singly linked list of Nodes, non-circular, with:
        - `topPtr`: pointing to the Node containing the element at the top of the stack, or nullptr if the stack is empty.
        - `height`: holding the number of elements in the stack, 0 if the stack is empty.
        - `iterPtr`: used to maintain the state of the iterator, utilized only by initializeIterator, hasNext, and next operations.
       Each Node contains a stack element (`data`) and a pointer (`next`) pointing to the Node that contained the previous top element of the stack,
       or nullptr if the stack was empty before this.
    */
    struct Node {
        T data;  
        Node* next;
    };

    Node* topPtr; // top of the stack
    int height;   // number of elements in the stack
    Node* iterPtr; // used for the iterator
};

// Function implementations remain similar but with the names updated in English
// Example:
template<typename T> 
void createEmpty(Stack<T>& s) {
    s.topPtr = nullptr;
    s.height = 0;
}


/* Adds `element` as the new top of the Stack `stack`. */
template<typename T>
void push(Stack<T>& stack, const T& element) {
    typename Stack<T>::Node* temp = stack.top;  // Save pointer to the previous top
    stack.top = new typename Stack<T>::Node;  // Allocate memory for the new top Node
    stack.top->data = element;  // Assign data to the new top
    stack.top->next = temp;  // Link the new top to the previous one
    stack.height++;  // Increment the height of the stack
}

/* If the stack is not empty, removes the top element. */
template<typename T>
void pop(Stack<T>& stack) {
    if (!isEmpty(stack)) {
        typename Stack<T>::Node* temp = stack.top;  // Pointer to the Node to be removed
        stack.top = stack.top->next;  // Update top to the previous one
        delete temp;  // Free the memory of the removed Node
        stack.height--;  // Decrement the height of the stack
    }
}

/* If the stack is not empty, retrieves the top element in `element` and sets `error` to false. 
   If the stack is empty, sets `error` to true. */
template<typename T>
void getTop(const Stack<T>& stack, T& element, bool& error) {
    if (isEmpty(stack)) {
        error = true;
    } else {
        element = stack.top->data;
        error = false;
    }
}

/* Returns true if and only if the stack is empty (i.e., `stack.top` is nullptr). */
template<typename T>
bool isEmpty(const Stack<T>& stack) {
    return stack.top == nullptr;
}

/* Returns the number of elements in the stack. */
template<typename T>
int getHeight(const Stack<T>& stack) {
    return stack.height;
}

/* Creates a deep copy of the source stack `sourceStack` into the target stack `targetStack`. 
   Each element is copied using the copy operator of type T. */
template<typename T>
void duplicate(const Stack<T>& sourceStack, Stack<T>& targetStack) {
    if (isEmpty(sourceStack)) {
        createEmpty(targetStack);
    } else {
        typename Stack<T>::Node* sourcePointer = sourceStack.top;  // Pointer to traverse sourceStack
        targetStack.top = new typename Stack<T>::Node;
        targetStack.top->data = sourcePointer->data;  // Copy the top of sourceStack to targetStack
        typename Stack<T>::Node* targetPointer = targetStack.top;  // Pointer to build targetStack
        sourcePointer = sourcePointer->next;
        while (sourcePointer != nullptr) {
            targetPointer->next = new typename Stack<T>::Node;  // Create and link a new Node
            targetPointer = targetPointer->next;
            targetPointer->data = sourcePointer->data;  // Copy data
            sourcePointer = sourcePointer->next;
        }
        targetPointer->next = nullptr;  // Mark the end of the stack
        targetStack.height = sourceStack.height;  // Copy the height
    }
}

/* Returns true if and only if `stack1` and `stack2` have the same elements in the same positions. 
   Elements are compared using the equality operator of type T. */
template<typename T>
bool operator==(const Stack<T>& stack1, const Stack<T>& stack2) {
    if (stack1.height != stack2.height) {
        return false;
    } else {
        typename Stack<T>::Node* pointer1 = stack1.top;
        typename Stack<T>::Node* pointer2 = stack2.top;
        bool areEqual = true;
        while (pointer1 != nullptr && areEqual) {
            areEqual = (pointer1->data == pointer2->data);  // Compare elements at the same position
            pointer1 = pointer1->next;
            pointer2 = pointer2->next;
        }
        return areEqual;
    }
}

/* Frees all dynamic memory used by the stack and resets it to an empty state. */
template<typename T>
void freeStack(Stack<T>& stack) {
    typename Stack<T>::Node* temp = stack.top;
    while (temp != nullptr) {
        stack.top = stack.top->next;
        delete temp;
        temp = stack.top;
    }
    stack.height = 0;
}

/* Internal iterator operations for the Stack: */

/* Prepares the iterator to visit the first element in the stack (i.e., the top element), if it exists. */
template<typename T>
void initializeIterator(Stack<T>& stack) {
    stack.iterator = stack.top;
}

/* Returns false if all elements of the stack have been visited; returns true otherwise. */
template<typename T>
bool hasNext(const Stack<T>& stack) {
    return stack.iterator != nullptr;
}

/* If there are elements left to visit, retrieves the next element in `element` and sets `error` to false. 
   Advances the iterator to the next element. If no elements are left, sets `error` to true. */
template<typename T>
void getNext(Stack<T>& stack, T& element, bool& error) {
    if (hasNext(stack)) {
        error = false;
        element = stack.iterator->data;  // Return the next element
        stack.iterator = stack.iterator->next;  // Advance the iterator
    } else {
        error = true;
    }
}

#endif // DYNAMIC_STACK_HPP
