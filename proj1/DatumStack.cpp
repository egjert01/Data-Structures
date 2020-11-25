/*
*
*  COMP 15 Project1: CalcYouLater
*
*  DatumStack.cpp
*  
*  Created By (UTLN): egjert01
*          On       : February 26, 2020
*
* Purpose: Implementation of the DatumStack class. Dictates how the 
* client can interact with a vector: the user can only work with the back so  
* that the vector is essentially a stack.
*
*/

#include "DatumStack.h"
#include "Datum.h"

#include <iostream>
#include <vector>

using namespace std;

//Default constructor, empty. 
DatumStack::DatumStack(){
    length = 0;
}
//Constructor that takes in an array of Datum and its size and creates a 
//stack with those datum on it
DatumStack::DatumStack(Datum data[], int size){
    length = size;
    for (int i = 0; i < size; i++){
        stackArr.push_back(data[i]);
    }
}
//Function that takes no parameters and returns a bool. True if the stack
//is empty, and false if it is not. 
bool DatumStack::isEmpty(){
    if (length == 0){
        return true;
    } else {
        return false;
    }
}
//Takes no arguments and return is void. Clears everything from the stack
void DatumStack::clear(){
    if (length == 0){
        return;
    }
    while (length > 0){
        cout << "LENGTH: " << length << endl;
        pop();
    }
}
//Takes no arguments and returns an integer representing the size of the
//stack (how many elements/Datum it holds)
int DatumStack::size(){
    return length;
}
//Takes no parameters and returns a Datum which is at the top of the stack
Datum DatumStack::top(){
    //testing isEmpty();
    if (isEmpty()){
        throw runtime_error("empty_stack");
    } else {
        return stackArr.at(length-1);
    }
}
//Takes no parameters and has a void return type. Removes the top-most 
//element from the stack.
void DatumStack::pop(){
    stackArr.pop_back();
    length--;
}
//Void return type, and takes in a Datum, which it then adds to the top of 
//the stack.
void DatumStack::push(Datum element){
    stackArr.push_back(element);
    length++;
}