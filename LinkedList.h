#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include <iostream>

class LinkedList {
private:
    Node* head;  // Pointer to the first node
    int size;    // Number of nodes in the list

    // Helper function for recursive deletion
    void recursiveDelete(Node* node);

    // Helper function for sorting
    void insertNodeInSortedOrder(Node** sortedList, Node* node);

public:
    // Default constructor
    LinkedList();

    // Destructor
    ~LinkedList();

    // Accessors (Getters)
    Node* getHead() const;
    int getSize() const;

    // Mutators (Setters)
    void setHead(Node* node);
    void setSize(int s);

    // Overloaded [] operator
    Node* operator[](int index) const;

    // Overloaded stream insertion operator
    friend std::ostream& operator<<(std::ostream& out, const LinkedList& list);

    // Overloaded += operator
    LinkedList& operator+=(Node* newNode);

    // Sort function
    void sortList();

    // Clear function
    void clear();
};

#endif // LINKEDLIST_H