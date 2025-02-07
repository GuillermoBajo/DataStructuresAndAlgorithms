/* Álvaro de Francisco Nievas (838819) and Guillermo Bajo Laborda (842748).

  Program that reads a text file and writes to another file, first the words that
  were not repeated, sorted alphabetically, one per line, followed by the rest of
  the words in the input file (those that were repeated), sorted alphabetically,
  one per line, and each followed by a space and the number of times it appears in the input file.
*/

#include <iostream>
#include <fstream>
#include <string>

#include "multiset.hpp"
#include "priorityQueue.hpp"

using namespace std;

const string INPUT_FILE = "entrada.txt";
const string OUTPUT_FILE = "salida.txt";

struct Element
{
    string word;
    int count = 0;
};

// Pre: <multiset> is initialized and <fileName> is the name of the file to read.
// Post: The strings stored in <fileName> (one per line) are read and stored in the multiset <multisetWords>.
//       Returns true if everything went as expected, false otherwise.
bool loadData(const string fileName, multiset<string> &multisetWords)
{

    ifstream inputFile;
    inputFile.open(fileName); // Opens the input file

    if (inputFile.is_open())
    {

        string wordRead;
        string newline;

        while (inputFile >> wordRead)
        {
            add(multisetWords, wordRead); // Reads and adds the word
            getline(inputFile, newline);  // Skips the newline
        }
        inputFile.close();

        return true;
    }
    else // If the file could not be opened
        return false;
}

// Pre: <multiset> and <priorityQueue> are initialized. <priorityQueue> is empty, <multiset> contains the words.
// Post: Loops through the words in the multiset and adds them (with their counts) into <priorityQueue>
//       (storing one element per distinct word in the multiset), such that: a word is prioritized in the queue if
//       and only if it has a count equal to one.
void fillPriorityQueue(multiset<string> &multisetWords, priorityQueue<Element> &queue)
{

    Element elem;
    bool error;

    next(multisetWords, elem.word, elem.count, error); // Reads the first element

    while (!error)
    {

        bool isPriority = (elem.count == 1); // Checks if the element is a priority element

        enqueuePriority(queue, elem, isPriority); // Enqueues the element

        next(multisetWords, elem.word, elem.count, error); // Reads the next element
    }
}

// Pre: <queue> is initialized and <fileName> is the name of the file to write
// Post: If it returns true, the file <fileName> was created and the words in the queue are written.
//       First, the words with a count of 1 (if any) appear, sorted alphabetically. Then,
//       the words with a count > 1 are written, also sorted alphabetically.
bool writeOutput(const string fileName, priorityQueue<Element> &queue)
{

    ofstream outputFile;
    outputFile.open(fileName); // Opens the output file

    if (outputFile.is_open())
    {

        bool error = false;
        Element elem;

        while (hasNextPriorityQueue(queue))
        {
            nextAndAdvancePriorityQueue(queue, elem, error); // Reads element
            if (!error)
            {
                outputFile << elem.word; // Writes element
                if (elem.count != 1)
                    outputFile << " " << elem.count; // Writes the count of the element (if count > 1)

                outputFile << "\n";
            }
        }
        outputFile.close();

        return true;
    }
    else // If the file could not be opened
        return false;
}

int main()
{
    multiset<string> multisetWords;
    empty(multisetWords);

    if (!loadData(INPUT_FILE, multisetWords))
        return -1;

    priorityQueue<Element> queue;
    initialize(queue);
    startIterator(multisetWords);

    fillPriorityQueue(multisetWords, queue);

    initializeIteratorPriorityQueue(queue);

    if (!writeOutput(OUTPUT_FILE, queue))
        return -1;

    return 0;
}
