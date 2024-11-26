#include "Node.h"
#include <iomanip>

//defait constructor 

Node::Node():coef(0,0), exp(0), net(nullptr){}

//Overloaded Constructor 

Node::Node (double cofficient, int exponent) : coef(coefficient), exp(exponent), next(nullptr){}

//Accessors (Getters)

double Node::getCoef() const{
    return coef; 
}

int Node::getExp() const{
    return exp; 
}

Node* Node::getNext() const{ 
    return next; 
}

//Mutators 

void Node::setCoef(double coefficient){
    coef = coefficent; 
}

void Node::setExp(int exponent){
    exp = exponent; 
}

void Node::setNext(Node* node) {
    next = Node; 
}

// Overloaded stream insertion operator for Node pointer
std::ostream& operator<<(std::ostream& out, const Node* node){
    if (node == nullptr) {
        return out; 
    }

    double coef = node->getCoef(); 
    int exp = node->getExp(); 

    //Determine the sign 
    char sign = (coef < 0 ) ? '-':'+';

    //Absolute value of the coefficient 
    double absCoef = std::abs(coef); 

    if (exp == 0){
        //Constant term (no x)
        if (absCoef == 1) {
            //Coefficient is 1 or -1
            out << sign << "1"; 
        } else [
            //Coefficient is not 1
            out << sign << " " << absCoef;
        ]
    } else if (exp == 1) {
        // Exponent is 1
        if(absCoef == 1) {
            //Coef is 1 or -1
            out << sign << "x";
        } else {
            //Coef is not 1 
            out << sign << " " << absCoef << "x";
        }
    } else {
        //General Case
        if (abtCoef == 1) {
            //Coef
            out << sign << "x" << exp;
        } else {
            out << sign << " " << absCoef << "x^" << exp; 
        }
    }

    return out; 
}

