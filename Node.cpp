#include "Node.h"
#include <cmath>
#include <iomanip>

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
    double absCoef = std::abs(coef);

    // Set the output format for coefficients
    out << std::fixed << std::setprecision(3);

    // Format and output the term
    if (exp == 0) {
        // Constant term
        out << absCoef;
    } else if (exp == 1) {
        // Exponent is 1
        if (absCoef == 1.0) {
            out << "x";
        } else {
            out << absCoef << "x";
        }
    } else {
        // Exponent is not 0 or 1 (could be positive or negative)
        if (absCoef == 1.0) {
            out << "x^" << exp;
        } else {
            out << absCoef << "x^" << exp;
        }
    }

    return out;
}