# Data Structures And Algorithms

This program processes a text file (`entrada.txt`) and writes an output file (`salida.txt`) with words sorted in a specific way.

## Algorithmic Aspects

1. **Reading the Input File**:

   - The function `loadData` reads words from `entrada.txt` and stores them in a _multiset_ (`multiset`) that maintains the multiplicity (repetition count) of each word.

2. **Word Organization**:

   - Two data structures are used to organize the words:
     - A _multiset_ (`multiset`) to store words and their multiplicity.
     - A _priority queue_ (`priorityQueue`) to organize words based on their priority:
       - Words with a multiplicity of 1 (non-repeated) are considered high priority.
       - Words with a multiplicity greater than 1 (repeated) are considered low priority.

3. **Generating the Priority Queue**:

   - The function `fillPriorityQueue` iterates through the `multiset` and fills the `queue` with elements of type `elm` (a structure that stores a word and its multiplicity).
   - Elements are enqueued based on their priority using the function `enqueuePQ`.

4. **Writing the Output File**:
   - The function `outputData` writes the words from the `queue` to `salida.txt` following these specifications:
     - High-priority words (non-repeated) are written first, sorted alphabetically.
     - Low-priority words (repeated) are written afterward, along with their multiplicity, sorted alphabetically.

## Structural Aspects

1. **Data Structures**:

   - A _multiset_ (`multiset`) is used to store words and their multiplicity, implemented as a self-balancing binary search tree.
   - A _priority queue_ (`priorityQueue`) organizes words by priority, using two queues: one for high-priority words and another for low-priority words.

2. **Iterators**:
   - Iterators are used to traverse both the `multiset` and the `priority queue` in an ordered manner.
