#include <iostream>
#include "LinkedList.h"
#include "Node.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std; 


LinkedList parseLine(string line, double& value);



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
        } else if (sign == "+"){
            string term = tokens[index];
            index++;

        }







    

}