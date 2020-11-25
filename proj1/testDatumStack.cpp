/*
*
*  COMP 15 Project1: CalcYouLater
*
*  testDatumStack.cpp
*  
*  Created By (UTLN): egjert01
*          On       : February 16, 2020
*
* Purpose: A separate file with a main function used to test every 
* function made in the DatumStack class. See below for more information on 
* testing.
*
*/
#include "DatumStack.h"
#include "Datum.h"

#include <iostream>

using namespace std;

void testClearAndSize(DatumStack &stacks);
void testTop(DatumStack stacks);
void testPush(DatumStack &stacks);

int main(){
    cout << "hello" << endl;
    
    Datum data[4] = {Datum(1), Datum(2), Datum(3), Datum(4)};
    
    //testing constructors
    DatumStack stack;
    DatumStack stack2(data, 4);
    
    //testTop(stack2);
    testPush(stack2);
    cout << "TESTING CLEAR FOR STACK2" << endl;
    testClearAndSize(stack2);
    cout << "TESTING CLEAR FOR STACK" << endl;
    testClearAndSize(stack);
    
    
    /*testing throwing exceptions*/
    //testTop(stack);
    
}

void testPush(DatumStack &stacks){
    stacks.push(Datum(5));
    testTop(stacks);
    stacks.push(Datum(6));
    testTop(stacks);
}

void testTop(DatumStack stacks){
    Datum top = stacks.top();
    cout << "TOP: " << top.toString() << endl;
    
}

void testClearAndSize(DatumStack &stacks){    
    cout << "SIZE before clear" ;
    cout << stacks.size() << endl;
    stacks.clear();
    cout << "SIZE after clear" << stacks.size() << endl;
    
}

