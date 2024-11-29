#include "Node.h"
#include <cmath>

// Default constructor
Node::Node() : coef(0.0), exp(0), next(nullptr) {}

// Overloaded constructor
Node::Node(double coefficient, int exponent) : coef(coefficient), exp(exponent), next(nullptr) {}

// Accessors (Getters)
double Node::getCoef() const {
    return coef;
}

int Node::getExp() const {
    return exp;
}

Node* Node::getNext() const {
    return next;
}

// Mutators (Setters)
void Node::setCoef(double coefficient) {
    coef = coefficient;
}

void Node::setExp(int exponent) {
    exp = exponent;
}

void Node::setNext(Node* node) {
    next = node;
}

// Overloaded stream insertion operator
std::ostream& operator<<(std::ostream& out, const Node& node) {
    double coef = node.getCoef();
    int exp = node.getExp();

    // Format and output the term according to specifications
    if (exp == 0) {
        // Constant term
        out << coef;
    } else if (exp == 1) {
        // Exponent is 1
        if (coef == 1.0) {
            out << "x";
        } else if (coef == -1.0) {
            out << "-x";
        } else {
            out << coef << "x";
        }
    } else {
        // Exponent is greater than 1
        if (coef == 1.0) {
            out << "x^" << exp;
        } else if (coef == -1.0) {
            out << "-x^" << exp;
        } else {
            out << coef << "x^" << exp;
        }
    }

    return out;
}