/*
*
*  COMP 15 Project1: CalcYouLater
*
*  RPNCalc.cpp
*
*  Created By (UTLN): egjert01
*          On       : February 26, 2020
*  Acknowledgement  : got_int function written by Mark Sheldon
* 
* Purpose: Implementation of the RPNCalc class. It is what makes the 
* program work like a calculator, and allows the user to interact with the 
* calculator. Takes in input from cin, and runs whatever the user is asking 
* it to run. Examples of things the user can do: add numbers to the stack, 
* perform mathematical equations on those numbers, compare the numbers (<, >), 
* work with booleans and create if statements. 
* 
*/

#include "DatumStack.h"
#include "Datum.h"
#include "RPNCalc.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <sstream>
#include <fstream>

using namespace std;
/* 
takes no parameters and initializes one object
Note: both are empty because the program uses the vector class which 
has built in destructors and constructors.
 */
RPNCalc::RPNCalc(){
}
RPNCalc::~RPNCalc(){
}
/*
* Purpose : Launch a process reading in commands from standard input (cin). 
* Arguments : None 
* Returns : None 
* Effects : Calls the readQueryB helper function which takes care of all queries
* that are not integers or brackets. Runs the whole program and responsible
* for quitting the program and sending the last message thanking the user 
* for using the CalcYouLater
*/
void RPNCalc::run(){
    int value;
    string rString, query;    
    cin >> query;

    while (query != "quit"){
        if (got_int(query, &value)){
            numInput(value);
        } else if (query == "{"){
            rString = parseRString(cin);
            stack.push(Datum(rString));
        } else {
            readQueryB(query);
        }
        cin >> query;
    }
    cerr << "Thank you for using CalcYouLater." << endl;
}
/*
* Purpose : A function that runs the program for istreams that are not cin 
* Arguments : an istream passed by reference and a string also passed by 
* reference
* Returns : Nothing exlicitly (the istream and string by reference)
* Effects : Calls the readQueryB function which takes care of all queries 
* that are not integers or brackets. Runs the whole program and responsible
* for quitting the program and sending the last message thanking the user 
* for using the CalcYouLater
*/
void RPNCalc::readQueryA(istream &input, string &query){
    string parsing;
    input >> query;
    int value;
    while (!input.eof()){
        if (got_int(query, &value)){
            numInput(value);
        } else if (query == "{"){
            parsing = parseRString(input);
            stack.push(Datum(parsing));
        } else {
            readQueryB(query);
        }
        input >> query;
    }    

}
/*
* Purpose : Helper function to the run() function, which reads in all 
* queries that are not integers or brackets
* Arguments : A string which holds the query
* Returns : None
* Effects : Calls the private function that takes executes the function that
* the query is correlated with. 
*/
void RPNCalc::readQueryB(string query){
    for (int i = 0; i < 5; i++){
        if (query == comparisons[i]){
            comparing(comparisons[i]);
            return;
        }
    }
    if (query == "print") {
        print();
    } else if (query == "#f" || query == "#t") {
        trueFalse(query);
    } else if (query == "not"){
        invert();
    } else if (query == "drop"){
        drop();
    } else if (query == "clear"){
        clear();
    } else if (query == "dup"){
        dup();
    } else if (query == "swap"){
        swap();
    } else if (query == "+" || query == "-"){
        plusMinus(query);
    } else if (query == "*" || query == "/" || query == "mod"){
        quotients(query);
    } else {
        bigCommands(query);
    }
}
/*
* Purpose : Helper function to the run() function, which handles all of the 
* more complicated queries
* Arguments : A string which holds the query
* Returns : None
* Effects : Calls the private function that takes executes the function that
* the query is correlated with. 
*/
void RPNCalc::bigCommands(string query){
    if (query == "exec"){
        exec();
    } else if (query == "file"){
        file();
    } else if (query == "if"){
        ifQuery();
    }
    else {
        cout << query << ": unimplemented" << endl;
    }
}
/*
* Purpose : Push the given number onto the DatumStack, stack
* Arguments : An integer
* Returns : None
* Effects : None
*/
void RPNCalc::numInput(int number){
    stack.push(number);
}
/*
* Purpose : Takes the argument and pushes the associated boolean onto the 
* stack (if arg = "#f", push false onto the stack). 
* Arguments : A string holding either #t or #f, representing a boolean
* Returns : None
*Effects: None
*/
void RPNCalc::trueFalse(string boolean){
    if (boolean == "#t"){
        stack.push(Datum(true));
    } else {
        stack.push(Datum(false));
    }
    
}
/*
* Purpose : Replace the current boolean on the stack with its inverse
* Arguments : None
* Returns : None
* Effects : Pops off the current boolean (if the top element is not a bool 
* let the user know), and push on the other one by calling the trueFalse 
* function. 
*/
void RPNCalc::invert(){
    if (isEmpty()){
        return;
    }
    if(!stack.top().isBool()){
        errorMessage("notBool");
        return;
    }
    string currBool = stack.top().toString();
    drop();
    if (currBool == "#t"){
        trueFalse("#f");
    } else {
        trueFalse("#t");
    }
}
/*
* Purpose : Print the value on the top of the stack. 
* Arguments : None
* Returns : None
* Effects : If the stack is empty send a message to cerr that the stack is 
* empty
*/
void RPNCalc::print(){
    if (isEmpty()){
        return;
    }
    cout << stack.top().toString() << endl;
}
/*
* Purpose : To remove all of the elements from the stack
* Arguments : None
* Returns : None
* Effects : Calls the drop() function to remove the elements
*/
void RPNCalc::clear(){
    while(stack.size() != 0){
        drop();
    }
}
/*
* Purpose : To pop the top-most element from the stack
* Arguments : None
* Returns : None
* Effects : None
* Note: Will send a message to cerr reporting that the stack is empty if 
* this function is called on an empty stack
*/
void RPNCalc::drop(){
    if (isEmpty()){
        return;
    }
    stack.pop();
}
/*
* Purpose : Duplicate and push the element on the top of the stack
* Arguments : None
* Returns : None
* Effects : Calls the errorMessage function if the stack is empty
*/
void RPNCalc::dup(){
    if (isEmpty()){
        return;
    }
    stack.push(stack.top());
}
/*
* Purpose : Swap the first and second elements on the stack
* Arguments : None
* Returns : None
* Effects : Sends an error message to the user and returns if the stack 
* is empty.
*/
void RPNCalc::swap(){
  if (stack.size() < 2){
            cerr << "Error: empty_stack" << endl;
            return;
        }
    Datum top = stack.top();
    stack.pop();
    Datum second = stack.top();
    stack.pop();
    stack.push(top);
    stack.push(second);
}
/*
* Purpose : opens up the rString and runs the commands within the first 
* brackets.
* Arguments : None
* Returns : None
* Effects : If the top-most element on the stack is not an rString, send 
* a message to cerr. 
*/
void RPNCalc::exec(){
    string query, rstring = stack.top().toString();
    stack.pop();
    if (!verifyRString(rstring)){
        cerr << "Error: cannot execute non rstring" << endl;
        return;
    }
    rstring.pop_back();
    istringstream stream; 
    stream.str(rstring);
    stream >> query;
    readQueryA(stream, query);
}
/*
* Purpose : Pop off the element on the top of the stack, and make sure that 
* it is an rstring. Open the file name contained in the rstring and run 
* the commands contained in the file.
* Arguments : None
* Returns : None
* Effects : Print error messages if the top element is not what is expected 
* (an rstring with a filename), and if the program can't open the file
*/
void RPNCalc::file(){
    string query, fileName, rstring = stack.top().toString();
    stack.pop();
    if (!verifyRString(rstring)){
        cerr << "Error: file operand not rstring" << endl;
        return;
    }
    istringstream stream;
    stream.str(rstring);
    stream >> fileName;
    stream >> fileName;
    
    ifstream infile;
    infile.open(fileName);
    if (!infile.is_open()){
        cerr << "Unable to read " << fileName << endl;
        return;
    }
    
    readQueryA(infile, query);
}
/*
* Purpose : Takes a conditional, if it's false it executes the first rstring
* and if it's true execute the first rstring.
* Arguments : None
* Returns : None
* Effects : Remove the top three elements from the stack. If they are not in
* the expected format send the user a cerr message. Pushes the result of 
* the if statement onto the stack
*/
void RPNCalc::ifQuery(){
    string query;
    string falseCase = stack.top().toString();
    stack.pop();
    string trueCase = stack.top().toString();
    stack.pop();
    if (!verifyRString(falseCase) || !verifyRString(trueCase)){
        cerr << "Error: file operand not rstring" << endl;
        return;
    }
    string condition = stack.top().toString();
    if (condition == "#t"){
        //execute trueCase;
        trueCase.pop_back();
        istringstream stream; 
        stream.str(trueCase);
        stream >> query;
        readQueryA(stream, query);
    } else {
        //execute falseCase
        falseCase.pop_back();
        istringstream stream; 
        stream.str(falseCase);
        stream >> query;
        readQueryA(stream, query);
    }
}
/*
* Purpose : Checks if the input is an rString
* Arguments : string, which represents the top element of the stack
* Returns : Boolean (true if it is an rString, false if not)
* Effects : None
*/
bool RPNCalc::verifyRString(string rString){
    if (rString.size() <= 3){
        return false;
    }
    char lastElement = rString.at(rString.size()-2);
    if (rString.front() == '{' &&  lastElement == '}'){
        return true;
    } else {
        return false;
    }    
}

/*
* Purpose : Add/subtract the two top elements of the stack
* Arguments : A string the holds either a "+" or a "-"
* Returns : Nothing
* Effects : Pops off the two top elements and replaces them with the result 
* of the operation. Also, quits the function and sends out a cerr message 
* to the user if the top two elements of the stack are not ints 
*/
void RPNCalc::plusMinus(string operation){
    if (stack.size() < 2){
        cerr << "Error: empty_stack" << endl;
        return;
    }
    int elem1, elem2;
    if (!areInts(&elem1, &elem2)){
        return;
    }
    
    if (operation == "+"){
        stack.push(elem1 + elem2);
    } else {
        stack.push(elem2 - elem1);
    }
}
/*
* Purpose : Execute the following operations: multiplication, division, 
* and remainder
* Arguments : The operation being performed on the integers
* Returns : None
* Effects : Pops off the two top elements and replaces them with the result 
* of the operation. Also, quits the function and sends out a cerr message 
* to the user if the top two elements of the stack are not ints 
*/
void RPNCalc::quotients(string operation){
    if (stack.size() < 2){
        cerr << "Error: empty_stack" << endl;
        return;
    }

    int elem1, elem2;
    if (!areInts(&elem1, &elem2)){
        return;
    }
    if (operation == "*"){
        stack.push(elem1 * elem2);
    } else if (operation == "/"){
        stack.push(elem2 / elem1);
    } else if (operation == "mod"){
        stack.push(elem2 % elem1);
    }
}
/*
* Purpose : compare the integers with the given operation, and push either
* true or false onto the stack depending on what the outcome of the 
* comparison is
* Arguments : A string holding one of the following: "<" ">" "<=" ">=" "=="
* Returns : None
* Effects : Calls helper functions that will pop off the top two elements of
* the stack and compare them, or send out an error message if the top two 
* elements aren't both integers
*/
void RPNCalc::comparing(string comparison){
    if (stack.size() < 2){
        cerr << "Error: empty_stack" << endl;
        return;
    }
    int elem1, elem2;
    if (!areInts(&elem1, &elem2)){
        return;
    }
    
    if (comparison == "<"){
        lessThan(elem1, elem2);
    } else if (comparison == ">"){
        greaterThan(elem1, elem2);
    } else if (comparison == "<="){
        lessOrEqual(elem1, elem2);
    } else if (comparison == ">="){
        greaterOrEqual(elem1, elem2);
    } else if (comparison == "=="){
        equals(elem1, elem2);
    }
}

/*
* Purpose : Helper function for the comparing function. checks if the 
* second element is less than the first element, and pushes on the 
* boolean
* Arguments : the two integers being compared
* Returns : None
* Effects : pushes on a true or false boolean onto the stack 
*/
void RPNCalc::lessThan(int elem1, int elem2){
    if (elem2 < elem1){
        stack.push(Datum(true));
    } else {
        stack.push(Datum(false));
    }
}
/*
* Purpose : Helper function for the comparing function. checks if the 
* second element is greater than the first element, and pushes on the 
* boolean
* Arguments : the two integers being compared
* Returns : None
* Effects : pushes on a true or false boolean onto the stack 
*/
void RPNCalc::greaterThan(int elem1, int elem2){
    if (elem2 > elem1){
        stack.push(Datum(true));
    } else {
        stack.push(Datum(false));
    }
}
/*
* Purpose : Helper function for the comparing function. checks if the 
* second element is less than or equal to the first element, and pushes on 
* the boolean
* Arguments : the two integers being compared
* Returns : None
* Effects : pushes on a true or false boolean onto the stack 
*/
void RPNCalc::lessOrEqual(int elem1, int elem2){
    if (elem2 <= elem1){
        stack.push(Datum(true));
    } else {
        stack.push(Datum(false));
    }
}
/*
* Purpose : Helper function for the comparing function. checks if the 
* second element is greater than or equal to the first element, and pushes 
* on the boolean
* Arguments : the two integers being compared
* Returns : None
* Effects : pushes on a true or false boolean onto the stack 
*/
void RPNCalc::greaterOrEqual(int elem1, int elem2){
    if (elem2 >= elem1){
        stack.push(Datum(true));
    } else {
        stack.push(Datum(false));
    }
}
/*
* Purpose : Helper function for the comparing function. checks if the 
* second element is equal to the first element, and pushes on 
* the boolean
* Arguments : the two integers being compared
* Returns : None
* Effects : pushes on a true or false boolean onto the stack 
*/
void RPNCalc::equals(int elem1, int elem2){
    if (elem2 == elem1){
        stack.push(Datum(true));
    } else {
        stack.push(Datum(false));
    }
}

/*
* Purpose : verify that an rstring is valid by checking to make sure the 
* brackets match up. As long as they do, build a string that contains every 
* character read in until the matching closing bracket is found
* Arguments : An istream 
* Returns : A string representing the rstring that will be pushed onto the 
* stack
* Effects : Will send an error message if the brackets of the rstring do 
* not match up
*/
string RPNCalc::parseRString(istream &input){
    int stackLength = 1;
    string search;
    string buildString = "{ ";
    
    while (input >> search){
        if (search == "{"){
            stackLength++;
        } else if (search == "}"){
            if (checkLength(stackLength)){
                return buildString;
            }
            stackLength--;
        }
        
        buildString += search;
        buildString += " ";
        
        if (checkLength(stackLength)){
            return buildString;
        }
    }
    if (stackLength == 0){
        return buildString;
    } else {
        cerr << "NOT RIGHT" << endl;
        exit(0);
    }
}

/*
* Purpose : Helper function for the parseRString function, which checks if 
* the brackets have matched up by checking how many brackets have been 
* counted (once the brackets have all matched up the counter should be 0, 
* because I add 1 every time an opening bracket is found and subtract 1 
* every time a closing bracket is found)
* Arguments : the integer that is used in parseRString function counting 
* the brackets
* Returns : A boolean (true if the brackets match up, false if they don't)
* Effects : None
*/
bool RPNCalc::checkLength(int stackLength){
    if (stackLength == 0){
        return true;
    } else {
        return false;
    }
}

/*
* Purpose : Helper function for the plusMinus, quotients, and comparing 
* functions, which confirms if the top two elements on the stack are ints 
* and pops them off if they are. 
* Arguments : pointers to two integers
* Returns : A boolean that returns true if the string can be interpereted as
* an integer and false if it cannot
* Effects : If the string can be interpereted as an integer, update the 
* integer the argument is pointing to, to the string's integer. Also, pop 
* off the top two elements from the stack. If the top two elements aren't 
* integers, then print a message through cerr to let the user know the issue
*/
bool RPNCalc::areInts(int *elem1, int *elem2){
    //making sure that the input is an integer
    if (!got_int(stack.top().toString(), &(*elem1))){
        errorMessage("notInt");
        return false;
    }
    
    drop();
    
    if (!got_int(stack.top().toString(), &(*elem2))){
        errorMessage("notInt");
        return false;
    }
    
    drop();
    return true;
}
/*
* Purpose : Check if the stack is empty, and if it call the error message 
* function to send a message to cerr letting the user know.
* Arguments : None
* Returns : A boolean that returns true if the stack is empty and false 
* otherwise.
* Effects : None
*/
bool RPNCalc::isEmpty(){
    if (stack.size() <= 0){
        errorMessage("empty");
        return true;
    } else {
        return false;
    }
}
/*
* Purpose : send a message to cerr with an appropriate error message
* depending on what error code gets passed to it
* Arguments : A string that represents what kind of error the program 
* needs to inform the user of
* Returns : None
* Effects : Sends a message to cerr that corresponds to the kind of error
*/
void RPNCalc::errorMessage(string code){
    if (code == "empty"){
        cerr << "Error: empty_stack" << endl;
    } else if (code == "notBool"){
        cerr << "Error: datum_not_bool" << endl;
    } else if (code == "notInt"){
        cerr << "Error: datum_not_int" << endl;
    }
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
bool RPNCalc::got_int(string s, int *resultp){
        return sscanf(s.c_str(), "%d", resultp) == 1;
}