/*
*
*  COMP 15 HW 1 Cheshire ConCATenation - no strings attached
*
*  CharArrayList.cpp
*
*  Complete CharArrayList Class Implementation
*
*  Modified By YOUR NAME: Emily Gjertsson
*           On          : January 22, 2020
*
*/

#include "CharArrayList.h"
#include <iostream>

using namespace std;

//default constructor
CharArrayList::CharArrayList(){
  capacity = 0;
  length = 0;
  array = new char[0];
}
//constructor that creates an array of one character
CharArrayList::CharArrayList(char element){
  capacity = 1;
  length = 1;
  array = new char[1];
  array[0] = element;
}
//constructor that creates an array of a given length
CharArrayList::CharArrayList(char *arrayCopy, int lengthCopy){
  capacity = lengthCopy;
  length = lengthCopy;
  array = new char[length];
  for (int i = 0; i < length; i++){
    array[i] = arrayCopy[i];
  }
}
//copy constructor
CharArrayList::CharArrayList(const CharArrayList &other){
  capacity = other.capacity;
  length = other.length;
  array = new char[length];
  for (int i = 0; i < length; i++){
    array[i] = other.array[i];
  }
}
//Assignment operator overload 
CharArrayList &CharArrayList::operator=(CharArrayList &rhs){
  //Make sure that the arrays don't have the same address
  if (this != &rhs){
    delete[] array;
    
    //copying over members of the class
    capacity = rhs.capacity;
    length = rhs.length;
    array = new char[length];
    for (int i = 0; i < length; i++){
      array[i] = rhs.array[i];
    }
    
  }
  //return the copied CharArrayList
  return *this;
}

//Destructor
CharArrayList::~CharArrayList(){
  delete[] array;
}

//Prints the array and the size of the array
void CharArrayList::print(){
  cout << "[CharArrayList of size " << length << " <<";
  for (int i = 0; i < length; i++){
    cout << array[i];
  }
  cout << ">>]" << endl;
}

//Returns the size of the array (how many elements there are)
int CharArrayList::size(){
  return length;
}

//Check if the array is empty
bool CharArrayList::isEmpty(){
  if (length == 0){
    return true;
  } else {
    return false;
  }
}

//Set the length to 0 so that for the user the array is "empty"
void CharArrayList::clear(){
  for(int i = 0; i < length; i++){
    array[i] = '\0';
  }
  length = 0;
}

//Returns the first element of the array
char CharArrayList::first(){
  //if the array is empty throw an exception
  if(length==0){
    throw runtime_error("cannot get first of empty ArrayList");
  }   
  return array[0];
}
//Returns the last element of the array
char CharArrayList::last(){
  //Throw an exception of the array is empty
  if (length == 0){
    throw runtime_error("cannot get last of empty ArrayList");
  }
  return array[length-1];
}

//Return the element from the array at a given index
char CharArrayList::elementAt(int index){
  //If the given index is out of bounds throw an exception
 if (index < 0 || index >= length || isEmpty()){
    throw range_error("index (" + to_string(index) + ") not in range [0.." + to_string(length) + ")");
  }
  return array[index];
}

//Add a given element to the back of the array
void CharArrayList::pushAtBack(char element){
  //If there is no space left in the array use the expand function to double it
  if (capacity == length){
    expand();
  }
  //Keep track of the length and insert the given element at the back
  length += 1;
  array[length-1] = element;
}
//Add a given element to the front of the array
void CharArrayList::pushAtFront(char element){
  insertAt(element, 0);
}
//Insert a given element at the given index
void CharArrayList::insertAt(char element, int index){
  char oldElement;
  //If the given index is out of range or if the array is empty throw an error
  if (index > length + 1 || index < 0){
    throw range_error("index (" + to_string(index) + 
                      ") not in range [0.." + to_string(length) + "]");
  } else if (isEmpty() && index != 0){
    throw range_error("index (" + to_string(index) + 
                      ") not in range [0.." + to_string(length) + "]");
  }
  //If there is no space in the array call the expand function to double it
  if (capacity == length){
    expand();
  }
  //Increase the length
  length += 1;
  //Add the element at the given index and shift everything else to the left
  for (int i = index; i < length; i++){
    oldElement = array[i];
    array[i] = element;
    element = oldElement;
  }
}

//Override a member of the array at the given index with the given element
void CharArrayList::replaceAt(char element, int index){
  //If the given index is out of range throw an exception
  if (index < 0 || index >= length || isEmpty()){
    throw range_error("index (" + to_string(index) + 
                      ") not in range [0.." + to_string(length) + ")");
  }
  //Replace the element
  array[index] = element;
}

//Remove the first element from the array
void CharArrayList::popFromFront(){
  //Throw an error of the array is empty
  if(length==0){
    throw runtime_error("cannot get first of empty ArrayList");
  }  
  //call the removeAt function with 0 as the argument for the first element
  removeAt(0);
}
//Remove the last element from the array
void CharArrayList::popFromBack(){
  //Throw an error if the array is empty
  if(length==0){
    throw runtime_error("cannot get first of empty ArrayList");
  }  
  //Call the removeAt function with the last index as the argument
  removeAt(length-1);
}
//Remove the element at the given index
//Also takes care of the functionality of popFromBack and popFromFront
void CharArrayList::removeAt(int index){
  //If the given index is out of scope/the array is empty throw an exception
  if (index < 0 || index >= length || isEmpty()){
    throw range_error("index (" + to_string(index) + 
                      ") not in range [0.." + to_string(length) + ")");
  }
  //adjust the length
  length -= 1;
  //Remove the element and shift everything over so there are no holes
  for (int i = index; i < length; i++){
    array[i] = array[i+1];
  }
}

//Double the capacity of the array
void CharArrayList::expand(){
  //If the array is empty, make the capacity 1
  if(capacity == 0){
    capacity = 1;
  } else {
    //Call the resize function with double capacity as the argument
    resize(capacity*2);
  }
}
//Divide the capacity of the array by two
void CharArrayList::shrink(){
  resize(capacity/2);
}
//Change the capacity of the array to a given size
void CharArrayList::resize(int newSize){
  //Set the capacity
  capacity = newSize;
  //Create a new character array of the same size and then copy everything over
  char *list = new char[capacity];
  for (int i = 0; i < length; i++){
    list[i] = array[i];
  }
  //Delete the old array and then reassign the private pointer member to the 
  // new array
  delete[] array;
  array = list;
}

//Add the array (given in the arg) to the private member array
void CharArrayList::concatenate(CharArrayList *array2){
  int i = length, counter = 0;
  //Keep looping through until the size of the new array = the size of the first
  //  plus the size of the second one (meaning they will have been added)
  while (i < length + array2->size()){
    for (int j = 0; j < array2->size(); j++){
      //If there is no space left to add members double the capacity
      if (length == capacity){
        expand();
      }
      //Add the elements from array2 to the end of array
      array[i] = array2->elementAt(j);
      counter += 1;
      i++;
    }
  }
  //Adjust length to the size of the new array
  length += counter;
}

//Insert a given element in alphabetical order
void CharArrayList::insertInOrder(char element){
  //Cycle through the array until a character is found with a higher ASCII value
  for (int i = 0; i < length; i++){
    if (element <= array[i]){
      insertAt(element, i);
      break;
    }
    //Once the for loop has cycled through the whole array add the element to 
    // the end of the array, since it must be alphabetically last
    if (i == length-1){
      insertAt(element, length);
      break;
    }
  }
}

//Getter - return the capacity
int CharArrayList::getCapacity(){
  return capacity;
}

