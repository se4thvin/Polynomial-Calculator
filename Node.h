#ifndef NODE_H
#define NODE_H

#include <iostream>

// Node class definition
class Node {
private:
    double coef;   // Coefficient
    int exp;       // Exponent
    Node* next;    // Pointer to the next node

public:
    // Default constructor
    Node();

    // Overloaded constructor
    Node(double coefficient, int exponent);

    // Accessors (Getters)
    double getCoef() const;
    int getExp() const;
    Node* getNext() const;

    // Mutators (Setters)
    void setCoef(double coefficient);
    void setExp(int exponent);
    void setNext(Node* node);

    // Overloaded stream insertion operator
    friend std::ostream& operator<<(std::ostream& out, const Node& node);
};

#endif // NODE_H