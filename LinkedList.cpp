#include "LinkedList.h"


//Default Constructor 
LinkedList::LinkedList() : head(nullptr), size(0){}

//Destructor
LinkedList::~LinkedList(){
    recursiveDelete(head);
}

//Recursive delete fuction (delete linked list recursively)
void LinkedList::recursiveDelete(Node* node){
    if (node == nullptr){
        return; 
    } else {
        recursiveDelete(node->getNext());
        delete node; 

    }
}
//Accessor for size 
int LinkedList::getSize() const{
    return size; 
}

//Accesor for Head
Node* LinkedList::getHead() const{
    return head; 
}

//Head setter (only for testing)
void LinkedList::setHead(Node* newHead){
    head = newHead; 
}

//Overloaded [] Operator
const Node* LinkedList::operator[](int index) const{
    if (index < 0  || index >= size ){
        return nullptr;
    }

    const Node* current = head;
    int currentIndex = 0; 

    while(current != nullptr && currentIndex < index){
        current = current->getNext();
        currentIndex++;
    }

    return current; 
}

//Overloaded stream insertion operator 
std::ostream& operator<<(std::ostream& out, const LinkedList& list){
    int listSize = list.getSize();
    if(listSize == 0){
        out <<"0";
        return out;
    }

    for(int i=0; i < listSize; i++){
        const Node* node = list[i];

        if(node == nullptr){
            continue;
        }        

        double coef = node->getCoef();

        if(i == 0){ // Handle the sign for the first term 
            if(coef < 0){  //neg coef 
                out<<"-";
            }
        }

        out << node;

        if(i < listSize - 1) {
            out << " "; 
        }

    }

    return out; 
}

LinkedList& LinkedList::operator+=(Node* newNode){
    if(newNode == nullptr){
        return *this;
    }

    newNode->setNext(head);
    head = newNode;
    size++; 

    return *this; 

}

//Sort for exponents in dec order 
void LinkedList::sortList(){
    if(head == nullptr || head->getNext() == nullptr){
        return; 
    }

    bool swapped; 
    do {
        swapped = false; 
        Node* current = head; 
        Node* prev = nullptr; 

        while (current->getNext() != nullptr) {
            if(current->getExp() < current->getNext()->getExp()){
                //swap the nodes
                Node* temp = current->getNext(); 
                current->setNext(temp->getNext());
                temp->setNext(current);

                if(prev == nullptr){
                    head = temp;   
                } else {
                    prev->setNext(temp);
                }

                swapped = true; 
                prev = temp; 
            } else {
                //move to next node
                prev = current;
                current = current->getNext(); 
            }
        }
    } while (swapped); 
}

void LinkedList::insertNodeInSortedOrder(Node** sortedList, Node* node){
    if (*sortedList == nullptr || node->getExp() <= (*sortedList)->getExp()) {
        node->setNext(*sortedList);
        *sortedList = node;
    } else {
        Node* current = *sortedList;
        while(current->getNext() != nullptr && current->getNext()->getExp() > node->getExp()) {
            current = current->getNext();
        }
        node->setNext(current->getNext());
        current->setNext(node);
    }
}