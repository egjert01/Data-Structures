/*
*
*  COMP 15 Project1: CalcYouLater
*
*  DatumStack.h
*  
*  Created By (UTLN): egjert01
*          On       : February 19, 2020
*
* Purpose: Interface of DatumStack class
*
*/

#ifndef _DATUMSTACK_H_
#define _DATUMSTACK_H_

#include <vector>
#include <string>

#include "Datum.h"

using namespace std;

class DatumStack{
public:
     //Default constructor, empty. 
     DatumStack();
     //Constructor that takes in an array of Datum and its size and creates a 
     //stack with those datum on it
     DatumStack(Datum arr[], int size);
     
     //Function that takes no parameters and returns a bool. True if the stack
     //is empty, and false if it is not. 
     bool isEmpty();
     //Takes no arguments and return is void. Clears everything from the stack
     void clear();
     //Takes no arguments and returns an integer representing the size of the
     //stack (how many elements/Datum it holds)
     int size();
     //Takes no parameters and returns a Datum which is at the top of the stack
     Datum top();
     //Takes no parameters and has a void return type. Removes the top-most 
     //element from the stack.
     void pop();
     //Void return type, and takes in a Datum, which it then adds to the top of 
     //the stack.
     void push(Datum element);
     
private:
    //a vector holding the stack
    vector<Datum> stackArr;
    int length;
     
};

#endif
