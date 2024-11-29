#include "LinkedList.h"
#include <cmath>
#include <iomanip>

// Default constructor
LinkedList::LinkedList() : head(nullptr), size(0) {}

// Destructor
LinkedList::~LinkedList() {
    recursiveDelete(head);
}

// Recursive delete function
void LinkedList::recursiveDelete(Node* node) {
    if (node == nullptr) {
        return;
    } else {
        recursiveDelete(node->getNext());
        delete node;
    }
}

// Accessors (Getters)
Node* LinkedList::getHead() const {
    return head;
}

int LinkedList::getSize() const {
    return size;
}

// Mutators (Setters)
void LinkedList::setHead(Node* node) {
    head = node;
}

void LinkedList::setSize(int s) {
    size = s;
}

// Overloaded [] operator
Node* LinkedList::operator[](int index) const {
    if (index < 0 || index >= size) {
        return nullptr;
    }
    Node* currentNode = head;
    for (int i = 0; i < index; ++i) {
        currentNode = currentNode->getNext();
    }
    return currentNode;
}

// Overloaded stream insertion operator
std::ostream& operator<<(std::ostream& out, const LinkedList& list) {
    Node* currentNode = list.head;
    bool firstTerm = true;

    // Set the output format for coefficients
    out << std::fixed << std::setprecision(3);

    while (currentNode != nullptr) {
        double coef = currentNode->getCoef();
        int exp = currentNode->getExp();
        double absCoef = std::abs(coef);

        // Skip terms with zero coefficients
        if (coef == 0.0) {
            currentNode = currentNode->getNext();
            continue;
        }

        // Determine the sign
        if (firstTerm) {
            if (coef < 0) {
                out << "-";
            }
            firstTerm = false;
        } else {
            if (coef < 0) {
                out << " - ";
            } else {
                out << " + ";
            }
        }

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

        currentNode = currentNode->getNext();
    }

    // If the list was empty or all coefficients were zero
    if (firstTerm) {
        out << "0";
    }

    return out;
}

// Overloaded += operator
LinkedList& LinkedList::operator+=(Node* newNode) {
    if (head == nullptr) {
        head = newNode;
    } else {
        // Traverse to the end of the list and append newNode
        Node* currentNode = head;
        while (currentNode->getNext() != nullptr) {
            currentNode = currentNode->getNext();
        }
        currentNode->setNext(newNode);
    }
    size++;
    return *this;
}

// Sort function
void LinkedList::sortList() {
    if (head == nullptr || head->getNext() == nullptr) {
        return;
    }
    Node* sortedList = nullptr;
    Node* currentNode = head;
    while (currentNode != nullptr) {
        Node* nextNode = currentNode->getNext();
        currentNode->setNext(nullptr);  // Disconnect the node
        insertNodeInSortedOrder(&sortedList, currentNode);
        currentNode = nextNode;
    }
    head = sortedList;
}

// Helper function for sorting
void LinkedList::insertNodeInSortedOrder(Node** sortedList, Node* node) {
    if (*sortedList == nullptr || node->getExp() >= (*sortedList)->getExp()) {
        node->setNext(*sortedList);
        *sortedList = node;
    } else {
        Node* current = *sortedList;
        while (current->getNext() != nullptr && current->getNext()->getExp() > node->getExp()) {
            current = current->getNext();
        }
        node->setNext(current->getNext());
        current->setNext(node);
    }
}

// Clear function
void LinkedList::clear() {
    recursiveDelete(head);
    head = nullptr;
    size = 0;
}