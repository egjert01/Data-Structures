/*
*
*  COMP 15 HW 1 Cheshire ConCATenation - no strings attached
*
*  testCharArrayList.cpp
*  Testing File for the sequence CharArrayList class
*
*  Written by:
*        UTLN:
*          on:
*/
#include "CharArrayList.h"
#include <iostream>

using namespace std;

void testingArrayObject(CharArrayList &array);
void testingCharObject(CharArrayList &array);
void testingEmptyObject(CharArrayList &array);

void checkPrint(CharArrayList array);
void checkSize(CharArrayList array);
void checkIsEmpty(CharArrayList array);
void checkClear(CharArrayList &array);
void checkFirst(CharArrayList array);
void checkLast(CharArrayList array);
void checkElementAt(CharArrayList array);
void checkResize(CharArrayList array);
void checkPushAtBack(CharArrayList &array);
void checkPushAtFront(CharArrayList &array);
void checkInsertAt(CharArrayList &array);
void checkRemoveAt(CharArrayList &array);
void checkReplaceAt(CharArrayList &array);
void checkInsertInOrder(CharArrayList &array);
void checkPopping(CharArrayList &array);


int main(){
  //Create an array 
  char howdy[5] = {'h','o','w','d','y'};
  char *arrayCopy = howdy;
  
  //Create objects using each constructor
  CharArrayList array(arrayCopy, 5); 
  CharArrayList array1('o');  
  CharArrayList array2;
  CharArrayList *ptr = &array;

  array.concatenate(ptr);
  cout << "TESTING CONCATENATE: ";
  array.print();
  
  //Separate functions for testing functions on each object
   testingArrayObject(array);
   testingCharObject(array1);
   testingEmptyObject(array2);
  
}
//Testing functions on the object created as a full array
void testingArrayObject(CharArrayList &array){
  cout << endl << endl <<  "ARRAY TESTS: " << endl << endl;
  checkSize(array);
  checkFirst(array);
  checkLast(array);
  checkElementAt(array);
  checkResize(array);
  checkPushAtBack(array);
  checkPushAtFront(array);
  checkInsertAt(array);
  checkPopping(array);
  checkSize(array);

  checkReplaceAt(array);
  checkRemoveAt(array);
  checkClear(array);
}
//Testing functions on the object created with a single character
void testingCharObject(CharArrayList &array){
  cout <<  endl << endl << "CHAR OBJECT TESTS: " << endl << endl;
  checkSize(array);
  checkIsEmpty(array);
  checkResize(array);
  checkPushAtBack(array);
  checkPushAtFront(array);
  checkInsertAt(array);
  checkReplaceAt(array);
  checkRemoveAt(array);
}
//Testing functions on the object created as an empty array                                    
void testingEmptyObject(CharArrayList &array){
  cout << endl << endl <<  "EMPTY OBJECT TESTS: " << endl << endl;
  checkSize(array);
  checkIsEmpty(array);
  checkResize(array);
  checkPushAtBack(array);
  checkPushAtFront(array);
  array.insertAt('t', 0);
  array.print();
  checkClear(array);
  
  //TESTS FOR THROWING ERRORS
  //checkFirst(array);
  //checkLast(array);
  //checkElementAt(array);
  //checkInsertAt(array);
  //checkReplaceAt(array);
  //checkRemoveAt(array);
}

//Test the popFromFront and popFromBack function
void checkPopping(CharArrayList &array){
  array.popFromFront();
  cout << "POPPED FROM FRONT: \n";
  array.print();
  array.pushAtFront('r');
  cout << "REPLACED: \n";
  array.print();
  array.popFromBack();
  cout << "POPPED FROM BACK: \n";
  array.print();
  
}
/*Test the insert in order function by inserting characters of different
ASCII values -  from the front, from the middle, and from the end*/
void checkInsertInOrder(CharArrayList &array){
  array.insertInOrder('i');
  //print to make sure the char was inserted correctly
  array.print();
  array.insertInOrder('a');
  array.print();
  array.insertInOrder('z');
  array.print();
}
//Test the replaceAt function by  calling the function and printing the results
void checkReplaceAt(CharArrayList &array){
  array.replaceAt('x', 1);
  array.print();
}
//Test the removeAt function by removing elements at different indices
void checkRemoveAt(CharArrayList &array){
  int size = array.size();
  array.removeAt(size-1); //remove last element
  array.removeAt(0); //remove first element
  array.print(); //print to ensure expected outcome 
}
//Check the pushAtFront function by calling the function then printing result
void checkPushAtFront(CharArrayList &array){
  array.pushAtFront('n');
  checkPrint(array);
}
//Check the insertAt function by inserting an element and printing the result
void checkInsertAt(CharArrayList &array){
  array.insertAt('t', 1);
  checkPrint(array);
}
//Check the pushAtBack function by adding something to the end and printing 
//the result
void checkPushAtBack(CharArrayList &array){
  array.pushAtBack('m');
  checkPrint(array);
}
//Check the print function
void checkPrint(CharArrayList array){
  array.print();
}
//Check the size function by calling the function
void checkSize(CharArrayList array){
  cout << "LENGTH: " << array.size() << endl;
}
//Check the isEmpty function by printing whether or not it's empty
void checkIsEmpty(CharArrayList array){
  if (array.isEmpty() == true){
    cout << "EMPTY ARRAY" << endl;
  } else {
    cout << "ARRAY ISN't EMPTY" << endl;
  }
}
//Check the isClear function
void checkClear(CharArrayList &array){
  array.clear();
  checkIsEmpty(array);
}
//Check the first function by printing it out
void checkFirst(CharArrayList array){
  cout << "FIRST CHAR: " << array.first() << endl;
}
//Check the last function by printing it out
void checkLast(CharArrayList array){
  cout << "LAST CHAR: " << array.last() << endl;
}
//Check the elementAt function by printing out elements at different indices
void checkElementAt(CharArrayList array){
  cout << "Element AT 0: " << array.elementAt(0) << endl;
  cout << "Element AT 2: " << array.elementAt(2) << endl;
}
//Check the expand and shrink function sby getting the capacity before and after
//expanding and shrinking
void checkResize(CharArrayList array){
  cout << "Capacity before expanding: " << array.getCapacity();
  array.expand();
  cout << " Capacity after expanding: " << array.getCapacity() << endl; 
  
  cout << "Capacity before shrinking: " << array.getCapacity();
  array.shrink();
  cout << " Capacity after shrinking: " << array.getCapacity() << endl;
}


