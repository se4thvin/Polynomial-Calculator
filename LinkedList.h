#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"

class LinkedList{
private:
    Node* head; 
    int size; 

public:

    //Default Constructor 
    LinkedList(); 

    //Destructor 
    ~LinkedList(); 

    //Accessor for size
    int getSize() const; 

    //Accessor for head(debugging)
    Node* getHead() const; 

    //Mutator for head
    void setHead(Node* newHead); 

    //Overloaded [] operator 
    const Node* operator[](int index) const;

    //Overloaded stream insertion operator
    friend std::ostream& operator<<(std::ostream& out, const LinkedList& list);

    //Overloaded += operator 
    LinkedList& operator+=(Node* newNode);

    //sort for expo in dec 
    void sortList(); 

};

#endif 