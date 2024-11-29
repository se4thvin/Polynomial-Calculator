#include <iostream>
#include "LinkedList.h"
#include "Node.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <cmath>
#include <iomanip>

using namespace std;

// Function prototypes
LinkedList parseLine(const std::string& line, double& xValue);
void combineLikeTerms(LinkedList& linkedList);
double evaluateExpression(const LinkedList& linkedList, double xValue);
std::string formatExpression(const LinkedList& linkedList);
std::string normalizeOperators(const std::string& line);

int main() {
    // 1. Prompt User for Filename
    cout << "Enter the filename containing the expressions: ";
    std::string filename;
    getline(cin, filename);

    // 2. Open File
    ifstream file(filename.c_str());
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        return 1;
    }

    // 3. Read and Process Each Line in the File
    std::string line;
    while (getline(file, line)) {
        if (line.empty()) {
            continue;  // Skip empty lines
        }


        double xValue = 0.0;
        // Call parseLine(line, xValue) to get linkedList
        LinkedList linkedList = parseLine(line, xValue);

        if (linkedList.getSize() == 0) {
            continue;  // Skip invalid expressions
        }

        // Call combineLikeTerms(linkedList)
        combineLikeTerms(linkedList);

        // Call linkedList.sortList()
        linkedList.sortList();

        // Call evaluateExpression(linkedList, xValue) to get result
        double result = evaluateExpression(linkedList, xValue);

        // Output the expression and result
        // Use the overloaded << operator to display linkedList
        std::string expression = formatExpression(linkedList);

        // Format result to three decimal places
        cout << expression << " = " << fixed << setprecision(3) << result << endl;
    }

    // 4. Close File
    file.close();

    return 0;
}

// Function: parseLine
LinkedList parseLine(const std::string& line, double& xValue) {
    LinkedList linkedList;
    if (line.empty()) {
        return linkedList;
    }

    // 1. Split Line into LHS and RHS
    size_t pos = line.find('=');
    if (pos == std::string::npos) {
        cout << "Invalid expression" << endl;
        return linkedList;
    }
    std::string lhs = line.substr(0, pos);
    std::string rhs = line.substr(pos + 1);

    // 2. Extract xValue from LHS
    size_t posParan1 = lhs.find('(');
    size_t posParan2 = lhs.find(')');
    if (posParan1 == std::string::npos || posParan2 == std::string::npos || posParan2 <= posParan1) {
        cout << "Invalid expression" << endl;
        return linkedList;
    }
    std::string xValueString = lhs.substr(posParan1 + 1, posParan2 - posParan1 - 1);
    try {
        xValue = std::stod(xValueString);
    } catch (const std::exception& e) {
        cout << "Invalid x value: " << xValueString << endl;
        return linkedList;
    }

    // 4. Tokenize RHS into Terms and Operators
    std::vector<std::string> tokens;
    std::istringstream iss(rhs);
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    size_t index = 0;

    // 5. Initialize Variables
    std::string sign = "+";

    // 6. Process Each Token
    while (index < tokens.size()) {
        if (tokens[index] == "+" || tokens[index] == "-") {
            sign = tokens[index];
            index++;
            if (index >= tokens.size()) {
                cout << "Invalid expression: operator at the end" << endl;
                return linkedList;
            }
        } else if (index == 0) {
            sign = "+";
        }
        if (index >= tokens.size()) {
            cout << "Invalid expression" << endl;
            return linkedList;
        }
        std::string term = tokens[index];
        index++;

        // Process Term:
        double coefficient = 1.0;
        int exponent = 0;
        size_t xPos = term.find('x');
        if (xPos != std::string::npos) {
            std::string coef_part = term.substr(0, xPos);
            std::string exp_part = term.substr(xPos + 1);

            if (coef_part.empty()) {
                coefficient = 1.0;
            } else {
                try {
                    coefficient = std::stod(coef_part);
                } catch (const std::exception& e) {
                    cout << "Invalid coefficient: " << coef_part << endl;
                    return linkedList;
                }
            }

            if (exp_part.empty()) {
                exponent = 1;
            } else if (exp_part[0] == '^') {
                std::string exp_string = exp_part.substr(1);
                try {
                    exponent = std::stoi(exp_string);
                } catch (const std::exception& e) {
                    cout << "Invalid exponent: " << exp_string << endl;
                    return linkedList;
                }
            } else {
                cout << "Invalid exponent format in term: " << term << endl;
                return linkedList;
            }
        } else {
            try {
                coefficient = std::stod(term);
            } catch (const std::exception& e) {
                cout << "Invalid term: " << term << endl;
                return linkedList;
            }
            exponent = 0;
        }

        if (sign == "-") {
            coefficient = -coefficient;
        }

        Node* newNode = new Node(coefficient, exponent);
        linkedList += newNode;
    }

    return linkedList;
}

// Function: combineLikeTerms
void combineLikeTerms(LinkedList& linkedList) {
    // 1. Initialize a Map to Store Terms
    std::map<int, double> expToCoefMap;

    // 2. Traverse the LinkedList
    Node* currentNode = linkedList.getHead();
    while (currentNode != nullptr) {
        int exp = currentNode->getExp();
        double coef = currentNode->getCoef();
        expToCoefMap[exp] += coef;
        currentNode = currentNode->getNext();
    }

    // 3. Rebuild the LinkedList
    linkedList.clear();
    for (std::map<int, double>::reverse_iterator it = expToCoefMap.rbegin(); it != expToCoefMap.rend(); ++it) {
        int exp = it->first;
        double coef = it->second;
        if (coef != 0.0) {
            Node* newNode = new Node(coef, exp);
            linkedList += newNode;
        }
    }
}

// Function: evaluateExpression
double evaluateExpression(const LinkedList& linkedList, double xValue) {
    double result = 0.0;
    Node* currentNode = linkedList.getHead();
    while (currentNode != nullptr) {
        double termValue = currentNode->getCoef() * std::pow(xValue, currentNode->getExp());
        result += termValue;
        currentNode = currentNode->getNext();
    }
    return result;
}

// Function: formatExpression
std::string formatExpression(const LinkedList& linkedList) {
    std::ostringstream oss;
    oss << linkedList;
    return oss.str();
}
