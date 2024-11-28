#include <iostream>
#include "LinkedList.h"
#include "Node.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <cmath>
using namespace std; 


LinkedList parseLine(string line, double& value);
void combineLikeTerms(LinkedList& list);
double evaluateExpression(const LinkedList& list, double xValue);
string formatExpression(const LinkedList& linkedList);

int main(){

    //prompt user for file name
    cout << "Enter the file name: ";
    string fileName;
    cin >> fileName;

    //open file 
    ifstream file(fileName);
    
    //check if file is open 
    if(!file.is_open()){
        cout << "Error opening file" << endl; 
        return 1;
    }

    //read file line by line
    string line; 
    while(getline(file, line)){
        if(line.empty()){
            continue;
        }

        line = normalizeOperators(line);

        double xValue = 0.0; 

        LinkedList polyList = parseLine(line, xValue);

        if(polyList.getSize() == 0){
            continue;
        }

        //combine like terms
        combineLikeTerms(polyList);

        //Sort the list
        polyList.sortList();

        //evaluate the expression
        double result = evaluateExpression(polyList, xValue);

        //format the expression
        string formattedExpression = formatExpression(polyList);

        //display the expression
        cout << formattedExpression << " = "
             << fixed << setprecision(3) << result << endl;
    }

    file.close(); 

    return 0;

}

//function parseLine
LinkedList parseLine(string line, double& value){

    LinkedList linkedList; 

    if(line.empty()){
        return LinkedList();
    }

    LinkedList list;

    int pos = line.find('=');

    if(pos == string::npos){
        cout << "Invalid expression" << endl;
        return list; 
    }
    //split line into lhs and rhs 
    //lhs is the function, rhs is the expression
    string lhs = line.substr(0,pos); 
    string rhs = line.substr(pos+1);
    
    //handle the left side of the equation
    int posParan = lhs.find('(');
    int posParan2 = lhs.find(')');

    if(posParan == string::npos || posParan2 == string::npos || posParan2 <= posParan){
        cout << "Invalid expression" << endl;
        return list; 
    }
    //finding the X value 
    string xValueString = lhs.substr(posParan+1, posParan2 - posParan - 1);
    double xValue = stod(xValueString); //convert X string to double 

    //Handle right side of the equation
    //Tokenize rhs into terms and operators 
    // Tokenize RHS into Terms and Operators
	// Split rhs by spaces into a list of tokens
    //terms being numbers and x 
    //operators being +, - 

    vector <string> tokens;
    istringstream iss(rhs);
    string token; 
    while(iss>>token){
        tokens.push_back(token);
    }

    string sign = "+";
    size_t index = 0;
    LinkedList linkedList;

    while(index < tokens.size()){

        string currentToken = tokens[index];

        if(tokens[index] == "+" || tokens[index] == "-"){
            sign = currentToken;
            index++;
            if (index >= tokens.size()) {
                std::cout << "Invalid expression: operator at the end" << std::endl;
                return linkedList;
            }
            currentToken = tokens[index];
        } else if (index == 0){
            sign = "+"; //Assume is + at the start
        }

        double coef = 1.0;
        int exp = 0; 
        size_t xPos = currentToken.find('x');

    if(xPos != string::npos){

        string coefPart = currentToken.substr(0, xPos);
        string expPart = currentToken.substr(xPos+1);

        if (coefPart.empty()){
            //coef stays 1.0 
        }
        else {
            try {
                    coef = std::stod(coefPart);
                } catch (const std::exception& e) {
                    std::cout << "Invalid coefficient: " << coefPart << std::endl;
                    return linkedList;
                }
        }

        //process exponent
        if (expPart.empty()) {
            exp = 1;
        } else if(expPart[0] == '^'){
            string expString = expPart.substr(1); // After ^
            try {
                exp = std::stoi(expString);
            } catch (const std::exception& e) {
                std::cout << "Invalid exponent: " << expString << std::endl;
                return linkedList;
            }
        } else {
            cout << "Invalid exponent format in term: " << currentToken << endl;
            return linkedList;
        } 
        } else {
            // Term is a constant (no 'x')
            try {
                coef = std::stod(currentToken);
            } catch (const std::exception& e) {
                std::cout << "Invalid term: " << currentToken << std::endl;
                return linkedList;
            }
            exp = 0;
        }

        if (sign == "-"){
            coef = -coef;
        }

        Node* newNode = new Node(coef, exp);
        linkedList += newNode;
        index++;
    }

    return linkedList;

}

//function combine like terms 
void combineLikeTerms(LinkedList& list){
    std::map<int, double> expTocoefMap;
    

    //Travese the linkedList 
    Node* currentNode = list.getHead(); 
    while(currentNode != nullptr) {
        int expo = currentNode->getExp();
        double coef = currentNode->getCoef(); 

        if(expTocoefMap.find(expo) != expTocoefMap.end()){
            expTocoefMap[expo] += coef;
        } else {
            expTocoefMap[expo] = coef; 
        }

        currentNode = currentNode->getNext(); 
    }

    //rebuild the linkedList
    //clear the current list
    list.~LinkedList();
    for(const auto& pair: expTocoefMap){
        int exp = pair.first;
        double coef = pair.second; 

        //if coef is 0, skip
        if(coef == 0){
            continue; 
        }
        //if coef is not 0, add to the list
        if(coef != 0.0){
            Node* newNode = new Node(coef, exp);
            list += newNode;
        }
    }

    list.sortList(); 

}

//function to evaluate the polynomial
double evaluateExpression(const LinkedList& list, double xValue){
    double result = 0.0; 

    Node* currentNode = list.getHead();
    while(currentNode != nullptr){
        double coef = currentNode->getCoef();
        int exp = currentNode->getExp(); 
        double termValue = coef * pow(xValue, exp);

        result += termValue; 
        currentNode = currentNode->getNext();
    }

    return result;
}

//function to format the expression
string formatExpression(const LinkedList& linkedList) {
    std::ostringstream oss;
    oss << linkedList;  // Use the overloaded << operator for LinkedList
    return oss.str();
}

//Normalize the expression
string normalizeOperators(const string& line) {
    string normalizedLine = line;
    for (char& c : normalizedLine) {
        if (c == '–' || c == '—') {
            c = '-';
        }
    }
    return normalizedLine;
}