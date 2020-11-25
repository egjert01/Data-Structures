/*
*
*  COMP 15 HW 1 Cheshire ConCATenation - no strings attached
*
*  testCharLinkedList.cpp
*  Testing File for the sequence CharLinkedList class
*
*  Written by:
*        UTLN:
*          on:
*/
#include "CharLinkedList.h"
#include <iostream>

using namespace std;

void testingArrayObject(CharLinkedList &list);
void testingCharObject(CharLinkedList &list);
void testingEmptyObject(CharLinkedList &list);

void checkPrint(CharLinkedList list);
void checkSize(CharLinkedList list);
void checkIsEmpty(CharLinkedList list);
void checkClear(CharLinkedList &list);
void checkFirst(CharLinkedList list);
void checkLast(CharLinkedList list);
void checkElementAt(CharLinkedList list);
void checkPushAtBack(CharLinkedList &list);
void checkPushAtFront(CharLinkedList &list);
void checkInsertAt(CharLinkedList &list);
void checkRemoveAt(CharLinkedList &list);
void checkReplaceAt(CharLinkedList &list);
void checkInsertInOrder(CharLinkedList &list);
void checkPopping(CharLinkedList &list);


int main(){
  //Create an array 
  char howdy[5] = {'h','o','w','d','y'};
  char *arrayCopy = howdy;
  
  //Create objects using each constructor
  CharLinkedList arrayList(arrayCopy, 5); 
  CharLinkedList charList('o');  
  CharLinkedList emptyList;;
  CharLinkedList *arrayCopy2 = &charList;

  arrayList.concatenate(arrayCopy2);
  cout << "TESTING CONCATENATE: ";
  arrayList.print();
  
  //Separate functions for testing functions on each object
   testingArrayObject(arrayList);
   //testingCharObject(charList);
   //testingEmptyObject(emptyList);
  
}
//Testing functions on the object created as a full array
void testingArrayObject(CharLinkedList &list){
  cout << endl << endl <<  "ARRAY TESTS: " << endl << endl;
  checkSize(list);
  checkFirst(list);
  checkLast(list);
  checkElementAt(list);
  checkPushAtBack(list);
  checkPushAtFront(list);
  checkInsertAt(list);
  checkPopping(list);
  checkSize(list);

  checkReplaceAt(list);
  checkRemoveAt(list);
  checkClear(list);
}
//Testing functions on the object created with a single character
void testingCharObject(CharLinkedList &list){
  cout <<  endl << endl << "CHAR OBJECT TESTS: " << endl << endl;
  checkSize(list);
  checkIsEmpty(list);
  checkPushAtBack(list);
  checkPushAtFront(list);
  checkInsertAt(list);
  checkReplaceAt(list);
  checkRemoveAt(list);
}
//Testing functions on the object created as an empty list                                    
void testingEmptyObject(CharLinkedList &list){
  cout << endl << endl <<  "EMPTY OBJECT TESTS: " << endl << endl;
  checkSize(list);
  checkIsEmpty(list);
  checkPushAtBack(list);
  checkPushAtFront(list);
  list.insertAt('t', 0);
  list.print();
  checkClear(list);
  
  //TESTS FOR THROWING ERRORS
  //checkFirst(list);
  //checkLast(list);
  //checkElementAt(list);
  //checkInsertAt(list);
  //checkReplaceAt(list);
  //checkRemoveAt(list);
}

//Test the popFromFront and popFromBack function
void checkPopping(CharLinkedList &list){
  list.popFromFront();
  cout << "POPPED FROM FRONT: \n";
  list.print();
  list.pushAtFront('r');
  cout << "REPLACED: \n";
  list.print();
  list.popFromBack();
  cout << "POPPED FROM BACK: \n";
  list.print();
  
}
/*Test the insert in order function by inserting characters of different
ASCII values -  from the front, from the middle, and from the end*/
void checkInsertInOrder(CharLinkedList &list){
  list.insertInOrder('i');
  //print to make sure the char was inserted correctly
  list.print();
  list.insertInOrder('a');
  list.print();
  list.insertInOrder('z');
  list.print();
}
//Test the replaceAt function by  calling the function and printing the results
void checkReplaceAt(CharLinkedList &list){
  list.replaceAt('x', 1);
  list.print();
}
//Test the removeAt function by removing elements at different indices
void checkRemoveAt(CharLinkedList &list){
  int size = list.size();
  list.removeAt(size-1); //remove last element
  list.removeAt(0); //remove first element
  list.print(); //print to ensure expected outcome 
}
//Check the pushAtFront function by calling the function then printing result
void checkPushAtFront(CharLinkedList &list){
  list.pushAtFront('n');
  checkPrint(list);
}
//Check the insertAt function by inserting an element and printing the result
void checkInsertAt(CharLinkedList &list){
  list.insertAt('t', 1);
  checkPrint(list);
}
//Check the pushAtBack function by adding something to the end and printing 
//the result
void checkPushAtBack(CharLinkedList &list){
  list.pushAtBack('m');
  checkPrint(list);
}
//Check the print function
void checkPrint(CharLinkedList list){
  list.print();
}
//Check the size function by calling the function
void checkSize(CharLinkedList list){
  cout << "LENGTH: " << list.size() << endl;
}
//Check the isEmpty function by printing whether or not it's empty
void checkIsEmpty(CharLinkedList list){
  if (list.isEmpty() == true){
    cout << "EMPTY list" << endl;
  } else {
    cout << "list ISN't EMPTY" << endl;
  }
}
//Check the isClear function
void checkClear(CharLinkedList &list){
  list.clear();
  checkIsEmpty(list);
}
//Check the first function by printing it out
void checkFirst(CharLinkedList list){
  cout << "FIRST CHAR: " << list.first() << endl;
}
//Check the last function by printing it out
void checkLast(CharLinkedList list){
  cout << "LAST CHAR: " << list.last() << endl;
}
//Check the elementAt function by printing out elements at different indices
void checkElementAt(CharLinkedList list){
  cout << "Element AT 0: " << list.elementAt(0) << endl;
  cout << "Element AT 2: " << list.elementAt(2) << endl;
}



