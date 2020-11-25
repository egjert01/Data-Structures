/*
*
*  COMP 15 HW 2 Cheshire ConCATenation - Time to Get Linked up in Fur
*
*  CharLinkedList.cpp
*  Complete CharLinkedList Class Implementation
*  Modified By (UTLN): egjert01
*           On       : February 5, 2020
*
*/

#include "CharLinkedList.h"
#include <iostream>

using namespace std;

//default constructor
CharLinkedList::CharLinkedList(){
    head = nullptr;
    back = nullptr;
    currNode = nullptr;
    length = 0;
}
//Single character constructor
CharLinkedList::CharLinkedList(char element){
    Node *newNode = makeFirstNode();
    newNode->element = element;
    length = 1;
}
//Array constructor
CharLinkedList::CharLinkedList(char *arrayCopy, int lengthCopy){
    Node *newNode = makeFirstNode();
    newNode->element = arrayCopy[0];
    length = 1;
    
    for (int i = 1; i < lengthCopy; i++){
        pushAtBack(arrayCopy[i]);
    }
    
}

//Copy constructor
CharLinkedList::CharLinkedList(const CharLinkedList &other){
    Node *oCurrNode = other.head;
    Node *currNode = makeFirstNode();
    
    //copy over the length
    length = other.length;
    
    //check if the list is empty
    if (oCurrNode == nullptr){
        currNode = nullptr;
    } else {            
        while(oCurrNode != nullptr){
            //create the list with same values as the other
            Node *newNode = new Node;
            newNode->prev = currNode;
            currNode->next = newNode;
            newNode->element = oCurrNode->element;
            currNode = currNode->next;
            oCurrNode = oCurrNode->next;
        }
    }
}

//Assignment operator overload
CharLinkedList &CharLinkedList::operator=(CharLinkedList &rhs){
    //check for self-assignment
    if (this != &rhs){
        //Recycling lhs memory
        currNode = currNode->next;
        for (int i = 0; i < length-1; i++){
            currNode = currNode->next;
            delete(currNode->prev);
        }
        delete(currNode);
        
        //setting the current nodes to the first node after the head
        length = rhs.length;
        Node *rhsCurrNode = rhs.head->next;
        
        Node *currNode = makeFirstNode();
        currNode = head->next;
        
        //check if the list is empty
        if (rhsCurrNode->next == nullptr){
            currNode->next = nullptr;
        } else {
            //create new nodes and copy information from rhs to new linkedList
            currNode->element = rhsCurrNode->element;
            while(rhsCurrNode->next != nullptr){
                currNode->next = new Node;
                currNode->next->element = rhsCurrNode->next->element;           
                currNode = currNode->next;
                rhsCurrNode = rhsCurrNode->next;
            }
        }
        
    } return *this; //return a pointer to the new linkedList
    
}

//Destructor
CharLinkedList::~CharLinkedList(){
    currNode = head;
    Node *temp;
    //as long as head is not a nullptr keep deleting the first node
    while(head != nullptr){
        temp = head->next;
        delete head;
        head = temp;
    }
    //delete the remaining node
    delete(head);
    
}

/* Takes no parameters and returns a
boolean value that is true if this specific instance of the
class is empty (has no characters) and false otherwise.*/
bool CharLinkedList::isEmpty(){
    if (length <= 0){
        return true;
    } else {
        return false;
    }
}
/* Takes no parameters and has a void
return type. It makes the instance into an empty array list.
For example if you call the "clear" function and then the
"isEmpty" function the "isEmpty" function should return true.*/
void CharLinkedList::clear(){
    currNode = head;
    Node *temp;
    //as long as the head is not a nullptr keep deleting the first node
    while(head != nullptr){
        temp = head->next;
        delete head;
        head = temp;
    }
    
    //delete the remaining node
    delete(head);
    
    length = 0;
}
/*Takes no parameters and returns an
integer value that is the number of characters in the array
list. The size of an array list is 0 if and only if it isEmpty.*/
int CharLinkedList::size(){
    return length;
}
/*Takes no parameters and returns the
first element (char) in the array list. */
char CharLinkedList::first(){
    if (isEmpty()){
        throw runtime_error("cannot get first of empty doubly-linked list");
    }
    return head->element;
}
/*Takes no parameters and returns the last
element (char) in the array list. */
char CharLinkedList::last(){
    if (isEmpty()){
        throw runtime_error("cannot get last of empty doubly-linked list");
    }
    return back->element;
}
/*Takes an integer index and returns
the element (char) in the array list at that index. NOTE: Indices are
0−based. */
char CharLinkedList::elementAt(int index){
    //make sure the index is in bounds
    if (index < 0 || index >= length || isEmpty()){
        throw range_error("index (" + to_string(index) + ") not in range [0.." +
        to_string(length) + ")");
    }
    //cycle through the linked list until the node is found
    currNode = head->next;
    for (int i = 0; i < index; i++){
        currNode = currNode->next;
    }
    return currNode->element;
}
/* Takes no parameters and has a void
return type. It prints the array list of characters stored in
the instance to the screen (cout).*/
void CharLinkedList::print(){
    currNode = head;
    cout << "[CharLinkedList of size " << length << " <<";
    while (currNode != nullptr){
        cout << currNode->element;
        currNode = currNode->next;
    }
    cout << ">>]" << endl;
}
/* Takes an element (char) and has a
void return type. It inserts the given new element after the end
of the existing elements of the array list.*/
void CharLinkedList::pushAtBack(char element){
    Node *newNode = new Node;
    //check if the list is empty
    if (length == 0){
        head = newNode;
        back = newNode;
    } 
    currNode = back;
    
    //copy over values and adjust pointers
    newNode->element = element;
    newNode->prev = currNode;
    newNode->next = nullptr;
    currNode->next = newNode;
    
    //update the back pointer and the length
    back = newNode;
    
    length++;
}
/* Takes an element (char) and has
a void return type. It inserts the given new element in front
of the existing elements of the array list.*/
void CharLinkedList::pushAtFront(char element){
    if (isEmpty()){
        Node *newNode = makeFirstNode();
        newNode->element = element;
    } else {
        Node *newNode = new Node;
        
        currNode = head;
        newNode->element = element;
        head = newNode;
        newNode->prev = nullptr;
        newNode->next = currNode;
        currNode->prev = newNode;
    }
    
    length++;
}
/* Takes an element (char) and an
integer index as parameters and has a void return type. It
inserts the new element at the specified index and shifts the
existing elements as necessary. The new element is then in the
index−th position.*/
void CharLinkedList::insertAt(char element, int index){
    //check for errors
    if (index > length || index < 0){
        throw range_error("index (" + to_string(index) + 
        ") not in range [0.." + to_string(length) + "]");
    } else if (isEmpty() && index != 0){
        throw range_error("index (" + to_string(index) + 
        ") not in range [0.." + to_string(length) + "]");
        
    }
    //if user is trying to insert at front or back call according functions
    if (index == 0){
        pushAtFront(element);
    } else if (index == length){
        pushAtBack(element);
    } else {
        currNode = head;
        for (int i = 0; i < index; i++){
            currNode = currNode->next;
        }
        //create and insert the node
        Node *temp = currNode->prev;
        temp->next = currNode;
        Node *newNode = new Node;
        newNode->element = element;
        newNode->next = currNode;
        newNode->prev = temp; 
        temp->next = newNode;
        currNode->prev = newNode;
        
        length++;
    }
    
    
}
/*Takes an element (char),
inserts it into the array list in alphabetical order, and
returns nothing. When this function is called, it may assume
the array list is correctly sorted in ascending order, and it
should insert the element at the first correct index. */
void CharLinkedList::insertInOrder(char element){
    currNode = head;
    if (isEmpty()){
        pushAtFront(element);
    }
    int counter = 0;
    while (currNode->element < element ){
        if (counter == length-1){
            break;
        }
        currNode = currNode->next;
        counter++;
    }
    if (counter != length - 1){
        insertAt(element, counter);
    } else {
        pushAtBack(element);
    }
    
}
/*Takes no parameters and has a
void return type. It removes the first element from the
array list.*/
void CharLinkedList::popFromFront(){
    if (isEmpty()){
        throw runtime_error("cannot pop from empty doubly−linked list");
    }
    currNode = head;
    head = currNode->next;
    delete(currNode);
    currNode = head;
    currNode->prev = nullptr;
    
    length--;
}
/*Takes no parameters and has a
void return type. It removes the last element from the
array list. */
void CharLinkedList::popFromBack(){
    if (isEmpty()){
        throw runtime_error("cannot pop from empty doubly−linked list");
    }
    currNode = back;
    back = currNode->prev;
    delete(currNode);
    currNode = back;
    currNode->next = nullptr;
    
    length--;
}
/* Takes an integer index and has a
void return type. It removes the element at the specified
index. */
void CharLinkedList::removeAt(int index){
    if (index < 0 || index >= length || isEmpty()){
        throw range_error("index (" + to_string(index) + 
        ") not in range [0.." + to_string(length) + ")");
    }
    
    if (index == length-1){
        popFromBack();
        return;
    } else if (index == 0){
        popFromFront();
        return;
    }
    currNode = head;
    for (int i = 0; i < index-1; i++){
        currNode = currNode->next;
    }
    Node *temp = currNode->next;
    
    temp = temp->next;
    delete(currNode->next);
    length--;
    currNode->next = temp;
    temp->prev = currNode;
    
}
/*Takes an element (char) and an integer
index as parameters and has a void return type. It replaces the
element at the specified index with the new element. */
void CharLinkedList::replaceAt(char element, int index){
    if (index < 0 || index >= length || isEmpty()){
        throw range_error("index (" + to_string(index) + 
        ") not in range [0.." + to_string(length) + ")");
    }
    
    currNode = head;
    for (int i = 0; i < index; i++){
        currNode = currNode->next;
    }
    currNode->element = element;
}
/* Takes a pointer to a second
CharLinkedList and has a void return type. It adds a copy of the
array list pointed to by the parameter value to the end of the
array list the function was called from. */
void CharLinkedList::concatenate(CharLinkedList *list2){
    currNode = back;
    cout << "test1" << endl;
    
    Node *list2Curr = list2->head;
    pushAtBack(list2Curr->element);
    cout << "test2" << endl;
    for (int i = 0; i < list2->size()-1; i++){
        cout << "i: " << i << " " << list2->elementAt(i) << endl;
        char listElement = list2->elementAt(i);
        pushAtBack(listElement);
        if (i != list2->size() - 1){
            list2Curr = list2Curr->next;
        }
    }
    
}
/* Takes no parameters and has a void
return type. It reduces the object’s memory usage to the bare
minimum required to store its elements (i.e. it does not use any
extra space).*/
void CharLinkedList::shrink(){
    return;
}
/* Takes an element (char) and returns a
boolean. It will return "true" if the CharLinkedList contains
the specified element and "false" if it does not. The find
operation must use a recursive algorithm (it can call a
recursive private function, for example). */
bool CharLinkedList::find(char element){
    if (isEmpty()){
        return false;
    }
    currNode = head;
    for (int i = 0; i < size()-1; i++){
        if (currNode->element == element){
            return true;
        }
        if (i != size() - 1){
            currNode = currNode->next;
        }
        
    }
    return false;
}
/* Takes no parameters and returns a pointer to a node.
The purpose of this function is to create the new node that
appears at the very front of the Linked List directly after
the head node */
CharLinkedList::Node *CharLinkedList::makeFirstNode(){
    Node *newNode = new Node;
    head = newNode;
    back = newNode;
    
    newNode->next = nullptr;
    newNode->prev = nullptr;
    currNode = newNode;
    
    return currNode;
}

/* A void function that takes no arguments. It follows the linkedList forwards 
and backwards to check for any missing links */
void CharLinkedList::followList(){
    currNode = head;
    cout << "forwards: " << endl;
    //travel the list using the ->next until we reach the end
    cout << currNode->element;
    while (currNode->next != nullptr){
        currNode = currNode->next;
        cout << currNode->element;
    }
    cout << endl <<  "backwards" << endl;
    //travel the list using the ->prev until we reach the front
    cout << currNode->element;
    while(currNode->prev != nullptr){
        currNode = currNode->prev;
        cout << currNode->element;
    }
    
    cout << endl;
}
