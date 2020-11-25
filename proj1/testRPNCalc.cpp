/*
*
*  COMP 15 Project1: CalcYouLater
*
*  testRPNCalc.cpp
*
*  Created By (UTLN): egjert01
*          On       : February 19, 2020
*
* Purpose: A separate file with a main function used to test several 
* functions made in the RPNCalc class. It is not as fleshed out because the 
* majority of the testing was submitting commands into terminal and using cout 
* statements throughout the program to find bugs and make sure functions were 
* working
*
*/

#include "RPNCalc.h"
#include "Datum.h"
#include <iostream>
#include <cstdio>


void testIsEmpty(RPNCalc calc);
void testAreInts(RPNCalc &calc);
void testSwap(RPNCalc calc);
bool got_int(string s, int *resultp);


int main(){
    RPNCalc calc;
    testIsEmpty(calc);
    testAreInts(calc);
    testSwap(calc);
    
    calc.run();
    return 0;
}

/*
* Purpose: make sure swap is working by printing out the top-most element of the
* stack before and after running the swap function. 
* Arguments: the RPNCalc object
* Returns: None
* Effects: prints the top most element before and after the top two elements 
* are swapped
*/
void testSwap(RPNCalc calc){
    // STUB 
    (void) calc;
    
    
    // cout << "TestSwap: before -> ";
    // calc.print();
    // calc.swap();
    // cout << endl << "TestSwap: After -> ";
    // calc.print();
    // cout << endl;
}
/*
* Purpose: make sure the areInts() function is working, but grabbing some of the
* code from that function that does everything but pop the elements off of the 
* stack (I wanted to keep those elements for other tests).
* Arguments: the RPNCalc object passed by reference
* Returns: None
* Effects: Prints whether the object is an integer or not
*/
void testAreInts(RPNCalc &calc){
    // STUB 
    (void) calc;
    
    // calc.stack.push(5);
    // int elem1;
    // if (!got_int(calc.stack.top().toString(), &elem1)){
    //     cout << "TestAreInts: NOT an integer" << endl;
    // } else {
    //     cout << "TestAreInts: IS an integer" << endl;
    // }
    // 
    // 
    // calc.stack.push(Datum("{ 5 5 +}"));
    // 
    // if (!got_int(calc.stack.top().toString(), &elem1)){
    //     cout << "TestAreInts: NOT an integer" << endl;
    // } else {
    //     cout << "TestAreInts: IS an integer" << endl;
    // }
}
/*
* Purpose : Test if the isEmpty() function works as expected
* Arguments : the RPNCalc object
* Returns : None
* Effects : Prints the stack size, and then prints whether it is empty or not
*/
void testIsEmpty(RPNCalc calc){
    // STUB 
    (void) calc;
    
    // cout << "Stack size: " << calc.stack.size() << endl;
    // if (calc.isEmpty()){
    //     cout << "Is empty" << endl;
    // } else {
    //     cout << "Is not empty" << endl;
    // }
}
/*
* Purpose : Use to check if the argument is an integer
* Arguments : A string and a pointer to an integer
* Returns : A boolean that returns true if the string can be interpereted as
* an integer and false if it cannot
* Effects : If the string can be interpereted as an integer, update the 
* integer the argument is pointing to, to the string's integer. 
* Note: written by Mark Sheldon
*/
bool got_int(string s, int *resultp){
    // STUB 
    (void) s;
    (void) resultp;
    return true; //REMOVE WHEN RUNNING
    

        // return sscanf(s.c_str(), "%d", resultp) == 1;
}
