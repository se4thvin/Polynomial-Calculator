#ifndef NODE_H
#define NODE_H


#include <iostream>


class Node; 

std::ostream& operator<<(std::ostream& out, const Node* node); 

class Node {
private: 
    double coef; //Coef
    int exp;     //Exp
    Node* next;  //Ptr to next node 

public:

    //Default Constructor
    Node(); 

    //Overloaded Constructor 
    Node(double coefficient, int exponent);

    //Accessors 
    double getCoef() const; 
    int getExp() const; 
    Node* getNext() const; 

    //Mutators 
    void setCoef(double coefficient); 
    void setExp(int exponent); 
    void setNext(Node* node); 

    //Friend declaration for overloaded 
    friend std::ostream& operator<<(std::ostream& out,  const Node* node);


};

#endif